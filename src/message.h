
#ifndef GUI_GRAPHS_MESSAGE_H
#define GUI_GRAPHS_MESSAGE_H

#include <map>
#include <string>


enum class Message
{
    OK,
    CONNECTION_EXISTS,
    CONNECTION_INPUT_ERROR,
    CONNECTION_NOT_SELECTED,
    CONNECTION_REQUIREMENT,
    GRAPH_SET_TYPE,
    NODE_KEY_EXISTS,
    NODE_LIMIT,
    NODE_VALUE_ERROR,
    NODE_SELECT_ONE,
    NODE_NOT_SELECTED,
    NODE_SELECT_TWO,
    NO_FILE_NAME,
    READ_FILE_ERROR,
    RESET_GRAPH,
    WRITE_FILE_ERROR,
};


static const std::map<Message, std::string> MessageStr = 
{
    { Message::CONNECTION_EXISTS,            { "Connection exists for selected nodes" }},
    { Message::CONNECTION_INPUT_ERROR,       { "Connection value must be empty or an integer with a maximum of three digits" }},
    { Message::CONNECTION_NOT_SELECTED,      { "Select at least one connection to perform an action" }},
    { Message::CONNECTION_REQUIREMENT,       { "Select two nodes to create a conection or use a right mouse button" }},
    { Message::GRAPH_SET_TYPE,               { "Remove graph to change type of graph" }},
    { Message::NODE_VALUE_ERROR,             { "Choose only one letter or digit for node value" }},
    { Message::NODE_KEY_EXISTS,              { "There is a node with provided key" }},
    { Message::NODE_LIMIT,                   { "Maximum number of nodes is 30" }},
    { Message::NODE_SELECT_ONE,              { "Select only one node to perform an action" }},
    { Message::NODE_NOT_SELECTED,            { "Select at least one node to perform an action" }},
    { Message::NODE_SELECT_TWO,              { "Select two nodes to perform an action" }},
    { Message::NO_FILE_NAME,                 { "File name is empty" }},
    { Message::READ_FILE_ERROR,              { "Reading graph file error" }},
    { Message::WRITE_FILE_ERROR,             { "Writing graph file error" }}
};

#endif

