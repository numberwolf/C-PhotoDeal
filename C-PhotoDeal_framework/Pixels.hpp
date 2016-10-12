//
//  Pixels.hpp
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


#ifndef Pixels_hpp
#define Pixels_hpp

#include <stdio.h>

/**
 图形像素点 数据结构
 **/

class Pixels {
    int *my_pixels = NULL;
    int width = NULL;
    int height = NULL;
    
public:
    Pixels(int *pixels, int width, int height){
        this->my_pixels = pixels;
        this->width = width;
        this->height = height;
    }
    
    ~Pixels(){
        //this->my_pixels = NULL;
    }
    
    int getRed(int x, int y);
    int getGreen(int x, int y);
    int getBlue(int x, int y);
    int getAlpha(int x, int y);
    int getGray(int x, int y);
    
    void rgbMake(int x,int y, int R, int G, int B, int alpha);
    void GrayPixels();
    int* MountionsPic();
    
private:
    int *getColorPixel(int x, int y);
    
protected:
    
};

#endif /* Pixels_hpp */
