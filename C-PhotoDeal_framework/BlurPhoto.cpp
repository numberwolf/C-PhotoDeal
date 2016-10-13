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
#include "BlurPhoto.hpp"
#include "Common.hpp"

#pragma mark 高斯模糊 - 半径不要太大 图片半径的百分之1-2合适
void BlurPhoto::GaussDeal(Pixels *tempPixels, int width, int height, int r) {
    
    // **array是二维数组，是rgb8888 最后的每个像素组成的数组
    double xaver = 0.0, x2aver = 0.0;
    
    for (int h = 0; h < height; h++) {
        
        xaver=0.0, x2aver=0.0;
        for (int w = 0 ; w < width; w++) {
            
            int *pixelsArr = new int[(2*r+1)*(2*r+1)]; // 存储半径内像素
            int *pixTemp = pixelsArr;
            
            int pixelSum = 0;
            int pix2Sum = 0;
            
            for (int j = 0; j <= (2*r); j++) {
                int y = h - r + j;
                
                for (int i = 0; i <= (2*r); i++) {
                    int x = w - r + i;
                    
                    // 除去中心点 和 越界点
                    if ( y < 0 || x < 0 || y >= height || x >= width || (y == h && x == w)) {
                        *pixTemp = 0;
                        pixTemp++;
                        continue;
                    }
                    
                    *pixTemp = tempPixels->getGray(x, y);
                    
                    pixelSum += *pixTemp; // 总数
                    pix2Sum += (*pixTemp) * (*pixTemp); // 总数^2
                    
                    pixTemp++;
                }
            }
            
            /** change End **/
            
            int theNum = tempPixels->getGray(w,h);
            // 开始计算方差
            xaver = (pixelSum - theNum)/((2*r+1)*(2*r+1)-1);
            x2aver = (pix2Sum - theNum*theNum)/((2*r+1)*(2*r+1)-1);
            
            double fc = sqrt(x2aver - xaver*xaver); // 得到方差
            
            // 开始计算权重
            double left = 1/(2*PI*fc*fc);
            
            double *weightArr = new double[(2*r+1)*(2*r+1)]; // 得到权重数组
            int weightArrNum = 0;
            double weightSum = 0.0;
            
            // 周围像素权重
            for (int j = 0; j <= (2*r); j++) {
                int y = r - j;
                int y_real = h - r + j; // 真坐标
                
                for (int i = 0; i <= (2*r); i++) {
                    int x = i - r;
                    int x_real = w - r + i; // 真坐标
                    
                    // 除去中心点
                    if ((x == 0 && y == 0) || y_real < 0 || x_real < 0 || y_real > height || x_real > width) {
                        weightArr[weightArrNum] = 0;
                        weightArrNum++;
                        continue;
                    }
                    
                    double right = pow(e, -(x*x + y*y)/(2*fc*fc));
                    double weight = left*right;
                    
                    weightArr[weightArrNum] = weight;
                    
                    weightArrNum++;
                }
            }
            
            for (int n = 0; n < ((2*r+1)*(2*r+1)); n++) {
                weightSum += weightArr[n];
            }
            
            weightArrNum = 0;
            
            int array_h_w_temp = 0;
            
            // 得到周围像素权重
            for (int j = 0; j <= (2*r); j++) {
                for (int i = 0; i <= (2*r); i++) {
                    weightArr[weightArrNum] /= weightSum;
                    *pixelsArr = (*pixelsArr) * weightArr[weightArrNum]; // 周围像素的 权值 * 像素
//                    printf("%3f ",weightArr[weightArrNum]);
                    array_h_w_temp += *pixelsArr;
                    
                    weightArrNum++;
                    pixelsArr++;
                }
            }
            
            this->BlurPixels->rgbMake(w, h, array_h_w_temp, array_h_w_temp, array_h_w_temp);
            
            delete [] weightArr;
//            delete [] pixelsArr;
            
        }
    }
}

