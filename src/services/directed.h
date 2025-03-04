

#ifndef GUI_GRAPHS_DIRECTED_H
#define GUI_GRAPHS_DIRECTED_H


class Directed
{
public:
    static void setDirected(bool isDirected)
    {
        directed = isDirected;
    }

    static bool isDirected()
    {
        return directed;
    }

private:
    inline static bool directed;
};


#endif

