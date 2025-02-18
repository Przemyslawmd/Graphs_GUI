
#ifndef GUI_GRAPHS_UTILS_H
#define GUI_GRAPHS_UTILS_H

#include "message.h"

constexpr float PI = 3.14159265;


static float calculateAngle(const sf::Vector2f& pos_1, const sf::Vector2f& pos_2)
{
    float distance_x = abs(pos_1.x - pos_2.x);
    float distance_y = abs(pos_1.y - pos_2.y);
    float angle = atan(distance_y / distance_x) * 180 / PI;

    if (pos_1.x <= pos_2.x && pos_1.y <= pos_2.y) {
        return angle;
    }
    if (pos_1.x > pos_2.x && pos_1.y <= pos_2.y) {
        return 180 - angle;
    }
    if (pos_1.x > pos_2.x && pos_1.y > pos_2.y) {
        return 180 + angle;
    }
    return 360 - angle;
}


static bool matchAngles(const float connectionAngle, const sf::FloatRect& rect, const float posX, const float posY)
{
    float xCorner = 0.0f;
    float yCorner = 0.0f;

    if (connectionAngle <= 90 ){ 
        xCorner = rect.position.x + rect.size.x;
        yCorner = rect.position.y + rect.size.y;
    }
    else if (connectionAngle > 90 && connectionAngle <= 180) {
        xCorner = rect.position.x;;
        yCorner = rect.position.y + rect.size.y;
    }
    else if (connectionAngle > 180 && connectionAngle <= 270) {
        xCorner = rect.position.x;
        yCorner = rect.position.y;
    }
    else {
        xCorner = rect.position.x + rect.size.x;
        yCorner = rect.position.y;
    }
    auto posAngle = calculateAngle({ posX, posY }, { xCorner, yCorner });
    return abs(connectionAngle - posAngle) < 2;
}


static float calculateConnectionLength(sf::Vector2f& pos_1, sf::Vector2f& pos_2)
{
    float distance_x = pos_1.x - pos_2.x;
    float distance_y = pos_1.y - pos_2.y;
    return sqrt(pow(distance_x, 2) + pow(distance_y, 2)); 
}


static std::tuple<Message, size_t> getWeightFromString(const std::string& text)
{
    if (text.size() == 0) {
        return { Message::OK, 1 };
    }
    if (text.size() > 3) {
        return { Message::CONNECTION_INPUT_ERROR, 0 };
    }

    size_t weight = 0;
    for (const auto& c : text) {
        if (!isdigit(c)) {
            return { Message::CONNECTION_INPUT_ERROR, 0 }; 
        }
        weight = weight * 10 + c - '0';
    }
    return { Message::OK, weight };
} 

#endif

