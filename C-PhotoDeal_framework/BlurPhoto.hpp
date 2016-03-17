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

class BlurPhoto {
    
public:
    
    BlurPhoto() {
    }
    
    ~BlurPhoto() {}
    
    static void GaussDeal(int **array, int **temp, int width, int height, int r);
    
private:
    
protected:
    
};

#endif /* BlurPhoto_hpp */
