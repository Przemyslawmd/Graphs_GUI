
#include "model.h"

#include <algorithm>
#include <ranges>

#include "utils.h"
#include "defines.h"


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


std::unique_ptr<std::vector<char>> Model::removeNodes()
{
    auto nodesSelected = nodes | std::views::filter([](const auto& node) { return node.selected; });
    if (nodesSelected.empty()) {
        return nullptr;
    }

    auto nodesToRemove = std::make_unique<std::vector<char>>();
    for (auto& node : nodesSelected) {
        std::erase_if(connections, [key = node.key](const auto& conn) { return conn.srcKey == key || conn.dstKey == key; });
        keys->giveBackKey(node.key);
        nodesToRemove->push_back(node.key);
    }
    std::erase_if(nodes, [](const auto& node) { return node.selected; });
    return std::move(nodesToRemove);
}


std::tuple<Message, std::optional<ConnectionData>> Model::createConnection(const sf::Text& text)
{
    if (countSelectedNodes() != 2) {
        return { Message::CONNECTION_REQUIREMENT, std::nullopt };
    }
    auto node_1 = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) { return node.selected; });
    auto node_2 = (std::find_if(nodes.rbegin(), nodes.rend(), [](const auto& node) { return node.selected; }) + 1).base();

    auto src = node_1->selectTime < node_2->selectTime ? node_1 : node_2;
    auto dst = src == node_1 ? node_2 : node_1;

    char srcKey = src->key;
    char dstKey = dst->key;

    if (std::ranges::any_of(connections, [srcKey, dstKey](const auto& conn) { return conn.isMatch(srcKey, dstKey); })) {
        return { Message::CONNECTION_EXISTS, std::nullopt };
    }

    const auto [result, weight] = getWeightFromString(text.getString());
    if (result != Message::OK) {
        return { result, std::nullopt };
    }
    setupConnection(*src, *dst, text);
    return { Message::OK, {{ srcKey, dstKey, weight }}};
}


std::tuple<Message, std::optional<ConnectionData>> Model::createConnection(size_t index_1, size_t index_2, const sf::Text& text)
{
    auto src = nodes[index_1];
    auto dst = nodes[index_2];

    char srcKey = src.key;
    char dstKey = dst.key;

    if (std::ranges::any_of(connections, [srcKey, dstKey](const auto& conn) { return conn.isMatch(srcKey, dstKey); })) {
        return { Message::CONNECTION_EXISTS, std::nullopt };
    }

    const auto [result, weight] = getWeightFromString(text.getString());
    if (result != Message::OK) {
        return { result, std::nullopt };
    }
    setupConnection(src, dst, text);
    return { Message::OK, {{ srcKey, dstKey, weight }}};
}


void Model::createConnectionFromFile(char srcKey, char dstKey, size_t weight)
{
    auto src = std::ranges::find_if(nodes, [srcKey](const auto& node) { return node.key == srcKey; });
    auto dst = std::ranges::find_if(nodes, [dstKey](const auto& node) { return node.key == dstKey; });

    sf::Vector2f srcPos{ src->getPositionX(), src->getPositionY() };
    sf::Vector2f dstPos{ dst->getPositionX(), dst->getPositionY() };
    float length = calculateConnectionLength(srcPos, dstPos);
    auto& connection = connections.emplace_back(length, src->key, dst->key, directed);
    connection.setCoordinates(srcPos, dstPos);
    connection.text.setString(std::to_string(weight));
}


void Model::setupConnection(const NodeGui& src, const NodeGui& dst, const sf::Text& text)
{
    sf::Vector2f srcPos{ src.getPositionX(), src.getPositionY() };
    sf::Vector2f dstPos{ dst.getPositionX(), dst.getPositionY() };
    float length = calculateConnectionLength(srcPos, dstPos);

    auto& connection = connections.emplace_back(length, src.key, dst.key, directed);
    connection.setCoordinates(srcPos, dstPos);
    connection.text.setString(text.getString());

    if (!directed) {
        return;
    }
    char srcKey = src.key;
    char dstKey = dst.key;
    if (std::ranges::any_of(connections, [srcKey, dstKey](const auto& conn) { return conn.isMatch(dstKey, srcKey); })) {
        setConnectionLevel(src, dst, Level::LOWER);
        setConnectionLevel(dst, src, Level::UPPER);
    }
}


void Model::setConnectionLevel(const NodeGui& src, const NodeGui& dst, Level level)
{
    sf::Vector2f srcPos{ src.getPositionX(), src.getPositionY() };
    sf::Vector2f dstPos{ dst.getPositionX(), dst.getPositionY() };

    char srcKey = src.key;
    char dstKey = dst.key;
    auto current = std::ranges::find_if(connections, [srcKey, dstKey](const auto& conn) { return conn.isMatch(srcKey, dstKey); });
    current->level = level;
    moveConnection(*current);
}


