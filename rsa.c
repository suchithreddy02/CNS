#include<stdio.h>
#include<gmp.h>
#include<math.h>



int findPower(mpz_t q,int arr[])
{
    mpz_t c,r;
    mpz_inits(c,r,NULL);
    mpz_set(c,q);
   
    int k=0;

    while(mpz_cmp_ui(c,0)>0)
    {
        mpz_fdiv_r_ui(r,c,2);
        if(mpz_cmp_ui(r,1)==0)arr[k]=1;
        mpz_fdiv_q_ui(c,c,2);
        k++;
    }
 
   return k-1;

}
void findRemainder(mpz_t a,mpz_t q,mpz_t n,mpz_t r)
{
    mpz_t c,f;
    mpz_inits(c,f,NULL);
    mpz_set_ui(c,0);
    mpz_set_ui(f,1);
    int arr[1024] = {0};
    int k=findPower(q,arr);


    while(k>=0)
    {
        mpz_mul_ui(c,c,2);
        mpz_mul(f,f,f);
        mpz_fdiv_r(f,f,n);
        if(arr[k]==1)
        {
            mpz_add_ui(c,c,1);
            mpz_mul(f,f,a);
            mpz_fdiv_r(f,f,n);
        }
      
       k--;

    }
   
    mpz_set(r,f);

}

void findMultiplicativeInverse(mpz_t a,mpz_t b,mpz_t c)
{

mpz_t x0,y0,x1,y1,x2,y2;
mpz_inits(x0,y0,x1,y1,x2,y2,NULL);

mpz_set_ui(x0,1);
mpz_set_ui(y0,0);
mpz_set_ui(x1,0);
mpz_set_ui(y1,1);

mpz_t r0,r1,r2,q;
mpz_inits(r0,r1,r2,q,NULL);

mpz_set(r0,a);
mpz_set(r1,b);

while(1 )
{
 mpz_fdiv_q(q,r0,r1);
 mpz_fdiv_r(r2,r0,r1);
 
 if(mpz_cmp_ui(r2,0)==0)break;
 
 mpz_t t1,t2;
 mpz_inits(t1,t2,NULL);
 
 mpz_mul(t1,q,x1);
 mpz_mul(t2,q,y1);
 
 mpz_sub(x2,x0,t1);
 mpz_sub(y2,y0,t2);
 
 mpz_swap(x0,x1);
 mpz_swap(y0,y1);
 
 mpz_swap(x1,x2);
 mpz_swap(y1,y2);
 
 mpz_swap(r0,r1);
 mpz_swap(r1,r2); 

}

mpz_fdiv_r(x1,x1,b);

if(mpz_cmp_ui(r1,1)!=0)
{
    gmp_printf("\n the multiplicative inverse doesnt exist as a , m are not coprime");
}

mpz_set(c,x1);
return ;
}

void findGCD(mpz_t r,mpz_t x,mpz_t y)
{
    mpz_t a,b;
    mpz_inits(a,b,NULL);
    mpz_set(a,x);
    mpz_set(b,y);
    if(mpz_cmp(a,b)<0)mpz_swap(a,b);

    while(mpz_cmp_ui(b,0)>0)
    {
        mpz_t t;
        mpz_init(t);
        mpz_fdiv_r(t,a,b);
        mpz_set(a,b);
        mpz_set(b,t);
    }

    mpz_set(r,a);
    return ;
}

int checkPrime(mpz_t p)
{
    mpz_t q,a,r;
    mpz_inits(q,a,r,NULL);

    int k=0;
    mpz_sub_ui(q,p,1);
    
    while(1)
    {
        mpz_fdiv_r_ui(r,q,2);
        if(mpz_cmp_ui(r,1)==0)break;
        mpz_fdiv_q_ui(q,q,2);
        k++;
    }

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state,seed);

    mpz_t max,no;
    mpz_inits(max,no,NULL);
    mpz_sub_ui(max,p,1);

    mpz_urandomm(a,state,max);

    for(int i=0;i<k;i++)
    {
        int x=pow(2,i);
        mpz_mul_ui(no,q,x);

        findRemainder(a,no,p,r);

        if(mpz_cmp(r,max)==0)return 1;
    }

    return 0;
}
void generatePrime(mpz_t ans)
{
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state,seed);

    int bits=5;
    int isPrime=0;
    mpz_t p;

    while(!isPrime)
    {
        mpz_init(p);
        mpz_rrandomb(p,state,bits);

        mpz_t r;
        mpz_init(r);
        mpz_fdiv_r_ui(r,p,2);

        if(mpz_cmp_ui(r,0)==0)continue;

        for(int i=0;i<20;i++)
        {
            isPrime = checkPrime(p);

            if(!isPrime)break;
        }

        if(isPrime)break;
    }
    
    mpz_set(ans,p);
    return ;
}

void generateE(mpz_t e,mpz_t p,mpz_t q)
{
    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state,seed);

    mpz_t max,no,a;
    mpz_inits(max,no,a,NULL);
    mpz_mul(max,p,q);

    int iscoprime=0;

    while(!iscoprime)
    {
        mpz_urandomm(a,state,max);
        if(mpz_cmp_ui(a,1)==0||mpz_cmp(a,max)==0)continue;
        findGCD(no,max,a);
        if(mpz_cmp_ui(no,1)==0)
        {
          iscoprime=1;
          mpz_set(e,a);
        }

    }

    return ;

}

int main()
{
     mpz_t p,q,n;
     mpz_inits(p,q,n,NULL);
     generatePrime(p);
     generatePrime(q);

     while(mpz_cmp(p,q)==0)generatePrime(q);
     mpz_mul(n,p,q);
     
     gmp_printf("p: %Zd \nq: %Zd \n",p,q);
     mpz_t e;
     mpz_init(e);
     generateE(e,p,q);

     gmp_printf("e: %Zd \n",e);

     mpz_t T,M,C,temp;
     mpz_inits(temp,T,M,C,NULL);
     printf("Entre the msg : ");
     gmp_scanf("%Zd",T);
     mpz_set(temp,e);

     findRemainder(T,temp,n,C);

     gmp_printf("Encrypted msg %Zd \n",C);

     //Decryption
     mpz_t d,fin;
     mpz_inits(d,fin,NULL);
     mpz_mul(fin,p,q);
     
     findMultiplicativeInverse(e,fin,d);

     gmp_printf("d : %Zd \n",d);

     findRemainder(C,d,n,M);

     gmp_printf("Decrypted msg %Zd \n",M);



    return 0;
}