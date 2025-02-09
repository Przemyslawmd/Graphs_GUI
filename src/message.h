

#ifndef GUI_GRAPHS_MESSAGE_H
#define GUI_GRAPHS_MESSAGE_H

#include <map>
#include <string>


enum class Message
{
    OK,
    CONNECTION_EXISTS,
    CONNECTION_NODES_COUNT_ERROR,
    NODE_VALUE_ERROR,
    NODE_LIMIT,
    NODE_SELECT_ONE
};


static const std::map<Message, std::string> MessageStr = 
{
    { Message::CONNECTION_NODES_COUNT_ERROR, { "To make a connection select two nodes by clicking the mouse button" }},
    { Message::CONNECTION_EXISTS,            { "Connection exists for selected nodes" }},
    { Message::NODE_VALUE_ERROR,             { "Choose only one letter or digit for node value." }},
    { Message::NODE_LIMIT,                   { "Maximum number of nodes is 30" }},
    { Message::NODE_SELECT_ONE,              { "Select only one node to perform an action" }}
};


#endif

