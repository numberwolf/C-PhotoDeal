//
//  Pixels.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/12.
//  Copyright © 2016年 numberwolf. All rights reserved.
//
/**************************************************************************
 * Email：porschegt23@foxmail.com || numberwolf11@gmail.com
 * Github:https://github.com/numberwolf
 * APACHE 2.0 LICENSE
 * Copyright [2016] [Chang Yanlong]
 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 **************************************************************************/


#include "Pixels.hpp"
#define Mask8(x) ( (x) & 0xFF )
#define R(x) ( Mask8(x) )
#define G(x) ( Mask8(x >> 8 ) )
#define B(x) ( Mask8(x >> 16) )
#define A(x) ( Mask8(x >> 24) )
#define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )

uint32_t* Pixels::getColorPixel(int x, int y) {
    return this->my_pixels + (y * this->width) + x;
}

uint32_t Pixels::getRed(int x, int y) {
    return R(*this->getColorPixel(x, y));
}

uint32_t Pixels::getGreen(int x, int y) {
    
    return G(*this->getColorPixel(x, y));
}

uint32_t Pixels::getBlue(int x, int y) {
    
    return B(*this->getColorPixel(x, y));
}

uint32_t Pixels::getAlpha(int x, int y) {
    return A(*this->getColorPixel(x, y));
}

void Pixels::rgbMake(int x, int y, uint32_t R, uint32_t G, uint32_t B, uint32_t alpha) {
    uint32_t *currentPixels = this->getColorPixel(x, y);
    *currentPixels = RGBAMake(R, G, B, alpha);
}
