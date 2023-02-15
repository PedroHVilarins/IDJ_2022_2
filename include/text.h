#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
#include "rect.h"
#include "resources.h"
#include "camera.h"
#include "timer.h"

using namespace std;

class GameObject;

class Text : public Component
{

public:
    enum TextStyle
    {
        SOLID,
        SHADED,
        BLENDED
    };

    Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color, float tempo);
    ~Text();

    void Update(float dt);
    void Render();
    bool Is(string type);

    void SetText(string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(string fontFile);
    void SetFontSize(int fontSize);

private:
    void RemakeTexture();

    shared_ptr<TTF_Font> font;
    SDL_Texture *texture;

    string text;
    TextStyle style;
    string fontFile;
    int fontSize;
    SDL_Color color;
    float cooldown;
    Timer *timer;
    SDL_Color auxiliar;
};

#endif