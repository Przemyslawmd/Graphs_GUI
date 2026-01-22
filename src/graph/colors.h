
#ifndef GUI_GRAPHS_COLORS_H
#define GUI_GRAPHS_COLORS_H

#include <map>
#include <stdint.h>


struct RGB 
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
};


constexpr size_t DEFAULT_COL = 0;

static const std::map<uint8_t, RGB> colors =
{
    {  DEFAULT_COL, { 51, 153, 255 }}, // default, no color
    {  1,           { 255, 0, 0 }},    // red
    {  2,           { 0, 255, 0 }},    // lime
    {  3,           { 0, 0, 255 }},    // blue
    {  4,           { 255, 255, 0 }},  // yellow
    {  5,           { 255, 165, 0 }},  // orange
    {  6,           { 128, 128, 0 }},  // olive
    {  7,           { 0, 0, 128 }},    // navy
    {  8,           { 255, 0, 255 }},  // magenta
    {  9,           { 128, 0, 0 }},    // maroon
    { 10,           { 0, 128, 0 }},    // green
};

#endif

