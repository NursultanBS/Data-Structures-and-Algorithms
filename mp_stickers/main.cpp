#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image base_picture, gorilla1, gorilla2, gorilla3;
  base_picture.readFromFile("mars.png");
  gorilla1.readFromFile("gorilla1.png");
  gorilla1.scale(0.4);
  gorilla2.readFromFile("gorilla2.png");
  gorilla2.scale(0.4);
  gorilla3.readFromFile("gorilla3.png");
  gorilla3.scale(0.2);

  StickerSheet * my_sticker = new StickerSheet(base_picture, 3);
  my_sticker->addSticker(gorilla1, 100, 350);
  my_sticker->addSticker(gorilla2, 400, 500);
  my_sticker->addSticker(gorilla3, 800, 450);

  Image my_image = my_sticker->render();
  my_image.writeToFile("myImage.png");

  delete my_sticker;
  return 0;
}
