#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//#define samples 100
//#define parameter 6
extern int samples;
extern int parameter;

//sample_main 样本 对应三种不同的分布类型 x_sample y_sample x_normal y_normal x_uniform y_uniform x_exponential y_exponential
void CPD(double **sample_main,double **x_sample,double **y_sample,double **x_normal,double **y_normal,double **x_uniform,double **y_uniform,double **x_exponential,double **y_exponential)
{
    int i,j,m;
    double a,b,k,t,p,q,sum;
//    double c=1000;
    double *lambda1 = new double[parameter],**x;
    x = new double *[samples];
    for(int i = 0;i<samples;i++){
        x[i] = new double [parameter];
    }
    for(int i=0;i<samples;i++){
        for(int j=0;j<parameter;j++){
            x[i][j] = 0;
        }
    }
    double *sd = new double[parameter],*u = new double[parameter]; //计算标准差.均值
    double Romberg(double a,double b,double e,double u,double sd);
    for(int i =0;i<parameter;i++){
        lambda1[i]=0;
        sd[i]=0;
        u[i]=0;
        for(int j=0;j<samples;j++){
            x[j][i]=0;
        }
    }
    //对一位数组进行排序
    for (j=0;j<parameter;j++)
    {
         for (i=0;i<samples;i++)
         {
              for(m=i+1;m<samples;m++)
              {
                  if (sample_main[i][j]>sample_main[m][j])
                  {
                      t=sample_main[i][j];
                      sample_main[i][j]=sample_main[m][j];
                      sample_main[m][j]=t;
                  }
              }
         }
    }


    for (j=0;j<parameter;j++)
    {
         for (i=0;i<samples;i++)
         {
              x_sample[i][j]=sample_main[i][j];
         }
    }


    for (j=0;j<parameter;j++)
    {
         k=0.0;
         for(i=0;i<samples;i++)
         {
             y_sample[i][j]=(k/samples);
             k++;
         }
    }

    for (j=0;j<parameter;j++)
    {
        a=sample_main[0][j];
        b=sample_main[samples-1][j];
        for (i=0;i<samples;i++)
        {
        x[i][j]=a+i*(b-a)/samples;
        }
    }

    for (j=0;j<parameter;j++)
    {
        for (i=0;i<samples;i++)
        {
             x_normal[i][j]=x[i][j];
             x_uniform[i][j]=x[i][j];
             x_exponential[i][j]=x[i][j];
        }
    }

    for (j=0;j<parameter;j++)
    {
         sum=0.0;
         for (i=0;i<samples;i++)
         {
              sum=sum+sample_main[i][j];
         }
         u[j]=sum/samples;
    }

    for (j=0;j<parameter;j++)
    {
         sum=0;
         for (i=0;i<samples;i++)
         {
              sum=sum+(sample_main[i][j]-u[j])*(sample_main[i][j]-u[j]);
         }
         sd[j]=sqrt(sum/(samples-1));
    }

    //正态分布
    for (j=0;j<parameter;j++)
    {
         p=u[j];
         q=sd[j];
         double pi = 3.1415926;
         for (i=0;i<samples;i++)
         {
              if(i<1)
              {
                 y_normal[i][j]= Romberg(-100,x_normal[i][j],0.00001,p,q);
              }
              else
              {
                 y_normal[i][j]= y_normal[i-1][j]+ Romberg (x_normal[i-1][j],x_normal[i][j],0.000001,p,q);
              }
          }
    }

    //均匀分布
    for (j=0;j<parameter;j++)
    {
         for (i=0;i<samples;i++)
         {
              y_uniform[i][j]=(x_uniform[i][j]-x_uniform[0][j])/(x_uniform[(int)samples-1][j]-x_uniform[0][j]);
         }
    }

    //指数分布
    for (j=0;j<parameter;j++)
    {
         lambda1[j]=1/u[j];
         for (i=0;i<samples;i++)
         {
              y_exponential[i][j]=1-exp(-x_exponential[i][j]*lambda1[j]);
         }
    }

}

double Romberg(double a,double b,double e,double u,double sd)
{//龙贝格积分，在区间[a,b]上积分，误差为e
   int k=1;
   double pi=3.1415926;
   double T1,T2,S1,S2,C1=0,C2=0,R1=0,R2=0;
   double h=b-a;
   double i;
   //printf("h=%f",h);
   double s;
   //printf("f(b)=%f\n",fx(b));
   T1=(exp(-(a-u)*(a-u)/(2*sd*sd))/(sqrt(2*pi)*sd)+exp(-(b-u)*(b-u)/(2*sd*sd))/(sqrt(2*pi)*sd))*h/2.0;
   //printf("T1=%f\n",T1);
   int counter=0;//循环上限
   while(1)
    {
       counter++;
       //s=getS(a,b,h);
       s=0.0;
       for(i=a+h/2.0; i<b; i+=h)
       {
           s+=exp(-(i-u)*(i-u)/(2*sd*sd))/(sqrt(2*pi)*sd);
       }
       //printf("%lf\n",s);
       T2=(T1+h*s)/2.0;
       S2=(4.0*T2-T1)/3.0;
       h/=2.0;
       T1=T2;
       S1=S2;
       C1=C2;
       R1=R2;
       if(k==1)
       {
           k++;
           continue;
       }
       C2=(16.0*S2-S1)/15.0;
       if(k==2)
       {
           k++;
           continue;
       }
       R2=(64.0*C2-C1)/63.0;
       if(k==3)
       {
           k++;
           continue;
       }
    //    printf("%lf\n",fabs(R1-R2));
       if(fabs(R1-R2)<e||counter>=100)break;
    }
   return R2;
}
