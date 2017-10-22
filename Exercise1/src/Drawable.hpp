#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

 
class Drawable
{
public:
    virtual ~Drawable() = default;

    virtual void drawOn(sf::RenderTarget& target) const = 0;
};

#endif
