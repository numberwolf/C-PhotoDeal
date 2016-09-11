####C-PhotoDeal_framework    
* 更新  
    * 2016/09/10,更新sobel算子、中值滤波
    * 2016/03/25,更新OTSU算法 
       
* Email：porschegt23@foxmail.com || numberwolf11@gmail.com       
* Github:https://github.com/numberwolf       
* APACHE 2.0 LICENSE       
* Copyright [2016] [Chang Yanlong]                     
http://www.apache.org/licenses/LICENSE-2.0     

[查看效果图](#pic)           
####类库在C-PhotoDeal_framework目录下，Android或者iOS或者Windows都可以兼用，C++原生  
* C-PhotoDeal_framework(RGB8888)    
    * Pixels.hpp 图像数据结构      
        * Pixels 载入图像
        * getRed 该点红色通道
        * getGreen 该点绿色通道
        * getBlue 该点蓝色通道
        * getAlpha 该点透明度通道
        * rgbMake 改变图像通道值
        * GrayPixels 灰度化

    * Common.hpp 共用数据结构    
        * GetAverage 平均值
        * GetVariance 方差
        * GetStandard 标准差

    * BlurPhoto.hpp 为锐化、模糊算法       
        * GaussDeal 高斯模糊
        * PointyDeal 基础锐化

    * BinaryzationPhoto 二值化和边缘算法       
        * binaryzation 区域二值化
        * binaryCanny 边缘检测

    * numberPhoto.hpp 为滤镜入口       
        * void static method_zero 输出原图
        * void static method_one 模糊图
        * void static method_two 二值化 / 边缘检测
        * void static method_three 锐化图像
        * void static otsuBinary OTSU算法 ---- 2016/03/25更新
        * void static sobelCanny sobel算子 ---- 2016/09/10更新

    * CannyPhoto.hpp 非二值化加成边缘检测算法
        * sobelCanny sobel算子边缘检测算法

    * removeNoisePhoto.hpp 滤波处理
        * mid_remove 中值滤波

                  
                  
<span id="pic" >效果图:</span>                 
<img src="Demo_img/ferrari_yuantu.png" />
<img src="Demo_img/gtr_yuantu.png" />
<img src="Demo_img/otsu_ferrari458.png" />
<img src="Demo_img/binaryCut_gtr.png" />

<img src="Demo_img/sobel_ferrari458.png" />
<img src="Demo_img/canByBinCut_gtr.png" />

<img src="Demo_img/otsyCanny_ferrary458.png" />
<img src="Demo_img/gtr_gauss.png" />

<img src="Demo_img/pointy_ferrari458.png" />




