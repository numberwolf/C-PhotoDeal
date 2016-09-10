//
//  CannyPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/9/10.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "CannyPhoto.hpp"
#include "Common.hpp"
#include <math.h>

void CannyPhoto::sobelCanny(int width, int height){
    // 定义sobel数组常量长度
    const int sobel_len = 9;
    
    int sobel_y[sobel_len] = {
        1,2,1,
        0,0,0,
        -1,-2,-1
    };  //sobel算子
    int sobel_x[sobel_len] = {
        1,0,-1,
        2,0,-2,
        1,0,-1
    };
//    int sobel_l[sobel_len] = {
//        2,1,0,
//        1,0,-1,
//        0,-1,-2
//    };
//    int sobel_r[sobel_len] = {
//        0,1,2,
//        -1,0,1,
//        -2,-1,0
//    };
    
    int a[9],k;
    
    int **temp_data = new int*[height];
    
    for (int j = 0; j < height; j++) {
        temp_data[j] = new int[width];
        
        for (int i = 0; i < width; i++) {
            temp_data[j][i] = this->CannyPixels->getGray(i, j);
            
        }
    }
    
    for (int y = 1; y < height-1; y++) {
        for (int x = 1; x < width-1; x++) {
            /****/
            int grayx = 0;
            int grayy = 0;
//            int grayl = 0;
//            int grayr = 0;
            
            a[0] = temp_data[y-1][x-1];
            a[1] = temp_data[y][x-1];
            a[2] = temp_data[y+1][x-1];
            
            a[3] = temp_data[y-1][x];
            a[4] = temp_data[y][x];
            a[5] = temp_data[y+1][x];
            
            a[6] = temp_data[y-1][x+1];
            a[7] = temp_data[y][x+1];
            a[8] = temp_data[y+1][x+1];
            
            for(k = 0;k < 9;k++)
                grayy+=a[k]*sobel_y[k];
            for(k = 0;k < 9;k++)
                grayx+=a[k]*sobel_x[k];
//            for(k = 0;k < 9;k++)
//                grayl+=a[k]*sobel_l[k];
//            for(k = 0;k < 9;k++)
//                grayr+=a[k]*sobel_r[k];
            
            int px = grayx + grayy ;//+ grayl + grayr
//            printf("%3d\r\n",px);
            px = (px<0?0:px);
            
            this->CannyPixels->rgbMake(x, y, px, px, px, 255);
            /****/
        }
    }
}
