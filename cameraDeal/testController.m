//
//  testController.m
//  cameraDeal
//
//  Created by numberwolf on 16/2/25.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#import "testController.h"
#import "GCD.h"
#import "dealFaceFace.h"

@interface testController ()
@property (weak, nonatomic) IBOutlet UIImageView *protoImg;
@property (weak, nonatomic) IBOutlet UIImageView *deaImg;

@end

@implementation testController

- (void)viewDidLoad {
    [super viewDidLoad];
    __weak typeof(self) weakSelf = self;
//    NSString *imgName = @"psd.jpg";
    NSString *imgName = @"ferrari.png";
//    NSString *imgName = @"test";
    
    [GCDQueue executeInMainQueue:^{
        [weakSelf.protoImg setImage:[UIImage imageNamed:imgName]];
    }];
    [GCDQueue executeInGlobalQueue:^{
//        UIImage *deal = [dealFaceFace GaussBlurMyImage:[UIImage imageNamed:imgName] andBlurValue:2];
        UIImage *deal = [UIImage imageNamed:imgName];
        
        [GCDQueue executeInMainQueue:^{
            [weakSelf.protoImg setImage:deal];
        }];
        
//        UIImage *after_deal = [dealFaceFace otsuCannytMyImage:deal wRadius:150 hRadius:150];
//        UIImage *after_deal = [dealFaceFace BinaryMyImage:deal wRadius:80 hRadius:80 scanScaleOfRadius:20];
//        UIImage *after_deal = [dealFaceFace otsuBinaryMyImage:deal wRadius:80 hRadius:80];// Cannyt
//        UIImage *after_deal = [dealFaceFace PointyMyImage:deal Radius:10];
        UIImage *after_deal = [dealFaceFace sobelCannyMyImage:deal];
        
//        [dealFaceFace testMyImage:deal];
        

        [GCDQueue executeInMainQueue:^{
//            weakSelf.deaImg.image = deal;
            weakSelf.deaImg.image = after_deal;
        }];
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


@end
