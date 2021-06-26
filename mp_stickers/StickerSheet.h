/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

class StickerSheet {
    public:
    StickerSheet(const Image & picture, unsigned max);
    ~StickerSheet();
    void clear();
    StickerSheet(const StickerSheet & other);
    void copy(const StickerSheet & other);
    const StickerSheet & operator = (const StickerSheet & other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image & sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index);
    Image render() const;

    private:
    Image base_picture;
    unsigned max_num;
    Image ** image_grid;
    unsigned *x_coordinate;
    unsigned *y_coordinate;
};
