//
//  BinaryzationPhoto.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/1.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

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
