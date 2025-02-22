
#include "iofile.h"

#include <fstream>
#include <filesystem>

#include "graph/model.h"
#include "graph/node.h"
#include "graph/connection.h"


void IOFile::saveGraph(const std::vector<NodeGui>& nodes, const std::vector<Connection>& connections)
{
    std::fstream ofs;
    ofs.open(std::filesystem::current_path().append("graph.txt"), std::ios::out);
    for (const auto& node : nodes) {
        ofs << "N" << "," << node.key << "," << node.circle.getPosition().x << "," << node.circle.getPosition().y << "\n"; 
    }
    ofs.close();
}


bool IOFile::readGraph()
{
    std::fstream ifs;
    ifs.open(std::filesystem::current_path().append("graph.txt"), std::ios::in);
    if (!ifs) {
        return false;
    }

    std::stringstream sstr;
    sstr << ifs.rdbuf();
    ifs.close();

    const std::string delimiter = ","; 
    std::string line;
    size_t pos = 0;
    char key;
    size_t posX;
    size_t posY;
    while (std::getline(sstr, line)) {
        pos = line.find(delimiter);
        line.erase(0, pos + 1);
        pos = line.find(delimiter);
        key = line[0];
        line.erase(0, pos + 1);
        pos = line.find(delimiter);
        posX = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(delimiter);
        posY = stoi(line.substr(0, pos));
        nodesData.emplace_back( key, posX, posY );
    }
}


const std::vector<NodeData>& IOFile::getNodesData()
{
    return nodesData;
}


const std::vector<ConnectionData>& IOFile::getConnectionsData()
{
    return connectionsData;
}

