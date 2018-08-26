#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "math.h"
#include<QDebug>

////#define parameter 20
int parameter;
////#define samples 1000
int samples;
//CUSA
void LHS(double **samples_LHS,double *mean_LHS,double **cov_input_LHS,int x,int y);
void LHS_CDC(double **sample_LHS_CDC,double *mean_LHS_CDC,double **cov_input_LHS_CDC,int x,int y);

void sampling(double **cov_input_main,double *mean_main,int method,int *sigma,double **final_sample,int x,int y)
{   
  samples =x;
  parameter = y;
  int i,j; // integer variable in loops
//  /FILE *fp; //file opening
//  parameter = y;
//  samples = x;
//function called in main function


//calling sampling method :1 for LHS;2 for LHS-CDC
  switch(method)
  {
  case 1  :
                LHS(final_sample,mean_main,cov_input_main,samples,parameter);
      break;
  case 2  :
                LHS_CDC(final_sample,mean_main,cov_input_main,samples,parameter);
      break;
  } 

// output controlling
// final random samples output
/* 
  fp=fopen("samples.txt","w");
  fprintf(fp,"Final Samples are:\n");
  for (i=0;i<samples;i++)
  {
	   for (j=0;j<parameter;j++)
	   {
			fprintf(fp," %15e",final_sample[i][j]);
	   }
		    fprintf(fp,"\n");
  }
  fclose(fp);
  */

}

//LHS Sampling Method
void LHS(double **samples_LHS,double *mean_LHS,double **cov_input_LHS,int x,int y)
{
	int i,j,m,k; // integer variable in loops
	int ro,a; // middle variable in calculation
    int **arrage_LHS;
    double **random_LHS;// 1-N arrangement and 0-1 random number

    double sum; // middle variable in calculation
    double *z_LHS=new double[samples],*prob_LHS = new double[samples]; // middle variable in random samples space generation

    double **M_LHS,**rp_LHS; // middle variable in final samples space generation
    M_LHS = new double*[parameter];
    for(int i =0;i<parameter;i++){
        M_LHS[i] = new double[parameter];
    }
    for(int i =0;i<parameter;i++){
        for(int j =0;j<parameter;j++){
            M_LHS[i][j] = 0;
        }
    }
    double **random_samples_LHS; // random samples space
    arrage_LHS = new int*[samples];
    random_LHS = new double*[samples];
    rp_LHS = new double*[samples];
    random_samples_LHS = new double*[samples];
    for(int i =0;i<samples;i++){
        arrage_LHS[i] = new int[parameter];
        random_LHS[i] = new double[parameter];
        rp_LHS[i] =new double[parameter];
        random_samples_LHS[i] =new double[parameter];
    }
    for(int i =0;i<samples;i++){
        for(int j =0;j<parameter;j++){
           arrage_LHS[i][j] = 0;
           random_LHS[i][j] = 0;
           rp_LHS[i][j] = 0;
           random_samples_LHS[i][j] = 0;
        }
    }

    void ltqnorm(double *prob_ltqnorm,double *z_ltqnorm,int x);
    void cdc(double **cov_input_cdc,double **M_cdc,int y);
    void statistic(double **sample_statistic,double *average_statistic,double *rsd_statistic,double **cc_statistic,double **rcov_statistic,int x,int y);

    cdc(cov_input_LHS,M_LHS,y); //calling Cholesky decomposition

// 0-1 random number matrix
  srand((int)time(NULL));
  for (i=0;i<x;i++)
  {
	    for (j=0;j<y;j++)
		{
			a=rand();
			random_LHS[i][j]=a/32767.0;
		}
  }

// 1-N random arrangement
  for(j=0;j<y;j++)
  {
       for (i=0;i<x;i++)
       {
	    loop: ro=rand()%samples+1;
	    arrage_LHS[i][j]=ro;
          for (k=0;k<i;k++)
	      {
             if (arrage_LHS[k][j]==arrage_LHS[i][j])
	         {
		      goto loop;
	         }
	      }
       }
   }

// cumulative probability calculation and random samples space generation
	for (i=0;i<y;i++)
	{
		for (j=0;j<x;j++)
		{
			prob_LHS[j]=(double(arrage_LHS[j][i])-1)/samples+random_LHS[j][i]/samples;
		}
		ltqnorm(prob_LHS,z_LHS,x);
		for (k=0;k<x;k++)
		{
			random_samples_LHS[k][i]=z_LHS[k];
		}
	}

// relative perturbation generation
	for (i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			sum=0;
		    for(m=0;m<y;m++)
			{
			sum=sum+random_samples_LHS[i][m]*M_LHS[m][j];
		    }
			rp_LHS[i][j]=sum;
		}
	}

