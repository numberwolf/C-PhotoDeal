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

#endif /* Pixels_hpp */

/**
 图形像素点 数据结构
 **/

class Pixels {
    uint32_t *my_pixels;
    
public:
    Pixels(uint32_t *pixels){
        this->my_pixels = pixels;
    }
    
    ~Pixels(){}
    
    uint32_t getRed(int x, int y);
    uint32_t getGreen(int x, int y);
    uint32_t getBlue(int x, int y);
    
    uint32_t changeRed(int x, int y);
    uint32_t changeGreen(int x, int y);
    uint32_t changeBlue(int x, int y);
    
    uint32_t rgbMake(uint32_t R, uint32_t G, uint32_t B);
    
private:
    
protected:
    
};