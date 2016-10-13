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
#include "CannyPhoto.hpp"
#include "removeNoisePhoto.hpp"
#include "Common.hpp"

// 模糊
void numberPhoto::method_one(int *pixels, int width, int height, int value) {
    
    Pixels *the_pixels = new Pixels(pixels,width,height);
//    the_pixels->GrayPixels();
    //BinaryzationPhoto *the_binary = new BinaryzationPhoto(the_pixels);
    BlurPhoto *the_blur = new BlurPhoto(the_pixels);
    
    //printf("width:%d,height:%d\n",(int)width,(int)height); // 480,360
    /*       w
      h  {  [1,2,3]
            [a,b,c] }
     */
    
    // start
    int *temp(pixels);

    
    Pixels *tempPixels = new Pixels(temp,width,height);
    // end
    
    the_blur->GaussDeal(tempPixels,width, height, value);
    //the_binary->binaryzation(50, 50, width, height);
    //the_binary->binaryCanny(50, 50, width, height);

    the_pixels = NULL;
    the_blur = NULL;
//    delete [] temp;
//    delete [] tempPixels;
}

// 二值化 - 边缘检测
void numberPhoto::method_two(int *pixels, int width, int height, bool isCanny, int wRadius, int hRadius, int scanScaleOfRadius) {
    Pixels *the_pixels = new Pixels(pixels,width,height);
    BinaryzationPhoto *the_binary = new BinaryzationPhoto(the_pixels);
    
    the_binary->binaryzation(wRadius, hRadius, width, height, scanScaleOfRadius);
    
    if (isCanny == true) {
        the_binary->binaryCanny(wRadius, hRadius, width, height);
    }
    
    the_pixels = NULL;
    the_binary = NULL;
}

// 基础锐化
void numberPhoto::method_three(int *pixels, int width, int height, int Radius) {
    Pixels *the_pixels = new Pixels(pixels,width,height);
    BlurPhoto *the_blur = new BlurPhoto(the_pixels); 
    
    int *temp(pixels);
    Pixels *tempPixels = new Pixels(temp,width,height);
//    tempPixels->GrayPixels();
    
    the_blur->PointyDeal(tempPixels, width, height, Radius);
    
    the_pixels = NULL;
    the_blur = NULL;
    //    delete [] temp;
    //    delete [] tempPixels;
}

// OTSU算法
void numberPhoto::otsuBinary(int *pixels, int width, int height, bool isCanny, int wRadius, int hRadius) {
    Pixels *the_pixels = new Pixels(pixels,width,height);
    BinaryzationPhoto *the_binary = new BinaryzationPhoto(the_pixels);
    
    the_binary->otsuBinary(width, height);
    if (isCanny == true) {
        the_binary->binaryCanny(wRadius, hRadius, width, height);
    }
    
    the_pixels = NULL;
    the_binary = NULL;
}

// test
void numberPhoto::testAction(int *pixels, int width, int height) {
    Pixels *the_pixels = new Pixels(pixels,width,height);
    int *mon = the_pixels->MountionsPic();
    
    for (int i = 0; i < 256; i++) {
        printf(" %d=>%3d ",i,mon[i]);
    }
    
    the_pixels = NULL;
    mon = NULL;
    
}

// sobel
void numberPhoto::sobelCanny(int *pixels, int width, int height) {
    Pixels *the_pixels = new Pixels(pixels,width,height);
    
    // 进行中值滤波处理
//    removeNoisePhoto *remove_pix = new removeNoisePhoto(the_pixels);
//    remove_pix->mid_remove(width, height, 1);
    
    CannyPhoto *the_canny = new CannyPhoto(the_pixels);
    the_canny->sobelCanny(width, height);
    
    delete the_canny;
    delete the_pixels;
    
    the_pixels = NULL;
    //    remove_pix = NULL;
    the_canny = NULL;
    
}