// final samples generation
	for (j=0;j<y;j++)
	{
		for (i=0;i<x;i++)
        {
            samples_LHS[i][j]=mean_LHS[j]+mean_LHS[j]*rp_LHS[i][j];

		}
	}

}

//LHS_CDC Sampling Method
void LHS_CDC(double **sample_LHS_CDC,double *mean_LHS_CDC,double **cov_input_LHS_CDC,int x,int y)
{
	int i,j,m,k;
	int a,ro;
    int **arrage_LHS_CDC;
    double **random_sample;
	double sum;
    double *z_LHS_CDC = new double [samples];
    double **random_LHS_CDC,*prob_LHS_CDC = new double[samples],**random_samples_LHS_CDC;
    double **inverse_a_LHS_CDC;
    double **rp_LHS_CDC,**M_LHS_CDC,**cc_LHS_CDC,**cc_M_LHS_CDC;
    double *average_LHS_CDC = new double[parameter],*rsd_LHS_CDC = new double[parameter],**rcov_LHS_CDC;
    arrage_LHS_CDC = new int*[samples];
    random_sample = new double*[samples];
    random_LHS_CDC = new double*[samples];
    random_samples_LHS_CDC = new double*[samples];
    rp_LHS_CDC = new double*[samples];
    for(int i =0;i<samples;i++){
        arrage_LHS_CDC[i] = new int[parameter];
        random_sample[i] = new double[parameter];
        random_LHS_CDC[i] =new double[parameter];
        random_samples_LHS_CDC[i] =new double[parameter];
        rp_LHS_CDC[i] =new double[parameter];
    }
    for(int i =0;i<samples;i++){
        for(int j =0;j<parameter;j++){
            arrage_LHS_CDC[i][j] = 0;
            random_sample[i][j] = 0;
            random_LHS_CDC[i][j] = 0;
            random_samples_LHS_CDC[i][j] = 0;
            rp_LHS_CDC[i][j] = 0;
        }
    }

    inverse_a_LHS_CDC = new double*[parameter];
    M_LHS_CDC = new double*[parameter];
    cc_LHS_CDC = new double*[parameter];
    cc_M_LHS_CDC = new double*[parameter];
    rcov_LHS_CDC = new double*[parameter];

    for(int i =0;i<parameter;i++){
        inverse_a_LHS_CDC[i] = new double[parameter];
        M_LHS_CDC[i] = new double[parameter];
        cc_LHS_CDC[i] = new double[parameter];
        cc_M_LHS_CDC[i] = new double[parameter];
        rcov_LHS_CDC[i] = new double[parameter];

    }
    for(int i =0;i<parameter;i++){
        for(int j =0;j<parameter;j++){
           inverse_a_LHS_CDC[i][j] = 0;
           M_LHS_CDC[i][j] = 0;
           cc_LHS_CDC[i][j] = 0;
           cc_M_LHS_CDC[i][j] = 0;
           rcov_LHS_CDC[i][j] = 0;
        }
    }
    void ltqnorm(double *prob_ltqnorm,double *z_ltqnorm,int x);
    void cdc(double **cov_input_cdc,double **M_cdc,int y);
    void statistic(double **sample_statistic,double *average_statistic,double *rsd_statistic,double **cc_statistic,double **rcov_statistic,int x,int y);
    void inverse(double **A_inverse,double **INVA_inverse,int y);

// 0-1 random number matrix
  srand((int)time(NULL));
  for (i=0;i<x;i++)
  {
	    for (j=0;j<y;j++)
		{
			a=rand();
			random_LHS_CDC[i][j]=a/32767.0;
		}
  }

// 1-N random arrangement
  for(j=0;j<y;j++)
  {
       for (i=0;i<x;i++)
       {
	    loop: ro=rand()%samples+1;
	    arrage_LHS_CDC[i][j]=ro;
          for (k=0;k<i;k++)
	      {
             if (arrage_LHS_CDC[k][j]==arrage_LHS_CDC[i][j])
	         {
		      goto loop;
	         }
	      }
       }
   }

// cumulative probability calculation and random samples space generation
	for (i=0;i<y;i++)
	{
		for (j=0;j<x;j++)
		{
			prob_LHS_CDC[j]=(double(arrage_LHS_CDC[j][i])-1)/samples+random_LHS_CDC[j][i]/samples;
		}
		ltqnorm(prob_LHS_CDC,z_LHS_CDC,x);
		for (k=0;k<x;k++)
		{
			random_samples_LHS_CDC[k][i]=z_LHS_CDC[k];
		}
	}

// calling subfuctions	
	cdc(cov_input_LHS_CDC,M_LHS_CDC,y);
	statistic(random_samples_LHS_CDC,average_LHS_CDC,rsd_LHS_CDC,cc_LHS_CDC,rcov_LHS_CDC,x,y);
	cdc(cc_LHS_CDC,cc_M_LHS_CDC,y);
	inverse(cc_M_LHS_CDC,inverse_a_LHS_CDC,y);

// random samples retreatnment
	for (i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			sum=0;
		    for(m=0;m<y;m++)
			{
			sum=sum+random_samples_LHS_CDC[i][m]*inverse_a_LHS_CDC[j][m];
		    }
			random_sample[i][j]=sum;
		}
	}

