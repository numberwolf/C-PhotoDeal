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

#import "UIImage+OpenCV.h"
#import <TesseractOCR/TesseractOCR.h>

#define navBarHeight    44.
#define markViewTag    100

#define METHOD_CANNY 100
#define METHOD_BINARY 101
#define METHOD_GAUSS 102
#define METHOD_PROTYPE 103
#define METHOD_PIONTY 104

const int kCannyAperture = 7;

@interface ViewController ()<AVCaptureVideoDataOutputSampleBufferDelegate> {
    int _METHOD_CHOSE_TAG;
}

@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property NSData *mData;
@property (nonatomic, retain) AVCaptureSession *session;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setupCaptureSession];
    self.imageView.image = [UIImage imageNamed:@"mailicon.png"];
    _METHOD_CHOSE_TAG = METHOD_PROTYPE;

}

- (void)setupCaptureSession
{
    NSError *error = nil;
    

    self.session = [[AVCaptureSession alloc] init] ;
    
    self.session.sessionPreset = AVCaptureSessionPresetMedium;
    

    AVCaptureDevice *device = [AVCaptureDevice
                               defaultDeviceWithMediaType:AVMediaTypeVideo];//这里默认是使用后置摄像头，你可以改成前置摄像头
    

    AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:device
                                                                        error:&error];
    if (!input) {

    } else {
        [self.session addInput:input];
        
        AVCaptureVideoDataOutput *output = [[AVCaptureVideoDataOutput alloc] init];
        [self.session addOutput:output];
        
        dispatch_queue_t queue = dispatch_queue_create("myQueue", NULL);
        [output setSampleBufferDelegate:self queue:queue];
        //    dispatch_release(queue);
        
        output.videoSettings = [NSDictionary dictionaryWithObjectsAndKeys:
                                [NSNumber numberWithInt:kCVPixelFormatType_32BGRA], kCVPixelBufferPixelFormatTypeKey,
                                [NSNumber numberWithInt: self.view.frame.size.width], (id)kCVPixelBufferWidthKey,
                                [NSNumber numberWithInt: self.view.frame.size.height], (id)kCVPixelBufferHeightKey,
                                nil]; // 320,240

        [self.session startRunning];

    }
    
}

#pragma mark 对于视频输出流进行帧处理
-(void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    __weak typeof(self) weakSelf = self;
    
    UIImage *image = [self imageFromSampleBuffer:sampleBuffer];
    //    self.mData = UIImageJPEGRepresentation(image, 0.5);//这里的mData是NSData对象，后面的0.5代表生成的图片质量
    
    UIImage *temp;
    
    if (_METHOD_CHOSE_TAG == METHOD_GAUSS) {
        temp = [dealFaceFace GaussBlurMyImage:image andBlurValue:3];
    } else if (_METHOD_CHOSE_TAG == METHOD_CANNY) {
        temp = [dealFaceFace CannyMyImage:image wRadius:150 hRadius:150 scanScaleOfRadius:10];
    } else if (_METHOD_CHOSE_TAG == METHOD_BINARY) {
        temp = [dealFaceFace BinaryMyImage:image wRadius:100 hRadius:100 scanScaleOfRadius:10];
    } else if (_METHOD_CHOSE_TAG == METHOD_PROTYPE) {
        temp = [dealFaceFace autoConfigUIImage:image with_deal_CODE:^(UInt32 *pixels, NSUInteger width, NSUInteger height) {
        }];
    } else if (_METHOD_CHOSE_TAG == METHOD_PIONTY) {
        temp = [dealFaceFace PointyMyImage:image Radius:10];
    } else {
        temp = [dealFaceFace autoConfigUIImage:image with_deal_CODE:^(UInt32 *pixels, NSUInteger width, NSUInteger height) {
        }];
    }
    
    temp = [self opencvFaceDetect:temp];
    
    [GCDQueue executeInMainQueue:^{
        weakSelf.imageView.image = temp;
    }];
    
}

- (IBAction)cannyButtonClick:(id)sender {
    _METHOD_CHOSE_TAG = METHOD_CANNY;
}

- (IBAction)binaryButtonClick:(id)sender {
    _METHOD_CHOSE_TAG = METHOD_BINARY;
}

- (IBAction)GaussButtonClick:(id)sender {
    _METHOD_CHOSE_TAG = METHOD_GAUSS;
}

- (IBAction)pointyButtonClick:(id)sender {
    _METHOD_CHOSE_TAG = METHOD_PIONTY;
}

- (IBAction)protypeButtonClick:(id)sender {
    _METHOD_CHOSE_TAG = METHOD_PROTYPE;
}

- (IplImage *)CreateIplImageFromUIImage:(UIImage *)image {
    // Getting CGImage from UIImage
    CGImageRef imageRef = image.CGImage;
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    // Creating temporal IplImage for drawing
    IplImage *iplimage = cvCreateImage(
                                       cvSize(image.size.width,image.size.height), IPL_DEPTH_8U, 4
                                       );
    // Creating CGContext for temporal IplImage
    CGContextRef contextRef = CGBitmapContextCreate(
                                                    iplimage->imageData, iplimage->width, iplimage->height,
                                                    iplimage->depth, iplimage->widthStep,
                                                    colorSpace, kCGImageAlphaPremultipliedLast|kCGBitmapByteOrderDefault
                                                    );
    // Drawing CGImage to CGContext
    CGContextDrawImage(
                       contextRef,
                       CGRectMake(0, 0, image.size.width, image.size.height),
                       imageRef
                       );
    CGContextRelease(contextRef);
    CGColorSpaceRelease(colorSpace);
    
    // Creating result IplImage
    IplImage *ret = cvCreateImage(cvGetSize(iplimage), IPL_DEPTH_8U, 3);
    cvCvtColor(iplimage, ret, CV_RGBA2BGR);
    cvReleaseImage(&iplimage);
    
    return ret;
}


