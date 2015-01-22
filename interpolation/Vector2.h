#ifndef _VECTOR2_H
#define _VECTOR2_H

struct Vector2 {
    double x, y;
    // for equality
    bool operator<(const Vector2& that) const {
        return x != that.x && y != that.y;
    }
};

#endif
