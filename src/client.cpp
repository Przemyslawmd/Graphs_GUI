
#include "client.h"


Client::Client()
{
    graphClient = std::make_unique<GraphClient>();
}


void Client::addNode(char key)
{
    graphClient->addNode(key);
}


void Client::addEdge(char srcKey, char dstKey)
{
    graphClient->addEdge(srcKey, dstKey);
}


void Client::BFS(const std::vector<NodeGui>& nodes, const std::vector<Connection>& connections)
{
    graphClient->addNodes({ 'a', 'b', 'c' });
}


void Client::DFS(const std::vector<NodeGui>& nodes, const std::vector<Connection>& connections)
{
    graphClient->addEdges('a', { 'a', 'b', 'c' });
}

