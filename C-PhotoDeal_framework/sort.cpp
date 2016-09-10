//
//  sort.cpp
//  cameraDeal
//
//  Created by numberwolf on 16/9/10.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

#include "sort.hpp"
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}
#define SWAP_ELEMENT_WITH_ARRAY(array,i,j){int temp = array[i];array[i]=array[j];array[j]=temp;}

#pragma mark 冒泡排序
void normalSort::bubbleSort(int originArray[],int len){
    //    sortPrintf(originArray, len); // 原始数据
    
    for (int i = len; i > 0; i--) {;
        for (int j = 0; j < i; j++) {
            int k = j+1;
            if (originArray[j] > originArray[k]) {
                SWAP_ELEMENT_WITH_ARRAY(originArray, j, k);
            }
        }
    }
//    printf("\n冒泡排序:\n");
//    sortPrintf(originArray, len);
}

#pragma mark 快速排序
void normalSort::quickSort(int originArray[], int left, int right, int len){
    if (left < right){
        int low = Partition(originArray, left, right);
        quickSort(originArray, left, low - 1, len); // 递归调用
        quickSort(originArray, low + 1, right, len);
    }
    
    int tempLen = right-left+1;
    if (tempLen == len) {
//        printf("\n快速排序:\n");
        sortPrintf(originArray, right-left+1);
    }
}

// 获取中间数
int normalSort::Partition(int originArray[],int i,int j){
    int low = i, high = j, x = originArray[i];
    while (low < high)
    {
        // 从右向左找第一个小于x的数
        while(low < high && originArray[high]>= x)
            high--;
        if(low < high)
            originArray[low++] = originArray[high];
        // 从左向右找第一个大于等于x的数
        while(low < high && originArray[low]< x)
            low++;
        if(low < high)
            originArray[high--] = originArray[low];
    }
    
    return low;
    
} //partition

#pragma mark 插入排序
void normalSort::insertSort(int *originArray, int len){
    
    for (int i = 1; i < len; i++) {
        for (int j = 0; j < i; j++) {
            if (originArray[j] > originArray[i]) {
                SWAP_ELEMENT_WITH_ARRAY(originArray, i, j);
            }
        }
    }
    
//    printf("\n插入排序:\n");
    sortPrintf(originArray, len);
}

#pragma mark 分治归并排序
void normalSort::mergeSort(int *originArray, int left, int right){
    if (left < right) {
        int center = (right + left)/2;
        mergeSort(originArray, left, center);
        mergeSort(originArray, center + 1, right);
        merge(originArray, left, center, right);
    }
    
    int tempLen = right-left+1;
    if (tempLen == 10) {
//        printf("\n分治归并排序:\n");
        sortPrintf(originArray, tempLen);
    }
}

void normalSort::merge(int *originArray, int left, int center, int right){
    
    int firstArrCount = center - left + 1; // 第一个数组的个数
    int secondArrCount = right - center; // 第二个数组的个数
    
    // 两个临时数组储存数据
    int firstArray[firstArrCount];
    int secondArray[secondArrCount];
    
    // 分成两部分之后重新赋值
    for (int i = 0; i < firstArrCount; i++) {
        firstArray[i] = originArray[left + i];
    }
    
    for (int j = 0; j < secondArrCount; j++) {
        secondArray[j] = originArray[center + j + 1];
    }
    
    // 哨兵牌
    firstArray[firstArrCount] = 10000000;
    secondArray[secondArrCount] = 10000000;
    
    // 给数组进行发牌排序
    for (int i = 0, j = 0, originNum = left; originNum <= right; originNum++) {
        if (firstArray[i] <= secondArray[j]) {
            originArray[originNum] = firstArray[i];
            i++;
        }else{
            originArray[originNum] = secondArray[j];
            j++;
        }
    }
}

#pragma mark 选择排序
void normalSort::choseSort(int *originArray, int len){
    int tempArray[len];
    
    for (int i = 0; i < len; i++) {
        int min_element = originArray[i];
        
        for (int j = i; j < len; j++) {
            if (originArray[j] < min_element) {
                min_element = originArray[j];
            }
        }
        tempArray[i] = min_element;
    }
    
//    printf("\n选择排序:\n");
    sortPrintf(originArray, len);
}

#pragma mark 希尔排序
void normalSort::shellSort(int *originArray, int len, int shellNum){
    for (int i = shellNum; i > 0; i--) {
        for (int j = 0; j + shellNum < len; j++) {
            mergeSort(originArray, j, j + shellNum);
        }
    }
    
//    printf("\n希尔排序:\n");
    sortPrintf(originArray, len);
}

#pragma mark 输出数组
void normalSort::sortPrintf(int originArray[],int len){
    for (int i = 0; i < len; i++) {
        printf("%d",originArray[i]);
    }
//    printf("\n以上为排序之后,长度:%d\n\n",len);
}

