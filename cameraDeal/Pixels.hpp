//
//  Pixels.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/12.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#ifndef Pixels_hpp
#define Pixels_hpp

#include <stdio.h>

/***
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
 ***/

#endif /* Pixels_hpp */

/**
 图形像素点 数据结构
 **/

class Pixels {
    uint32_t *my_pixels = NULL;
    uint32_t width = NULL;
    uint32_t height = NULL;
    
public:
    Pixels(uint32_t *pixels, uint32_t width, uint32_t height){
        this->my_pixels = pixels;
        this->width = width;
        this->height = height;
    }
    
    ~Pixels(){
        this->my_pixels = NULL;
    }
    
    uint32_t getRed(int x, int y);
    uint32_t getGreen(int x, int y);
    uint32_t getBlue(int x, int y);
    uint32_t getAlpha(int x, int y);
    
    uint32_t changeRed(int x, int y, uint32_t newValue);
    uint32_t changeGreen(int x, int y, uint32_t newValue);
    uint32_t changeBlue(int x, int y, uint32_t newValue);
    uint32_t changeAlpha(int x, int y, uint32_t newValue);
    
    uint32_t rgbMake(uint32_t R, uint32_t G, uint32_t B);
    
private:
    uint32_t *getColorPixel(int x, int y);
    
protected:
    
};