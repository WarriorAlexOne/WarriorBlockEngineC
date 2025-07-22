#ifndef WBE_VECTOR2D_H
#define WBE_VECTOR2D_H

#include "WBE_Defines.h"

typedef struct {
    byte x;
    byte y;
} WBE_Vector2D_B;

typedef struct {
    short x;
    short y;
} WBE_Vector2D_S;

typedef struct {
    int x;
    int y;
} WBE_Vector2D_I;

typedef struct {
    long long x;
    long long y;
} WBE_Vector2D_LL;

typedef struct {
    float x;
    float y;
} WBE_Vector2D_F;

typedef struct {
    double x;
    double y;
} WBE_Vector2D_D;

typedef struct {
    long double x;
    long double y;
} WBE_Vector2D_LD;

// Unsigned Variants

typedef struct {
    unsigned byte x;
    unsigned byte y;
} WBE_Vector2D_UB;

typedef struct {
    unsigned short x;
    unsigned short y;
} WBE_Vector2D_US;

typedef struct {
    unsigned int x;
    unsigned int y;
} WBE_Vector2D_UI;

typedef struct {
    unsigned long long x;
    unsigned long long y;
} WBE_Vector2D_ULL;

#endif