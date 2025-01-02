#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
int main() {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 50, 200);
  sheet.addSticker(i, 30, 400);
  Image render = sheet.render();
  render.writeToFile("myImage.png");
  return 0;
}
