//
//  dealFaceFace.m
//  cameraDeal
//
//  Created by numberwolf on 16/2/20.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#import "dealFaceFace.h"

#define Mask8(x) ( (x) & 0xFF )
#define R(x) ( Mask8(x) )
#define G(x) ( Mask8(x >> 8 ) )
#define B(x) ( Mask8(x >> 16) )
#define A(x) ( Mask8(x >> 24) )
#define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )

@implementation dealFaceFace
+ (UIImage *)blackAndWhiteWithUIImage:(UIImage *)image {
    /***************************
     *                         *
     *           Start         *
     *                         *
     ***************************/
    
    
    // 1.定义了一些简单处理32位像素的宏。为了得到红色通道的值，你需要得到前8位。为了得到其它的颜色通道值，你需要进行位移并取截取。
    CGImageRef inputCGImage = [image CGImage];
    NSUInteger width = CGImageGetWidth(inputCGImage);
    NSUInteger height = CGImageGetHeight(inputCGImage);
    
    // 2.定义一个指向第一个像素的指针，并使用2个for循环来遍历像素。其实也可以使用一个for循环从0遍历到width*height，但是这样写更容易理解图形是二维的。
    NSUInteger bytesPerPixel = 4;
    NSUInteger bytesPerRow = bytesPerPixel * width;
    NSUInteger bitsPerComponent = 8;
    
    UInt32 * pixels;
    
    pixels = (UInt32 *) calloc(height * width,     sizeof(UInt32));
    
    // 3.得到当前像素的值赋值给currentPixel并把它的亮度值打印出来。
    CGColorSpaceRef colorSpace =     CGColorSpaceCreateDeviceRGB();
    CGContextRef context =     CGBitmapContextCreate(pixels, width, height,     bitsPerComponent, bytesPerRow, colorSpace,     kCGImageAlphaPremultipliedLast |     kCGBitmapByteOrder32Big);
    
    // 4.增加currentPixel的值，使它指向下一个像素。如果你对指针的运算比较生疏，记住这个：currentPixel是一个指向UInt32的变量，当你把它加1后，它就会向前移动4字节（32位），然后指向了下一个像素的值。
    CGContextDrawImage(context, CGRectMake(0,     0, width, height), inputCGImage);
    
    
//        NSLog(@"Brightness of image:");
//        // 2.
//        UInt32 * currentPixel = pixels;
//        for (NSUInteger j = 0; j < height; j++) {
//            for (NSUInteger i = 0; i < width; i++) {
//                // 3.
//                UInt32 color = *currentPixel;
//                printf("%3.0f ",(R(color)+G(color)+B(color))/3.0);
//                // 4.
//                currentPixel++;
//            }
//            printf("\n");
//        }
    
    // Convert the image to black and white
    for (NSUInteger i = 0; i < width; i++) {
        for (NSUInteger j = 0; j < height; j++) {
            
            UInt32 * currentPixel = pixels + (j * width) + i;
            UInt32 color = *currentPixel;
            
            // Average of RGB = greyscale
            UInt32 averageColor = (R(color) + G(color) + B(color)) / 3.0;
            
            *currentPixel = RGBAMake(averageColor, averageColor, averageColor, A(color));
        }
    }
    
    // Create a new UIImage
    CGImageRef newCGImage = CGBitmapContextCreateImage(context);
    // 旋转90度
    UIImage * processedImage = [UIImage imageWithCGImage:newCGImage scale:1 orientation:UIImageOrientationRight];
//    UIImage * processedImage = [UIImage imageWithCGImage:newCGImage];
    
    // Free up the context and color space
    CGColorSpaceRelease(colorSpace);
    CGContextRelease(context);
    CGImageRelease(newCGImage);
    free(pixels);

    
    return processedImage;
}

+ (UIImage *)autoConfigUIImage:(UIImage *)image withRed:(int)red withGreen:(int)green withBlue:(int)blue{

    
    // 1.定义了一些简单处理32位像素的宏。为了得到红色通道的值，你需要得到前8位。为了得到其它的颜色通道值，你需要进行位移并取截取。
    CGImageRef inputCGImage = [image CGImage];
    NSUInteger width = CGImageGetWidth(inputCGImage);
    NSUInteger height = CGImageGetHeight(inputCGImage);
    
    // 2.定义一个指向第一个像素的指针，并使用2个for循环来遍历像素。其实也可以使用一个for循环从0遍历到width*height，但是这样写更容易理解图形是二维的。
    NSUInteger bytesPerPixel = 4;
    NSUInteger bytesPerRow = bytesPerPixel * width;
    NSUInteger bitsPerComponent = 8;
    
    UInt32 * pixels;
    
    pixels = (UInt32 *) calloc(height * width,     sizeof(UInt32));
    
    // 3.得到当前像素的值赋值给currentPixel并把它的亮度值打印出来。
    CGColorSpaceRef colorSpace =     CGColorSpaceCreateDeviceRGB();
    CGContextRef context =     CGBitmapContextCreate(pixels, width, height,     bitsPerComponent, bytesPerRow, colorSpace,     kCGImageAlphaPremultipliedLast |     kCGBitmapByteOrder32Big);
    
    // 4.增加currentPixel的值，使它指向下一个像素。如果你对指针的运算比较生疏，记住这个：currentPixel是一个指向UInt32的变量，当你把它加1后，它就会向前移动4字节（32位），然后指向了下一个像素的值。
    CGContextDrawImage(context, CGRectMake(0,     0, width, height), inputCGImage);
    
    // Convert the image to black and white
    for (NSUInteger i = 0; i < width; i++) {
        for (NSUInteger j = 0; j < height; j++) {
            
            UInt32 * currentPixel = pixels + (j * width) + i;
            UInt32 color = *currentPixel;
            
            // Average of RGB = greyscale
//            UInt32 averageColor = (R(color) + G(color) + B(color)) / 3.0;
            
            *currentPixel = RGBAMake(R(color)+red, G(color)+green, B(color)+blue, A(color));
        }
    }
    
    // Create a new UIImage
    CGImageRef newCGImage = CGBitmapContextCreateImage(context);
    // 旋转90度
    UIImage * processedImage = [UIImage imageWithCGImage:newCGImage scale:1 orientation:UIImageOrientationRight];
//    UIImage * processedImage = [UIImage imageWithCGImage:newCGImage];
    
    // Free up the context and color space
    CGColorSpaceRelease(colorSpace);
    CGContextRelease(context);
    CGImageRelease(newCGImage);
    free(pixels);
    
    
    return processedImage;
}
@end
