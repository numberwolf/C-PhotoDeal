//
//  removeNoisePhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/9/10.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "removeNoisePhoto.hpp"
#include "Common.hpp"
#include "sort.hpp"
#include <math.h>

void removeNoisePhoto::mid_remove(int width, int height, int radius) {
    int **temp_data = new int*[height];
    
    for (int j = 0; j < height; j++) {
        temp_data[j] = new int[width];
        
        for (int i = 0; i < width; i++) {
            temp_data[j][i] = this->removeNoisePixels->getGray(i, j);
        }
    }
    
    for (int y = 0; y < height-radius-1; y++) {
        int y_real = y + radius; // 真坐标
        for (int x = 0; x < width-radius-1; x++) {
            int x_real = radius + x; // 真坐标
            
            int lenX = ((x+radius*2+1))>=width?0:radius*2+1;
            int lenY = ((y+radius*2+1))>=height?0:radius*2+1;
//            printf("lenX=%3d,lenY=%3d;x,y(%3d,%3d)=%3d \r\n",lenX,lenY,x,y,this->removeNoisePixels->getGray(x, y));
            
            int tempSortArr[lenX*lenY];
            
            add_into_arr(tempSortArr, temp_data,x, y, lenX, lenY);
            int mid = normalSort::Partition(tempSortArr, 0, lenX*lenY-1);
//            printf("(%d,%d) = %3d \r\n",x_real,y_real,tempSortArr[mid]);
            
            this->removeNoisePixels->rgbMake(x_real, y_real, tempSortArr[mid], tempSortArr[mid], tempSortArr[mid]);
            
            
        }
    }
    
    delete [] temp_data;
}



