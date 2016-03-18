//
//  dealFaceFace.h
//  cameraDeal
//
//  Created by numberwolf on 16/2/20.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreImage/CoreImage.h>
#import <CoreGraphics/CoreGraphics.h>


@interface dealFaceFace : NSObject
+ (UIImage *)autoConfigUIImage:(UIImage *)image with_deal_CODE:(void (^)(UInt32 *pixels,NSUInteger width,NSUInteger height))block;
+ (UIImage *)GaussBlurMyImage:(UIImage *)image andBlurValue:(int)value ;
+ (UIImage *)BinaryMyImage:(UIImage *)image wRadius:(int)wRadius hRadius:(int)hRadius;
+ (UIImage *)CannyMyImage:(UIImage *)image wRadius:(int)wRadius hRadius:(int)hRadius;
@end
