#include "rect.h"

Rect::Rect(){};
Rect::Rect(float d, float f, float j, float l)
{

    this->x = d;
    this->y = f;
    this->w = j;
    this->h = l;
};

bool Rect::Contains(Vec2 vetor)
{

    int xmax = this->x + w;
    int ymax = this->y + h;

    if ((vetor.x >= this->x) and (vetor.x <= xmax))
    {
        if ((vetor.y >= this->y) and (vetor.y <= ymax))
        {
            return true;
        };
    };
    return false;
}
