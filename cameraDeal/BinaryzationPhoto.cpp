//
//  BinaryzationPhoto.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/1.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "BinaryzationPhoto.hpp"
#include "Common.hpp"
#include <math.h>

#pragma mark 边缘检测
void BinaryzationPhoto::edgeExamine(int **array, int wRadius, int hRadius ,int width, int height) {
    
    for (int j = 0; j < height; j+=hRadius) {
        for (int i = 0; i < width; i+=wRadius) {
            
            // (y,x)->(h,w)
            int *localArr = new int[wRadius*hRadius];
            int *pointer = localArr;
            
            // 将范围内的添加进数组
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        *pointer = 0;
                    } else {
                        *pointer = array[y][x];
                    }
                    
                    pointer++;
                }
            } // 添加结束
            
            // 标准差
            int standard = Common::GetStandard(localArr, 0, wRadius*hRadius);
            // 平均数
            int average = Common::GetAverage(localArr, 0, wRadius*hRadius);
            
            // 范围内处理
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        continue;
                    } else {
                        if (array[y][x] > (average - standard) && array[y][x] < (average + standard)) {
                            array[y][x] = 255;
                        } else {
                            array[y][x] = 0;
                        }
                    }
                    
                }
            } // 处理结束
            
            pointer = NULL;
            delete [] localArr;
            
        }
    }
}

// 区域二值化
void BinaryzationPhoto::binaryzation(int **array, int wRadius, int hRadius, int width, int height) {
    
    for (int j = 0; j < height; j+=hRadius) {
        for (int i = 0; i < width; i+=wRadius) {
            
            // (y,x)->(h,w)
            int *localArr = new int[wRadius*hRadius];
            int *pointer = localArr;
            
            // 将范围内的添加进数组
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        *pointer = 0;
                    } else {
                        *pointer = array[y][x];
                    }
                    
                    pointer++;
                }
            } // 添加结束
            
            // 标准差
            //int standard = Common::GetStandard(localArr, 0, wRadius*hRadius);
            
            // 平均数
            int average = Common::GetAverage(localArr, 0, wRadius*hRadius);
            
            // 范围内处理
            for (int y = j; y < (j+hRadius); y++) {
                for (int x = i; x < (i+wRadius); x++) {
                    
                    if (x >= width || y >= height) {
                        continue;
                    } else {
                        if (array[y][x] > average) {
                            array[y][x] = 255;
                        } else {
                            array[y][x] = 0;
                        }
                    }
                    
                }
            } // 处理结束
            
            pointer = NULL;
            delete [] localArr;
            
        }
    }
}