-(UIImage *) opencvFaceDetect:(UIImage *)originalImage {
    cvSetErrMode(CV_ErrModeParent);
    
    IplImage *image = [self CreateIplImageFromUIImage:originalImage];
    
    // Scaling down
    IplImage *small_image = cvCreateImage(cvSize(image->width/2,image->height/2), IPL_DEPTH_8U, 3);
    cvPyrDown(image, small_image, CV_GAUSSIAN_5x5);
    int scale = 2;
    
    // Load XML
    NSString *path = [[NSBundle mainBundle] pathForResource:@"haarcascade_frontalface_alt2" ofType:@"xml"];
    CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad([path cStringUsingEncoding:NSASCIIStringEncoding], NULL, NULL, NULL);
    CvMemStorage* storage = cvCreateMemStorage(0);
    
    // Detect faces and draw rectangle on them
    CvSeq* faces = cvHaarDetectObjects(small_image, cascade, storage, 1.2f, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(20, 20), cvSize(100, 100));
    cvReleaseImage(&small_image);
    
    NSLog(@"found %d faces in image", faces->total);
    
    // Create canvas to show the results
    CGImageRef imageRef = originalImage.CGImage;
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef contextRef = CGBitmapContextCreate(NULL, originalImage.size.width, originalImage.size.height, 8, originalImage.size.width * 4,
                                                    colorSpace, kCGImageAlphaPremultipliedLast|kCGBitmapByteOrderDefault);
    CGContextDrawImage(contextRef, CGRectMake(0, 45, originalImage.size.width, originalImage.size.height), imageRef);
    
    CGContextSetLineWidth(contextRef, 4);
    CGContextSetRGBStrokeColor(contextRef, 0.0, 0.0, 1.0, 0.5);
    
    // Draw results on the iamge
    for(int i = 0; i < faces->total; i++) {
        
        // Calc the rect of faces
        CvRect cvrect = *(CvRect*)cvGetSeqElem(faces, i);
        CGRect face_rect = CGContextConvertRectToDeviceSpace(contextRef,
                                                             CGRectMake(cvrect.x * scale, cvrect.y * scale, cvrect.width * scale, cvrect.height * scale));
        CGContextStrokeRect(contextRef, face_rect);
        
    }
    
    UIImage *returnImage = [UIImage imageWithCGImage:CGBitmapContextCreateImage(contextRef) scale:1 orientation:UIImageOrientationRight];
    CGContextRelease(contextRef);
    CGColorSpaceRelease(colorSpace);
    
    cvReleaseMemStorage(&storage);
    cvReleaseHaarClassifierCascade(&cascade);
    
    return returnImage;
}



/**
#pragma mark 抽轮廓
// Perform image processing on the last captured frame and display the results
cv::Mat processFrame(cv::Mat _lastFrame, int code_one, int code_two)
{
    double t = (double)cv::getTickCount();
    
    cv::Mat grayFrame, output;
    
    // Convert captured frame to grayscale
    cv::cvtColor(_lastFrame, grayFrame, cv::COLOR_RGB2GRAY);
    
    // Perform Canny edge detection using slide values for thresholds
    cv::Canny(grayFrame, output,
              code_one * kCannyAperture * kCannyAperture,
              code_two * kCannyAperture * kCannyAperture,
              kCannyAperture);
    
    t = 1000 * ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    

    return rotateMat(output,1);
}

// 旋转
cv::Mat rotateMat(cv::Mat mat,int flipCode) {
    cv::Mat temp,temp_second;
    transpose(mat, temp);
    flip(temp, temp_second, 1);
    
    return temp_second;
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
    
    __weak typeof(self) weakSelf = self;
    if ([features count]==0) {
        NSLog(@">>>>> 人脸监测【失败】啦 ～！！！");
        [GCDQueue executeInMainQueue:^{
            weakSelf.infoLabel.text = @"检测中";
        }];
        
        return;
    }
    
    
    NSLog(@">>>>> 人脸监测【成功】～！！！>>>>>> ");
    dispatch_async(dispatch_get_main_queue(), ^{
        weakSelf.infoLabel.text = @">>>>> 人脸监测【成功】啦 ～！！！";
        [weakSelf markAfterFaceDetect:features];
    });
    
}


// 人脸标识 ---  方块
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
        _face.backgroundColor = [UIColor clearColor];
        _face.layer.borderWidth = 2;
        _face.layer.borderColor = [UIColor yellowColor].CGColor;
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
    }
}

******/


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
    
    // Create an image object from the Quartz image
    UIImage *image = [UIImage imageWithCGImage:quartzImage];
//    UIImage *image = [UIImage imageWithCGImage:quartzImage scale:1 orientation:UIImageOrientationRight];
    
    // Free up the context and color space
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    // Release the Quartz image ARC无法自动管理cgimage内存
    CGImageRelease(quartzImage);
    
    return (image);
}
@end
