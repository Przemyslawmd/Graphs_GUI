
#include "client.h"

#include <memory>


Client::Client()
{
    graphClient = std::make_unique<GraphClient>(false);
}


void Client::addNode(char key)
{
    graphClient->addNode(key);
}


void Client::removeNodes(std::unique_ptr<std::vector<char>> nodes)
{
    graphClient->removeNodes(nodes);
}


void Client::addEdge(char srcKey, char dstKey, size_t weight)
{
    graphClient->addEdgeWeighted(srcKey, dstKey, weight);
}


void Client::removeEdges(std::unique_ptr<std::vector<std::tuple<char, char>>> edges)
{
    graphClient->removeEdges(std::move(edges));
}


void Client::resetGraph(bool isDirected)
{
    graphClient->resetGraph(isDirected);
}


std::unique_ptr<std::vector<char>> Client::BFS(char key)
{
    return graphClient->traverseBFS(key);
}


std::unique_ptr<std::vector<char>> Client::DFS(char key)
{
    return graphClient->traverseDFS(key);
}


std::unique_ptr<std::vector<char>> Client::shortestPath(char src, char dst)
{
    return graphClient->findShortestPath(src, dst);
}


std::unique_ptr<std::vector<std::tuple<char, char>>> Client::minSpanningTree()
{
    return graphClient->findMinSpanningTree();
}


const std::string Client::getLastErrorMessage()
{
    return (graphClient->getLastErrorMessage() != std::nullopt) ? graphClient->getLastErrorMessage().value() : "Graph client unknown error"; 
}

