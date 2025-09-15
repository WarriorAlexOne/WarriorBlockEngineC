#ifndef WBE_VECTOR2D_H
#define WBE_VECTOR2D_H

#include "WBE/WBE_Defines.h"

typedef struct {
    byte x;
    byte y;
} WBE_Vec2_B;

typedef struct {
    short x;
    short y;
} WBE_Vec2_S;

typedef struct {
    int x;
    int y;
} WBE_Vec2_I;

typedef struct {
    long long x;
    long long y;
} WBE_Vec2_LL;

typedef struct {
    float x;
    float y;
} WBE_Vec2_F;

typedef struct {
    double x;
    double y;
} WBE_Vec2_D;

typedef struct {
    long double x;
    long double y;
} WBE_Vec2_LD;

// Unsigned Variants

typedef struct {
    unsigned byte x;
    unsigned byte y;
} WBE_Vec2_UB;

typedef struct {
    unsigned short x;
    unsigned short y;
} WBE_Vec2_US;

typedef struct {
    unsigned int x;
    unsigned int y;
} WBE_Vec2_UI;

typedef struct {
    unsigned long long x;
    unsigned long long y;
} WBE_Vec2_ULL;

#endif