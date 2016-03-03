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
    
    // (y,x)->(h,w)
    for (int j = 0, i = 0; j < height, i < width; j+=hRadius, i+=wRadius) {
        
        for (int y = j, x = i; y < (j+hRadius), x < (i+wRadius); y++,x++) {
            // 开始求平均数和方差 计算权值
        }
    }
}
