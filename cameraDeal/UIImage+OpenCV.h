//
//  UIImage+OpenCV.h
//  cameraDeal
//
//  Created by numberwolf on 16/2/21.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIImage (UIImage_OpenCV)

+(UIImage *)imageWithCVMat:(const cv::Mat&)cvMat;
-(id)initWithCVMat:(const cv::Mat&)cvMat;

@property(nonatomic, readonly) cv::Mat CVMat;
@property(nonatomic, readonly) cv::Mat CVGrayscaleMat;

@end