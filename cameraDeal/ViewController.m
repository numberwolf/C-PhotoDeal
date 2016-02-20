//
//  ViewController.m
//  cameraDeal
//
//  Created by numberwolf on 16/2/20.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "ViewController.h"
#import "GCD.h"
#import "dealFaceFace.h"

#define navBarHeight    44.
#define markViewTag    100

@interface ViewController ()<AVCaptureVideoDataOutputSampleBufferDelegate> {
    CGRect      rectFaceDetect;
    UIView      *_face;
    UIView      *_eye_left;
    UIView      *_eye_right;
    
}
@property (weak, nonatomic) IBOutlet UISlider *redSilder;
@property (weak, nonatomic) IBOutlet UISlider *greenSlider;
@property (weak, nonatomic) IBOutlet UISlider *blueSlider;

@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UILabel *infoLabel;
@property NSData *mData;
@property (nonatomic, retain) AVCaptureSession *session;


@property int redNum;
@property int greenNum;
@property int blueNum;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.redNum = 1;
    [self setupCaptureSession];
    self.imageView.image = [UIImage imageNamed:@"mailicon.png"];
    
    _face = [UIView new];
    _eye_left = [UIView new];
    _eye_right = [UIView new];
    [self.imageView addSubview:_face];
    [self.imageView addSubview:_eye_left];
    [self.imageView addSubview:_eye_right];
}

// Create and configure a capture session and start it running
- (void)setupCaptureSession
{
    NSError *error = nil;
    
    // Create the session
    self.session = [[AVCaptureSession alloc] init] ;
    
    // Configure the session to produce lower resolution video frames, if your
    // processing algorithm can cope. We'll specify medium quality for the
    // chosen device.
    self.session.sessionPreset = AVCaptureSessionPresetMedium;
    
    // Find a suitable AVCaptureDevice
    AVCaptureDevice *device = [AVCaptureDevice
                               defaultDeviceWithMediaType:AVMediaTypeVideo];//这里默认是使用后置摄像头，你可以改成前置摄像头
    
    // Create a device input with the device and add it to the session.
    AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:device
                                                                        error:&error];
    if (!input) {
        // Handling the error appropriately.
    }
    [self.session addInput:input];
    
    // Create a VideoDataOutput and add it to the session
    AVCaptureVideoDataOutput *output = [[AVCaptureVideoDataOutput alloc] init];
    [self.session addOutput:output];
    
    // Configure your output.
    dispatch_queue_t queue = dispatch_queue_create("myQueue", NULL);
    [output setSampleBufferDelegate:self queue:queue];
//    dispatch_release(queue);
    
    // Specify the pixel format
   	output.videoSettings = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSNumber numberWithInt:kCVPixelFormatType_32BGRA], kCVPixelBufferPixelFormatTypeKey,
                            [NSNumber numberWithInt: 320], (id)kCVPixelBufferWidthKey,
                            [NSNumber numberWithInt: 240], (id)kCVPixelBufferHeightKey,
                            nil];
    
//    AVCaptureVideoPreviewLayer* preLayer = [AVCaptureVideoPreviewLayer layerWithSession: self.session];
//    
//    //preLayer = [AVCaptureVideoPreviewLayer layerWithSession:session];
////    preLayer.frame = CGRectMake(0, 0, 320, 240);
//    preLayer.frame = CGRectMake(0, self.view.frame.size.height/2, self.view.frame.size.width, self.view.frame.size.height/2);
//    
//    preLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
//    [self.view.layer addSublayer:preLayer];
//    // If you wish to cap the frame rate to a known value, such as 15 fps, set
//    // minFrameDuration.
//    output.minFrameDuration = CMTimeMake(1, 15);
    
    // Start the session running to start the flow of data
    [self.session startRunning];
    
    // Assign session to an ivar.
    //[self setSession:session];
}

