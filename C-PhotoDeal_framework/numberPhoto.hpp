//
//  numberPhoto.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/2/22.
//  Copyright © 2016年 numberwolf. All rights reserved.
//  hahah
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

#ifndef numberPhoto_hpp
#define numberPhoto_hpp

#include <stdio.h>
#include <iostream>

class numberPhoto {
    
public:
    numberPhoto() {
    }
    
    ~numberPhoto() {
    }
    
    // 入口
    static void method_zero(int *pixels, int width, int height);
    static void method_one(int *pixels, int width, int height, int value);
    static void method_two(int *pixels, int width, int height, bool isCanny, int wRadius, int hRadius, int scanScaleOfRadius);
    static void method_three(int *pixels, int width, int height, int Radius);
    static void otsuBinary(int *pixels, int width, int height, bool isCanny, int wRadius, int hRadius);
    
    static void testAction(int *pixels, int width, int height);
    
    static void sobelCanny(int *pixels, int width, int height);
private:
protected:
    
};

#endif /* numberPhoto_hpp */
