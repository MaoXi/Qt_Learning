#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define samples 100
#define parameter 6

void statistical(double **sample_statistical[][parameter],double *average_statistical[],double *rsd_statistical[],double **cc_statistical[][parameter],double **rcov_statistical[][parameter])
{
        int i,j,m;
        double sum;
        double **deviation[samples][parameter],**cov_statistical[parameter][parameter],*sd[parameter]; //middle quantity used in calculation

        for (j=0;j<parameter;j++)
        {
                 sum=0;
                 for(i=0;i<samples;i++)
                 {
                         sum=sum+sample_statistical[i][j];
                 }
                     average_statistical[j]=sum/samples;
        }

        for (j=0;j<parameter;j++)
        {
                 for(i=0;i<samples;i++)
                 {
                         deviation[i][j]=sample_statistical[i][j]-average_statistical[j];
                 }
        }

        for (j=0;j<parameter;j++)
        {
                 sum=0;
                 for(i=0;i<samples;i++)
                 {
                         sum=sum+(deviation[i][j])*(deviation[i][j]);
                 }
                     sum=sqrt(sum/(samples-1));
                     sd[j]=sum;
                     rsd_statistical[j]=sd[j]/average_statistical[j];
        }

        for (j=0;j<parameter;j++)
        {
                 for(m=0;m<parameter;m++)
                 {
                     sum=0;
                     for(i=0;i<samples;i++)
                     {
                             sum=sum+deviation[i][j]*deviation[i][m];
                     }
                         cov_statistical[j][m]=sum/(samples-1);
                         rcov_statistical[j][m]=cov_statistical[j][m]/average_statistical[j]/average_statistical[m];
                 }
        }

        for (j=0;j<parameter;j++)
        {
                 for(i=0;i<parameter;i++)
                 {
                         cc_statistical[j][i]=cov_statistical[j][i]/sd[j]/sd[i];
                 }
        }

}

//void main()
//{
//        int i,j;
//        double sample[samples][parameter];
//        double average[parameter],rsd[parameter],cc[parameter][parameter],cov[parameter][parameter],rcov[parameter][parameter];
//        FILE *fp;

//        fp=fopen("sample.txt","r");
//        for (i=0;i<samples;i++)
//        {
//                for (j=0;j<parameter;j++)
//                         fscanf(fp,"%lf",&sample[i][j]);
//        }
//    fclose(fp);

//        statistical(sample,average,rsd,cc,rcov);

//        fp=fopen("output.txt","w");
//        for (j=0;j<parameter;j++)
//        {
//                fprintf(fp,"MEAN VALUE OF SAMPLER FOR PARAMETER %d is:%.4e \n",j+1,average[j]);
//        }
//        fprintf(fp,"\n");

//        for (j=0;j<parameter;j++)
//        {
//                fprintf(fp,"RSD OF SAMPLER FOR PARAMETER %d is:%f \n",j+1,rsd[j]);
//        }
//        fprintf(fp,"\n");

//        fprintf(fp,"CORRELATION COEFFICIENTS BETWEEN SAMPLERS :\n");
//        for (j=0;j<parameter;j++)
//        {
//                for(i=0;i<parameter;i++)
//                        {
//                                fprintf(fp," %9f",cc[j][i]);
//                        }
//                    fprintf(fp,"\n");
//        }
//        fprintf(fp,"\n");

//        fprintf(fp,"RELAVITE COVARIANCE BETWEEN SAMPLERS :\n");
//        for (j=0;j<parameter;j++)
//        {
//                for(i=0;i<parameter;i++)
//                {
//                    fprintf(fp," %15e",rcov[j][i]);
//                }
//                    fprintf(fp,"\n");
//        }
//        fprintf(fp,"\n");
//        fclose(fp);
//}


