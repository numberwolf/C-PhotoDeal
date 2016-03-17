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


#endif /* BinaryzationPhoto_hpp */

class BinaryzationPhoto {
    
public:
    
    BinaryzationPhoto() {
    }
    
    ~BinaryzationPhoto() {}
    
    static void edgeExamine(int **array, int wRadius, int hRadius, int width, int height);
    static void binaryzation(int **array, int wRadius, int hRadius, int width, int height);
    
    // 二值化后边缘检测
    static void binaryCanny(uint32_t *pixels, int **cannyArr,int wRadius, int hRadius, int width, int height);
    
private:
    
protected:
    
};
