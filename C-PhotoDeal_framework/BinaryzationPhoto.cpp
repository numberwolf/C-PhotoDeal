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

#define CANNY_PIXELS_VAL 200  // 临时存放边界key
#define CANNY_PIXELS_ALPHA 255

#pragma mark
void BinaryzationPhoto::binaryCanny(int wRadius, int hRadius, int width, int height) {
    
    for (int j = 0; j < height; j+=wRadius) {
        for (int i = 0; i < width; i+=hRadius) {
            // 区域内处理
            int *localArr = new int[wRadius*hRadius];
            int *pointer = localArr;
            
            // 将范围内的添加进数组
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        *pointer = 0;
                    } else {
                        *pointer = this->BinaryPixels->getGray(x, y); // 因为是已经二值化的图 所以只需要取其中一个通道就可以
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
                                if (this->BinaryPixels->getGray(x, y) > this->BinaryPixels->getGray(x_under, y_under) || this->BinaryPixels->getGray(x, y) < this->BinaryPixels->getGray(x_under, y_under)) {
                                    
                                    this->BinaryPixels->rgbMake(x, y, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_ALPHA);
                                }
                                
                            } else {
                                if (this->BinaryPixels->getGray(x, y) > this->BinaryPixels->getGray(x_right, y_right) || this->BinaryPixels->getGray(x, y) > this->BinaryPixels->getGray(x_under, y_under) || this->BinaryPixels->getGray(x, y) < this->BinaryPixels->getGray(x_right, y_right) || this->BinaryPixels->getGray(x, y) < this->BinaryPixels->getGray(x_under, y_under)) {
                                    
                                    this->BinaryPixels->rgbMake(x, y, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_VAL, CANNY_PIXELS_ALPHA);
                                }
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
            if (this->BinaryPixels->getGray(i, j) == CANNY_PIXELS_VAL) {
                //printf("白线");
                this->BinaryPixels->rgbMake(i, j, 255, 255, 255, 255);
            } else {
                this->BinaryPixels->rgbMake(i, j, 0, 0, 0, 255);
            }
        }
    } // 第二步处理结束
}

void BinaryzationPhoto::otsuBinary(int width, int height) {
    
    // 创建直方图
    int *Histograms = new int[256];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int gray = this->BinaryPixels->getGray(x, y);
            Histograms[gray]++;
//            if (gray > 200) {
//                printf("G ");
//            } else {
//                printf("i ");
//            }
            
        }
//        printf("\n");
    }
    
    int k,total,q;
    //直方图平滑化
    for (k = 0; k <= 255; k++)
    {
        total = 0;
        for (int t = -2; t <= 2; t++) //与附近2个灰度做平滑化，t值应取较小的值
        {
            q = k + t;
            if (q < 0) { //越界处理
                q = 0;
            }
            if (q > 255) {
                q = 255;
            }
            total = total + Histograms[q]; //total为总和，累计值
        }
        //平滑化，左边2个+中间1个+右边2个灰度，共5个，所以总和除以5，后面加0.5是用修正值
        Histograms[k] = (int)((float)total / 5.0 + 0.5);
    }
    
    int threshValue = 1; // 阈值
    
    double m1, m2, sum, csum, fmax, sb; //sb为类间方差，fmax存储最大方差值
    int n, n1, n2;
    
    //求阈值
    sum = csum = 0.0;
    n = 0;
    //计算总的图象的点数和质量矩，为后面的计算做准备
    for (k = 0; k <= 255; k++)
    {
        //x*f(x)质量矩，也就是每个灰度的值乘以其点数（归一化后为概率），sum为其总和
        sum += (double)k * (double)Histograms[k];
        n += Histograms[k]; //n为图象总的点数，归一化后就是累积概率
    }
    
    fmax = -1.0; //类间方差sb不可能为负，所以fmax初始值为-1不影响计算的进行
    n1 = 0;
    
    for (k = 0; k < 255; k++) //对每个灰度（从0到255）计算一次分割后的类间方差sb
    {
        n1 += Histograms[k]; //n1为在当前阈值遍前景图象的点数
        if (n1 == 0) {
            continue;
        } //没有分出前景后景
        
        n2 = n - n1; //n2为背景图象的点数
        
        //n2为0表示全部都是后景图象，与n1=0情况类似，之后的遍历不可能使前景点数增加，所以此时可以退出循环
        if (n2 == 0) {
            break;
        }
        csum += (double)k * Histograms[k]; //前景的“灰度的值*其点数”的总和
        
        m1 = csum / n1; //m1为前景的平均灰度
        m2 = (sum - csum) / n2; //m2为背景的平均灰度
        sb = (double)n1 * (double)n2 * (m1 - m2) * (m1 - m2); //sb为类间方差
        
        if (sb > fmax) //如果算出的类间方差大于前一次算出的类间方差
        {
            fmax = sb; //fmax始终为最大类间方差（otsu）
            threshValue = k; //取最大类间方差时对应的灰度的k就是最佳阈值
        }
    }
    
    printf("阀值为：%3d",threshValue);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int gray = this->BinaryPixels->getGray(x, y);
            if (gray > threshValue) {
                this->BinaryPixels->rgbMake(x, y, 255, 255, 255, 255);
            } else {
                this->BinaryPixels->rgbMake(x, y, 0, 0, 0, 255);
            }
        }
    }
    
    delete [] Histograms;
}

// 区域二值化
void BinaryzationPhoto::binaryzation(int wRadius, int hRadius, int width, int height, int scanScaleOfRadius) {
    printf("width:%d ",width/20);
    for (int j = 0; j < height; j+=wRadius) {
        for (int i = 0; i < width; i+=hRadius) {
            
            // (y,x)->(h,w)
            int *localArr = new int[wRadius*hRadius];
            int *pointer = localArr;
            
            // 将范围内的添加进数组
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        *pointer = 0;
                    } else {
                        *pointer = this->BinaryPixels->getGray(x, y);
                    }
                    
                    pointer++;
                }
            } // 添加结束
            
            // 标准差
//            int standard = Common::GetStandard(localArr, 0, wRadius*hRadius);
            
            // 平均数
            int average = Common::GetAverage(localArr, 0, wRadius*hRadius);
            
            // 范围内处理
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        continue;
                    } else {
                        if (this->BinaryPixels->getGray(x, y) > average) {
                            this->BinaryPixels->rgbMake(x, y, 255, 255, 255, 255);
                        } else {
                            this->BinaryPixels->rgbMake(x, y, 0, 0, 0, 255);
                        }
                        //printf("-->%3d ",this->BinaryPixels->getGray(x, y));
                    }
                }
            } // 处理结束
            
            pointer = NULL;
            delete [] localArr;
            
        }
    }
}
