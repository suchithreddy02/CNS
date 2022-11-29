#include<bits/stdc++.h>
using namespace std;



vector<vector<string>> sbox
       { {"63","7C","77","7B","F2","6B","6F","C5","30","01","67","2B","FE","D7","AB","76"},
        {"CA","82","C9","7D","FA","59","47","F0","AD","D4","A2","AF","9C","A4","72","C0"},
        {"B7","FD","93","26","36","3F","F7","CC","34","A5","E5","F1","71","D8","31","15"},
        {"04","C7","23","C3","18","96","05","9A","07","12","80","E2","EB","27","B2","75"},
        {"09","83","2C","1A","1B","6E","5A","A0","52","3B","D6","B3","29","E3","2F","84"},
        {"53","D1","00","ED","20","FC","B1","5B","6A","CB","BE","39","4A","4C","58","CF"},
        {"D0","EF","AA","FB","43","4D","33","85","45","F9","02","7F","50","3C","9F","A8"},
        {"51","A3","40","8F","92","9D","38","F5","BC","B6","DA","21","10","FF","F3","D2"},
        {"CD","0C","13","EC","5F","97","44","17","C4","A7","7E","3D","64","5D","19","73"},
        {"60","81","4F","DC","22","2A","90","88","46","EE","B8","14","DE","5E","0B","DB"},
        {"E0","32","3A","0A","49","06","24","5C","C2","D3","AC","62","91","95","E4","79"},
        {"E7","C8","37","6D","8D","D5","4E","A9","6C","56","F4","EA","65","7A","AE","08"},
        {"BA","78","25","2E","1C","A6","B4","C6","E8","DD","74","1F","4B","BD","8B","8A"},
        {"70","3E","B5","66","48","03","F6","0E","61","35","57","B9","86","C1","1D","9E"},
        {"E1","F8","98","11","69","D9","8E","94","9B","1E","87","E9","CE","55","28","DF"},
        {"8C","A1","89","0D","BF","E6","42","68","41","99","2D","0F","B0","54","BB","16"}
       };

vector<string> rcon {"01","02","04","08","10","20","40","80","1B","36"};
string hextobin(string s){

unordered_map<char, string> mp;
	mp['0'] = "0000";
	mp['1'] = "0001";
	mp['2'] = "0010";
	mp['3'] = "0011";
	mp['4'] = "0100";
	mp['5'] = "0101";
	mp['6'] = "0110";
	mp['7'] = "0111";
	mp['8'] = "1000";
	mp['9'] = "1001";
	mp['A'] = "1010";
	mp['B'] = "1011";
	mp['C'] = "1100";
	mp['D'] = "1101";
	mp['E'] = "1110";
	mp['F'] = "1111";

string bin="";

for(int i=0;i<s.size();i++)
{
    bin+=mp[s[i]];
}

return bin;
}

string bintohex(string s)
{
    unordered_map<string, string> mp;
	mp["0000"] = "0";
	mp["0001"] = "1";
	mp["0010"] = "2";
	mp["0011"] = "3";
	mp["0100"] = "4";
	mp["0101"] = "5";
	mp["0110"] = "6";
	mp["0111"] = "7";
	mp["1000"] = "8";
	mp["1001"] = "9";
	mp["1010"] = "A";
	mp["1011"] = "B";
	mp["1100"] = "C";
	mp["1101"] = "D";
	mp["1110"] = "E";
	mp["1111"] = "F";
    string hex="";
    string temp="";
    for(int i=0;i<s.size();i++)
    {
        temp+=s[i];
        if(temp.size()==4)
        {
            hex+=mp[temp];
            temp="";
        }
    }
    return hex;
}

string xorOperation(string s1,string s2)
{
   s1=hextobin(s1);
   s2=hextobin(s2);
   string ans="";
   int n=s1.size();

   for(int i=0;i<n;i++)
   {
     if(s1[i]==s2[i])
     {
        ans+="0";
     }
     else
     {
        ans+="1";
     }
   }
  return bintohex(ans);

}

string dectobin(int x)
{
    string ans="";
    int n=4;
    while(n--)
    {
        int rem = x%2;
        x/=2;
        ans = ((rem == 0) ? "0" : "1") + ans;
    }
    return ans;
}

int bintodec(string x)
{
    int j = 0;
    int n = x.size();
    int ans = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        if(x[i]=='1')
            ans += pow(2, j);
        j++;
    }

    return ans;
}

string subSbox(string s)
{
    string x=s.substr(0,1);
    string y=s.substr(1,1);

    x=hextobin(x);
    y=hextobin(y);
    int i=bintodec(x);
    int j=bintodec(y);

    return sbox[i][j];
}

string g(string s,int rno)
{
 
 vector<string> v(4,"");

 for(int i=0;i<s.size();i+=2)
 {
    v[i/2]=s.substr(i,2);
 }

 //performing the left one-byte circular shift

 string temp=v[0];
 for(int i=0;i<3;i++)
 {
    v[i]=v[i+1];
 }
 v[3]=temp;

 //performing the substitution using substitution box

 for(int i=0;i<4;i++)
 {
    v[i]=subSbox(v[i]);
 }

 // performing xor with roundconstant
 v[0] = xorOperation(v[0], rcon[rno]);

 string W = "";
 for (int i = 0; i < 4; i++)
    W += v[i];

 return W;
}

