//
//  BlurPhoto.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/3/1.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

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
