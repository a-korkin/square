#ifndef SQUARE_H
#define SQUARE_H

#define SPEED 200

typedef struct {
    int x, y;
} Vector2;

typedef struct {
    unsigned char r, g, b, a;
} Color;

typedef struct {
    int size;
    Vector2 position;
    Vector2 direction;
    Color color;
} Square;

void draw_square(void);

#endif // SQUARE_H