vector<string> KtoW(vector<vector<string>> &k)
{
   vector<string> W(4,"");

   for(int j=0;j<4;j++)
   {
    for(int i=0;i<4;i++)
    {
        W[j]+=k[i][j];
    }
   }

   return W;
}

vector<vector<string>> WtoK(vector<string> &W)
{
    vector<vector<string>> K(4,vector<string>(4,""));

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            K[i][j]=W[j].substr(2*i,2);
        }
    }

    return K;
}

vector<vector<string>> keyExpansion(vector<vector<string>> &k,int rno)
{
   
  vector<string> W = KtoW(k);
  vector<string> WF(4,"");

  for(int i=0;i<4;i++)
  {
    if(i==0)
    {
        WF[i]=xorOperation(W[i],g(W[i+3],rno));
    }
    else
    {
       WF[i]=xorOperation(W[i],WF[i-1]);
    }
  }

  return WtoK(WF);

}

void addRoundKey(vector<vector<string>> &ip,vector<vector<string>> &k)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            ip[i][j]=xorOperation(ip[i][j],k[i][j]);
        }
    }
}

void subStituteByteTransformation(vector<vector<string>> &ip)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            ip[i][j]=subSbox(ip[i][j]);
        }
    }
}

void leftCircularShift(vector<string> &v,int pos)
{
    int n=v.size();
    vector<string> temp(n,"");

    for(int i=0;i<n;i++)
    {
        temp[i]=v[(i+pos)%n];
    }

    for(int i=0;i<n;i++)
    {
        v[i]=temp[i];
    }
}

void shiftRow(vector<vector<string>> &ip)
{
    for(int i=0;i<4;i++)
    {
        leftCircularShift(ip[i],i);
    }
}

string multiply(string s,int no)
{
    string temp="1B";
    if(no>=2)
    {
        string bs = hextobin(s);
        bool b7 = false;

        if(bs[0]=='1')b7=true;

        for(int i=0;i<bs.size();i++)
        {
            if(i+1<bs.size())bs[i]=bs[i+1];
        }
        bs[7] = '0';

        bs = bintohex(bs);
        if (b7)
            bs = xorOperation(bs, temp);

        if(no>2)
        {
            bs=xorOperation(bs,s);
        }
       
        s=bs;      
    }

    return s;
}
void mixColoumn(vector<vector<string>> &ip)
{
     vector<vector<int>> mat {{2,3,1,1},
                              {1,2,3,1},
                              {1,1,2,3},
                              {3,1,1,2}};

      vector<vector<string>> temp(4,vector<string>(4,""));
    
      for(int i=0;i<4;i++)
      {
        for(int j=0;j<4;j++)
        {
            string ans="00";
            for(int k=0;k<4;k++)
            {
                string x=multiply(ip[k][j],mat[i][k]);
                // cout << x << " ";
                ans = xorOperation(ans, x);
            }
            temp[i][j] = ans;
        }
      }

      for(int i=0;i<4;i++)
      {
        for(int j=0;j<4;j++)
        {
            ip[i][j]=temp[i][j];
        }
      }

}

int main()
{

      vector<vector<string>> ip{
          {"01", "89", "FE", "76"},
          {"23", "AB", "DC", "54"},
          {"45", "CD", "BA", "32"},
          {"67", "EF", "98", "10"}};

      vector<vector<string>> key{
          {"0F", "47", "0C", "AF"},
          {"15", "D9", "B7", "7F"},
          {"71", "E8", "AD", "67"},
          {"C9", "59", "D6", "98"}};

      // vector<vector<string>> ip(4,vector<string>(4,""));
      // vector<vector<string>> key(4,vector<string>(4,""));

      // cout<<"Entre the 4*4 matrix (hexadecimal) input \n";

      // for(int i=0;i<4;i++)
      // {
      //     for(int j=0;j<4;j++)
      //     {
      //         cin>>ip[j][i];
      //     }
      // }

      // cout<<"Entre the 4*4 matrix (hexadecimal) key \n";

      // for(int i=0;i<4;i++)
      // {
      //     for(int j=0;j<4;j++)
      //     {
      //         cin>>key[j][i];
      //     }
      // }

      // preprocessing round before 1 round
      addRoundKey(ip, key);

      // performing the 9 rounds

      for (int i = 0; i < 10; i++)
      {

        cout << "\n ip " <<i+1<< endl;

        for (int p = 0; p < 4;p++)
        {
            for (int q = 0; q < 4;q++)
                cout << ip[p][q] << " ";
            cout << endl;
        }

        // performing key expansion for next round
        key = keyExpansion(key, i);

        // Substitute Byte Transformation
        subStituteByteTransformation(ip);

        //Shift Rows
        shiftRow(ip);

        //Mix Coloumn

        if (i < 9)
            mixColoumn(ip);

        //addRound key
        addRoundKey(ip,key);

   }

   cout << " \n Encrypted message \n";
   for (int i = 0; i < 4;i++)
   {
     for (int j = 0; j < 4;j++)
     {
            cout << ip[i][j] << " ";
     }
     cout << endl;
   }

   return 0;
}