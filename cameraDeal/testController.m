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
//    NSString *imgName = @"mailicon.png";
    
    [GCDQueue executeInMainQueue:^{
        [weakSelf.protoImg setImage:[UIImage imageNamed:imgName]];
    }];
    [GCDQueue executeInGlobalQueue:^{
//        UIImage *deal = [dealFaceFace GaussBlurMyImage:[UIImage imageNamed:imgName] andBlurValue:2];
        UIImage *deal = [UIImage imageNamed:imgName];
        
        [GCDQueue executeInMainQueue:^{
            [weakSelf.protoImg setImage:deal];
        }];
        
        UIImage *after_deal = [dealFaceFace CannyMyImage:deal wRadius:80 hRadius:80];
//        UIImage *after_deal = [dealFaceFace BinaryMyImage:deal wRadius:80 hRadius:80];
        
//          UIImage *after_deal = [dealFaceFace PointyMyImage:deal Radius:10];
//          UIImage *after_deal = [dealFaceFace PointyFixMyImage:deal wRadius:80 hRadius:80];
        [GCDQueue executeInMainQueue:^{
            weakSelf.deaImg.image = after_deal;
        }];
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


@end
