#include<stdio.h>
#include <time.h>
#include <stdlib.h>
typedef long long int lli;
//IFib
long long int IFib(long long int n)
{
    if(n==0)return 0;
    if(n==1)return 1;
    long long int a=0,b=1,temp;
    for(long long int i=2;i<=n;i++)
    {
        temp=b;
        b=(b+a)%2021;
        a=temp;
    }
    return b;
}
//RFib
long long int RFib(long long int n)
{
    if(n==0)return 0;
    if(n==1)return 1;
    return ((RFib(n-1)+RFib(n-2))%2021);
}
//CleverFib
lli* matrixMul(lli* a1,lli* a2)
{
    lli *a=(lli*)malloc(sizeof(lli)*4);
    a[0]=((a1[0]*a2[0])+(a1[1]*a2[2]))%2021;
    a[1]=((a1[0]*a2[1])+(a1[1]*a2[3]))%2021;
    a[2]=((a1[2]*a2[0])+(a1[3]*a2[2]))%2021;
    a[3]=((a1[2]*a2[1])+(a1[3]*a2[3]))%2021;
    return a;
}
lli * matrixPow(lli* a,lli n){
    lli* a1=(lli*)malloc(4*sizeof(lli));
    a1[0]=1;
    a1[1]=0;
    a1[2]=0;
    a1[3]=1;
    if(n==0)return a1;
    if(n==1)return a;
    lli *a2=matrixPow(a,n/2);
    a1=matrixMul(a2,a2);
    if(n%2==0)return a1;
    else return matrixMul(a1,a);
}
lli CleverFib(lli n)
{
    if(n==0)return 0;
    if(n==1)return 1;
    lli* a1=(lli*)malloc(4*sizeof(lli));
    a1[0]=1;
    a1[1]=1;
    a1[2]=1;
    a1[3]=0;
    lli* a=matrixPow(a1,n-1);
    return a[0];
}
//main function
int main()
{
    lli n;
    scanf("%lld",&n);
    clock_t start_t, end_t;
    double total_t;
    //calling CleverFib
    start_t = clock();
    printf("CleverFib answer is %lld\n",CleverFib(n));
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken: %lf\n", total_t );
    //calling RFib
    start_t = clock();
    printf("RFib answer is %lld\n",RFib(n));
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken: %lf\n", total_t );
    //calling IFib
    start_t = clock();
    printf("IFib answer is %lld\n",IFib(n));
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken: %lf\n", total_t );
    return 0;
}