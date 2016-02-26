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
    //int CUT_NUM = (int)width/20;
    int CUT_NUM_WIDTH = (int)width/20;
    int CUT_NUM_HEIGH = (int)height/20;
    //printf("width:%d,height:%d\n",(int)width,(int)height); // 480,360
    
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
    
//    ReduceNoise(gray_arr, temp,(int)width, (int)height, 0, 0);
    
    // 进行处理
    for (int i = 0; i < height; i+=CUT_NUM_HEIGH) {
        for (int j = 0; j < width; j+=CUT_NUM_WIDTH) {
            /**
            double fc = fangcha(gray_arr[i], j, j+CUT_NUM);
            printf("%3f,%3f\n",fangcha(gray_arr[i], j, j+CUT_NUM),fangcha(gray_arr[i], j, j+CUT_NUM));
            double average = GetSumOfArray(gray_arr[i], j, CUT_NUM)/CUT_NUM;
            
            if ( gray_arr[i][j] <= (average + fc/3) && gray_arr[i][j] >= (average - fc/3) ) {
                gray_arr[i][j] = 0;
            } else {
                gray_arr[i][j] = 255;
            }
            **/
            
            RectHandle(gray_arr, temp,CUT_NUM_WIDTH, CUT_NUM_HEIGH, j, i);
        }
    }

    
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
    for (int h = hStart+1; h < (hStart + height - 1); h++) {
        for (int w = wStart+1; w < (wStart + width - 1); w++) {
            int localAverage = 0;
            
//            if (h == hStart) {
//                /*
//                 h,w-1     h,w    h,w+1
//                 
//                 h+1,w-1   h+1,w  h+1,w+1
//                 */
//                
//                if (w == wStart) {
//                    localAverage = (temp[h][w+1] + temp[h+1][w] + temp[h+1][w+1])/3;
//                } else if (w == (wStart + width -1)) {
//                    localAverage = (temp[h][w-1] + temp[h+1][w-1] + temp[h+1][w])/3;
//                } else {
//                    localAverage = (temp[h][w-1] + temp[h][w+1] + temp[h+1][w-1] + temp[h+1][w] + temp[h+1][w+1])/5;
//                }
//                
//            } else if (h == (hStart + height - 1)) {
//                
//                if (w == wStart) {
//                    localAverage = (temp[h-1][w] + temp[h-1][w+1] + temp[h][w+1])/3;
//                } else if (w == (wStart + width -1)) {
//                    localAverage = (temp[h-1][w-1] + temp[h-1][w] + temp[h][w-1])/3;
//                } else {
//                    localAverage = (temp[h-1][w-1] + temp[h-1][w] + temp[h-1][w+1] + temp[h][w-1] + temp[h][w+1])/5;
//                }
//                
//            } else {
//                
//                if (w == wStart) {
//                    localAverage = (temp[h-1][w] + temp[h-1][w+1] + temp[h][w+1] + temp[h+1][w] + temp[h+1][w+1])/5;
//                } else if (w == (wStart + width -1)) {
//                    localAverage = (temp[h-1][w-1] + temp[h-1][w] + temp[h][w-1] + temp[h+1][w-1] + temp[h+1][w])/5;
//                } else {
//                    localAverage = (temp[h-1][w-1] + temp[h-1][w] + temp[h-1][w+1] + temp[h][w-1] + temp[h][w+1] + temp[h+1][w-1] + temp[h+1][w] + temp[h+1][w+1])/8;
//                }
//                
//                //localAverage = array[h-1][w-1] + array[h-1][w] + array[h-1][w+1] + array[h][w-1] + array[h][w] + array[h][w+1] + array[h+1][w-1] + array[h+1][w] + array[h+1][w+1];
//            }
            localAverage = (array[h-1][w-1] + array[h-1][w] + array[h-1][w+1] + array[h][w-1] + array[h][w+1] + array[h+1][w-1] + array[h+1][w] + array[h+1][w+1])/8;
            
            array[h][w] = localAverage;
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

