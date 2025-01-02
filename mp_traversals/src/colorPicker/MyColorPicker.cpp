#include "cs225/HSLAPixel.h"
#include "../Point.h"
#include <cmath>
#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(double hue, double saturation, unsigned center_x, unsigned center_y, unsigned radius) : hue_(hue), saturation_(saturation), center_x_(center_x), center_y_(center_y), radius_(radius) {}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  double distance = std::sqrt(std::pow(x - center_x_, 2) + std::pow(y - center_y_, 2));
  if (distance <= radius_) {
    return HSLAPixel(hue_, saturation_, 0.5, 1);
  } else {
    return HSLAPixel(hue_, saturation_, 1, 1);
  }
}
