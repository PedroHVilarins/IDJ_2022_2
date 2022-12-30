#include "vec2.h"
#include <cmath>

Vec2::Vec2(){};
Vec2::Vec2(int d, int j) : x(d), y(j){};

Vec2 Vec2::GetRotated(float ang)
{

    int j, k;

    j = x * cos(ang) - y * sin(ang);
    k = y * cos(ang) + x * sin(ang);

    return Vec2(j, k);
}

Vec2 Vec2::operator+(Vec2 primeiro)
{

    int j, l;

    j = primeiro.x + x;
    l = primeiro.y + y;

    Vec2 temp(j, l);

    return temp;
}

Vec2 Vec2::normalizar(Vec2 vet)
{

    float norm = sqrt((vet.x * vet.x) + (vet.y * vet.y));

    vet = {(vet.x / norm), (vet.y / norm)};

    return vet;
}