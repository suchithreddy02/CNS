#include<stdio.h>
#include<gmp.h>
#include<math.h>


void findRemainder(mpz_t a,mpz_t q,mpz_t n,mpz_t r)
{
    if(mpz_cmp_ui(q,1)==0)
    {
        mpz_fdiv_r(r,a,n);
    }
    else
    {
        mpz_t rem;
        mpz_init(rem);
        
        mpz_fdiv_r_ui(rem,q,2);
        mpz_fdiv_q_ui(q,q,2);

        findRemainder(a,q,n,r);
        mpz_mul(r,r,r);
        if(mpz_cmp_ui(rem,1)==0)mpz_mul(r,r,a);
        mpz_fdiv_r(r,r,n);
    }
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

int main()
{
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state,seed);

    int bits=1024;
    int isPrime=0;

    while(!isPrime)
    {
        mpz_t p;
        mpz_init(p);
        mpz_rrandomb(p,state,bits);

        mpz_t r;
        mpz_init(r);
        mpz_fdiv_r_ui(r,p,2);

        if(mpz_cmp_ui(r,0)==0)continue;

        isPrime = checkPrime(p);

        if(isPrime)
        {
            gmp_printf("%Zd is 1024 bit prime \n",p);
        }
    }

    return 0;
}