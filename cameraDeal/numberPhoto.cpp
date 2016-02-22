//
//  numberPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/2/22.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "numberPhoto.hpp"
#define CUT_NUM 30 // 块大小
#define Mask8(x) ( (x) & 0xFF )
#define R(x) ( Mask8(x) )
#define G(x) ( Mask8(x >> 8 ) )
#define B(x) ( Mask8(x >> 16) )
#define A(x) ( Mask8(x >> 24) )
#define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )

uint32_t* numberPhoto::blackAndWhite(uint32_t *pixels, int width, int height) {
    int length = width * height;
    uint32_t *pixels_temp = new uint32_t[length];
    
    uint32_t *temp = pixels;
    int num = 0;
    
//    int CUT_NUM = width/10;
    
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            uint32_t *currentPixel = temp + (j * height) + i;
            uint32_t color = *currentPixel;

            int grey = (R(color)+G(color)+B(color))/3.0;
            
            pixels_temp[num] = grey; // 把所有灰度保存进来
            num++;
        }
    }
    
//    // 进行处理
//    for (int n = 0; n < length; n+=CUT_NUM) {
//        int average = 0;
//        
//        int littleTemp = length - n;
//        int Count = 0;
//        
//        if (littleTemp < CUT_NUM) {
//            Count = littleTemp;
//            
//        } else {
//            Count = CUT_NUM;
//        }
//        
//        average = GetSumOfArray(pixels_temp, n, Count)/Count;
//
//        for (int j = 0; j < Count; j++) {
//
//            if (average >= 200) {
////                if (pixels_temp[j+n] > average) {
//                    pixels_temp[j+n] = 255;
////                } else {
////                    pixels_temp[j+n] = 0;
////                }
//            } else {
//                pixels_temp[j+n] = 0;
//            }
//            
//        }
//    }
    
//    for (int i = 0 ; i<length; i++) {
//        printf("%3d ",pixels_temp[i]);
//    }
//    printf("\n.............\n");
    
    
    int numVal = 0;
    // 每个像素
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            uint32_t *currentPixel = pixels + (j * height) + i;
            uint32_t color = *currentPixel;
            
            uint32_t averageColor = pixels_temp[numVal];

            numVal++;
            
            *currentPixel = RGBAMake(averageColor, averageColor, averageColor, A(color));
        }

    }
    
    return pixels;
}

int numberPhoto::GetSumOfArray(uint32_t *array, int start, int count) {
    int sum = 0;
    
    for (int j = 0; j < count; j++) {
        int num = start + j;
        sum += array[num];
    }
    
    return sum;
}

