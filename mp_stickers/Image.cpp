#include <cmath>
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

void Image::lighten() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).l <= 0.9) {
                getPixel(x, y).l = getPixel(x, y).l + 0.1;
            } else {
                getPixel(x, y).l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).l <= 1 - amount) {
                getPixel(x, y).l = getPixel(x, y).l + amount;
            } else {
                getPixel(x, y).l = 1;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).l >= 0.1) {
                getPixel(x, y).l = getPixel(x, y).l - 0.1;
            } else {
                getPixel(x, y).l = 0;
            }
        }
    }
}

void Image::darken(double amount ) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).l >= amount) {
                getPixel(x, y).l = getPixel(x, y).l - amount;
            } else {
                getPixel(x, y).l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).s <= 0.9) {
                getPixel(x, y).s = getPixel(x, y).s + 0.1;
            } else {
                getPixel(x, y).s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).s <= 1-amount) {
                getPixel(x, y).s = getPixel(x, y).s + amount;
            } else {
                getPixel(x, y).s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).s >= 0.1) {
                getPixel(x, y).s = getPixel(x, y).s - 0.1;
            } else {
                getPixel(x, y).s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).s >= amount) {
                getPixel(x, y).s = getPixel(x, y).s - amount;
            } else {
                getPixel(x, y).s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            getPixel(x, y).s = 0;            
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).h + degrees < 0) {
                getPixel(x, y).h = 360 - (std::fmod(std::abs(getPixel(x, y).h + degrees), 360));
            } else {
                getPixel(x, y).h = std::fmod((getPixel(x, y).h + degrees), 360);
            }            
        }
    }
}

void Image::illinify() {
    const double orange = 11;
    const double blue = 216;
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x, y).h < orange + (blue - orange)/2 || getPixel(x, y).h > blue + ((orange + 360) - blue)/2){
                getPixel(x, y).h = orange;
            } else if (getPixel(x, y).h >= orange + (blue - orange)/2 && getPixel(x, y).h <= blue + ((orange + 360) - blue)/2){
                getPixel(x, y).h = blue;
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned int new_width = (unsigned int)(width() * factor);
    unsigned int new_height = (unsigned int)(height() * factor);
    Image * new_image = new Image;
    *new_image = *this;
    new_image->resize(new_width, new_height);

    for (unsigned int x = 0; x < new_width; x++) {
        for (unsigned int y = 0; y < new_height; y++) {
            cs225::HSLAPixel & pixel_old = getPixel((unsigned int)(x/factor), (unsigned)(y/factor));
            cs225::HSLAPixel & pixel_new = new_image->getPixel(x, y);
            pixel_new = pixel_old;
        }
    }

    this->resize(new_width, new_height);
    *this = *new_image;

    delete new_image;
}

void Image::scale(unsigned w, unsigned h) {
    double width_factor = (double)(w)/(double)(width());
    double height_factor = (double)(h)/(double)(height());
    double factor;
    if (width_factor <= height_factor) {
        factor = width_factor;
    } else {
        factor = height_factor;
    }
    scale(factor);
}