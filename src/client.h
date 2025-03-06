
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
    void removeNodes(std::unique_ptr<std::vector<char>> keys);

    void addEdge(char src, char dst, size_t weight = 1);
    void removeEdges(std::unique_ptr<std::vector<std::tuple<char, char>>> edges);

    void resetGraph(bool isDirected);

    std::unique_ptr<std::vector<char>> BFS(char key);
    std::unique_ptr<std::vector<char>> DFS(char key);

    std::unique_ptr<std::vector<char>> shortestPath(char src, char dst);

    std::unique_ptr<std::vector<std::tuple<char, char>>> minSpanningTree();

    const std::string getLastErrorMessage();

private:
    std::unique_ptr<GraphClient> graphClient;
};

#endif

