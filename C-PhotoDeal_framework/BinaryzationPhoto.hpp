//
//  BinaryzationPhoto.hpp
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


#ifndef BinaryzationPhoto_hpp
#define BinaryzationPhoto_hpp

#include <stdio.h>
#include <iostream>
#include "Pixels.hpp"

class BinaryzationPhoto {
    Pixels *BinaryPixels = NULL;
    
public:
    
    BinaryzationPhoto(Pixels *p_Pixels) {
        this->BinaryPixels = p_Pixels;
    }
    
    ~BinaryzationPhoto() {
        BinaryPixels = NULL;
    }
    
    void binaryzation(int wRadius, int hRadius, int width, int height);
    
    // 二值化后边缘检测
    void binaryCanny(int **cannyArr,int wRadius, int hRadius, int width, int height);
    
private:
    
protected:
    
};

#endif /* BinaryzationPhoto_hpp */
