#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
 
#define SYS_kernel_2d_memcpy 448
 
int main(void){
    float from[3][2] = {{24, 67.8}, {34, 5}, {9, 6.01}};
    float to[3][2] = {{0,0},{0,0},{0,0}};
    int ret = syscall(SYS_kernel_2d_memcpy, from, to, 3, 2);
    printf("copy from matrix:\n");
    for (int i=0;i<3;i++){
        for (int j=0;j<2;j++){
            printf(" %f ", from[i][j]);
        }
        printf("\n");
    }
    printf("return val of syscall %d\n", ret);
    printf("copy to matrix\n");
    for (int i=0;i<3;i++){
        for (int j=0;j<2;j++){
            printf("%f ", to[i][j]);
        }
        printf("\n");
    }
}