-(void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    
    //    [GCDQueue executeInGlobalQueue:^{
    // Create a UIImage from the sample buffer data
    UIImage *image = [self imageFromSampleBuffer:sampleBuffer];
//    self.mData = UIImageJPEGRepresentation(image, 0.5);//这里的mData是NSData对象，后面的0.5代表生成的图片质量
    
    //    NSLog(@"图片:%@",self.mData);
    //    CIImage *ciimage = [[CIImage alloc] initWithImage:image];
    //    CIFilter *filter = [CIFilter filterWithName:@"CIPixellate"];
    //    [filter setValue:ciimage forKey:kCIInputImageKey];
    //    [filter setDefaults];
    //    CIImage *outputImage = [filter valueForKey:kCIOutputImageKey];
    //    CIContext *content = [CIContext contextWithOptions:nil];
    //    CGImageRef cgimage = [content createCGImage:outputImage fromRect:[outputImage extent]];
    

    [self faceDetect:image];

    [GCDQueue executeInMainQueue:^{
//        self.imageView.image = [UIImage imageWithData:self.mData];
//        self.imageView.image = [UIImage imageWithCGImage:cgimage];
//        self.imageView.image = [dealFaceFace blackAndWhiteWithUIImage:image];
        self.imageView.image = [dealFaceFace autoConfigUIImage:image withRed:self.redNum withGreen:self.greenNum withBlue:self.blueNum];
    }];
//    }];
    
    
//    CATransition *transition = [CATransition animation];
//    transition.duration = 2.0f;
//    transition.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
//    transition.type = kCATransitionFade;
//    [self.imageView.layer addAnimation:transition forKey:nil];

}

#pragma mark - 人脸检测方法
- (void)faceDetect:(UIImage *)aImage
{
    
    //Create a CIImage version of your photo
    CIImage* image = [CIImage imageWithCGImage:aImage.CGImage];
    
    //create a face detector
    //此处是CIDetectorAccuracyHigh，若用于real-time的人脸检测，则用CIDetectorAccuracyLow，更快
    NSDictionary  *opts = [NSDictionary dictionaryWithObject:CIDetectorAccuracyHigh
                                                      forKey:CIDetectorAccuracy];
    CIDetector* detector = [CIDetector detectorOfType:CIDetectorTypeFace
                                              context:nil
                                              options:opts];
    
    //Pull out the features of the face and loop through them
    NSArray* features = [detector featuresInImage:image];
    
    if ([features count]==0) {
        NSLog(@">>>>> 人脸监测【失败】啦 ～！！！");
        return;
    }
    
    
    NSLog(@">>>>> 人脸监测【成功】～！！！>>>>>> ");
    dispatch_async(dispatch_get_main_queue(), ^{
        self.infoLabel.text = @">>>>> 人脸监测【成功】啦 ～！！！";
        [self markAfterFaceDetect:features];
    });
    
}


//人脸标识
-(void)markAfterFaceDetect:(NSArray *)features
{

    if ([features count] == 0) {
        UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Failed"
                                                       message:@"The face detecting failed"
                                                      delegate:self
                                             cancelButtonTitle:@"Ok"
                                             otherButtonTitles:nil, nil];
        [alert show];
        return;
    }
    
    for (CIFaceFeature *f in features)
    {
        
        //旋转180，仅y
        CGRect aRect = f.bounds;
        aRect.origin.y = self.imageView.bounds.size.height - aRect.size.height - aRect.origin.y;//self.bounds.size
        
        _face.frame = aRect;
        _face.tag = markViewTag;
        [_face setTransform:CGAffineTransformMakeScale(1, -1)];
        _face.backgroundColor = [UIColor redColor];
        _face.alpha = 0.6;

        
        rectFaceDetect = aRect;
        
        
        NSLog(@"%@",NSStringFromCGRect(f.bounds));
        if (f.hasLeftEyePosition){

            
            printf("Left eye %g %g\n", f.leftEyePosition.x, f.leftEyePosition.y);
            
            _eye_left.frame = CGRectMake(0, 0, 10, 10);
            _eye_left.tag = markViewTag;
            //旋转180，仅y
            CGPoint newCenter =  f.leftEyePosition;
            newCenter.y = self.imageView.bounds.size.height-newCenter.y;
            _eye_left.center = newCenter;
            
            _eye_left.backgroundColor = [UIColor yellowColor];
            [_eye_left setTransform:CGAffineTransformMakeScale(1, -1)];
            _eye_left.alpha = 0.6;

        }
        if (f.hasRightEyePosition)
        {

            printf("Right eye %g %g\n", f.rightEyePosition.x, f.rightEyePosition.y);
            
            _eye_right.frame = CGRectMake(0, 0, 10, 10);
            _eye_right.tag = markViewTag;
            //旋转180，仅y
            CGPoint newCenter =  f.rightEyePosition;
            newCenter.y = self.imageView.bounds.size.height-newCenter.y;
            _eye_right.center = newCenter;
            
            _eye_right.backgroundColor = [UIColor blueColor];
            [_eye_right setTransform:CGAffineTransformMakeScale(1, -1)];
            _eye_right.alpha = 0.6;

        }
//        if (f.hasMouthPosition)
//        {
//            
//            printf("Mouth %g %g\n", f.mouthPosition.x, f.mouthPosition.y);
//            
//            UIView *faceView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, 10, 10)];
//            faceView.tag = markViewTag;
//            //旋转180，仅y
//            CGPoint newCenter =  f.mouthPosition;
//            newCenter.y = self.imageView.bounds.size.height-newCenter.y;
//            faceView.center = newCenter;
//            
//            faceView.backgroundColor = [UIColor greenColor];
//            [faceView setTransform:CGAffineTransformMakeScale(1, -1)];
//            faceView.alpha = 0.6;
//            [self.imageView addSubview:faceView];
//            faceView = nil;
//            [faceView removeFromSuperview];
//            
//        }
    }
}




