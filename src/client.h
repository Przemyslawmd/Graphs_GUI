
#ifndef GUI_GRAPHS_CLIENT_H
#define GUI_GRAPHS_CLIENT_H

#include <memory>
#include <vector>

#include "graphclient.h"

#include "graph/node.h"
#include "graph/connection.h"


class Client 
{
public:
    Client();

    void addNode(char key);
    void removeNode(char key);
    void addEdge(char srcKey, char dstKey);

    std::unique_ptr<std::vector<char>> BFS(char key);
    std::unique_ptr<std::vector<char>> DFS(char key);

private:
    std::unique_ptr<GraphClient> graphClient;
};

#endif

