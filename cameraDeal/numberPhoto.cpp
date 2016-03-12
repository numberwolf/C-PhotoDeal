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
#include "Pixels.hpp"

#define e 2.71828
#define PI 3.1416
#define GRAY_RED_POINT 0.299
#define GRAY_GREEN_POINT 0.587
#define GRAY_BLUE_POINT 0.114

#define Mask8(x) ( (x) & 0xFF )
#define R(x) ( Mask8(x) )           // 红色通道
#define G(x) ( Mask8(x >> 8 ) )     // 绿色通道
#define B(x) ( Mask8(x >> 16) )     // 蓝色通道
#define A(x) ( Mask8(x >> 24) )     // 透明度通道
#define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )

void numberPhoto::blackAndWhite(uint32_t *pixels, unsigned long width, unsigned long height) {
    printf("测试一数据：\n");
    Pixels *pixel = new Pixels(pixels,width,height);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            /**
             pixels:
             如果选择(2,3)的话，则pixels + (1 * height) + 2;
             
             [{a,b,c},{d,e,f},{g,h,i}]
             
             ^
             |
             |
             
             [{a,   {d,   {g,
               b,    e,    h,
               c} ,  f} ,  i}]
             
             **/
            
//            uint32_t *currentPixel = pixels + (i * width) + j;
//            uint32_t color = *currentPixel;
            
            // Average of RGB = greyscale
            uint32_t averageColor = (pixel->getRed(j, i) + pixel->getGreen(j, i) + pixel->getBlue(j, i)) / 3.0;
            averageColor > 200?printf("255 ") : printf("    ");
            
        }
        printf("\n");
    }
    
    // 进行临时赋值处理
    int **gray_arr = new int*[height];
    int **temp = new int*[height];
    
    //printf("width:%d,height:%d\n",(int)width,(int)height); // 480,360
    /*       w
      h  {  [1,2,3]
            [a,b,c] }
     */
    
    printf(">>>----测试2数据：\n");
    uint32_t *currentPixel = pixels;
    for (int j = 0; j < height; j++) {
        gray_arr[j] = new int[width];
        temp[j] = new int[width];
        for (int i = 0; i < width; i++) {
            // 3
            uint32_t color = *currentPixel;
            
            /*** 两种求灰度值的方法 第二种更标准 ***/
            //int averageColor = (R(color)+G(color)+B(color))/3.0;
            uint32_t gray_color = (uint32_t)(R(color) * GRAY_RED_POINT + G(color) * GRAY_GREEN_POINT + B(color) * GRAY_BLUE_POINT);
            
            gray_arr[j][i] = gray_color;
            temp[j][i] = gray_color;
            // 4.
            currentPixel++;
            
            gray_color > 200?printf("255 ") : printf("    ");
        }
        printf("\n");
    }
    
    BlurPhoto::GaussDeal(gray_arr, temp, (int)width, (int)height, 3); // 灰度图高斯模糊
//    BinaryzationPhoto::binaryzation(gray_arr, 40, 30, width, height); // 二值
/*    边缘 */
//    BinaryzationPhoto::edgeExamine(temp, 40, 30, width, height);
//    BinaryzationPhoto::edgeExamine(gray_arr, 40, 40, width, height);
/* */

    
    // 进行处理

    
    // 最终将处理结果赋值过去
    currentPixel = pixels;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            // 3.
            *currentPixel = RGBAMake(gray_arr[j][i], gray_arr[j][i], gray_arr[j][i], A(*currentPixel));
            //*currentPixel = RGBAMake(0xff-R(*currentPixel), 0xff-G(*currentPixel), 0xff-B(*currentPixel), A(*currentPixel));
            
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

