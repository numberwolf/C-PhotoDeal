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

/*****
 for (NSUInteger i = 0; i < width; i++) {
     for (NSUInteger j = 0; j < height; j++) {
     
         UInt32 * currentPixel = pixels + (j * width) + i;
         UInt32 color = *currentPixel;
         
         // Average of RGB = greyscale
         UInt32 averageColor = (R(color) + G(color) + B(color)) / 3.0;
         if (averageColor > 120 && averageColor <130) {
            *currentPixel = RGBAMake(0, 0, 0, A(color));
         } else {
            *currentPixel = RGBAMake(255, 255, 255, A(color));
         }
         
         //            *currentPixel = RGBAMake(R(color)+red, G(color)+green, B(color)+blue, A(color));
     }
 }
 *****/

uint32_t* numberPhoto::blackAndWhite(uint32_t *pixels, int width, int height) {
    int **gray_arr = new int*[height];
    
    uint32_t *temp = pixels;
    printf("start");
    
    for (int j = 0; j < height; j++) {
        gray_arr[j] = new int[width];
        
        for (int i = 0; i < width; i++) {
            uint32_t *currentPixel = pixels + (j * height) + i;
            uint32_t color = *currentPixel;

            int grey = (R(color)+G(color)+B(color))/3.0;
            
            gray_arr[j][i] = grey;
        }
    }
    
    // 进行处理
    for (int j = 0; j < height; j++) {
        int average = GetSumOfArray(gray_arr[j], 0, width)/width;
        
        for (int i = 0; i < width; i ++) {
            if (average >= 220) {
                gray_arr[j][i] = 255;
            } else {
                if (gray_arr[j][i] < average) {
                    gray_arr[j][i] = 0;
                } else {
                    gray_arr[j][i] = 255;
                }
            }
        }
        
    }
    
//    for (int i = 0 ; i<length; i++) {
//        printf("%3d ",pixels_temp[i]);
//    }
//    printf("\n.............\n");
    
    
    // 每个像素
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            uint32_t *currentPixel = pixels + (j * height) + i;
            uint32_t color = *currentPixel;
            
            uint32_t averageColor = gray_arr[j][i];
            printf("%3d ",gray_arr[j][i]);
            
            *currentPixel = RGBAMake(averageColor, averageColor, averageColor, A(color));
        }
        printf("\n");
    }
    
    free(gray_arr);
    
    return pixels;
}

int numberPhoto::GetSumOfArray(int *array, int start, int count) {
    int sum = 0;
    
    for (int j = 0; j < count; j++) {
        int num = start + j;
        sum += array[num];
    }
    
    return sum;
}

