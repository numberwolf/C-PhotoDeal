//
//  numberPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/2/22.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "numberPhoto.hpp"
//#define CUT_NUM 5 // 块大小
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

void numberPhoto::blackAndWhite(uint32_t *pixels, unsigned long width, unsigned long height) {
    
    // 进行临时赋值处理
    int **gray_arr = new int*[height];
    int **temp = new int*[height];
    int CUT_NUM = (int)width/20;
    printf("width:%d,height:%d\n",(int)width,(int)height); // 480,360
    
    for (int i = 0; i < height; i++) {
        gray_arr[i] = new int[width];
        temp[i] = new int[width];
        
        for (int j = 0; j < width; j++) {
            
            uint32_t * currentPixel = pixels + (j * height) + i;
            uint32_t color = *currentPixel;
            
            gray_arr[i][j] = (R(color)+G(color)+B(color))/3.0;
            temp[i][j] = (R(color)+G(color)+B(color))/3.0;
        }
    }
    
    // 进行处理
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
        
            double fc = fangcha(gray_arr[i], j, j+CUT_NUM);
            double average = GetSumOfArray(gray_arr[i], j, CUT_NUM)/CUT_NUM;
            
            if ( gray_arr[i][j] <= (average + fc/3) && gray_arr[i][j] >= (average - fc/3) /*&& gray_arr[i][j] > average*/) {
                gray_arr[i][j] = 0;
            } else {
                gray_arr[i][j] = 255;
            }
        }
    }
    

//    // 进行处理
//    int temps = 0;
//    for (int j = 0; j < height; j++) {
//        
//        for (int i = 0; i < width; i+=CUT_NUM) {
//            double fc = fangcha(gray_arr[j], i, i+CUT_NUM);
//            
//            for (int n = i; n < (i + CUT_NUM); n++) {
//                temps = temp[j][n-1];
//                
//                if ((gray_arr[j][n] - temps) > (fc/3)) {
//                    gray_arr[j][n] = 0;
//                } else {
//                    gray_arr[j][n] = 255;
//                }
//            }
//        }
//        
//    }

    
    // 最终将处理结果赋值过去
    // Convert the image to black and white
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            uint32_t * currentPixel = pixels + (j * height) + i;

            *currentPixel = RGBAMake(gray_arr[i][j], gray_arr[i][j], gray_arr[i][j], A(*currentPixel));
        }
    }
    
    /*** save
     for (int i = 0; i < width; i++) {
         for (int j = 0; j < height; j++) {
         
             uint32_t * currentPixel = pixels + (j * width) + i;
             uint32_t color = *currentPixel;
             uint32_t averageColor = (R(color) + G(color) + B(color)) / 3.0;
             
             *currentPixel = RGBAMake(averageColor, averageColor, averageColor, A(color));
         }
     }
     **/
    
    free(gray_arr);
    free(temp);
}

int numberPhoto::GetSumOfArray(int *array, int start, int count) {
    int sum = 0;
    
    for (int j = 0; j < count; j++) {
        int num = start + j;
        sum += array[num];
    }
    
    return sum;
}

double numberPhoto::fangcha(int x[], int start, int end){
    //求数组x（具有n个元素）的方差:S=(<x^2>-<x>)^0.5
    int i;
    double xaver=0.0, x2aver=0.0;
    
    for(i = start;i < end; ++i){
        xaver+=x[i]; x2aver+=x[i]*x[i];
    }
    
    int n = end - start + 1;
    xaver/=n; x2aver/=n; //求x的平均、x^2的平均
    return sqrt(x2aver-xaver*xaver);
}