// relative perturbation generation
	for (i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			sum=0;
		    for(m=0;m<y;m++)
			{
			sum=sum+random_sample[i][m]*M_LHS_CDC[j][m];
		    }
			rp_LHS_CDC[i][j]=sum;
		}
	}

// final samples generation
	for (j=0;j<y;j++)
	{
		for (i=0;i<x;i++)
		{
			sample_LHS_CDC[i][j]=mean_LHS_CDC[j]+mean_LHS_CDC[j]*rp_LHS_CDC[i][j];
		}
	}

}

// Cholesky Decomposition
void cdc(double **cov_input_cdc,double **M_cdc,int y)
{
    int i,j,p,k=0;
    double sum,up=0.0;
    double **L_cdc;
    L_cdc = new double*[parameter];
    for(int i =0;i<parameter;i++){
        L_cdc[i] = new double[parameter];
    }
    for(int i =0;i<parameter;i++){
        for(int j =0;j<parameter;j++){
            L_cdc[i][j] = 0.0;
        }
    }
    L_cdc[0][0]=sqrt(cov_input_cdc[0][0]);
    for(i=1;i<y;i++)
    {
        L_cdc[i][0]=cov_input_cdc[i][0]/L_cdc[0][0];
    }
    //K+1 column calculating
    for(j=1;j<y;j++)
    {
        sum=0.0;
        for(p=0;p<=j;p++)
        {
            sum=sum+(L_cdc[j][p]*L_cdc[j][p]);
        }
        L_cdc[j][j]=sqrt(cov_input_cdc[j][j]-sum);
        for(i=j+1;i<y;i++)
        {
            sum=0.0;
            for(p=0;p<=j-1;p++)
            {
                sum=sum+L_cdc[i][p]*L_cdc[j][p];
            }
            L_cdc[i][j]=(cov_input_cdc[i][j]-sum)/L_cdc[j][j];
        }
    }

	for (i=0;i<parameter;i++)
	{
		for(j=0;j<parameter;j++)
		{
			M_cdc[i][j]=L_cdc[i][j];
		}
	}

}
// Lower Triangular Matrix L Inversing Calculation
void inverse(double **A_inverse,double **INVA_inverse,int y)
{   
	int i,j,status,p;
	double sum;

	status=0;
    for (i=0;i<y;i++)
	{
		 if (A_inverse[i][i]+1.0==1.0)
		 {
		     status=1;
	         printf("MATRIX IS NOT INVERSE.");
		 }
	}
    for (i=0;i<y-1;i++)
	{
		 for (j=i+1;j<y;j++)
		 {
			  INVA_inverse[i][j]=0;
		 }
	}
	for (j=0;j<y;j++)
	{   
	     INVA_inverse[j][j]=1/A_inverse[j][j];
	     if (j!=y)
		 {
			 for (i=j+1;i<y;i++)
		     {   
				  sum=0;
			      for (p=j;p<=i-1;p++)
			      {
					   sum=sum-A_inverse[i][p]*INVA_inverse[p][j]/A_inverse[i][i];
			      }
				       INVA_inverse[i][j]=sum;
		     }
	     }
	}

}

