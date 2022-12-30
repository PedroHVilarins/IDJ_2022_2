#include "vec2.h"
#include <cmath>

Vec2::Vec2(){};
Vec2::Vec2(float d, float j) : x(d), y(j){};

Vec2 Vec2::GetRotated(float ang)
{

    float j, k;
    j = x * cos(ang) - y * sin(ang);
    k = y * cos(ang) + x * sin(ang);

    return Vec2(j, k);
}

Vec2 Vec2::operator+(Vec2 primeiro)
{

    float j, l;

    j = primeiro.x + x;
    l = primeiro.y + y;

    Vec2 temp(j, l);

    return temp;
}

Vec2 Vec2::operator-(Vec2 primeiro)
{

    float j, l;

    j = primeiro.x - x;
    l = primeiro.y - y;

    Vec2 temp(j, l);

    return temp;
}

Vec2 Vec2::operator*(Vec2 primeiro)
{

    float j, l;

    j = primeiro.x * x;
    l = primeiro.y * y;

    Vec2 temp(j, l);

    return temp;
}

float Vec2::magnitude()
{

    float mag = sqrt((this->x * this->x) + (this->y * this->y));

    return mag;
}

Vec2 Vec2::normalizar()
{

    float norm = this->magnitude();

    Vec2 vet = {(this->x / norm), (this->y / norm)};

    return vet;
}