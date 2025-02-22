
#include "iofile.h"

#include <fstream>
#include <filesystem>

#include "graph/model.h"
#include "graph/node.h"
#include "graph/connection.h"

constexpr char delimiter = ','; 


void IOFile::saveGraph(const std::vector<NodeGui>& nodes, const std::vector<Connection>& connections)
{
    std::fstream ofs;
    ofs.open(std::filesystem::current_path().append("graph.txt"), std::ios::out);
    for (const auto& node : nodes) {
        ofs << "N" << "," << node.key << "," << node.circle.getPosition().x << "," << node.circle.getPosition().y << "\n"; 
    }
    for (const auto& conn : connections) {
        std::string weight = conn.text.getString().isEmpty() ? "1" : conn.text.getString().toAnsiString();
        ofs << "C" << "," << conn.srcKey << "," << conn.dstKey << "," << weight << "\n"; 
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

    std::string line;
    while (std::getline(sstr, line)) {
        char type = line[0]; 
        line.erase(0, 2);
        if (type == 'N') {
            fillNodeData(line);
        }
        else {
            fillConnectionData(line);
        }
    }
}


void IOFile::fillNodeData(std::string& line)
{
    char key = line[0];
    line.erase(0, 2);
    size_t pos = line.find(delimiter);
    size_t posX = stoi(line.substr(0, pos));
    line.erase(0, pos + 1);
    pos = line.find(delimiter);
    size_t posY = stoi(line.substr(0, pos));
    nodesData.emplace_back( key, posX, posY );
}


void IOFile::fillConnectionData(std::string& line)
{
    size_t pos = line.find(delimiter);
    char src = line[0];
    line.erase(0, pos + 1);
    pos = line.find(delimiter);
    char dst = line[0];
    line.erase(0, pos + 1);
    pos = line.find(delimiter);
    size_t weight = stoi(line.substr(0, pos));
    connectionsData.emplace_back( src, dst, weight );
}


const std::vector<NodeData>& IOFile::getNodesData()
{
    return nodesData;
}


const std::vector<ConnectionData>& IOFile::getConnectionsData()
{
    return connectionsData;
}

