#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//#define samples 100
//#define parameter 6
extern int samples;
extern int parameter;
// K-S test
void ks(double **sam,double *prob_normal,double *prob_uni,double *prob_expcdf)
{
    int i,j;
    double *ex = new double[parameter],*esd = new double[parameter],*xmean = new double[parameter],*xsd = new double[parameter],*xvar = new double[parameter];
    double *dn_normal = new double[parameter];
    double *dn_uni = new double[parameter];
    double *dn_expcdf = new double[parameter];
    FILE *fp;

    void isqt1(double **xx,double *xmean,double *xvar,double *xsd);
    void ksnorm(double **sam,double *xmean,double *xsd,double *dn,double *prob);
    void ksuni(double **sam,double *dn,double *prob);
    void ksexpcdf(double **sam,double *xsd,double *dn,double *prob);

    for (i=0;i<parameter;i++)
    {
        ex[i]=0;
        esd[i]=1.0;
    }

    isqt1(sam,xmean,xvar,xsd);
    ksnorm(sam,xmean,xsd,dn_normal,prob_normal);
    ksuni(sam,dn_uni,prob_uni);
    ksexpcdf(sam,xsd,dn_expcdf,prob_expcdf);
}

//求解样本均值与标准差
void isqt1(double **xx,double *xmean,double *xvar,double *xsd)
{
    int i,j;
    double z;

    for (j=0;j<parameter;j++)
    {
         z=0;
         for (i=0;i<samples;i++)
         {
              z=z+xx[i][j]/samples;
         }
         xmean[j]=z;
    }
    for (j=0;j<parameter;j++)
    {
         z=0;
         for (i=0;i<samples;i++)
         {
              z=z+pow((xx[i][j]-xmean[j]),2);
         }
         xvar[j]=z/(samples-1);
         xsd[j]=sqrt(xvar[j]);
     }
}

// 正态分布K-S检验
void ksnorm(double **sam,double *xmean,double *xsd,double *dn,double *prob)
{
    double **fo;
    fo = new double*[samples];
    for(int i = 0;i<samples;i++){
        fo[i] = new double[parameter];
    }
    for(int i =0;i<samples;i++){
        for(int j =0;j<parameter;j++){
            fo[i][j] = 0;
        }
    }
    double en,fno,fn,ff,d,merrf,x;
    int i,j,m;

    double mgam2(double a,double x);
    double probks(double alam);
    void sort(double **a);

    for (j=0;j<parameter;j++)
    {
         if (xsd[j]<=0)
         {
             xsd[j]=1.0e-10;
         }
         for (i=0;i<samples;i++)
         {
             x=(sam[i][j]-xmean[j])/(sqrt(2.0)*xsd[j]);
             if (x>=0)
             {
                 merrf=mgam2(0.5,x*x);
             }
             else
             {
                 merrf=-mgam2(0.5,x*x);
             }
             fo[i][j]=0.5+0.5*merrf;
         }
     }
     sort(sam);
     sort(fo);
     en=samples;
     for (i=0;i<parameter;i++)
     {
          dn[i]=0.0;
     }
     for (j=0;j<parameter;j++)
     {
         fno=0.0;
         for (i=0;i<samples;i++)
         {
              m=i+1;
              fn=m*1.0/en;
              ff=fo[i][j];
              if (fabs(fno-ff)>fabs(fn-ff))
              {
                  d=fabs(fno-ff);
              }
              else
              {
                  d=fabs(fn-ff);
              }
              if (d>dn[j])
              {
                  dn[j]=d;
              }
           fno=fn;
           }
      prob[j]=probks(sqrt(en)*dn[j]);
      }
}

// 均匀分布KS检验
void ksuni(double **sam,double *dn,double *prob)
{
    int i,j,m;
    double **fo,*nmin = new double[parameter],*nmax = new double[parameter];
    float *lenth = new float[parameter];
    double max,min;
    double en,fno,fn,ff,d;
    fo = new double*[samples];
    for(int i =0;i<samples;i++){
        fo[i] = new double[parameter];
    }
    for(int i=0;i<samples;i++){
        for(int j =0;j<parameter;j++){
            fo[i][j] = 0;
        }
    }
    double probks(double alam);
    void sort(double **a);

    for (j=0;j<parameter;j++)
    {
        max=sam[0][j];
        min=sam[0][j];
        for (i=0;i<samples;i++)
        {
             if (max<sam[i][j])
             {
                 max=sam[i][j];
             }
             if (min>sam[i][j])
             {
                 min=sam[i][j];
             }
        }
             nmin[j]=min;
             nmax[j]=max;
             lenth[j]=nmax[j]-nmin[j];
    }
    for (j=0;j<parameter;j++)
    {
        for (i=0;i<samples;i++)
        {
              fo[i][j]=(sam[i][j]-nmin[j])/lenth[j];
        }
    }
     sort(sam);
     sort(fo);
     en=samples;
     for (i=0;i<parameter;i++)
     {
          dn[i]=0.0;
     }
     for (j=0;j<parameter;j++)
     {
         fno=0.0;
         for (i=0;i<samples;i++)
         {
              m=i+1;
              fn=m*1.0/en;
              ff=fo[i][j];
              if (fabs(fno-ff)>fabs(fn-ff))
              {
                  d=fabs(fno-ff);
              }
              else
              {
                  d=fabs(fn-ff);
              }
              if (d>dn[j])
              {
                  dn[j]=d;
              }
           fno=fn;
           }
      prob[j]=probks(sqrt(en)*dn[j]);
      }
}

