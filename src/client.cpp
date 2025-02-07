
#include "client.h"


Client::Client()
{
    graphClient = std::make_unique<GraphClient>();
}


void Client::BFS(const std::vector<NodeGui>& nodes, const std::vector<Connection>& connections)
{
    graphClient->addNodes({ 'a', 'b', 'c' });
}


void Client::DFS(const std::vector<NodeGui>& nodes, const std::vector<Connection>& connections)
{
    graphClient->addEdges('a', { 'a', 'b', 'c' });
}

