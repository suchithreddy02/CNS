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

while(1)
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

    //generating n bit prime number
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

void generateRandom(mpz_t x,mpz_t max)
{
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state,seed);

    mpz_urandomm(x,state,max);
    return ;

}

long generatePrimeFactors(mpz_t p,mpz_t pf[])
{
    mpz_t no,i,r;
    mpz_inits(no,i,r,NULL);
    mpz_sub_ui(no,p,1);
    mpz_set_ui(i,2);
    long cnt = 0;

    while(mpz_cmp_ui(no,1)>0)
    {
         int isPrimeFactor = 0;
         mpz_fdiv_r(r,no,i);

         while(mpz_cmp_ui(r,0)==0)
         {
            isPrimeFactor=1;
            mpz_fdiv_q(no,no,i);
            mpz_fdiv_r(r,no,i);
         }

         if(isPrimeFactor)
         {
              mpz_init(pf[cnt]);
              mpz_set(pf[cnt],i);
              cnt++;
         }
         
         mpz_add_ui(i,i,1);
    }

    return cnt;
} 

void generatePrimitveRoot(mpz_t alpha,mpz_t p)
{
    
    mpz_t pf[mpz_get_ui(p)];
    long size=generatePrimeFactors(p,pf);

    int isPrimitiveRoot = 0;
    mpz_t pow,phi,r;
    mpz_inits(phi,pow,r,NULL);


    while(!isPrimitiveRoot)
    {
        
        mpz_sub_ui(phi,p,1);
        generateRandom(alpha,phi);
        isPrimitiveRoot = 1;
        
        for(long i=0;i<size;i++)
        {
           mpz_fdiv_q(pow,phi,pf[i]);
           findRemainder(alpha,pow,p,r);

           if(mpz_cmp_ui(r,1)==0)
           {
               isPrimitiveRoot=0;
               break;
           }
        }

    }

    return ;
}

int main()
{
     mpz_t p,alpha,max;
     mpz_inits(p,alpha,max,NULL);
     generatePrime(p);
     generatePrimitveRoot(alpha,p);
     gmp_printf("prime : %Zd and primitive root : %Zd \n",p,alpha);
     

     //generating As private key
     mpz_t XA;
     mpz_sub_ui(max,p,2);
     mpz_init(XA);
     generateRandom(XA,max);

     //generating As public key
     mpz_t YA;
     mpz_init(YA);
     findRemainder(alpha,XA,p,YA);
     gmp_printf("A public key : %Zd\n",YA);

     //entering the plain text
     mpz_t M;
     mpz_init(M);
     gmp_printf("Entre the Msg: ");
     gmp_scanf("%Zd",M);

     //encrypting the msg
     mpz_t k,C1,C2,K;
     mpz_inits(k,C1,C2,K,NULL);
     mpz_sub_ui(max,p,1);
     generateRandom(k,max);
     findRemainder(YA,k,p,K);
     findRemainder(alpha,k,p,C1);
     mpz_mul(C2,K,M);
     mpz_fdiv_r(C2,C2,p);
     gmp_printf("C1 C2 : %Zd %Zd \n",C1,C2);


     //Decrypting
     mpz_t Kinv;
     mpz_init(Kinv);
     findRemainder(C1,XA,p,K);
     findMultiplicativeInverse(K,p,Kinv);
     mpz_mul(C2,C2,Kinv);
     mpz_fdiv_r(C2,C2,p);

     gmp_printf("Decrypted msg : %Zd \n",C2);

    return 0;
}