// 指数分布K-S检验
void ksexpcdf(double **sam,double *xsd,double *dn,double *prob)
{
    int i,j,m;
    double **fo;
    double en,fno,fn,ff,d,lan;
    fo = new double*[samples];
    for(int i =0;i<samples;i++){
        fo[i] = new double[parameter];
    }
    for(int i=0;i<samples;i++){
        for(int j =0;j<parameter;j++){
            fo[i][j] = 0;
        }
    }
    double probks(double alam);
    void sort(double **a);

    for (j=0;j<parameter;j++)
    {
         lan=1/xsd[j];
         for (i=0;i<samples;i++)
         {
              if (sam[i][j]>=0.0)
              {
                  fo[i][j]=1.0-exp(-lan*sam[i][j]);
              }
              else
              {
                  fo[i][j]=0.0;
              }
         }
    }

    sort(sam);
    sort(fo);
    en=samples;
    for (i=0;i<parameter;i++)
    {
         dn[i]=0.0;
    }
    for (j=0;j<parameter;j++)
    {
         fno=0.0;
         for (i=0;i<samples;i++)
         {
              m=i+1;
              fn=m*1.0/en;
              ff=fo[i][j];
              if (fabs(fno-ff)>fabs(fn-ff))
              {
                  d=fabs(fno-ff);
              }
              else
              {
                  d=fabs(fn-ff);
              }
              if (d>dn[j])
              {
                  dn[j]=d;
              }
           fno=fn;
           }
      prob[j]=probks(sqrt(en)*dn[j]);
      }
}

// 布朗桥函数
double probks(double alam)
{
    double eps1=0.001,eps2=1.0e-8;
    double a2,fac,term,termbf;
    double probks;
    int j;

    a2=-2*pow(alam,2);
    fac=2.0;
    probks=0.0;
    termbf=0.0;
    for (j=1;j<=100;j++)
    {
         term=fac*exp(a2*j*j);
         probks=probks+term;
         if ((fabs(term)<(eps1*termbf))||(fabs(term)<(eps2*probks)))
         {
              return probks;
              return 0;
         }
         fac=-fac;
         termbf=fabs(term);
    }
    probks=1.0;
    return probks;
}

// 数组每列从小到大排列
void sort(double **a)
{
    double temp;
    int i,j,k,iptr;

    for (j=0;j<parameter;j++)
    {
         for (i=0;i<samples-1;i++)
         {
              iptr=i;
              for (k=i+1;k<samples;k++)
              {
                   if (a[k][j]<a[iptr][j])
                   {
                       iptr=k;
                   }
              }
              if (iptr!=i)
              {
                  temp=a[i][j];
                  a[i][j]=a[iptr][j];
                  a[iptr][j]=temp;
              }
           }
    }
}

// 不完全伽马函数
double mgam2(double a,double x)
{
    double mgam2,p,q,d,s,s1,p0,q0,p1,q1,qq;
    int i;

    double mgam1(double x);

    if ((a<=0)||(x<0))
    {
         if (a<=0)
         {
             printf("err** a<=0!\n");
         }
         if (x<0)
         {
             printf("err** x<0!\n");
         }
         mgam2=-1;
     }
     if ((x+1)==1)
     {
         mgam2=0;
         return mgam2;
     }
     if (x>1.0e35)
     {
         mgam2=1.0;
         return mgam2;
      }
      q=log(x);
      q=a*q;
      qq=exp(q);
      if (x<(1.0+a))
      {
          p=a;
          d=1.0/a;
          s=d;
          for (i=1;i<=100;i++)
          {
               p=1.0+p;
               d=d*x/p;
               s=s+d;
          if (fabs(d)<(fabs(s)*1.0e-7))
          {
              s=s*exp(-x)*qq/mgam1(a);
              mgam2=s;
              return mgam2;
          }
          }
       }
       else
       {
           s=1.0/x;
           p0=0.0;
           p1=1.0;
           q0=1.0;
           q1=x;
           for (i=1;i<=100;i++)
           {
                p0=p1+(i-a)*p0;
                q0=q1+(i-a)*q0;
                p=x*p0+i*p1;
                q=x*q0+i*q1;
                if ((fabs(q)+1.0)!=1.0)
                {
                     s1=p/q;
                     p1=p;
                     q1=q;
                     if (fabs((s1-s)/s1)<1.0e-7)
                     {
                         s=s1*exp(-x)*qq/mgam1(a);
                         mgam2=1.0-s;
                         return mgam2;
                     }
                     s=s1;
                }
                p1=p;
                q1=q;
             }
         }
           printf("A too large!\n");
           s=1.0-s*exp(-x)*qq/mgam1(a);
           mgam2=s;
           return mgam2;
}

