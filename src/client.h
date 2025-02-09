
#ifndef GUI_GRAPHS_CLIENT_H
#define GUI_GRAPHS_CLIENT_H

#include <vector>

#include "graph/node.h"
#include "graph/connection.h"

#include "graphclient.h"


class Client 
{
public:
    Client();

    void addNode(char key);
    void addEdge(char srcKey, char dstKey);

    void BFS(const std::vector<NodeGui>&, const std::vector<Connection>&);
    void DFS(const std::vector<NodeGui>&, const std::vector<Connection>&);

private:
    std::unique_ptr<GraphClient> graphClient;
};

#endif

