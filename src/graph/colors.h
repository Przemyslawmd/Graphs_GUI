
#ifndef GUI_GRAPHS_COLORS_H
#define GUI_GRAPHS_COLORS_H

#include <map>
#include <stdint.h>


struct RGB 
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
};


static std::map<uint8_t, RGB> colors = 
{
    { 1, { 255, 0, 0 }},
    { 2, { 0, 255, 0 }},
    { 3, { 0, 0, 255 }},
};

#endif

