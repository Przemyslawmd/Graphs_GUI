
#include "model.h"

#include <algorithm>
#include <ranges>

#include "utils.h"
#include "defines.h"


Model::Model()
{
    keys = std::make_unique<Keys>();
}


std::tuple<Message, std::optional<char>> Model::createNode(const sf::Text& text)
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
        if (std::ranges::any_of(nodes, [key](const auto& node) { return node.key == key; })) {
            return { Message::NODE_KEY_EXISTS, std::nullopt };
        }
    }

    auto& node = nodes.emplace_back(key);
    return { Message::OK, node.key };
};


void Model::createNodeFromFile(char key, size_t posX, size_t posY)
{
    auto& node = nodes.emplace_back(key);
    node.setPosition({ (float) posX, (float) posY });
    keys->setKeyAsUsed(key);
}


std::vector<NodeGui>& Model::getNodes()
{
    return nodes;
}


std::optional<char> Model::getSelectedNode()
{
    if (countSelectedNodes() != 1) {
        return std::nullopt;
    }
    auto node = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
    return node->key;
}


std::tuple<std::optional<char>, std::optional<char>> Model::getTwoSelectedNodes()
{
    if (countSelectedNodes() != 2) {
        return { std::nullopt, std::nullopt };
    }

    auto node_1 = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
    auto node_2 = std::find_if(nodes.rbegin(), nodes.rend(), [](const auto& node) { return node.selected; });

    if (node_1->selectTime < node_2->selectTime) {
        return { node_1->key, node_2->key };
    }
    return { node_2->key, node_1->key };
}


std::tuple<Message, std::optional<ConnectionData>> Model::createConnection(const sf::Text& text)
{
    if (countSelectedNodes() != 2) {
        return { Message::NODE_SELECT_TWO, std::nullopt };
    }
    auto srcNode = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
    auto dstNode = std::find_if(nodes.rbegin(), nodes.rend(), [](const auto& node) { return node.selected; });
    char srcKey = srcNode->key;
    char dstKey = dstNode->key;

    if (std::any_of(connections.begin(), connections.end(), [srcKey, dstKey](const auto& con) { return con.isMatch(srcKey, dstKey); })) {
        return { Message::CONNECTION_EXISTS, std::nullopt };
    }

    const auto [result, weight] = getWeightFromString(text.getString());
    if (result != Message::OK) {
        return { result, std::nullopt };
    }

    sf::Vector2f srcPos = srcNode->circle.getPosition();
    sf::Vector2f dstPos = dstNode->circle.getPosition();
    float length  = calculateConnectionLength(srcPos, dstPos);
    auto& connection = connections.emplace_back( length, srcKey, dstKey);

    connection.setCoordinates(srcPos, dstPos);
    connection.text.setString(text.getString());
    return { Message::OK, {{ srcKey, dstKey, weight }}};
}


void Model::createConnectionFromFile(char src, char dst, size_t weight)
{
    auto srcNode = std::find_if(nodes.begin(), nodes.end(), [src](const auto& node) { return node.key == src; });
    auto dstNode = std::find_if(nodes.begin(), nodes.end(), [dst](const auto& node) { return node.key == dst; });

    sf::Vector2f srcPos = srcNode->circle.getPosition();
    sf::Vector2f dstPos = dstNode->circle.getPosition();
    float length  = calculateConnectionLength(srcPos, dstPos);
    auto& connection = connections.emplace_back( length, srcNode->key, dstNode->key);
    connection.setCoordinates(srcPos, dstPos);
    connection.text.setString(std::to_string(weight));
}


std::tuple<Message, std::optional<char>, std::optional<char>> Model::removeConnection()
{
    if (countSelectedConnections() != 1) {
        return { Message::CONNECTION_SELECT_ONE, std::nullopt, std::nullopt };
    }
    auto conn = std::find_if(connections.begin(), connections.end(), [](const auto& conn) { return conn.selected; });
    char src = conn->srcKey;
    char dst = conn->dstKey;
    connections.erase(conn);
    return { Message::OK, src, dst };
}


void Model::moveNodeConnections(char key)
{
    for (auto& conn : connections | std::views::filter([key](const auto& conn) { return conn.srcKey == key | conn.dstKey == key; })) {
        moveConnection(conn);
    }
}


std::vector<Connection>& Model::getConnections()
{
    return connections;
}


void Model::colorPath(const std::vector<char>& path)
{
    for (size_t i = 0; i < path.size() - 1; i++) {
        auto it = std::find_if(connections.begin(), connections.end(), [src = path[i], dst = path[i + 1]](const auto& con)
                              { return con.isMatch(src, dst); });
        it->line.setFillColor(sf::Color::Red);
    }
}


void Model::colorEdges(const std::vector<std::tuple<char, char>>& edges)
{
    for (const auto& edge : edges) {
        auto it = std::find_if(connections.begin(), connections.end(), [src = std::get<0>(edge), dst = std::get<1>(edge)](const auto& con)
            { return con.isMatch(src, dst); });
        it->line.setFillColor(sf::Color::Red);
    }
}


void Model::resetPath()
{
    for (auto& conn : connections | std::views::filter([](const auto& conn) { return conn.isColor(); })) {
        conn.line.setFillColor({ RED, GREEN, BLUE });
    }
}


void Model::removeAll()
{
    nodes.clear();
    connections.clear();
    keys->restoreKeys();
}


std::tuple<Message, std::optional<char>> Model::removeNode()
{
    if (countSelectedNodes() != 1) {
        return { Message::NODE_SELECT_ONE, std::nullopt };
    }
    auto node = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
    char key = node->key;

    std::erase_if(nodes, [key](const auto& node) { return node.key == key; });
    std::erase_if(connections, [key](const auto& conn) { return conn.srcKey == key || conn.dstKey == key; });
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
    return { -1, 0.0f, 0.0f };
}


void Model::checkMouseOverConnection(const sf::Vector2i& mousePos)
{
    for (auto& conn : connections) {
        const auto& shape = conn.line;
        sf::FloatRect rect = shape.getGlobalBounds();
        if (rect.contains({ (float)mousePos.x, (float)mousePos.y })) {
            if (matchAngles(shape.getRotation().asDegrees(), rect, mousePos.x, mousePos.y)) {
                conn.changeSelect();
                return;
            }
        }
    }
}

/*****************************************************************************************************/
/***************************************** PRIVATE ***************************************************/

size_t Model::countSelectedNodes()
{
    return std::count_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
};


size_t Model::countSelectedConnections()
{
    return std::count_if(connections.begin(), connections.end(), [](const auto& conn) { return conn.selected; });
};


void Model::moveConnection(Connection& connection)
{
    char src = connection.srcKey;
    char dst = connection.dstKey;
    auto srcNode = std::find_if(nodes.begin(), nodes.end(), [src](const auto& node) { return node.key == src; });
    auto dstNode = std::find_if(nodes.begin(), nodes.end(), [dst](const auto& node) { return node.key == dst; });

    sf::Vector2f srcPos = srcNode->circle.getPosition();
    sf::Vector2f dstPos = dstNode->circle.getPosition();
    float length  = calculateConnectionLength(srcPos, dstPos);

    auto& connectionLine = connection.line;
    connectionLine.setSize({ length, 3 });

    connection.setCoordinates(srcPos, dstPos);
}