//Inverse Function of Normal Distribution Calculation
void ltqnorm(double *prob_ltqnorm,double *z_ltqnorm,int x)
{
	double A[6]={-3.969683028665376e+01,2.209460984245205e+02,-2.759285104469687e+02,1.383577518672690e+02,-3.066479806614716e+01,2.506628277459239e+00};
	double B[5]={-5.447609879822406e+01,1.615858368580409e+02,-1.556989798598866e+02,6.680131188771972e+01,-1.328068155288572e+01};
	double C[6]={-7.784894002430293e-03,-3.223964580411365e-01,-2.400758277161838e+00,-2.549732539343734e+00, 4.374664141464968e+00, 2.938163982698783e+00};
	double D[4]={7.784695709041462e-03, 3.224671290700398e-01, 2.445134137142996e+00, 3.754408661907416e+00};
	double plow,phigh,q,r,e,u,fx2,er,pi;
	int i;
    void errc(double &fx_errc,double &x_errc);

	pi=3.1415926;
	plow=0.02425;
	phigh=1-plow;
	for(i=0;i<x;i++)
	{
		if (prob_ltqnorm[i]>=plow&&prob_ltqnorm[i]<=phigh)
		{
			q=prob_ltqnorm[i]-0.5;
			r=q*q;
			z_ltqnorm[i]=(((((A[0]*r+A[1])*r+A[2])*r+A[3])*r+A[4])*r+A[5])*q/(((((B[0]*r+B[1])*r+B[2])*r+B[3])*r+B[4])*r+1);
		}
		else if(prob_ltqnorm[i]>0&&prob_ltqnorm[i]<plow)
		{
			q=sqrt(-2*log(prob_ltqnorm[i]));
			z_ltqnorm[i]=(((((C[0]*q+C[1])*q+C[2])*q+C[3])*q+C[4])*q+C[5])/((((D[0]*q+D[1])*q+D[2])*q+D[3])*q+1);
		}
			
		else if(prob_ltqnorm[i]>phigh&&prob_ltqnorm[i]<1)
		{
			q=sqrt(-2*log(1-prob_ltqnorm[i]));
			z_ltqnorm[i]=-(((((C[0]*q+C[1])*q+C[2])*q+C[3])*q+C[4])*q+C[5])/((((D[0]*q+D[1])*q+D[2])*q+D[3])*q+1);
		}
	        
		else if(prob_ltqnorm[i]==0)
		{
			z_ltqnorm[i]=-1E24;
		}
		else if(prob_ltqnorm[i]==1)
		{
			z_ltqnorm[i]=1E24;
		}
		if (prob_ltqnorm[i]>0&&prob_ltqnorm[i]<1)
		{
			er=-z_ltqnorm[i]/sqrt(2.0);
			errc(fx2,er);
			e=0.5*fx2-prob_ltqnorm[i];
			u=e*sqrt(2*pi)*exp(pow(z_ltqnorm[i],2)/2);
			z_ltqnorm[i]=z_ltqnorm[i]-u/(1+z_ltqnorm[i]*u/2);
		}
	        
	}

}

