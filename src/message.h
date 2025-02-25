

#ifndef GUI_GRAPHS_MESSAGE_H
#define GUI_GRAPHS_MESSAGE_H

#include <map>
#include <string>


enum class Message
{
    OK,
    CONNECTION_EXISTS,
    CONNECTION_INPUT_ERROR,
    CONNECTION_SELECT_ONE,
    NODE_KEY_EXISTS,
    NODE_LIMIT,
    NODE_VALUE_ERROR,
    NODE_SELECT_ONE,
    NODE_SELECT_AT_LEAST_ONE,
    NODE_SELECT_TWO,
};


static const std::map<Message, std::string> MessageStr = 
{
    { Message::CONNECTION_EXISTS,            { "Connection exists for selected nodes" }},
    { Message::CONNECTION_INPUT_ERROR,       { "Connection value must be empty or an integer with a maximum of three digits" }},
    { Message::CONNECTION_SELECT_ONE,        { "Select only one connection to perform an action" }},
    { Message::NODE_VALUE_ERROR,             { "Choose only one letter or digit for node value" }},
    { Message::NODE_KEY_EXISTS,              { "There is a node with provided key" }},
    { Message::NODE_LIMIT,                   { "Maximum number of nodes is 30" }},
    { Message::NODE_SELECT_ONE,              { "Select only one node to perform an action" }},
    { Message::NODE_SELECT_AT_LEAST_ONE,     { "Select at least one node to perform an action" }},
    { Message::NODE_SELECT_TWO,              { "Select two nodes to perform an action" }}
};


#endif

