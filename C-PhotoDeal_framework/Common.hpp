//
//  Common.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/2.
//  Copyright © 2016年 numberwolf. All rights reserved.
//
/**************************************************************************
 * Email：porschegt23@foxmail.com || numberwolf11@gmail.com
 * Github:https://github.com/numberwolf
 * APACHE 2.0 LICENSE
 * Copyright [2016] [Chang Yanlong]
 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 **************************************************************************/


#ifndef Common_hpp
#define Common_hpp

#include <stdio.h>
#include <iostream>
#include <math.h>

/**  Common 共用Define **/
#define GRAY_RED_POINT 0.299
#define GRAY_GREEN_POINT 0.587
#define GRAY_BLUE_POINT 0.114

#define e 2.71828
#define PI 3.1416

#define Mask8(x) ( (x) & 0xFF )
#define R(x) ( Mask8(x) )
#define G(x) ( Mask8(x >> 8 ) )
#define B(x) ( Mask8(x >> 16) )
#define A(x) ( Mask8(x >> 24) )
#define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )

class Common {
    
public:
    Common() {}
    ~Common() {}
    
    template<typename T>
    static T GetAverage(T *array, int offset, int limit) {
        T sum = 0;
        
        for (int i = offset; i < (limit - offset); i++) {
            sum += array[i];
        }
        
        return sum/(limit - offset);
    }
    
    // 方差
    template<typename T>
    static double GetVariance(T *array, int offset, int limit) {
        
        //求数组x（具有n个元素）的方差:S=(<x^2>-<x>)^0.5
        double xaver=0.0, x2aver=0.0;
        
        for(int i = offset;i < (limit - offset); ++i){
            xaver+=array[i]; x2aver+=array[i]*array[i];
        }
        
        xaver/=limit; x2aver/=limit; //求x的平均、x^2的平均
        return sqrt(x2aver-xaver*xaver);
    }
    
    // 标准差
    template<typename T>
    static double GetStandard(T *array, int offset, int limit) {
        
        double sum = 0.0f;
        double average = GetAverage(array, offset, limit);
        
        for (int i = offset; i < (limit - offset); i++) {
            sum += (array[i] - average) * (array[i] - average);
        }
        
        return sqrt(sum/limit);
    }
    
private:
    
protected:
    
};

#endif /* Common_hpp */

