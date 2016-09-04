//
//  BlurPhoto.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/1.
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


#ifndef BlurPhoto_hpp
#define BlurPhoto_hpp

#include <stdio.h>
#include <iostream>
#include "Pixels.hpp"

class BlurPhoto {
    Pixels *BlurPixels = NULL;
public:
    
    
    BlurPhoto(Pixels *p_Pixels) {
        this->BlurPixels = p_Pixels;
    }
    
    ~BlurPhoto() {
        BlurPixels = NULL;
    }
    
    // 高斯模糊（黑白）
    void GaussDeal(Pixels *tempPixels, int width, int height, int r);
    // (彩色)
    void GaussColorfulDeal(Pixels *tempPixels, int width, int height, int r);
    
    // 基本锐化
    void PointyDeal(Pixels *tempPixels, int width, int height, int Radius);

    
private:
    
protected:
    
};

#endif /* BlurPhoto_hpp */
