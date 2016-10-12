//
//  CannyPhoto.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/9/10.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#ifndef CannyPhoto_hpp
#define CannyPhoto_hpp

#include <stdio.h>
#include "Pixels.hpp"
#include "Common.hpp"
#include <math.h>

class CannyPhoto {
    Pixels *CannyPixels = NULL;
    
public:
    
    CannyPhoto(Pixels *p_Pixels) {
        this->CannyPixels = p_Pixels;
    }
    
    ~CannyPhoto() {
        CannyPixels = NULL;
    }
    
    void sobelCanny(int width, int height);    
private:
    
protected:
    
};


#endif /* CannyPhoto_hpp */
