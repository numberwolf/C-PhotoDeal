#include<iostream>
#include<math.h>
int main() {
    int n,r,avg;
    
    bool inputRight = false;
    while(inputRight == false) {
        scanf("%d %d %d",&n,&r,&avg);
        if (n <= pow(10,5) && n >= 1 && r >= 1 && r <= pow(10,9) && avg >= 1 && avg <= pow(10,6)) {
            inputRight = true;
            //printf("first input right");
        } else {
            printf("Error:first input error");
        }
    }
    
    
    int *a_array = new int[n];
    int *b_array = new int[n];
    
    long long int result,sum;
    
    for(int i = 0; i < n; i++) {
        inputRight = false;
        while(inputRight == false) {
            scanf("%d %d",&a_array[i],&b_array[i]);
            
            if(a_array[i] <= pow(10,6) && a_array[i] >= 1 && b_array[i] <= pow(10,6) && b_array[i] >= 1) {
                inputRight = true;
                //printf("No %d input right",i);
            } else {
                printf("Error: No %d-%d-%d input error!",i,a_array[i],b_array[i]);
            }
            int temp = a_array[i] + b_array[i];
            sum += temp;
        }
    }
    
    result = sum/n;
    
    printf("%lld",result);
    return 0;
}