// Complementary Form of Error Function
void errc(double &fx_errc,double &x_errc)
{   
	double tmp1,m,n;
	void gp(double &fx_gp,double &a_gp,double &x_gp);
    void gq(double &fx_gq,double &a_gq,double &x_gq);

	m=0.5;
	n=x_errc*x_errc;
	if (x_errc<0.0)
	{
	gp(tmp1,m,n);
	fx_errc=1+tmp1;
	}
	else
	{
	gq(tmp1,m,n);
	fx_errc=tmp1;
	}
	
}

//  P£¨afa,x£©
void gp(double &fx_gp,double &a_gp,double &x_gp)
{
	double fx1_gp,fx2_gp;
	void series(double &gamser_series,double &a_series,double &x_series);
	void contfra(double &gammcf_contfra,double &a_contfra,double &x_contfra);

	if(x_gp<a_gp+1.0)
	{
	   series(fx1_gp,a_gp,x_gp);
	   fx_gp=fx1_gp;
	}
	else
	{
	   contfra(fx2_gp,a_gp,x_gp);
	   fx_gp=1.0-fx2_gp;
	}

}

// Q Calculation
void gq(double &fx_gq,double &a_gq,double &x_gq)
{
	double fx1_gq,fx2_gq;
	void series(double &gamser_series,double &a_series,double &x_series);
	void contfra(double &gammcf_contfra,double &a_contfra,double &x_contfra);

	if(x_gq<a_gq+1.0)
	{
       series(fx1_gq,a_gq,x_gq);
	   fx_gq=1.0-fx1_gq;
	}
	else
	{
	   contfra(fx2_gq,a_gq,x_gq);
	   fx_gq=fx2_gq;
	}
}

// Continued Fraction Approximate Q
void series(double &gamser_series,double &a_series,double &x_series)
{
	int Imax,n;
	double eps,del,sum,ap,gln;
    void lngamma(double &ln_gamma_lngamma,double &x0_lngamma);

	Imax=100;
	eps=3e-7;

	lngamma(gln,a_series);

	if (x_series<=0.0)
	{
	   gamser_series=0.0;
	}
	
	ap=a_series;
	sum=1.0/a_series;
	del=sum;
	for (n=0;n<Imax;n++)
	{
		ap=ap+1.0;
		del=del*x_series/ap;
		sum=sum+del;
        if(abs(int(del))<abs(int((sum)*eps)))
		{
		   gamser_series=sum*exp(-x_series+a_series*log(x_series)-gln);
		}	
	}

}

// Series Expansion gets P
void contfra(double &gammcf_contfra,double &a_contfra,double &x_contfra)
{
	int i,Imax;
	double eps,fpmin,b,c,d,h,an,del,gln;
    void lngamma(double &ln_gamma_lngamma,double &x0_lngamma);
	
	Imax=100;
	eps=3e-7;
	fpmin=1e-30;
	lngamma(gln,a_contfra);
	b=x_contfra+1.0-a_contfra;
	c=1.0/fpmin;
	d=1.0/b;
	h=d;
	for (i=1;i<=Imax;i++)
	{
		an=-i*(i-a_contfra);
		b=b+2.0;
		d=an*d+b;
        if(abs(int(d))<fpmin)
		{
		   d=fpmin;
		}
		   c=b+an/c;
        if(abs(int(c))<fpmin)
		{
           c=fpmin;
		}
		   d=1.0/d;
		   del=d*c;
		   h=h*del;

        if(abs(int(del-1.0))<eps)
		{
		   gammcf_contfra=exp(-x_contfra+a_contfra*log(x_contfra)-gln)*h;
		}
	}

}

