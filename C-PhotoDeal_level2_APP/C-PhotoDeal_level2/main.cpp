//
//  main.cpp
//  C-PhotoDeal_level2
//
//  Created by numberwolf on 2016/10/12.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include <iostream>
#include "canny_door.hpp"
#include "numberPhoto.hpp"
using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    char *path = "/Users/numberwolf/Documents/XCode&C++/C-PhotoDeal/C-PhotoDeal_level2_APP/img/cro.jpg";
//    canny_door *CannyDoor = new canny_door(path);
    
    IplImage *ColorImage = cvLoadImage(path);
    int height = ColorImage->height;
    int width = ColorImage->width;
    
//    numberPhoto::sobelCanny(ColorImage, width, height);
//    numberPhoto::otsuBinary(ColorImage, width, height, false, 80, 80);
    numberPhoto::method_two(ColorImage, width, height, false, 500, 500, 1);
    
    
    return 0;
}
