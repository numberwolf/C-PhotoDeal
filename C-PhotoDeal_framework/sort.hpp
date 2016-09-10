//
//  sort.hpp
//  cameraDeal
//
//  Created by numberwolf on 16/9/10.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#ifndef sort_hpp
#define sort_hpp

#include <stdio.h>
class normalSort {
    
public:
    normalSort(int temp,int tempb){
        this->tempNum = temp;
        this->tempNumb = tempb;
    }
    ~normalSort(){}
    
    void output(){
        printf("\n%d,%d\n",this->tempNum,this->tempNumb);
    }
    
    // static int* shellSort(int* originArray);
    static void bubbleSort(int originArray[],int len);
    
    static void quickSort(int originArray[], int left, int right, int len);
    static int Partition(int originArray[],int i,int j);
    
    static void shellSort(int *originArray, int len, int shellNum);
    static void choseSort(int originArray[],int len);
    static void insertSort(int originArray[],int len);
    
    static void mergeSort(int *originArray, int left, int right);
    static void merge(int originArray[], int left, int center, int right);
    
protected:
    
private:
    static void sortPrintf(int originArray[],int len);
    int tempNum;
    int tempNumb;
    
};

#endif /* sort_hpp */
