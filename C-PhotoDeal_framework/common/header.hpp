//
//  header.hpp
//  openCV
//
//  Created by numberwolf on 16/9/15.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#ifndef header_hpp
#define header_hpp

#include<opencv2/opencv.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//#include<opencv2/imgproc/types_c.h>
//#include<opencv2/highgui/highgui.hpp>
//#include<opencv2/core/core.hpp>
////#include<vector>
//#include<opencv2/nonfree/features2d.hpp>
//#include<opencv2/legacy/legacy.hpp>
//#include<opencv2/features2d/features2d.hpp>
//#include<opencv2/calib3d/calib3d.hpp>
//#include<opencv2/video/tracking.hpp>
//#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

/**  Common 共用Define **/
#define GRAY_RED_POINT 0.299
#define GRAY_GREEN_POINT 0.587
#define GRAY_BLUE_POINT 0.114

#define e 2.71828
#define PI 3.1416

#define Mask8(x) ( (x) & 0xFF )
#define R(x) ( Mask8(x) )
#define G(x) ( Mask8(x >> 8 ) )
#define B(x) ( Mask8(x >> 16) )
#define A(x) ( Mask8(x >> 24) )
#define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )

#ifndef BGR_DEFINED
struct BGR
{
    uchar b;
    uchar g;
    uchar r;
};

struct HSV
{
    int h;
    double s;
    double v;
};
#define BGR_DEFINED
#endif


class opencv_cyl_header {
    opencv_cyl_header(){}
    ~opencv_cyl_header(){}
public:
    // BGR(BGR: 0~255)转HSV(H: [0~360), S: [0~1], V: [0~1])
    static void BGR2HSV(BGR &bgr, HSV &hsv)
    {
        double b, g, r;
        double h, s, v;
        double min, max;
        double delta;
        
        b = bgr.b / 255.0;
        g = bgr.g / 255.0;
        r = bgr.r / 255.0;
        
        if (r > g)
        {
            max = MAX(r, b);
            min = MIN(g, b);
        }
        else
        {
            max = MAX(g, b);
            min = MIN(r, b);
        }
        
        v = max;
        delta = max - min;
        
        if (IsEquals(max, 0))
        {
            s = 0.0;
        }
        else
        {
            s = delta / max;
        }
        
        if (max == min)
        {
            h = 0.0;
        }
        else
        {
            if (IsEquals(r, max) && g >= b)
            {
                h = 60 * (g - b) / delta + 0;
            }
            else if (IsEquals(r, max) && g < b)
            {
                h = 60 * (g - b) / delta + 360;
            }
            else if (IsEquals(g, max))
            {
                h = 60 * (b - r) / delta + 120;
            }
            else if (IsEquals(b, max))
            {
                h = 60 * (r - g) / delta + 240;
            }
        }
        
        hsv.h = (int)(h + 0.5);
        hsv.h = (hsv.h > 359) ? (hsv.h - 360) : hsv.h;
        hsv.h = (hsv.h < 0) ? (hsv. h + 360) : hsv.h;
        hsv.s = s;
        hsv.v = v;
    }
    
    // HSV转BGR
    static void HSV2BGR(HSV &hsv, BGR &bgr)
    {
        //hsv.h = ptr[3*x+0];
        //hsv.h = hsv.h + 60;
        //hsv.h = (hsv.h > 359) ? (hsv.h - 360) : hsv.h;
        //hsv.h = (hsv.h < 0)   ? (hsv.h + 360) : hsv.h;
        
        int h = hsv.h;
        double s = hsv. s;
        double v = hsv. v;
        double b = 0.0;
        double g = 0.0;
        double r = 0.0;
        
        int flag = (int)abs(h / 60.0);
        double f = h/60.0 - flag;
        double p = v * (1 - s);
        double q = v * (1 - f*s);
        double t = v * (1 - (1- f)*s);
        
        switch (flag)
        {
            case 0:
                b = p;
                g = t;
                r = v;
                break;
            case 1:
                b = p;
                g = v;
                r = q;
                break;
            case 2:
                b = t;
                g = v;
                r = p;
                break;
            case 3:
                b = v;
                g = q;
                r = p;
                break;
            case 4:
                b = v;
                g = p;
                r = t;
                break;
            case 5:
                b = q;
                g = p;
                r = v;
                break;
            default:
                break;
        }
        
        int blue = int(b * 255);
        bgr.b = (blue > 255) ? 255 : blue;
        bgr.b = (blue < 0) ? 0 : bgr.b;
        
        int green = int(g * 255);
        bgr.g = (green > 255) ? 255 : green;
        bgr.g = (green < 0) ? 0 : bgr.g;
        
        int red = int(r * 255);
        bgr.r = (red > 255) ? 255 : red;
        bgr.r = (red < 0) ? 0 : bgr.r;
    }
    
private:
    static bool IsEquals(double val1 , double val2)
    {
        return fabs(val1 - val2) < 0.001;
    }
protected:
};

#endif /* header_hpp */
