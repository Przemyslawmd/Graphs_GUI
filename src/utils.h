
enum class Quarter 
{
    ONE,
    TWO,
    THREE,
    FOUR
};


static Quarter findQuarter(float x_1, float y_1, float x_2, float y_2)
{
    if (x_1 <= x_2 && y_1 <= y_2) {
        return Quarter::ONE;
    }
    if (x_1 > x_2 && y_1 <= y_2) {
        return Quarter::TWO;
    }
    if (x_1 > x_2 && y_1 > y_2) {
        return Quarter::THREE;
    }
    if (x_1 <= x_2 && y_1 > y_2) {
        return Quarter::FOUR;
    }
}
