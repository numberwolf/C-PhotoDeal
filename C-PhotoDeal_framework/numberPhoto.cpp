//
//  numberPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/2/22.
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



#include <math.h>
#include "numberPhoto.hpp"
#include "BlurPhoto.hpp"
#include "BinaryzationPhoto.hpp"
#include "Pixels.hpp"
#include "Common.hpp"

// 模糊
void numberPhoto::method_one(uint32_t *pixels, int width, int height, int value) {
    
    Pixels *the_pixels = new Pixels(pixels,width,height);
    //BinaryzationPhoto *the_binary = new BinaryzationPhoto(the_pixels);
    BlurPhoto *the_blur = new BlurPhoto(the_pixels);
    
    //printf("width:%d,height:%d\n",(int)width,(int)height); // 480,360
    /*       w
      h  {  [1,2,3]
            [a,b,c] }
     */
    
    // start
    uint32_t *temp(pixels);

    
    Pixels *tempPixels = new Pixels(temp,width,height);
    tempPixels->GrayPixels();
    // end
    
    the_pixels->GrayPixels();
    the_blur->GaussDeal(tempPixels,width, height, value);
    //the_binary->binaryzation(50, 50, width, height);
    //the_binary->binaryCanny(50, 50, width, height);

    the_pixels = NULL;
    the_blur = NULL;
//    delete [] temp;
//    delete [] tempPixels;
}

// 二值化 - 边缘检测
void numberPhoto::method_two(uint32_t *pixels, int width, int height, bool isCanny, int wRadius, int hRadius) {
    Pixels *the_pixels = new Pixels(pixels,width,height);
    BinaryzationPhoto *the_binary = new BinaryzationPhoto(the_pixels);
    
    the_binary->binaryzation(wRadius, hRadius, width, height);
    
    if (isCanny == true) {
        the_binary->binaryCanny(wRadius, hRadius, width, height);
    }
    
    the_pixels = NULL;
    the_binary = NULL;
}

// 简单锐化
void numberPhoto::method_three(uint32_t *pixels, int width, int height) {
    Pixels *the_pixels = new Pixels(pixels,width,height);
    BlurPhoto *the_blur = new BlurPhoto(the_pixels);
    
    uint32_t *temp(pixels);
    Pixels *tempPixels = new Pixels(temp,width,height);
    tempPixels->GrayPixels();
    
    the_blur->PointyDeal(tempPixels, width, height);
    
    the_pixels = NULL;
    the_blur = NULL;
    //    delete [] temp;
    //    delete [] tempPixels;
}

// 混合锐化测试
void numberPhoto::method_four(uint32_t *pixels, int width, int height, int wRadius, int hRadius) {
    

}