std::unique_ptr<std::vector<std::tuple<char, char>>> Model::removeConnections()
{
    auto connsSelected = connections | std::views::filter([](const auto& conn) { return conn.selected; });
    if (connsSelected.empty()) {
        return nullptr;
    }

    auto keysToRemove = std::make_unique<std::vector<std::tuple<char, char>>>();
    for (auto& conn : connsSelected) {
        keysToRemove->emplace_back(conn.srcKey, conn.dstKey);
    }
    std::erase_if(connections, [](const auto& conn) { return conn.selected; });
    return std::move(keysToRemove);
}


std::vector<NodeGui>& Model::getNodes()
{
    return nodes;
}


std::optional<char> Model::getSelectedNodeKey()
{
    if (countSelectedNodes() != 1) {
        return std::nullopt;
    }
    auto node = std::ranges::find_if(nodes, [](const auto& node) { return node.selected; });
    return node->key;
}


std::tuple<std::optional<char>, std::optional<char>> Model::getTwoSelectedNodesKeys()
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
        auto it = std::ranges::find_if(connections, [src = path[i], dst = path[i + 1]](const auto& conn)
                                      { return conn.isMatch(src, dst); });
        if (it != connections.end()) {
            it->colorConnection();
        }
    }
}


void Model::colorEdges(const std::vector<std::tuple<char, char>>& edges)
{
    for (const auto& edge : edges) {
        auto it = std::ranges::find_if(connections, [src = std::get<0>(edge), dst = std::get<1>(edge)](const auto& conn)
                                      { return conn.isMatch(src, dst); });
        if (it != connections.end()) {
            it->colorConnection();
        }
    }
}


void Model::colorNodes(std::unique_ptr<std::vector<std::tuple<char, uint8_t>>> colors)
{
    for (auto& [key, color] : *colors) {
        auto it = std::ranges::find_if(nodes, [key](auto& node) { return node.key == key; });
        if (it != nodes.end()) {
            it->fillColor(color);
        }
    }
}


void Model::resetColorNodes()
{
    for (auto& node : nodes) {
        node.fillColor(DEFAULT_COL);
    }
}


void Model::resetPath()
{
    for (auto& conn : connections | std::views::filter([](const auto& conn) { return conn.isColor(); })) {
        conn.resetColor();
    }
}


void Model::removeAll()
{
    nodes.clear();
    connections.clear();
    keys->restoreKeys();
}


std::tuple<int, float, float> Model::isMouseOverNode(const sf::Vector2i& mousePos)
{
    for (size_t i = 0; i < nodes.size(); i++) {
        float radius = nodes[i].circle.getRadius();
        float shiftX = mousePos.x - nodes[i].getPositionX() - radius;
        float shiftY = mousePos.y - nodes[i].getPositionY() - radius;
        int distance = sqrt(pow(shiftX, 2) + pow(shiftY, 2));
        if (distance <= radius) {
            return { i, shiftX, shiftY };
        }
    }
    return { -1, 0.0f, 0.0f };
}


void Model::isMouseOverConnection(const sf::Vector2i& mousePos)
{
    for (auto& conn : connections) {
        sf::FloatRect rect = conn.line.getGlobalBounds();
        if (rect.contains({ (float) mousePos.x, (float) mousePos.y }) && 
            matchAngles(conn.line.getRotation().asDegrees(), rect, mousePos.x, mousePos.y)) {
                conn.changeSelect();
                return;
        }
    }
}


void Model::setDirected(bool isDirected)
{
    directed = isDirected;
}


bool Model::isDirected() const
{
    return directed;
}


/*****************************************************************************************************/
/***************************************** PRIVATE ***************************************************/

size_t Model::countSelectedNodes()
{
    return std::ranges::count_if(nodes, [](const auto& node) { return node.selected; });
};


void Model::moveConnection(Connection& connection)
{
    char src = connection.srcKey;
    char dst = connection.dstKey;
    auto srcNode = std::ranges::find_if(nodes, [src](const auto& node) { return node.key == src; });
    auto dstNode = std::ranges::find_if(nodes, [dst](const auto& node) { return node.key == dst; });

    sf::Vector2f srcPos{ srcNode->getPositionX(), srcNode->getPositionY() };
    sf::Vector2f dstPos{ dstNode->getPositionX(), dstNode->getPositionY() };
    float length  = calculateConnectionLength(srcPos, dstPos);
    connection.setSize(length);

    if (connection.level == Level::UPPER) {
        connection.setCoordinates({ srcPos.x, srcPos.y - 10 }, { dstPos.x, dstPos.y - 10 } );
        return;
    }
    if (connection.level == Level::LOWER) {
        connection.setCoordinates({ srcPos.x, srcPos.y + 10 }, { dstPos.x, dstPos.y + 10 } );
        return;
    }
    connection.setCoordinates(srcPos, dstPos);
}

