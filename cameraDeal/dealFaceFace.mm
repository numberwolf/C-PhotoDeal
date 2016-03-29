//
//  dealFaceFace.m
//  cameraDeal
//
//  Created by numberwolf on 16/2/20.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#import "dealFaceFace.h"
#import "numberPhoto.hpp"

@implementation dealFaceFace

- (instancetype)init{
    if (self = [super init]) {

    }
    
    return self;
}

+ (UIImage *)autoConfigUIImage:(UIImage *)image with_deal_CODE:(void (^)(UInt32 *pixels,NSUInteger width,NSUInteger height))block{

    CGImageRef inputCGImage = [image CGImage];
    NSUInteger width = CGImageGetWidth(inputCGImage);
    NSUInteger height = CGImageGetHeight(inputCGImage);
    
    NSUInteger bytesPerPixel = 4;
    NSUInteger bytesPerRow = bytesPerPixel * width;
    NSUInteger bitsPerComponent = 8;
    
    UInt32 *pixels;
    
    pixels = (UInt32 *) calloc(height * width,     sizeof(UInt32));
    
    CGColorSpaceRef colorSpace =     CGColorSpaceCreateDeviceRGB();
    CGContextRef context =     CGBitmapContextCreate(pixels, width, height,     bitsPerComponent, bytesPerRow, colorSpace,     kCGImageAlphaPremultipliedLast |     kCGBitmapByteOrder32Big);

    CGContextDrawImage(context, CGRectMake(0,     0, width, height), inputCGImage);

    /*****************
     *     START     *
     numberPhoto *numberPhotoObj = new numberPhoto(pixels,width,height);
     numberPhotoObj->method_one();
     *****************/
    
    block(pixels,width,height);
    
    /*****************
     *      END      *
     *****************/

    CGImageRef newCGImage = CGBitmapContextCreateImage(context);
    // 旋转90度
//    UIImage * processedImage = [UIImage imageWithCGImage:newCGImage scale:1 orientation:UIImageOrientationRight];
    UIImage * processedImage = [UIImage imageWithCGImage:newCGImage];
    
    // Free up the context and color space
    CGColorSpaceRelease(colorSpace);
    CGContextRelease(context);
    CGImageRelease(newCGImage);
    
    delete [] pixels;
    
    return processedImage;
}

+ (UIImage *)GaussBlurMyImage:(UIImage *)image andBlurValue:(int)value{
    __weak typeof(self) weakSelf = self;

    return [dealFaceFace autoConfigUIImage:image with_deal_CODE:^(UInt32 *pixels, NSUInteger width, NSUInteger height) {
        numberPhoto::method_one(pixels, width, height, value);
    }];
}

+ (UIImage *)BinaryMyImage:(UIImage *)image wRadius:(int)wRadius hRadius:(int)hRadius scanScaleOfRadius:(int)scanScaleOfRadius{
    return [dealFaceFace autoConfigUIImage:image with_deal_CODE:^(UInt32 *pixels, NSUInteger width, NSUInteger height) {
        numberPhoto::method_two(pixels, width, height, false, wRadius, hRadius, scanScaleOfRadius);
    }];
}

+ (UIImage *)CannyMyImage:(UIImage *)image wRadius:(int)wRadius hRadius:(int)hRadius scanScaleOfRadius:(int)scanScaleOfRadius {
    return [dealFaceFace autoConfigUIImage:image with_deal_CODE:^(UInt32 *pixels, NSUInteger width, NSUInteger height) {
        numberPhoto::method_two(pixels, width, height, true, wRadius, hRadius, scanScaleOfRadius);
    }];
}

+ (UIImage *)PointyMyImage:(UIImage *)image Radius:(int)Radius {
    return [dealFaceFace autoConfigUIImage:image with_deal_CODE:^(UInt32 *pixels, NSUInteger width, NSUInteger height) {
        numberPhoto::method_three(pixels, width, height ,Radius);
    }];
}

+ (UIImage *)PointyFixMyImage:(UIImage *)image wRadius:(int)wRadius hRadius:(int)hRadius {
    return [dealFaceFace autoConfigUIImage:image with_deal_CODE:^(UInt32 *pixels, NSUInteger width, NSUInteger height) {
        numberPhoto::method_four(pixels, width, height, wRadius, hRadius);
    }];
}

+(UIImage *)otsuBinaryMyImage:(UIImage *)image {
    return [dealFaceFace autoConfigUIImage:image with_deal_CODE:^(UInt32 *pixels, NSUInteger width, NSUInteger height) {
        numberPhoto::otsuBinary(pixels, width, height);
    }];
}

@end