#pragma mark 红色调节
- (IBAction)redSilder:(id)sender {
    self.redNum = (int)self.redSilder.value;
//    NSLog(@"数值红色：%d",self.redNum);
}

#pragma mark 绿色调节
- (IBAction)greenSlider:(id)sender {
    self.greenNum = (int)self.greenSlider.value;
//    NSLog(@"绿色红色：%d",self.greenNum);
}

#pragma mark 蓝色调节
- (IBAction)blueSlider:(id)sender {
    self.blueNum = (int)self.blueSlider.value;
//    NSLog(@"蓝色红色：%d",self.blueNum);
}



// Create a UIImage from sample buffer data
- (UIImage *) imageFromSampleBuffer:(CMSampleBufferRef) sampleBuffer
{
    // Get a CMSampleBuffer's Core Video image buffer for the media data
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    // Lock the base address of the pixel buffer
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    // Get the number of bytes per row for the pixel buffer
    void *baseAddress = CVPixelBufferGetBaseAddress(imageBuffer);
    
    // Get the number of bytes per row for the pixel buffer
    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(imageBuffer);
    // Get the pixel buffer width and height
    size_t width = CVPixelBufferGetWidth(imageBuffer);
    size_t height = CVPixelBufferGetHeight(imageBuffer);
    
    // Create a device-dependent RGB color space
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    
    // Create a bitmap graphics context with the sample buffer data
    CGContextRef context = CGBitmapContextCreate(baseAddress, width, height, 8,
                                                 bytesPerRow, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
    
    // CGImageRef!核心图形库
    // Create a Quartz image from the pixel data in the bitmap graphics context
    CGImageRef quartzImage = CGBitmapContextCreateImage(context);
    
    // Unlock the pixel buffer
    CVPixelBufferUnlockBaseAddress(imageBuffer,0);
    
    // Free up the context and color space
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    
    // Create an image object from the Quartz image
    //UIImage *image = [UIImage imageWithCGImage:quartzImage];
    UIImage *image = [UIImage imageWithCGImage:quartzImage scale:1.0f orientation:UIImageOrientationRight];
    
    // Release the Quartz image ARC无法自动管理cgimage内存
    CGImageRelease(quartzImage);
    
    return (image);
}

/**********

-(void)click:(UIButton *)btn{
    
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    imagePicker.delegate = self;
    //    imagePicker.view.frame = s
    if([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]){
        imagePicker.sourceType = UIImagePickerControllerSourceTypeCamera;
        
    }
    // imagePicker.allowsEditing = YES;
    //    [self.view addSubview:imagePicker.view];
    [self presentViewController:imagePicker animated:YES completion:^{
        
    }];
}


- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingImage:(UIImage *)image editingInfo:(NSDictionary *)editingInfo {
    
}
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
    [self dismissViewControllerAnimated:YES completion:nil];
    NSLog(@"%@",info);
    UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
    
    self.image.image  =  image;
}
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    [self dismissViewControllerAnimated:YES completion:^{
        
    }];
}
 
 ******/

@end
