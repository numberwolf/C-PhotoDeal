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
    //DATA data;
    //treeData *left;
    
    numberPhoto() {
        //this->data = da;
        //this->left = NULL;
    }
    
    ~numberPhoto() {}
    
    // 黑白 边缘 二值化
    static void blackAndWhite(uint32_t *pixels, unsigned long width, unsigned long height);
    
private:
    static int GetSumOfArray(int *array, int start, int count);
    static double fangcha(int x[], int start, int end);
    
protected:
    
};
