#include<stdio.h>
#include<time.h>
#include<stdlib.h>
double f(double a[20][20],double b[20],int sample,int num,int method,int sigma[3],double sum[500][20])
{
   /*
    sum[0][0]=sample;       //参数量
    sum[1][1]=num;          //抽样数目
    sum[2][2]=method;       //抽样方法
    sum[3][3]=a[0][0];      //第一个不确定度的值
   */
    srand((unsigned)time(NULL));

    for(int i=0;i<sample;i++)
    {
        for(int j=0;j<num;j++)
        {
            double b=rand()*rand();
            double a=b/1000000000;
            sum[i][j]=a;
        }
    }


    return 0;
}
