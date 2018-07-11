#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int m(int a,int b)
{
    if(a>b)
        return a;
    else {
       return b;
    }
}

int suiji()
{
    srand((unsigned)time(NULL));
    return rand()%30;
}
