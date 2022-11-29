#include<bits/stdc++.h>
using namespace std;

int a,b,p;

typedef pair<int,int> pi;

int mod(int a)
{
    return  ((a%p)+p)%p;
}

bool pointOfInfinity(pi q)
{
    int y = mod(-1*q.second);
    return y == q.second;
}

int findMI(int a,int b)
{
    
    int x0=1,y0=0,x1=0,y1=1;
    int r0=a,r1=b;

    while(1)
    {
        int q=r0/r1;
        int r2=r0%r1;

        if(r2==0)break;
        int x2=x0-q*x1;
        int y2=y0-q*y1;

        x0=x1;y0=y1;
        x1=x2;y1=y2;

        r0=r1;r1=r2;
    }

    return x1%=b;
}

pi add(pi p1,pi p2)
{
    pi z;

    if(p1==p2)
    {
        int m=(3*p1.first*p1.first+a)*findMI(p1.second,p);
        m = mod(m);

        z.first = mod(m*m - 2*p1.first);
        z.second = mod(m*(p1.first-z.first)-p1.second);
    }
    else
    {
        int m=mod((p1.second-p2.second)*findMI(mod(p1.first-p2.first),p));
        z.first = mod(m*m-p1.first-p2.first);
        z.second = mod(m*(p1.first-z.first)-p1.second);
    }

    return z;
}

pi find(int n,pi q)
{
    if(n==1)return q;
    else
    {
        pi z=find(n/2,q);
        z=add(z,z);
        if(n%2==1)q = add(q,z);
        return q;
    }
}

int findN(pi g)
{
    pi q = g;
    int n=1;

    while(n<241)
    {
        bool x = pointOfInfinity(q);
        if(x)return n;
        cout<<q.first<<" "<<q.second<<endl;
        n++;
        q = add(q,g);
    }
    return 0;
}

int main()
{
    cout<<"Entre a b values: ";
    cin>>a>>b;
    cout<<"Entre p values: ";
    cin>>p;

    pair<int,int> g;
    cout<<"Entre g point: ";
    cin>>g.first>>g.second;

    int n = findN(g);
    int na,nb;
    cout<<"n value : "<<n<<endl;

    // generating A private key
    na = rand()%n;
    pi pa = find(na,g);

    cout<<"As public key "<<pa.first<<" "<<pa.second<<endl;

    //generating B private key
    nb = rand()%n;
    pi pb = find(nb,g);
    cout<<"Bs public key "<<pb.first<<" "<<pb.second<<endl;

    pi k = find(na,pb);
    cout<<"shared key "<<k.first<<endl;

    return 0;




}