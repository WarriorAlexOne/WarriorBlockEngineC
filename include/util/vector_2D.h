#ifndef VECTOR_2D_H
#define VECTOR_2D_H

typedef struct {
    double x;
    double y;
} Vec2;

typedef struct {
    int x;
    int y;
} Vec2_Int;


Vec2 Vec2Add (Vec2 vec1, Vec2 vec2);
Vec2_Int Vec2_IntAdd (Vec2_Int vec1, Vec2_Int vec2);

Vec2 Vec2Subtract (Vec2 vec1, Vec2 vec2);
Vec2_Int Vec2_IntSubtract (Vec2_Int vec1, Vec2_Int vec2);

Vec2 Vec2Divide (Vec2 vec1, double divisor);
Vec2_Int Vec2_IntDivide (Vec2_Int vec1, int divisor);

Vec2 Vec2Multiply (Vec2 vec1, double multiplier);
Vec2_Int Vec2_IntMultiply (Vec2_Int vec1, int multiplier);

Vec2_Int Vec2ToVec2_Int (Vec2 vec);
Vec2 Vec2_IntToVec2 (Vec2_Int vec);

double Vec2Magnitude (Vec2 vec);
double Vec2_IntMagnitude (Vec2_Int vec);

Vec2 Vec2Normalize (Vec2 vec);

Vec2 Vec2Interpolation (Vec2 currentPosition, Vec2 interpolation, double interpolationSpeed);

#endif