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
    NSString *imgName = @"psd.jpg";
//    NSString *imgName = @"mailicon.png";
    
    [GCDQueue executeInMainQueue:^{
        [weakSelf.protoImg setImage:[UIImage imageNamed:imgName]];
    }];
    [GCDQueue executeInGlobalQueue:^{
        UIImage *deal = [dealFaceFace BlurMyImage:[UIImage imageNamed:imgName] andBlurValue:3];
        [GCDQueue executeInMainQueue:^{
            weakSelf.deaImg.image = deal;
        }];
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


@end
