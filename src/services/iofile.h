
#ifndef GUI_GRAPHS_IOFILE_H
#define GUI_GRAPHS_IOFILE_H

#include <string>
#include <vector>

#include "graph/connection.h"
#include "graph/node.h"


class IOFile
{
public:
    bool saveGraph(const std::vector<NodeGui>&, const std::vector<Connection>&, bool isDirected, const std::string& fileName);
    bool readGraph(const std::string& fileName);

    const std::vector<NodeData>& getNodesData() const;
    const std::vector<ConnectionData>& getConnectionsData() const;
    bool isDirected() const;

private:
    bool fillNodeData(std::string&);
    bool fillConnectionData(std::string&);

    bool directed;
    std::vector<NodeData> nodesData;
    std::vector<ConnectionData> connectionsData;
};

#endif

