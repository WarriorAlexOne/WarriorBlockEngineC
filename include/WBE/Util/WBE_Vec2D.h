#ifndef WBE_VECTOR2D_H
#define WBE_VECTOR2D_H

#include "WBE/WBE_Defines.h"

// 2D Byte Vector
typedef struct {
    byte x;
    byte y;
} WBE_Vec2b;

// 2D Short Vector
typedef struct {
    short x;
    short y;
} WBE_Vec2s;

// 2D Int Vector
typedef struct {
    int x;
    int y;
} WBE_Vec2i;

// 2D Long Long Int Vector
typedef struct {
    long long x;
    long long y;
} WBE_Vec2ll;

// 2D Float Vector
typedef struct {
    float x;
    float y;
} WBE_Vec2f;

// 2D Double Vector
typedef struct {
    double x;
    double y;
} WBE_Vec2d;

// 2D Long Double Vector
typedef struct {
    long double x;
    long double y;
} WBE_Vec2ld;


// Unsigned Variants

// 2D Unsigned Byte Vector
typedef struct {
    unsigned byte x;
    unsigned byte y;
} WBE_Vec2ub;

// 2D Unsigned Short Vector
typedef struct {
    unsigned short x;
    unsigned short y;
} WBE_Vec2us;

// 2D Unsigned Int Vector
typedef struct {
    unsigned int x;
    unsigned int y;
} WBE_Vec2ui;

// 2D Unsigned Long Long Int Vector
typedef struct {
    unsigned long long x;
    unsigned long long y;
} WBE_Vec2ull;

#endif