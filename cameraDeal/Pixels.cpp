//
//  Pixels.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/12.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "Pixels.hpp"

uint32_t* Pixels::getColorPixel(int x, int y) {
    return this->my_pixels + (y * this->width) + x;
}

uint32_t Pixels::getRed(int x, int y) {
    
    return (*this->getColorPixel(x, y)) & 0xFF;
}

uint32_t Pixels::getGreen(int x, int y) {
    
    return (*this->getColorPixel(x, y) >> 8) & 0xFF;
}

uint32_t Pixels::getBlue(int x, int y) {
    
    return (*this->getColorPixel(x, y) >> 16) & 0xFF;
}

uint32_t Pixels::getAlpha(int x, int y) {
    return (*this->getColorPixel(x, y) >> 24) & 0xFF;
}

void Pixels::rgbMake(int x, int y, uint32_t R, uint32_t G, uint32_t B, uint32_t alpha) {
    /**
     #define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )
     **/
    
    uint32_t *currentPixels = this->getColorPixel(x, y);
    *currentPixels = ( ((R)& 0xFF) | ((G)& 0xFF << 8) | ((B)& 0xFF << 16) | ((alpha)& 0xFF << 24) );
    
}
