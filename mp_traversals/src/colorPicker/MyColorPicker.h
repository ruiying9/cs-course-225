#pragma once

#include "ColorPicker.h"
#include "cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(double hue, double saturation, unsigned center_x, unsigned center_y, unsigned radius);
  virtual HSLAPixel getColor(unsigned x, unsigned y);
private:
  unsigned hue_;
  unsigned saturation_;
  unsigned center_x_;
  unsigned center_y_;
  unsigned radius_;
};
