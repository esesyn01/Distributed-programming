#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PRIME_MAX 101
int* tab;
int n=4;
int primes[PRIME_MAX]={};
int prime_cnt=0;
pthread_mutex_t m;
struct my_struct
{
    int a,b,x;
};
struct my_struct* data;
void *f(void *i)
{
    printf("Watek sobie powstaje\n");
    return NULL;
}
void *erastotenes(void *i)
{
    struct my_struct* dataa = (struct my_struct*) i;
    int temp;
    for (int i=dataa->a; i<=dataa->b; i++)
    {
        if(tab[i-2]!= dataa->x + 1) 
        {
            temp = (i-2)+(i);
            while(temp<=dataa->x)
            {
                tab[temp]=dataa->x+1;
                temp+=i;
            }
        }
    }
}
void *erastotenes_with_arr(void *i)
{
    struct my_struct* dataa = (struct my_struct*) i;
        printf("Watek %d jest otwierany\n", dataa->a);
    int temp;
    for (int i=dataa->a; i<=dataa->b; i++)
    {
        if(tab[i-2]!= dataa->x + 1) 
        {
            temp = (i-2)+(i);
            while(temp<=dataa->x)
            {
                pthread_mutex_lock(&m);
                if(primes[temp]!=0)
                {
                    primes[temp]=0;
                    //prime_cnt-=1;
                }
                pthread_mutex_unlock(&m);
                tab[temp]=dataa->x+1;
                temp+=i;
            }
            pthread_mutex_lock(&m);
            primes[i-2]=tab[i-2];
            prime_cnt+=1;
            pthread_mutex_unlock(&m);
        }
        else
        {
            pthread_mutex_lock(&m);
            if (primes[i-2]!=0)
            {
                primes[i-2]=0;
            }
            pthread_mutex_unlock(&m);
        }
    }
}
int main()
{
    int a=2,b,x;
    pthread_mutex_init(&m,NULL);
    scanf("%d",&x);
    prime_cnt=x;
    pthread_t w[n];
    data = malloc(n*sizeof(struct my_struct));
    int end = x;
    tab = malloc(end*sizeof(int));
    for (int i=0; i<end; i++)
    {
        tab[i]=i+2;
    }
    int temp = end/n;
    for (int i=0; i<n; i++)
    {
        data[i].x=end;
        data[i].a=a;
        b=a+temp;
        data[i].b=b;
        a=b;
    }
    if (b!=end)
    {
        data[n-1].b+=1;
    }
    for (int i=0; i<n; i++)
    {
        pthread_create(&w[i], NULL, erastotenes_with_arr, (void*)&data[i]);
    }
    for (int i=0; i<n; i++)
    {
        pthread_join(w[i], NULL);
    }
    for (int i=0; i<PRIME_MAX; i++)
    {
        if(primes[i]!=0)
        {
            printf("%d ",primes[i]);
        }
    }
    printf("\n");
    pthread_mutex_destroy(&m);
}