

#ifndef GUI_GRAPHS_MESSAGE_H
#define GUI_GRAPHS_MESSAGE_H

#include <map>
#include <string>


enum class Message
{
    OK,
    CONNECTION_EXISTS,
    NODES_COUNT_CONNECTION_ERROR,
};


static const std::map<Message, std::string> MessageStr = 
{
    { Message::NODES_COUNT_CONNECTION_ERROR, { "To make a connection select two nodes by clicking the mouse button" }},
    { Message::CONNECTION_EXISTS, { "Connection exists for selected nodes" }}
};


#endif

