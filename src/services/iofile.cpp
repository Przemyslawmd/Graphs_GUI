
#include "iofile.h"

#include <fstream>
#include <filesystem>

constexpr char delimiter = ',';


bool IOFile::saveGraph(const std::vector<NodeGui>& nodes, const std::vector<Connection>& connections, const std::string& fileName, bool isDirected)
{
    std::fstream ofs;
    ofs.open(std::filesystem::current_path().append(fileName), std::ios::out);
    if (!ofs) {
        return false;
    }

    ofs << ((isDirected) ? "DIRECTED" : "UNDIRECTED") << "\n";

    for (const auto& node : nodes) {
        const auto& circle = node.circle;
        ofs << "N" << "," << node.key << "," << circle.getPosition().x << "," << circle.getPosition().y << "\n"; 
    }
    for (const auto& conn : connections) {
        const auto& weight = conn.text.getString().isEmpty() ? "1" : conn.text.getString().toAnsiString();
        ofs << "C" << "," << conn.srcKey << "," << conn.dstKey << "," << weight << "\n"; 
    }
    ofs.close();
    return true;
}


bool IOFile::readGraph(const std::string& fileName)
{
    std::fstream ifs;
    ifs.open(std::filesystem::current_path().append(fileName), std::ios::in);
    if (!ifs) {
        return false;
    }

    std::stringstream sstr;
    sstr << ifs.rdbuf();
    ifs.close();

    std::string line;
    std::getline(sstr, line);
    if (line.compare("DIRECTED") == 0) {
        directed = true;
    }
    else if (line.compare("UNDIRECTED") == 0) {
        directed = false;
    }
    else {
        return false;
    }

    while (std::getline(sstr, line)) {
        char type = line[0]; 
        line.erase(0, 2);
        if (type == 'N') {
            if (fillNodeData(line) == false) {
                return false;
            };
        }
        else if (type == 'C') {
            if (fillConnectionData(line) == false) {
                return false;
            };
        }
        else {
            return false;
        }
    }
    return true;
}


bool IOFile::fillNodeData(std::string& line)
{
    char key = line[0];
    line.erase(0, 2);

    size_t linePos = line.find(delimiter);
    if (linePos == std::string::npos) {
        return false;
    }
    size_t nodePosX;
    try {
        nodePosX = stoi(line.substr(0, linePos));
    } catch(const std::invalid_argument&) {
        return false;
    }
    line.erase(0, linePos + 1);

    linePos = line.find(delimiter);
    size_t nodePosY;
    try {
        nodePosY = stoi(line.substr(0, linePos));
    } catch(const std::invalid_argument&) {
        return false;
    }

    nodesData.emplace_back( key, nodePosX, nodePosY );
    return true;
}


bool IOFile::fillConnectionData(std::string& line)
{
    char src = line[0];
    line.erase(0, 2);

    size_t posLine = line.find(delimiter);
    if (posLine == std::string::npos) {
        return false;
    }
    char dst = line[0];
    line.erase(0, posLine + 1);

    size_t weight;
    try {
        weight = stoi(line);
    } catch(const std::invalid_argument&) {
        return false;
    }
    connectionsData.emplace_back(src, dst, weight);
    return true;
}


const std::vector<NodeData>& IOFile::getNodesData()
{
    return nodesData;
}


const std::vector<ConnectionData>& IOFile::getConnectionsData()
{
    return connectionsData;
}


bool IOFile::isDirected()
{
    return directed;
}

