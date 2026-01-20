
#ifndef GUI_GRAPHS_HOLD_H
#define GUI_GRAPHS_HOLD_H


enum class Press
{
    NO_PRESS,
    LEFT,
    RIGHT
};


class Hold
{
public:
    void reset()
    {
        press = Press::NO_PRESS;
        isMoved = false;
        index = -1;
        shiftX = 0;
        shiftY = 0;
    }

    void activate(size_t index_, float shiftX_, float shiftY_)
    {
        press = Press::LEFT;
        isMoved = false;
        index = index_;
        shiftX = shiftX_;
        shiftY = shiftY_;
    }

    bool isLeftPress()
    {
        return press == Press::LEFT;
    }

    bool isMoved;   // true if there is move between mouse button press and release, to recognize click without moving
    size_t index;   // index of held object in its container
    float shiftX;   // distance between the mouse X position and the center of held object
    float shiftY;   // distance between the mouse Y position and the center of held object

private:
    Press press;
};

#endif

