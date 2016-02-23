//
//  numberPhoto.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/2/22.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#ifndef numberPhoto_hpp
#define numberPhoto_hpp

#include <stdio.h>
#include <iostream>
#endif /* numberPhoto_hpp */

class numberPhoto {
    
public:
//    DATA data;
//    treeData *left;
//    treeData *right;
    
    numberPhoto() {
//        this->data = da;
//        this->left = NULL;
//        this->right = NULL;
    }
    
    ~numberPhoto() {}
    
    // 黑白 边缘 二值化
    static uint32_t* blackAndWhite(uint32_t *pixels, int width, int height);
    static int GetSumOfArray(int *array, int start, int count);
    
private:
    
protected:
    
};
