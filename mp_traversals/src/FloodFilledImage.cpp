#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) : baseImage_(png) {}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(Traversals::ImageTraversal & traversal, ColorPicker & colorPicker) {
  floodFilledImage_.push_back(std::make_pair(&traversal, &colorPicker));
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 * @param frameInterval how often to save frames of the animation
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  animation.addFrame(baseImage_); /*add based frame*/
  PNG baseImageCopy(baseImage_);
  int count = 0;
  for (auto const& flood : floodFilledImage_) { /*for each flood in image*/
    Traversals::ImageTraversal* traversal = flood.first;/*order of the corlor changing-loop through each order's pixel and change its color*/
    ColorPicker* colorPicker = flood.second;

    for (const Point& p : *traversal) {/*getting the pixel in order*/
      HSLAPixel* pix = &baseImageCopy.getPixel(p.x, p.y);
      *pix = colorPicker->getColor(p.x, p.y);
      count++;
      if (count % frameInterval == 0) {/*after changing the color, add the base image*/
        animation.addFrame(baseImageCopy);
      }
    }
    animation.addFrame(baseImageCopy);
  }
  return animation;
}