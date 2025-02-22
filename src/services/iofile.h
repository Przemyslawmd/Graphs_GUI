
#ifndef GUI_GRAPHS_IOFILE_H
#define GUI_GRAPHS_IOFILE_H

#include <vector>

#include "graph/connection.h"
#include "graph/node.h"


struct NodeData
{
    char key;
    size_t posX;
    size_t posY;
};


struct ConnectionData
{
    char src;
    char dst;
    size_t weight;
};


class IOFile
{
public:
    bool saveGraph(const std::vector<NodeGui>&, const std::vector<Connection>&);
    bool readGraph();

    const std::vector<NodeData>& getNodesData();
    const std::vector<ConnectionData>& getConnectionsData();

private:
    bool fillNodeData(std::string&);
    bool fillConnectionData(std::string&);

    std::vector<NodeData> nodesData;
    std::vector<ConnectionData> connectionsData;
};

#endif

