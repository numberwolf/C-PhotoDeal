//
//  ai_math.hpp
//  openCV
//
//  Created by numberwolf on 2016/9/24.
//  Copyright © 2016年 numberwolf. All rights reserved.
//

/************************************************
 *
 *                  测试转换二进制                 *
 *
 ************************************************
 
char c = 'A';
char S[30];
fflush(stdin);
ai_math::ToBin(c,S);
int ascii_c = ai_math::getASCII(c);
printf("(%c) %s - ascii=%d,meth:%d\n",c,S,c,ascii_c);

// "字符数组"C语言作为字符串处理，会自动在后面增加一个'\0'作为字符串的结束标志
//    char en[2] = "a";

char zw[4] = "中";

//    printf("%c,%c,%c,%c\r\n",zw[0],zw[1],zw[2],zw[3]);


//    fflush(stdin);
char *S_ZW = ai_math::ChnToBin(zw);
printf("%s\n",S_ZW);

//01000001
//0010 0111 0001 1101 1011 0101


 ************************************************
 *
 *                      END                     *
 *
 ************************************************/

#ifndef ai_math_hpp
#define ai_math_hpp

#include <stdio.h>

class ai_math {
    ai_math(){}
    ~ai_math(){}
private:
protected:
public:
    // 将字符单字节转换二进制八位
    static void ToBin(char c, char *s) {
        /*
         use it:
         char c='E';
         char S[20];
         scanf("%c",&c);
         fflush(stdin);
         ToBin(c,S);
         printf("(%c) %s\n",c,S);
         */
        s[0]=0;
        int b=128;
        for(int i=0;i<8;i++) {
            if(c>=b)
            {
                s[i]='1';
                c-=b;
            } else {
                s[i]='0';
            }
            b>>=1;
        }
        s[8]=0;
    }
    
    static char* ChnToBin(char *c) {
        char ch[9] = {'\0'};
        int i;
        int j = 0;
        int count = 0;
        char t[3] = {'\0'};
        
        char *result = new char[24];
        
        while('\0' != c[j])
        {
            for(i = 7;i >= 0;i--)
            {
                ch[i] = (c[j]&1)+'0'; // 做与运算
                if(ch[i] != '\0' && count < 24) {
                    result[count] = ch[i];
                    printf("%d=%c\n",count,result[count]);
                    count++;
                }
                
//                result[count] = ch[i];
                
                //右移
                c[j]>>=1;
            }
            j++;
        }
        
        return result;
        //0010 0111 0001 1101 1011 0101
        
    }
    
    static int getASCII(char c) {
        int returnNum = (int)c;
        return returnNum;
    }
    
    static void numToBin(int num, char *s) {
        
    }
    
};

#endif /* ai_math_hpp */
