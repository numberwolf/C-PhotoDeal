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

void numberPhoto::method_one(uint32_t *pixels, unsigned long width, unsigned long height) {
    
    Pixels *the_pixels = new Pixels(pixels,width,height);
    BinaryzationPhoto *the_binary = new BinaryzationPhoto(the_pixels);
    //BlurPhoto *the_blur = new BlurPhoto(the_pixels);
    
    //printf("width:%d,height:%d\n",(int)width,(int)height); // 480,360
    /*       w
      h  {  [1,2,3]
            [a,b,c] }
     */
//    the_pixels->GrayPixels();
//    
//    uint32_t *temp(pixels);
//    Pixels *tempPixels = new Pixels(temp,width,height);
    
    //the_blur->GaussDeal(tempPixels,width, height, 40);
    the_binary->binaryzation(50, 50, width, height);
    the_binary->binaryCanny(50, 50, width, height);
    
//    for (int i = 0; i < width; ++i) {
//        for (int j = 0; j < height; ++j) {
//            printf("%3d ",the_pixels->getRed(i, j));
//        }
//        printf("\n");
//    }
    
//    delete [] the_binary;
//    delete [] the_pixels;
    
}


