//
//  Pixels.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/12.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "Pixels.hpp"

uint32_t* Pixels::getColorPixel(int x, int y, int width) {
    return this->my_pixels + (y * width) + x;
}

uint32_t Pixels::getRed(int x, int y, int width) {
    
    return (*this->getColorPixel(x, y, width)) & 0xFF;
}

uint32_t Pixels::getGreen(int x, int y, int width) {
    
    return (*this->getColorPixel(x, y, width) >> 8) & 0xFF;
}

uint32_t Pixels::getBlue(int x, int y, int width) {
    
    return (*this->getColorPixel(x, y, width) >> 16) & 0xFF;
}

uint32_t Pixels::getAlpha(int x, int y, int width) {
    return (*this->getColorPixel(x, y, width) >> 24) & 0xFF;
}
