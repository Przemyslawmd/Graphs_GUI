
#include "client.h"

#include <memory>


Client::Client()
{
    graphClient = std::make_unique<GraphClient>(false);
}


void Client::removeNode(char key)
{
    graphClient->removeNode(key);
}


void Client::addNode(char key)
{
    graphClient->addNode(key);
}


void Client::addEdge(char srcKey, char dstKey, size_t weight)
{
    graphClient->addEdgeWeighted(srcKey, dstKey, weight);
}


void Client::removeEdge(char src, char dst)
{
    graphClient->removeEdge(src, dst);
}


void Client::removeGraph()
{
    graphClient->resetGraph(false);
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

