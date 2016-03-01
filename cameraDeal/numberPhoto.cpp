//
//  numberPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/2/22.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include <math.h>
#include "numberPhoto.hpp"

//#define CUT_NUM 5 // 块大小
#define e 2.71828
#define PI 3.1416

#define Mask8(x) ( (x) & 0xFF )
#define R(x) ( Mask8(x) )
#define G(x) ( Mask8(x >> 8 ) )
#define B(x) ( Mask8(x >> 16) )
#define A(x) ( Mask8(x >> 24) )
#define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )

/*****
 UInt32 * currentPixel = pixels;
 for (NSUInteger j = 0; j < height; j++) {
     for (NSUInteger i = 0; i < width; i++) {
         // 3.
         UInt32 color = *currentPixel;
         int temp = (R(color)+G(color)+B(color))/3.0;
         if(temp > 250) {
             temp = 255;
         } else {
             temp = 0;
         }
         printf("%3d ",temp);

         // 4.
         currentPixel++;
     }
     printf("\n");
 }
 *****/

void numberPhoto::blackAndWhite(uint32_t *pixels, unsigned long width, unsigned long height) {
    
    // 进行临时赋值处理
    int **gray_arr = new int*[height];
    int **temp = new int*[height];
    //int CUT_NUM = (int)width/20;
    int CUT_NUM_WIDTH = (int)width/20;
    int CUT_NUM_HEIGH = (int)height/20;
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
            // 3.
            uint32_t color = *currentPixel;
            int averageColor = (R(color)+G(color)+B(color))/3.0;
            
            gray_arr[j][i] = averageColor;
            temp[j][i] = averageColor;
            // 4.
            currentPixel++;
        }
    }
    
    /*
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (gray_arr[j][i] > 250) {
                printf("255");
            } else {
                printf("   ");
            }
            
        }
        printf("\n");
    }
    printf("结束了\n");*/
     
    
//    GaussDeal(gray_arr, temp, width, height, 1);
    
    // 进行处理
//    for (int i = 0; i < height; i+=CUT_NUM_HEIGH) {
//        for (int j = 0; j < width; j+=CUT_NUM_WIDTH) {
//            /**
//            double fc = fangcha(gray_arr[i], j, j+CUT_NUM);
//            printf("%3f,%3f\n",fangcha(gray_arr[i], j, j+CUT_NUM),fangcha(gray_arr[i], j, j+CUT_NUM));
//            double average = GetSumOfArray(gray_arr[i], j, CUT_NUM)/CUT_NUM;
//            
//            if ( gray_arr[i][j] <= (average + fc/3) && gray_arr[i][j] >= (average - fc/3) ) {
//                gray_arr[i][j] = 0;
//            } else {
//                gray_arr[i][j] = 255;
//            }
//            **/
//            
//            RectHandle(gray_arr, temp,CUT_NUM_WIDTH, CUT_NUM_HEIGH, j, i);
//        }
//    }

    
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
    
    free(gray_arr);
    free(temp);
    
//    int *test = new int[8];
//    test[0] = 14;
//    test[1] = 15;
//    test[2] = 16;
//    test[3] = 24;
//    test[4] = 26;
//    test[5] = 34;
//    test[6] = 35;
//    test[7] = 36;
//    //8.703448
//    
////    printf("\n方差:%3f\n",fangcha(test,0,8));
//    double fangchas = fangcha(test,0,7);
////    double fangchas = 1.5;
//    double left = 1/(2*PI*fangchas*fangchas);
//    double right = pow(e, -2/(2*fangchas*fangchas));
//    double result = left*right;
//    printf("\n%f\n",result);
}

#pragma mark 高斯模糊
void numberPhoto::GaussDeal(int **array, int **temp,int width, int height, int r) {
    /*
     //求数组x（具有n个元素）的方差:S=(<x^2>-<x>)^0.5
     int i;
     double xaver=0.0, x2aver=0.0;
     
     for(i = start;i <= end; ++i){
        xaver+=x[i]; x2aver+=x[i]*x[i];
     }
     
     int n = end - start + 1;
     xaver/=n; x2aver/=n; //求x的平均、x^2的平均
     return sqrt(x2aver-xaver*xaver);
     */
    
    // **array是二维数组，是rgb8888 最后的每个像素组成的数组
    double xaver=0.0, x2aver=0.0;
    for (int h = 0; h < height; h++) {
        
        xaver=0.0, x2aver=0.0;
        for (int w = 0 ; w < width; w++) {

            if (h > 0 && w > 0 && h < (height-1) && w < (width - 1)) {
//                    array[h][w] = (temp[h-1][w-1] + temp[h-1][w] + temp[h-1][w+1] + temp[h][w-1] + temp[h][w+1] + temp[h+1][w-1] + temp[h+1][w] + temp[h+1][w+1])/8;
                
                xaver = (temp[h-1][w-1] + temp[h-1][w] + temp[h-1][w+1] + temp[h][w-1] + temp[h][w+1] + temp[h+1][w-1] + temp[h+1][w] + temp[h+1][w+1])/8;
                x2aver = (temp[h-1][w-1]*temp[h-1][w-1] + temp[h-1][w]*temp[h-1][w] + temp[h-1][w+1]*temp[h-1][w+1] + temp[h][w-1]*temp[h][w-1] + temp[h][w+1]*temp[h][w+1] + temp[h+1][w-1]*temp[h+1][w-1] + temp[h+1][w]*temp[h+1][w] + temp[h+1][w+1]*temp[h+1][w+1])/8;
                
                double fc = sqrt(x2aver - xaver*xaver);
                double left = 1/(2*PI*fc*fc);
                
                double right_one = pow(e, -2/(2*fc*fc));
                double right_two = pow(e, -1/(2*fc*fc));
                
                double weight_one = left*right_one;
                double weight_two = left*right_two;
                
                // (h-1,w-1)-one    (h-1,w)-two     (h-1,w+1)-one
                // (h  ,w-1)-two    (h  ,w)         (h  ,w+1)-two
                // (h+1,w-1)-one    (h+1,w)-two     (h+1,w+1)-one
                
                double sum = weight_one*4 + weight_two*4;
                weight_one /= sum;
                weight_two /= sum;
                
                array[h][w] = temp[h-1][w-1]*weight_one + temp[h-1][w]*weight_two + temp[h-1][w+1]*weight_one + temp[h][w-1]*weight_two + temp[h][w+1]*weight_two + temp[h+1][w-1]*weight_one + temp[h+1][w]*weight_two + temp[h+1][w+1]*weight_one;

            }
        }
    }
}


#pragma mark 矩阵内处理
void numberPhoto::RectHandle(int **array, int **temp,int width, int height, int wStart, int hStart) {
    int sum = 0;
    
    for (int i = hStart; i < (hStart + height); i++) {
        for (int j = wStart; j < (wStart + width); j++) {
            sum += array[i][j];
        }
    }
    
    double average = sum/(width*height);
    
    double standard = Standard(array, width, height, wStart, hStart, average, width*height);
    
    for (int i = hStart; i < (hStart + height); i++) {
        for (int j = wStart; j < (wStart + width); j++) {
            
            if ( array[i][j] < (average + standard/3) && array[i][j] > (average - standard/3)) {
                array[i][j] = 0;
            } else {
                array[i][j] = 255;
            }
        }
    }
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
            sum += (array[i][j] - average) * (array[i][j] - average);
        }
    }
    
    return sqrt(sum/count);
}

