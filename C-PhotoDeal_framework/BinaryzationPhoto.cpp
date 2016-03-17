//
//  BinaryzationPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/1.
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


#include "BinaryzationPhoto.hpp"
#include "Common.hpp"
#include <math.h>

#define GRAY_RED_POINT 0.299
#define GRAY_GREEN_POINT 0.587
#define GRAY_BLUE_POINT 0.114

#define CANNY_PIXELS_VAL 200  // 临时存放边界key
#define CANNY_PIXELS_ALPHA 255

#pragma mark
void BinaryzationPhoto::binaryCanny(int **cannyArr,int wRadius, int hRadius, int width, int height) {
    
    for (int j = 0; j < height; j+=hRadius) {
        for (int i = 0; i < width; i+=wRadius) {
            // 区域内处理
            int *localArr = new int[wRadius*hRadius];
            int *pointer = localArr;
            
            // 将范围内的添加进数组
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        *pointer = 0;
                    } else {
                        *pointer = this->BinaryPixels->getRed(x, y); // 因为是已经二值化的图 所以只需要取其中一个通道就可以
                    }
                    
                    pointer++;
                }
            } // 添加结束
            
            // 范围内第一步处理
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    // (x,y)左边的点
                    int x_right = x + 1;
                    int y_right = y;
                    
                    // (x,y)下边的点
                    int x_under = x;
                    int y_under = y + 1;
                    
                    if (x_right >= width || y_right >= height || x_under >= width || y_under >= height) {
                        // 越界和不需要比对边缘的
                        continue;
                    } else {
                        if (y < (height - 1)) {
                            if (x == (width - 1)) { // 当遇到处理x最边像素的时候
                                if (this->BinaryPixels->getRed(x, y) > this->BinaryPixels->getRed(x_under, y_under) || this->BinaryPixels->getRed(x, y) < this->BinaryPixels->getRed(x_under, y_under)) {
                                    
                                    this->BinaryPixels->rgbMake(x, y, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_ALPHA);
                                }
                                
                            } else {
#warning error
                                if (this->BinaryPixels->getRed(x, y) > this->BinaryPixels->getRed(x_right, y_right) || this->BinaryPixels->getRed(x, y) > this->BinaryPixels->getRed(x_under, y_under) || this->BinaryPixels->getRed(x, y) < this->BinaryPixels->getRed(x_right, y_right) || this->BinaryPixels->getRed(x, y) < this->BinaryPixels->getRed(x_under, y_under)) {
                                    
                                    this->BinaryPixels->rgbMake(x, y, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_ALPHA);
//                                    this->BinaryPixels->rgbMake(x_right, y_right, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, 255);
//                                    this->BinaryPixels->rgbMake(x_under, y_under, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, 255);
                                }
#warning errorend
                            }
                        }
                    }
                    
                }
            } // 第一步处理结束
        
            pointer = NULL;
            delete [] localArr;
            
        } // end for-i-width
    } // end for-j-height
    
    // 范围内第二步处理
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (this->BinaryPixels->getRed(i, j) == CANNY_PIXELS_VAL) {
                printf("白线");
                this->BinaryPixels->rgbMake(i, j, 255, 255, 255, 255);
                
                //                        for (int r = 0; r < 5; r++) {
                //                            if (j > r && j < (height - r) && i > r && i < (width - r)) {
                //                                this->BinaryPixels->rgbMake(i+r, j, 255, 255, 255, 255);
                //                                this->BinaryPixels->rgbMake(i, j+r, 255, 255, 255, 255);
                //                                this->BinaryPixels->rgbMake(i-r, j, 255, 255, 255, 255);
                //                                this->BinaryPixels->rgbMake(i, j-r, 255, 255, 255, 255);
                //                                this->BinaryPixels->rgbMake(i+r, j+r, 255, 255, 255, 255);
                //                                this->BinaryPixels->rgbMake(i-r, j-r, 255, 255, 255, 255);
                //                                this->BinaryPixels->rgbMake(i+r, j-r, 255, 255, 255, 255);
                //                                this->BinaryPixels->rgbMake(i-r, j+r, 255, 255, 255, 255);
                //                            }
                //                        }
                
            } else {
                this->BinaryPixels->rgbMake(i, j, 0, 0, 0, 255);
            }
        }
    } // 第二步处理结束
    
    printf("\n");
}

// 区域二值化
void BinaryzationPhoto::binaryzation(int wRadius, int hRadius, int width, int height) {
    
    for (int j = 0; j < height; j+=hRadius) {
        for (int i = 0; i < width; i+=wRadius) {
            
            // (y,x)->(h,w)
            int *localArr = new int[wRadius*hRadius];
            int *pointer = localArr;
            
            // 将范围内的添加进数组
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        *pointer = 0;
                    } else {
                        *pointer = this->BinaryPixels->getRed(x, y);
                    }
                    
                    pointer++;
                }
            } // 添加结束
            
            // 标准差
            //int standard = Common::GetStandard(localArr, 0, wRadius*hRadius);
            
            // 平均数
            int average = Common::GetAverage(localArr, 0, wRadius*hRadius);
            
            // 范围内处理
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        continue;
                    } else {
                        if (this->BinaryPixels->getRed(x, y) > average) {
                            this->BinaryPixels->rgbMake(x, y, 255, 255, 255, 255);
                        } else {
                            this->BinaryPixels->rgbMake(x, y, 0, 0, 0, 255);
                        }
                        //printf("-->%3d ",this->BinaryPixels->getRed(x, y));
                    }
                }
            } // 处理结束
            
            pointer = NULL;
            delete [] localArr;
            
        }
    }
}
