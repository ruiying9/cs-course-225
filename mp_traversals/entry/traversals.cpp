
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "ImageTraversal.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;
  png.readFromFile("../data/pacman.png");
  FloodFilledImage image(png);
  MyColorPicker colorP1(50, 0.8, 200, 200, 100);
  MyColorPicker colorP2(178.3, .898, 400, 400, 100);
  Traversals::ImageTraversal traversal1(png, Point(100, 100), 0.2, Traversals::bfs_add, Traversals::bfs_pop);
  Traversals::ImageTraversal traversal2(png, Point(150, 150), 0.2, Traversals::dfs_add,Traversals::dfs_pop);
  image.addFloodFill(traversal1, colorP1);
  image.addFloodFill(traversal2, colorP2);

  Animation animation = image.animate(25);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}
