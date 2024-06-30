#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    double x;
    double y;
} Vec2;

typedef struct {
    int x;
    int y;
} Vec2_Int;

typedef struct {
    double x;
    double y;
    double z;
} Vec3;

typedef struct {
    int x;
    int y;
    int z;
} Vec3_Int;

typedef struct {
    double x;
    double y;
    double z;
    double w;
} Vec4;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Vec4_Int;

typedef struct {
    double x;
    double y;
    double z;
    double w;
    double v;
} Vec5;

typedef struct {
    int x;
    int y;
    int z;
    int w;
    int v;
} Vec5_Int;

#endif