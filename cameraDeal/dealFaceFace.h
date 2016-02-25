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
+ (UIImage *)blackAndWhiteWithUIImage:(UIImage *)image;
+ (UIImage *)autoConfigUIImage:(UIImage *)image withRed:(int)red withGreen:(int)green withBlue:(int)blue;
@end
