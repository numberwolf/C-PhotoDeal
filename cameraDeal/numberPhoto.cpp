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
     
    
    ReduceNoise(gray_arr, temp,(int)width, (int)height, 0, 0);
    
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
}

void numberPhoto::RectCanny(int **array, int width, int height) {
    int calcula = 0;
    bool letWhite = false;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (array[i][j] == 0) {
                calcula ++;
            } else {
                calcula = 0;
                letWhite = false;
            }
            
            if (calcula >= 3) {
                letWhite = true;
            } else {
                letWhite = false;
            }
            
            if (letWhite == true) {
                array[i][j] = 255;
            }
        }
    }
}

#pragma mark 降噪
void numberPhoto::ReduceNoise(int **array, int **temp, int width, int height, int wStart, int hStart) {
    
    /* h-1,w-1   h-1,w  h-1,w+1
     
       h,w-1     h,w    h,w+1
     
       h+1,w-1   h+1,w  h+1,w+1
     */
    
    // **array是二维数组，是rgb8888 最后的每个像素组成的数组

    for (int h = 0; h < height; h++) {
        for (int w = 0 ; w < width; w++) {
            
            if (h > 0 && w > 0 && h < (height-1) && w < (width - 1)) {
                array[h][w] = (temp[h-1][w-1] + temp[h-1][w] + temp[h-1][w+1] + temp[h][w-1] + temp[h][w+1] + temp[h+1][w-1] + temp[h+1][w] + temp[h+1][w+1])/8;

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

