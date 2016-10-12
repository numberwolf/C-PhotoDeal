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
#include "Common.hpp"

int* Pixels::getColorPixel(int x, int y) {
    return this->my_pixels + (y * this->width) + x;
}

int Pixels::getRed(int x, int y) {
    return R(*this->getColorPixel(x, y));
}

int Pixels::getGreen(int x, int y) {
    
    return G(*this->getColorPixel(x, y));
}

int Pixels::getBlue(int x, int y) {
    
    return B(*this->getColorPixel(x, y));
}

int Pixels::getAlpha(int x, int y) {
    return A(*this->getColorPixel(x, y));
}

int Pixels::getGray(int x, int y) {
    return (R(*this->getColorPixel(x, y))*GRAY_RED_POINT + G(*this->getColorPixel(x, y))*GRAY_GREEN_POINT + B(*this->getColorPixel(x, y))*GRAY_BLUE_POINT);
}

void Pixels::rgbMake(int x, int y, int R, int G, int B, int alpha) {
    int *currentPixels = this->getColorPixel(x, y);
    *currentPixels = RGBAMake(R, G, B, alpha);
}

void Pixels::GrayPixels() {
    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            int GrayColor = this->getRed(x, y)*GRAY_RED_POINT + this->getGreen(x, y)*GRAY_GREEN_POINT + this->getBlue(x, y)*GRAY_BLUE_POINT;
            
            this->rgbMake(x, y, GrayColor, GrayColor, GrayColor, 255);
        }
    }
}

int* Pixels::MountionsPic() {
    int *pic = new int[256];
    
    for(int i = 0;i < 256; i++) {
        pic[i] = 0;
    }
    
    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            int GrayColor = this->getRed(x, y)*GRAY_RED_POINT + this->getGreen(x, y)*GRAY_GREEN_POINT + this->getBlue(x, y)*GRAY_BLUE_POINT;
            this->rgbMake(x, y, GrayColor, GrayColor, GrayColor, 255);
            
            pic[GrayColor]++;
        }
    }
    
    return pic;
}

