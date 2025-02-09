
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


void Client::addEdge(char srcKey, char dstKey)
{
    graphClient->addEdge(srcKey, dstKey);
}


std::unique_ptr<std::vector<char>> Client::BFS(char key)
{
    return graphClient->traverseBFS(key);
}


std::unique_ptr<std::vector<char>> Client::DFS(char key)
{
    return graphClient->traverseDFS(key);
}

