
#include "model.h"

#include "utils.h"
#include "defines.h"


constexpr size_t INITIAL_NODE_X = 30;
constexpr size_t INITIAL_NODE_Y = 60;

constexpr size_t RED = 51;
constexpr size_t GREEN = 153;
constexpr size_t BLUE = 255;


Model::Model()
{
    keys = std::make_unique<Keys>();
    keys->prepareKeys();
}


std::tuple<Message, std::optional<char>> Model::createNode(sf::Font& font, sf::Text& text)
{
    if (nodes.size() == MAX_NODES) {
        return { Message::NODE_LIMIT, std::nullopt };
    }

    char key;
    if (text.getString().isEmpty()) {
        key = keys->getKey();
    }
    else if (text.getString().getSize() != 1) {
        return { Message::NODE_VALUE_ERROR, std::nullopt };
    }
    else {
        key = text.getString()[0];
    }

    auto& node = nodes.emplace_back(font);
    node.setPosition({ INITIAL_NODE_X, INITIAL_NODE_Y });
    node.circle.setFillColor({ RED, GREEN, BLUE });
    node.text.setFillColor(sf::Color::Black);
    node.text.setCharacterSize(14);
    node.text.setString(key);
    node.value = key;
    return { Message::OK, node.value };
};


std::vector<NodeGui>& Model::getNodes()
{
    return nodes;
}


std::tuple<Message, std::optional<char>> Model::getSelectedNode()
{
    if (checkSelectedNodes() != 1) {
        return { Message::NODE_SELECT_ONE, std::nullopt };
    }
    auto node = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
    return { Message::OK, node->value };
}


std::tuple<Message, std::optional<char>, std::optional<char>> Model::getTwoSelectedNodes()
{
    if (checkSelectedNodes() != 2) {
        return { Message::NODE_SELECT_ONE, std::nullopt, std::nullopt };
    }
    auto node_1 = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
    auto node_2 = std::find_if(nodes.rbegin(), nodes.rend(), [](const auto& node) { return node.selected; });

    if (node_1->selectTime < node_2->selectTime) {
        return { Message::OK, node_1->value, node_2->value };
    }
    return { Message::OK, node_2->value, node_1->value };
}


std::tuple<Message, std::optional<ConnectionLibraryInterface>> Model::createConnection(sf::Text& text, sf::Font& font)
{
    if (checkSelectedNodes() != 2) {
        return { Message::CONNECTION_NODES_COUNT_ERROR, std::nullopt };
    }
    auto node_1 = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
    auto node_2 = std::find_if(nodes.rbegin(), nodes.rend(), [](const auto& node) { return node.selected; });

    size_t index_1 = node_1 - nodes.begin();
    size_t index_2 = nodes.size() - 1 - (node_2 - nodes.rbegin());

    if (std::any_of(connections.begin(), connections.end(), [index_1, index_2](const auto& con)
                   { return (con.src == index_1 && con.dst == index_2) || (con.src == index_2 && con.dst == index_1); })) {
        return { Message::CONNECTION_EXISTS, std::nullopt };
    }

    const auto [result, weight] = getWeightFromString(text.getString());
    if (result != Message::OK) {
        return { result, std::nullopt };
    }

    sf::Vector2f pos_1 = node_1->circle.getPosition();
    sf::Vector2f pos_2 = node_2->circle.getPosition();
    float length  = calculateConnectionLength(pos_1, pos_2);
    auto& connection = connections.emplace_back( length, index_1, index_2, node_1->value, node_2->value, font );

    float radius = node_1->circle.getRadius();
    connection.line.setPosition({ pos_1.x + radius, pos_1.y + radius });

    float angle = calculateConnectionAngle(pos_1, pos_2);
    connection.line.rotate(sf::degrees(angle));
    connection.line.setFillColor({ RED, GREEN, BLUE });

    connection.text.setFillColor(sf::Color::Black);
    connection.text.setCharacterSize(14);
    connection.text.setString(text.getString());
    sf::FloatRect bound = connection.line.getGlobalBounds();
    connection.text.setPosition({ bound.getCenter().x, bound.getCenter().y - 15 });

    size_t connection_index = connections.size() - 1;
    node_1->connections.push_back(connection_index);
    node_2->connections.push_back(connection_index);
    return { Message::OK, {{ node_1->value, node_2->value, weight }}};
}


void Model::moveConnection(size_t index)
{
    size_t node_1 = connections[index].src;
    size_t node_2 = connections[index].dst;
 
    sf::Vector2f pos_1 = nodes[node_1].circle.getPosition();
    sf::Vector2f pos_2 = nodes[node_2].circle.getPosition();
    float length  = calculateConnectionLength(pos_1, pos_2);

    auto& connectionLine = connections[index].line;
    connectionLine.setSize({ length, 3 });

    float radius = nodes[node_1].circle.getRadius();
    connectionLine.setPosition({ pos_1.x + radius, pos_1.y + radius });

    float angle = calculateConnectionAngle(pos_1, pos_2);
    connectionLine.setRotation(sf::degrees(angle));

    sf::FloatRect bound = connectionLine.getGlobalBounds();
    connections[index].text.setPosition({ bound.getCenter().x, bound.getCenter().y - 15 });
}


std::vector<Connection>& Model::getConnections()
{
    return connections;
}


void Model::colorConnections(const std::vector<char>& path)
{
    for (size_t i = 0; i < path.size() - 1; i++) {
        auto it = std::find_if(connections.begin(), connections.end(), [src = path[i], dst = path[i + 1]](const auto& con)
                              { return con.isMatch(src, dst); });
        it->line.setFillColor(sf::Color::Red);
    }
}


void Model::removeAll()
{
    nodes.clear();
    connections.clear();
}


std::tuple<Message, std::optional<char>> Model::removeNode()
{
    if (checkSelectedNodes() != 1) {
        return { Message::NODE_SELECT_ONE, std::nullopt };
    }
    auto node = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
    char key = node->value;
    size_t index = node - nodes.begin();

    std::erase_if(nodes, [key](const auto& node) { return node.value == key; });
    std::erase_if(connections, [index](const auto& conn) { return conn.src == index || conn.dst == index; });
    keys->giveBackKey(key);
    return { Message::OK, key };
}


std::tuple<int, float, float> Model::isMouseOverNode(const sf::Vector2i& mousePos)
{
    for (size_t i = 0; i < nodes.size(); i++) {
        const auto& shape = nodes[i].circle;
        float radius = shape.getRadius();
        sf::Vector2f circlePos = shape.getPosition();
        float shiftX = mousePos.x - circlePos.x - radius;
        float shiftY = mousePos.y - circlePos.y - radius;
        int distance = sqrt(pow(shiftX, 2) + pow(shiftY, 2));
        if (distance <= radius) {
            return { i, shiftX, shiftY };
        }
    }
    return { -1, 0, 0 };
}


size_t Model::checkSelectedNodes()
{
    return std::count_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
};

