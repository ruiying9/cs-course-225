/**
* @file StickerSheet.h
* Contains your declaration of the interface for the StickerSheet class.
*/
#include "Image.h"
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
#pragma once
class StickerSheet{
    public: 
        StickerSheet (const Image &picture, unsigned max);
        StickerSheet (const StickerSheet &other);
        const StickerSheet & 	operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        int layers () const;
        Image render () const;
        Image baseP;
        std::vector<Image*> lay;
        std::vector<int> xCoor;
        std::vector<int> yCoor;
        int max_;
};