// Logarithm of Gamma Fuction
void lngamma(double &ln_gamma_lngamma,double &x0_lngamma)
{
	int i;
	double cof[6]={76.18009172947146,-86.50532032941677,24.01409824083091,-1.231739572450155,0.1208650973866179e-2,-0.5395239384953e-5};
	double temp1,ser,tmp,x,y;

	temp1=sqrt(2*3.141592653589793);
	x=x0_lngamma;
	y=x;
	tmp=x+5.5;
	tmp=(x+0.5)*log(tmp)-tmp;
	ser=1.000000000190015;
	for (i=0;i<6;i++)
	{
		 y=y+1.0;
		 ser=ser+cof[i]/y;
	}
	     ln_gamma_lngamma=tmp+log(temp1*ser/x);
}

//Statistical Calculation
void statistic(double **sample_statistic,double *average_statistic,double *rsd_statistic,double **cc_statistic,double **rcov_statistic,int x,int y) //statistical quantity array
{
	int i,j,m;
	double sum;
    double **deviation,*sd = new double[parameter],**cov; //middle quantity used in calculation
    deviation = new double*[samples];
    for(int i =0;i<samples;i++){
        deviation[i] = new double[parameter];
    }
    for(int i =0;i<samples;i++){
        for(int j =0;j<parameter;j++){
            deviation[i][j] = 0.0;
        }
    }
    cov = new double*[parameter];
    for(int i =0;i<samples;i++){
        cov[i] = new double[parameter];
    }
    for(int i =0;i<samples;i++){
        for(int j =0;j<parameter;j++){
            cov[i][j] = 0.0;
        }
    }
	for (j=0;j<y;j++)
	{
		 sum=0;
		 for(i=0;i<x;i++)
		 {
			 sum=sum+sample_statistic[i][j];
		 }
		     average_statistic[j]=sum/samples;
	}

	for (j=0;j<y;j++)
	{
		 for(i=0;i<x;i++)
		 {
			 deviation[i][j]=sample_statistic[i][j]-average_statistic[j];
		 }
	}

	for (j=0;j<y;j++)
	{
		 sum=0;
		 for(i=0;i<x;i++)
		 {
			 sum=sum+(deviation[i][j])*(deviation[i][j]);
		 }
		     sum=sqrt(sum/(samples-1));
		     sd[j]=sum;
		     rsd_statistic[j]=sd[j]/average_statistic[j];
	}
	
	for (j=0;j<y;j++)
	{
		 for(m=0;m<y;m++)
		 {
		     sum=0;
		     for(i=0;i<x;i++)
		     {
			     sum=sum+deviation[i][j]*deviation[i][m];
		     }
		         cov[j][m]=sum/(samples-1);
		         rcov_statistic[j][m]=cov[j][m]/average_statistic[j]/average_statistic[m];
		 }
	}
	
	for (j=0;j<y;j++)
	{
		 for(i=0;i<y;i++)
		 {
			 cc_statistic[j][i]=cov[j][i]/sd[j]/sd[i];
		 }
	}

}
/*
int main()
{
	int i,j;
	int x=10,y=3;
	int method=2;
	int sigma[3]={1,1,1};
	double cov_input_main[parameter][parameter],mean_main[parameter];
	double final_sample[samples][parameter];

  double a[][30]={ {9.88356E-05,0.00000E-00,0.00000E-00},
                            {0.00000E-00, 8.79084E-06,0.00000E-00},
                           {0.00000E-00,0.00000E-00,4.36275E-04}
						};
	double b[30]={8.03200E-03,5.95400E-02,1.46843E+00};
  sampling(a,b,method,sigma,final_sample,x,y);
  	for(int i=0;i<10;i++)
	{
		for(int j=0;j<3;j++)
		{
				printf("%f  ",final_sample[i][j]);
				if(j==2) printf("\n");
		}
	
	}
  printf("finished!!!");
  getchar();
}
*/
