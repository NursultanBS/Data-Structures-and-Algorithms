#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
#include <cmath>

#include <string>
using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG* image = new PNG();
  image->readFromFile(inputFile);

  for (unsigned x = 0; x < (image->width())/2.0; x++) {
    for (unsigned y = 0; y < image->height(); y++) {
      if ((image->width())%2 == 1 && x == (image->width())/2 && y == (image->height())/2) {
        break;
      }
      HSLAPixel & pixel = image->getPixel(x, y);
      
      unsigned x_inverse = image->width() - 1 - x;
      unsigned y_inverse = image->height() - 1 - y;
      HSLAPixel & pixel_inverse = image->getPixel(x_inverse, y_inverse);

      HSLAPixel tmp_pixel(pixel.h, pixel.s, pixel.l, pixel.a);

      pixel = pixel_inverse;
      pixel_inverse = tmp_pixel;
    }
  }
  image->writeToFile(outputFile);
  delete image;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  if (width < height) {
    height=width;
  } else {
    width=height;
  }
  // Setting the background
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = y%360;      
      pixel.s = 0.52;
      pixel.l = 0.3;
    }
  }
  // Setting the grey lines
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = png.height()*110/800; y < png.height()*138/800; y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
    for (unsigned y = png.height()*248/800; y < png.height()*276/800; y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
    for (unsigned y = png.height()*380/800; y < png.height()*414/800; y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
    for (unsigned y = png.height()*524/800; y < png.height()*552/800; y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
    for (unsigned y = png.height()*662/800; y < png.height()*690/800; y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
  }
  // Setting the grey lines
    for (unsigned y = 0; y < png.height(); y++) {
    for (unsigned x = png.width()*110/800; x < png.width()*138/800; x++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
    for (unsigned x = png.width()*248/800; x < png.width()*276/800; x++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
    for (unsigned x = png.width()*380/800; x < png.width()*414/800; x++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
    for (unsigned x = png.width()*524/800; x < png.width()*552/800; x++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
    for (unsigned x = png.width()*662/800; x < png.width()*690/800; x++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 274;
      pixel.s = 0.09;
      pixel.l = 0.63;
    }
  }

  //Column one for circles
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*124/800, 2) + std::pow((int)y - (int)png.height()*124/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*124/800, 2) + std::pow((int)y - (int)png.height()*262/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*124/800, 2) + std::pow((int)y - (int)png.height()*400/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*124/800, 2) + std::pow((int)y - (int)png.height()*538/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*124/800, 2) + std::pow((int)y - (int)png.height()*676/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }
  }  

  //Column two for circles
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*262/800, 2) + std::pow((int)y - (int)png.height()*124/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*262/800, 2) + std::pow((int)y - (int)png.height()*262/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*262/800, 2) + std::pow((int)y - (int)png.height()*400/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*262/800, 2) + std::pow((int)y - (int)png.height()*538/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*262/800, 2) + std::pow((int)y - (int)png.height()*676/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }
  }    

  //Column three for circles
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*400/800, 2) + std::pow((int)y - (int)png.height()*124/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*400/800, 2) + std::pow((int)y - (int)png.height()*262/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*400/800, 2) + std::pow((int)y - (int)png.height()*400/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*400/800, 2) + std::pow((int)y - (int)png.height()*538/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*400/800, 2) + std::pow((int)y - (int)png.height()*676/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }
  }  

  //Column four for circles
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*538/800, 2) + std::pow((int)y - (int)png.height()*124/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*538/800, 2) + std::pow((int)y - (int)png.height()*262/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*538/800, 2) + std::pow((int)y - (int)png.height()*400/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*538/800, 2) + std::pow((int)y - (int)png.height()*538/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*538/800, 2) + std::pow((int)y - (int)png.height()*676/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }
  }

  //Column five for circles
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*676/800, 2) + std::pow((int)y - (int)png.height()*124/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*676/800, 2) + std::pow((int)y - (int)png.height()*262/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*676/800, 2) + std::pow((int)y - (int)png.height()*400/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*676/800, 2) + std::pow((int)y - (int)png.height()*538/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }

    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      double distance = std::sqrt(std::pow((int)x - (int)png.width()*676/800, 2) + std::pow((int)y - (int)png.height()*676/800, 2));
      if (distance <= png.width()*20/800) {
        pixel.l = 1;
      } 
    }
  }    

  return png;
}
