#include "../../include/util/common.h"

#include "../../include/util/tools.h"
#include "../../include/util/vector_2D.h"

//Add
Vec2 Vec2Add (Vec2 vec1, Vec2 vec2) {
    Vec2 sum = {vec1.x + vec2.x, vec1.y + vec2.y};
    return sum;
}
Vec2_Int Vec2_IntAdd (Vec2_Int vec1, Vec2_Int vec2) {
    Vec2_Int sum = {vec1.x + vec2.x, vec1.y + vec2.y};
    return sum;
}

//Subtract
Vec2 Vec2Subtract (Vec2 vec1, Vec2 vec2) {
    Vec2 sum = {vec1.x - vec2.x, vec1.y - vec2.y};
    return sum;
}
Vec2_Int Vec2_IntSubtract (Vec2_Int vec1, Vec2_Int vec2) {
    Vec2_Int sum = {vec1.x - vec2.x, vec1.y - vec2.y};
    return sum;
}

//Divide
Vec2 Vec2Divide (Vec2 vec1, double divisor) {
    Vec2 sum = {vec1.x / divisor, vec1.y / divisor};
    return sum;
}
Vec2_Int Vec2_IntDivide (Vec2_Int vec1, int divisor) {
    Vec2_Int sum = {vec1.x / divisor, vec1.y / divisor};
    return sum;
}

//Multiply
Vec2 Vec2Multiply (Vec2 vec1, double multiplier) {
    Vec2 sum = {vec1.x * multiplier, vec1.y * multiplier};
    return sum;
}
Vec2_Int Vec2_IntMultiply (Vec2_Int vec1, int multiplier) {
    Vec2_Int sum = {vec1.x * multiplier, vec1.y * multiplier};
    return sum;
}

//Convert To Vec2/Vec2_Int
Vec2_Int Vec2ToVec2_Int (Vec2 vec) {
    Vec2_Int returnValue = {(int)vec.x, (int)vec.y};
    return returnValue;
}
Vec2 Vec2_IntToVec2 (Vec2_Int vec) {
    Vec2 returnValue = {(double)vec.x, (double)vec.y};
    return returnValue;
}

//Magnitude
double Vec2Magnitude (Vec2 vec) {
    return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}
double Vec2_IntMagnitude (Vec2_Int vec) {
    return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

//Normalize
Vec2 Vec2Normalize (Vec2 vec) {
    return Vec2Divide(vec, Vec2Magnitude(vec));
}

//Interpolation
Vec2 Vec2Interpolation (Vec2 currentPosition, Vec2 interpolation, double interpolationSpeed) {
    interpolationSpeed = max(0, min(1, interpolationSpeed));
    Vec2 value = {
        currentPosition.x + (interpolation.x - currentPosition.x) * interpolationSpeed,
        currentPosition.y + (interpolation.y - currentPosition.y) * interpolationSpeed
    };
    return value;
}
