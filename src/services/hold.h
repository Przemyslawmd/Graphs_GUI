
#ifndef GUI_GRAPHS_HOLD_H
#define GUI_GRAPHS_HOLD_H


struct Hold
{
    void reset()
    {
        isHeld = false;
        isMoved = false;
        index = -1;
        shiftX = 0;
        shiftY = 0;
    }

    void activate(size_t index_, float shiftX_, float shiftY_)
    {
        isHeld = true;
        isMoved = false;
        index = index_;
        shiftX = shiftX_;
        shiftY = shiftY_;
    }

    bool isHeld;    // true if mouse button is being pressed
    bool isMoved;   // true if there is move between mouse button press and release, to recognize click without moving
    int index;      // index of held object in its container
    float shiftX;   // distance between the mouse X position and the center of held object
    float shiftY;   // distance between the mouse Y position and the center of held object
};

#endif

