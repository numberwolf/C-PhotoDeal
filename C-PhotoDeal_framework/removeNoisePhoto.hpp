//
//  removeNoisePhoto.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/9/10.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#ifndef removeNoisePhoto_hpp
#define removeNoisePhoto_hpp

#include <stdio.h>
#include <iostream>
#include "Pixels.hpp"
class removeNoisePhoto {
    Pixels *removeNoisePixels = NULL;
    
public:
    
    removeNoisePhoto(Pixels *p_Pixels) {
        this->removeNoisePixels = p_Pixels;
    }
    
    ~removeNoisePhoto() {
        removeNoisePixels = NULL;
    }
    
    void mid_remove(int width, int height, int radius); // 中值滤波
    
private:
    void add_into_arr(int array[], int** temp_data,int x,int y,int endx_len,int endy_len) {
        int num=0;
        for(int i = x; i < x+endx_len;i++) {
            for(int j = y;j < y+endy_len; j++) {
                array[num] = temp_data[j][i];
//                printf("%3d\r\n",*array);
                num++;
            }
            
        }
    }
    
protected:
    
};


#endif /* removeNoisePhoto_hpp */
