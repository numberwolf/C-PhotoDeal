//
//  numberPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/2/22.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include <math.h>
#include "numberPhoto.hpp"
#include "BlurPhoto.hpp"
#include "BinaryzationPhoto.hpp"

#define e 2.71828
#define PI 3.1416

#define Mask8(x) ( (x) & 0xFF )
#define R(x) ( Mask8(x) )
#define G(x) ( Mask8(x >> 8 ) )
#define B(x) ( Mask8(x >> 16) )
#define A(x) ( Mask8(x >> 24) )
#define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )

void numberPhoto::blackAndWhite(uint32_t *pixels, unsigned long width, unsigned long height) {
    
    // 进行临时赋值处理
    int **gray_arr = new int*[height];
    int **temp = new int*[height];
    
    //printf("width:%d,height:%d\n",(int)width,(int)height); // 480,360
    /*       w
      h  {  [1,2,3]
            [a,b,c] }
     */
    
    uint32_t *currentPixel = pixels;
    for (int j = 0; j < height; j++) {
        gray_arr[j] = new int[width];
        temp[j] = new int[width];
        for (int i = 0; i < width; i++) {
            // 3
            uint32_t color = *currentPixel;
            int averageColor = (R(color)+G(color)+B(color))/3.0;
            
            gray_arr[j][i] = averageColor;
            temp[j][i] = averageColor;
            // 4.
            currentPixel++;
        }
    }
     
//    BinaryzationPhoto::binaryzation(gray_arr, 40, 30, width, height); // 二值
/*    
      BinaryzationPhoto::edgeExamine(gray_arr, 40, 40, width, height);
      BinaryzationPhoto::edgeExamine(temp, 20, 20, width, height);
 */
    BlurPhoto::GaussDeal(gray_arr, temp, (int)width, (int)height, 3); // 灰度图高斯模糊
    
    // 进行处理

    
    // 最终将处理结果赋值过去
    // Convert the image to black and white
    currentPixel = pixels;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            // 3.
            *currentPixel = RGBAMake(gray_arr[j][i], gray_arr[j][i], gray_arr[j][i], A(*currentPixel));
            // 4.
            currentPixel++;
        }
    }
    
    delete [] gray_arr;
    delete [] temp;
}


int numberPhoto::GetSumOfArray(int *array, int start, int count) {
    int sum = 0;
    
    for (int j = 0; j < count; j++) {
        int num = start + j;
        sum += array[num];
    }
    
    return sum;
}

#pragma mark 方差
double numberPhoto::fangcha(int x[], int start, int end){
    //求数组x（具有n个元素）的方差:S=(<x^2>-<x>)^0.5
    int i;
    double xaver=0.0, x2aver=0.0;
    
    for(i = start;i <= end; ++i){
        xaver+=x[i]; x2aver+=x[i]*x[i];
    }
    
    int n = end - start + 1;
    xaver/=n; x2aver/=n; //求x的平均、x^2的平均
    return sqrt(x2aver-xaver*xaver);
}

#pragma mark 标准差
double numberPhoto::Standard(int **array, int width, int height, int wStart, int hStart, double average, int count) {
    
    double sum = 0.0f;
    
    for (int i = hStart; i < (hStart + height); i++) {
        for (int j = wStart; j < (wStart + width); j++) {
            
            if (i > height || j > width) {
                continue;
            }
            
            sum += (array[i][j] - average) * (array[i][j] - average);
        }
    }
    
    return sqrt(sum/count);
}

