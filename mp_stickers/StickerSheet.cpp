#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    base_picture = picture;
    max_num = max;
    image_grid = new Image*[max_num];
    for (unsigned i = 0; i < max_num; i++) {
        image_grid[i] = nullptr;
    }
    x_coordinate = new unsigned[max_num];
    y_coordinate = new unsigned[max_num];
}

StickerSheet::~StickerSheet() {
    clear();
}

void StickerSheet::clear() {

    delete[] image_grid;
    image_grid = nullptr;

    delete[] x_coordinate;
    x_coordinate = nullptr;
    
    delete[] y_coordinate;
    y_coordinate = nullptr;
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    copy(other);
}

void StickerSheet::copy(const StickerSheet & other) {
    base_picture = other.base_picture;
    max_num = other.max_num;
    image_grid = new Image*[max_num];
    for (unsigned i = 0; i < max_num; i++) {
        image_grid[i] = nullptr;
    }
    x_coordinate = new unsigned[max_num];
    y_coordinate = new unsigned[max_num];
    for (unsigned i = 0; i < max_num; i++) {
        image_grid[i] = other.image_grid[i];
        x_coordinate[i] = other.x_coordinate[i];
        y_coordinate[i] = other.y_coordinate[i];
    }
}

const StickerSheet & StickerSheet::operator = (const StickerSheet & other) {
    clear();
    copy(other);
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max_num == max) {
        return;
    }
    Image **new_grid = new Image*[max];
    for (unsigned i = 0; i < max; i++) {
        new_grid[i] = nullptr;
    }
    unsigned * new_x_coordinate = new unsigned[max];
    unsigned * new_y_coordinate = new unsigned[max];

    if (max_num < max) {
        for (unsigned i = 0; i < max_num; i++) {
            new_grid[i] = image_grid[i];
            new_x_coordinate[i] = x_coordinate[i];
            new_y_coordinate[i] = y_coordinate[i];
        }
        for (unsigned i = max_num; i < max; i++) {
            new_grid[i] = nullptr;
        } 
    }

    if (max_num > max) {
        for (unsigned i = 0; i < max; i++) {
            new_grid[i] = image_grid[i];
            new_x_coordinate[i] = x_coordinate[i];
            new_y_coordinate[i] = y_coordinate[i];
        }
    }

    clear();
    max_num = max;
    image_grid = new_grid;
    x_coordinate = new_x_coordinate;
    y_coordinate = new_y_coordinate;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    for (unsigned i = 0; i < max_num; i++) {
        if (image_grid[i] == nullptr) {
            image_grid[i] = &sticker;
            x_coordinate[i] = x;
            y_coordinate[i] = y;
            return i;
        }
    }
    return -1; 
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (image_grid[index] == nullptr || index >= max_num) {
        return false;
    } else {
        x_coordinate[index] = x;
        y_coordinate[index] = y;
        return true;
    }
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < max_num) {
        image_grid[index] = nullptr;
    }
}

Image * StickerSheet::getSticker(unsigned index) {
    if (image_grid[index] == nullptr || index >= max_num) {
        return NULL;
    } 
    return image_grid[index];
}

Image StickerSheet::render() const {
    unsigned new_width = base_picture.width();
    unsigned new_height = base_picture.height();
    for (unsigned i = 0; i < max_num; i++) {
        if (image_grid[i] != nullptr) {
            if (x_coordinate[i]+image_grid[i]->width() > new_width) {
                new_width = x_coordinate[i]+image_grid[i]->width();
            }
            if (y_coordinate[i]+ image_grid[i]->height() > new_height) {
                new_height = y_coordinate[i]+ image_grid[i]->height();
            }
        }
    }
    
    Image image_filled = base_picture;
    image_filled.resize(new_width, new_height);

    for (unsigned i = 0; i < max_num; i++) {
        if (image_grid[i] != nullptr) {
            for (unsigned x = 0; x < image_grid[i]->width(); x++) {
                for (unsigned y = 0; y < image_grid[i]->height(); y++) {
                    cs225::HSLAPixel & image_pixel = image_filled.getPixel(x + x_coordinate[i], y + y_coordinate[i]);
                    cs225::HSLAPixel & sticker_pixel = image_grid[i]->getPixel(x, y);
                    if (sticker_pixel.a != 0) {
                        image_pixel = sticker_pixel;
                    }
                }
            }
        }
    }
    return image_filled;
}