// 锐化
void BlurPhoto::PointyDeal(Pixels *tempPixels, int width, int height, int Radius) {
    
    for (int h = 0; h < (height-1); h++) {
        for (int w = 0 ; w < (width-1); w++) {
            uint32_t first_red = tempPixels->getRed(w, h);
            uint32_t first_green = tempPixels->getGreen(w, h);
            uint32_t first_blue = tempPixels->getBlue(w, h);
            printf("(%3d,%3d,%3d)",first_red,first_green,first_blue);
            
            uint32_t second_red = tempPixels->getRed(w+1, h);
            uint32_t second_green = tempPixels->getGreen(w+1, h);
            uint32_t second_blue = tempPixels->getBlue(w+1, h);
            
            int diffRedVal = (first_red - second_red)*Radius;
            int diffGreenVal = (first_green - second_green)*Radius;
            int diffBlueVal = (first_blue - second_blue)*Radius;
            
            int red_value = this->BlurPixels->getRed(w, h) + diffRedVal;
            int green_value = this->BlurPixels->getGreen(w, h) + diffGreenVal;
            int blue_value = this->BlurPixels->getBlue(w, h) + diffBlueVal;
            
            red_value<0?red_value=0:(red_value>255?red_value=255:NULL);
            green_value<0?green_value=0:(green_value>255?green_value=255:NULL);
            blue_value<0?blue_value=0:(blue_value>255?blue_value=255:NULL);
            
            this->BlurPixels->rgbMake(w, h, red_value, green_value, blue_value);
        }
        printf("\r\n");
    }
    
//    for (int h = 0; h < (height-1); h++) {
//        for (int w = 0 ; w < (width-1); w++) {
//            uint32_t first = tempPixels->getRed(w, h);
//            uint32_t second = tempPixels->getRed(w, h+1);
//            
//            uint32_t diffVal = (first - second)/2;
//            uint32_t value = this->BlurPixels->getRed(w, h)+diffVal;
//            if (value > 255) {
//                value = 255;
//            } else if (value < 0) {
//                value = 0;
//            }
//            
//            this->BlurPixels->rgbMake(w, h, value, value, value , 255);
//        }
//    }
}

// 彩色 高斯模糊 - 开发ing
void BlurPhoto::GaussColorfulDeal(Pixels *tempPixels, int width, int height, int r) {
    // **array是二维数组，是rgb8888 最后的每个像素组成的数组
    double xaver = 0.0, x2aver = 0.0;
    
    for (int h = 0; h < height; h++) {
        
        xaver=0.0, x2aver=0.0;
        for (int w = 0 ; w < width; w++) {
            
            int *pixelsArr = new int[(2*r+1)*(2*r+1)]; // 存储半径内像素
            int *pixTemp = pixelsArr;
            
            int pixelSum = 0;
            int pix2Sum = 0;
            
            for (int j = 0; j <= (2*r); j++) {
                int y = h - r + j;
                
                for (int i = 0; i <= (2*r); i++) {
                    int x = w - r + i;
                    
                    // 除去中心点 和 越界点
                    if ( y < 0 || x < 0 || y >= height || x >= width || (y == h && x == w)) {
                        *pixTemp = 0;
                        pixTemp++;
                        continue;
                    }
                    
                    *pixTemp = tempPixels->getGray(x, y);
                    
                    pixelSum += *pixTemp; // 总数
                    pix2Sum += (*pixTemp) * (*pixTemp); // 总数^2
                    
                    pixTemp++;
                }
            }
            
            /** change End **/
            
            int theNum = tempPixels->getGray(w,h);
            // 开始计算方差
            xaver = (pixelSum - theNum)/((2*r+1)*(2*r+1)-1);
            x2aver = (pix2Sum - theNum*theNum)/((2*r+1)*(2*r+1)-1);
            
            double fc = sqrt(x2aver - xaver*xaver); // 得到方差
            
            // 开始计算权重
            double left = 1/(2*PI*fc*fc);
            
            double *weightArr = new double[(2*r+1)*(2*r+1)]; // 得到权重数组
            int weightArrNum = 0;
            double weightSum = 0.0;
            
            // 周围像素权重
            for (int j = 0; j <= (2*r); j++) {
                int y = r - j;
                int y_real = h - r + j; // 真坐标
                
                for (int i = 0; i <= (2*r); i++) {
                    int x = i - r;
                    int x_real = w - r + i; // 真坐标
                    
                    // 除去中心点
                    if ((x == 0 && y == 0) || y_real < 0 || x_real < 0 || y_real > height || x_real > width) {
                        weightArr[weightArrNum] = 0;
                        weightArrNum++;
                        continue;
                    }
                    
                    double right = pow(e, -(x*x + y*y)/(2*fc*fc));
                    double weight = left*right;
                    
                    weightArr[weightArrNum] = weight;
                    
                    weightArrNum++;
                }
            }
            
            for (int n = 0; n < ((2*r+1)*(2*r+1)); n++) {
                weightSum += weightArr[n];
            }
            
            weightArrNum = 0;
            
            int array_h_w_temp = 0;
            
            // 得到周围像素权重
            for (int j = 0; j <= (2*r); j++) {
                for (int i = 0; i <= (2*r); i++) {
                    weightArr[weightArrNum] /= weightSum;
                    *pixelsArr = (*pixelsArr) * weightArr[weightArrNum]; // 周围像素的 权值 * 像素
                    //                    printf("%3f ",weightArr[weightArrNum]);
                    array_h_w_temp += *pixelsArr;
                    
                    weightArrNum++;
                    pixelsArr++;
                }
            }
            
            this->BlurPixels->rgbMake(w, h, array_h_w_temp, array_h_w_temp, array_h_w_temp);
            
            delete [] weightArr;
            //            delete [] pixelsArr;
            
        }
    }
}


