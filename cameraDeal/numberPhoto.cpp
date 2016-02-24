//
//  numberPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/2/22.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "numberPhoto.hpp"
#define CUT_NUM 100 // 块大小
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
    int **temp = new int*[height];
    
//    uint32_t *temp = pixels;
//    printf("start");
    
    for (int j = 0; j < height; j++) {
        gray_arr[j] = new int[width];
        temp[j] = new int[width];
        
        for (int i = 0; i < width; i++) {
            uint32_t *currentPixel = pixels + (j * height) + i;
            uint32_t color = *currentPixel;
            
            gray_arr[j][i] = (R(color)+G(color)+B(color))/3.0;
            temp[j][i] = gray_arr[j][i];
        }
    }
    

    // 进行处理
    int temps = 0;
//    printf("开\n");
    for (int j = 0; j < height; j++) {
        
//        for (int i = 0; i < width; i++) {
        for (int i = 0; i < width; i+=CUT_NUM) {
            int fc = fangcha(gray_arr[j], i, i+CUT_NUM);
            
            for (int n = i; n < (i + CUT_NUM); n++) {
                temps = temp[j][n-1];
                
//                if (fc < 20) {
                    if ((gray_arr[j][n] - temps) > (fc/4)) {
                        gray_arr[j][n] = 0;
                    } else {
                        gray_arr[j][n] = 255;
                    }
//                }
            }
        }
        
//        printf("结束一行\n\n");
        
    }
    /*
     if (i == 0) {
        temp = (int)gray_arr[j][i-1];
     }
     
     if ((int)(gray_arr[j][i] - temp) > 10) {
         temp = gray_arr[j][i];
         gray_arr[j][i] = 0;
     } else {
         temp = gray_arr[j][i];
         gray_arr[j][i] = 255;
     }
     */
    
//    for (int i = 0 ; i<length; i++) {
//        printf("%3d ",pixels_temp[i]);
//    }
//    printf("\n.............\n");
    
    printf("输出最后的数组开\n");
    
    // 每个像素
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            uint32_t *currentPixel = pixels + (j * height) + i;
            
            *currentPixel = RGBAMake(gray_arr[j][i], gray_arr[j][i], gray_arr[j][i], A(*currentPixel));
        }
    }
    
    free(gray_arr);
    free(temp);
    
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

