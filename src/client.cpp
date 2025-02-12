
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


std::unique_ptr<std::vector<char>> Client::BFS(char key)
{
    return graphClient->traverseBFS(key);
}


std::unique_ptr<std::vector<char>> Client::DFS(char key)
{
    return graphClient->traverseDFS(key);
}

