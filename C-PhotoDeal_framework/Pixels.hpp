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
    
    void rgbMake(int x,int y, uint32_t R, uint32_t G, uint32_t B, uint32_t alpha);
    
private:
    uint32_t *getColorPixel(int x, int y);
    
protected:
    
};

#endif /* Pixels_hpp */
