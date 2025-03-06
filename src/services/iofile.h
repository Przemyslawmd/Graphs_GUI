
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


class IOFile
{
public:
    bool saveGraph(const std::vector<NodeGui>&, const std::vector<Connection>&, const std::string& fileName, bool isDirected);
    bool readGraph(const std::string& fileName);

    const std::vector<NodeData>& getNodesData();
    const std::vector<ConnectionData>& getConnectionsData();
    bool isDirected();

private:
    bool fillNodeData(std::string&);
    bool fillConnectionData(std::string&);

    bool directed;
    std::vector<NodeData> nodesData;
    std::vector<ConnectionData> connectionsData;
};

#endif

