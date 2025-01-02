/**
 * @file flower.h
 * Declaration of the Flower class.
 */

#pragma once

#include "shape.h"
#include "circle.h"
#include "color.h"
#include "rectangle.h"
#include "triangle.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
class Flower : public Drawable
{
  private:
    Shape *stem;
    Shape *pistil;
    Shape *leaf;

    void drawPetals(cs225::PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    Flower(const Vector2& center);
    ~Flower();
    void draw(cs225::PNG* canvas) const;
};
