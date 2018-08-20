#ifndef INTERFACE3_H
#define INTERFACE3_H

#endif // INTERFACE3_H
//#define parameter 20

void sampling(double **cov_input_main,double *mean_main,int method,int *sigma,double **final_sample,int x,int y);
void LHS(double **samples_LHS,double *mean_LHS,double **cov_input_LHS,int x,int y);
void LHS_CDC(double **sample_LHS_CDC,double *mean_LHS_CDC,double **cov_input_LHS_CDC,int x,int y);
