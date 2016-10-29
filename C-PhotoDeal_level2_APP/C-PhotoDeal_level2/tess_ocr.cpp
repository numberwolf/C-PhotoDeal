//
//  tess_ocr.cpp
//  C-PhotoDeal_level2
//
//  Created by numberwolf on 2016/10/29.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "tess_ocr.hpp"
#include <tesseract/baseapi.h>
#include <tesseract/strngs.h>
#include <tesseract/renderer.h>

//#include "header.hpp"

using namespace tesseract;

bool tess_orc::scan_eng_string_by_img(char *filename) {
    const char* lang = "eng"; // english
    const char* output_base = "/Users/numberwolf/Documents/XCode&C++/C-PhotoDeal/C-PhotoDeal_level2_APP/C-PhotoDeal_level2/ocr/output_file";
    
    //新建tess基类
    TessBaseAPI tess;
    //初始化
    tess.Init(NULL, lang, OEM_DEFAULT);

    //设置识别模式
    tess.SetPageSegMode(PSM_SINGLE_BLOCK);
    
    FILE* fin = fopen(filename, "rb");
    if (fin == NULL)
    {
	    printf("Cannot open");
        //cout << "Cannot open " << filename << endl;
        return false;
    }
    
    fclose(fin);
    
    TessResultRenderer* renderer = new TessTextRenderer(output_base);
    
    //进行识别
    if (!tess.ProcessPages(filename, NULL, 0, renderer)) {
        printf("Error during processing.\n");
        return false;
    }
    
    delete renderer;
    return true;
}