//伽马函数
double mgam1(double x)
{
    double a[11]={0.0000677106,-0.0003442342,0.0015397681,-0.0024467480,0.0109736958,-0.0002109075,0.0742379071,0.0815782188,0.4118402518,0.4227843370,1.0};
    double mgam1,y,t,s,u;
    int i;
    if (x<=0.0)
    {
        printf("err** x<0\n");
        mgam1=-1.0;
        return mgam1;
        return 0;
    }
    y=x;
    if (y<=1)
    {
        t=1.0/(y*(y+1.0));
        y=y+2.0;
    }
    else if (y<=2)
    {
        t=1.0/y;
        y=y+1.0;
    }
     else if (y<=3)
        t=1.0;
     if (y>3)
     {
         t=1.0;
         while (y>3)
         {
                y=y-1;
                t=t*y;
         }
      }
      s=a[0];
      u=y-2.0;
      for(i=0;i<10;i++)
      s=s*u+a[i+1];
      s=s*t;
      mgam1=s;
      return mgam1;
      return 0;
}

// 不完全Beta函数
double mbeta(double a,double b,double x)
{
    double mbeta;
    double y;

    double beta(double a,double b,double x);

    if (a<=0.0)
    {
        printf("' ERR** A<=0 !'");
        mbeta=-1.0;
        return mbeta;
    }
    if (b<=0.0)
    {
        printf("' ERR** B<=0 !'");
        mbeta=-1.0;
        return mbeta;
    }
    if ((x<0.0)||(x>1.0))
    {
        printf("' ERR** X<0 or X>1 !'") ;
        mbeta=1.0e+35;
        return mbeta;
    }
    if ((x+1.0==1.0)||(x+1.0==2.0))
    {
         y=0.0;
    }
    else
    {
         y=a*log(x)+b*log(1.0-x);
         y=exp(y);
         y=y*mgam1(a+b)/(mgam1(a)*mgam1(b));
    }
    if (x<(a+1.0)/(a+b+2.0))
    {
        y=y*beta(a,b,x)/a;
    }
    else
    {
        y=1.0-y*beta(b,a,1.0-x)/b;
    }
    mbeta=y;
    return mbeta;
}

//完全Beta函数
double beta(double a,double b,double x)
{
    int k;
    double beta;
    double d,p0,q0,p1,q1,s0,s1;

    p0=0.0;
    q0=1.0;
    p1=1.0;
    q1=1.0;
    for (k=1;k<=100;k++)
    {
         d=(a+k)*(a+b+k)*x;
         d=-d/((a+k+k)*(a+k+k+1.0));
         p0=p1+d*p0;
         q0=q1+d*q0;
         s0=p0/q0;
         d=k*(b-k)*x;
         d=d/((a+k+k-1.0)*(a+k+k));
         p1=p0+d*p1;
         q1=q0+d*q1;
         s1=p1/q1;
         if (fabs(s1-s0)<fabs(s1)*1.0e-07)
         {
             beta=s1;
             return beta;
         }

    }
    printf("' A or B too big !'");
    beta=s1;
    return beta;
}
//重载sort函数

//void main ()
//{
//    int i,j;
//    double sample_main[samples][parameter];
//    double prob_normal[parameter],prob_uni[parameter],prob_expcdf[parameter];
//    FILE *fp;

//    fp=fopen("sample.txt","r");
//    for (i=0;i<samples;i++)
//    {
//         for (j=0;j<parameter;j++)
//              fscanf(fp,"%lf",&sample_main[i][j]);
//    }
//    fclose(fp);

//    ks(sample_main,prob_normal,prob_uni,prob_expcdf);

//    fp=fopen("test results.txt","w");

//    fprintf(fp,"K-S TEST RESULTS OF NORMAL DISTRIBUTION:\n");
//    fprintf(fp,"OBSERVATION VALUE     SAGNIFICANT LEVEL\n");
//    for (i=0;i<parameter;i++)
//    {
//         fprintf(fp,"par %2d     %15e\n",i+1,prob_normal[i]);
//    }
//         fprintf(fp,"\n");
//    fprintf(fp,"K-S TEST RESULTS OF UNIFORM DISTRIBUTION:\n");
//    fprintf(fp,"OBSERVATION VALUE     SAGNIFICANT LEVEL\n");
//    for (i=0;i<parameter;i++)
//    {
//         fprintf(fp,"par %2d     %15e\n",i+1,prob_uni[i]);
//    }
//         fprintf(fp,"\n");
//    fprintf(fp,"K-S TEST RESULTS OF EXPONENTIAL DISTRIBUTION:\n");
//    fprintf(fp,"OBSERVATION VALUE     SAGNIFICANT LEVEL\n");
//    for (i=0;i<parameter;i++)
//    {
//         fprintf(fp,"par %2d     %15e\n",i+1,prob_expcdf[i]);
//    }
//         fprintf(fp,"\n");
//}











