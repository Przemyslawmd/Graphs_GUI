
#ifndef GUI_GRAPHS_UTILS_H
#define GUI_GRAPHS_UTILS_H


static float adjustAngleForQuarter(const sf::Vector2f& pos_1, const sf::Vector2f& pos_2, float angle)
{
    if (pos_1.x <= pos_2.x && pos_1.y <= pos_2.y) {
        return angle;
    }
    if (pos_1.x > pos_2.x && pos_1.y <= pos_2.y) {
        return 180 - angle;
    }
    if (pos_1.x > pos_2.x && pos_1.y > pos_2.y) {
        return 180 + angle;
    }
    if (pos_1.x <= pos_2.x && pos_1.y > pos_2.y) {
        return 360 - angle;
    }
}


#endif

