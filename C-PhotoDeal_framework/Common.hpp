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
#include <math.h>
#include<opencv2/opencv.hpp>

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

#ifndef BGR_DEFINED
struct BGR
{
    uchar b;
    uchar g;
    uchar r;
};

struct HSV
{
    int h;
    double s;
    double v;
};
#define BGR_DEFINED
#endif

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
    
    /******
     主要针对OpenCV 进行HSV BGR操作
     ******/
    // BGR(BGR: 0~255)转HSV(H: [0~360), S: [0~1], V: [0~1])
    static void BGR2HSV(BGR &bgr, HSV &hsv)
    {
        double b, g, r;
        double h, s, v;
        double min, max;
        double delta;
        
        b = bgr.b / 255.0;
        g = bgr.g / 255.0;
        r = bgr.r / 255.0;
        
        if (r > g)
        {
            max = MAX(r, b);
            min = MIN(g, b);
        }
        else
        {
            max = MAX(g, b);
            min = MIN(r, b);
        }
        
        v = max;
        delta = max - min;
        
        if (IsEquals(max, 0))
        {
            s = 0.0;
        }
        else
        {
            s = delta / max;
        }
        
        if (max == min)
        {
            h = 0.0;
        }
        else
        {
            if (IsEquals(r, max) && g >= b)
            {
                h = 60 * (g - b) / delta + 0;
            }
            else if (IsEquals(r, max) && g < b)
            {
                h = 60 * (g - b) / delta + 360;
            }
            else if (IsEquals(g, max))
            {
                h = 60 * (b - r) / delta + 120;
            }
            else if (IsEquals(b, max))
            {
                h = 60 * (r - g) / delta + 240;
            }
        }
        
        hsv.h = (int)(h + 0.5);
        hsv.h = (hsv.h > 359) ? (hsv.h - 360) : hsv.h;
        hsv.h = (hsv.h < 0) ? (hsv. h + 360) : hsv.h;
        hsv.s = s;
        hsv.v = v;
    }
    
    // HSV转BGR
    static void HSV2BGR(HSV &hsv, BGR &bgr)
    {
        //hsv.h = ptr[3*x+0];
        //hsv.h = hsv.h + 60;
        //hsv.h = (hsv.h > 359) ? (hsv.h - 360) : hsv.h;
        //hsv.h = (hsv.h < 0)   ? (hsv.h + 360) : hsv.h;
        
        int h = hsv.h;
        double s = hsv. s;
        double v = hsv. v;
        double b = 0.0;
        double g = 0.0;
        double r = 0.0;
        
        int flag = (int)abs(h / 60.0);
        double f = h/60.0 - flag;
        double p = v * (1 - s);
        double q = v * (1 - f*s);
        double t = v * (1 - (1- f)*s);
        
        switch (flag)
        {
            case 0:
                b = p;
                g = t;
                r = v;
                break;
            case 1:
                b = p;
                g = v;
                r = q;
                break;
            case 2:
                b = t;
                g = v;
                r = p;
                break;
            case 3:
                b = v;
                g = q;
                r = p;
                break;
            case 4:
                b = v;
                g = p;
                r = t;
                break;
            case 5:
                b = q;
                g = p;
                r = v;
                break;
            default:
                break;
        }
        
        int blue = int(b * 255);
        bgr.b = (blue > 255) ? 255 : blue;
        bgr.b = (blue < 0) ? 0 : bgr.b;
        
        int green = int(g * 255);
        bgr.g = (green > 255) ? 255 : green;
        bgr.g = (green < 0) ? 0 : bgr.g;
        
        int red = int(r * 255);
        bgr.r = (red > 255) ? 255 : red;
        bgr.r = (red < 0) ? 0 : bgr.r;
    }
    
private:
    static bool IsEquals(double val1 , double val2)
    {
        return fabs(val1 - val2) < 0.001;
    }
    
protected:
    
};

#endif /* Common_hpp */

