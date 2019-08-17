#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
using namespace std;
const int MAXB = 25 , MAXC = 105;
long long typedef LL;
int T,nbit,num;
int A[MAXB],C[MAXB];
bool f[MAXB][MAXB][MAXB];
pair<int,int>g[MAXC];
struct wyy{int d[3];}cur;
vector<wyy>t[5];
vector<int>Tmp;
LL n;
//多测不清空，爆零见祖宗。
LL read()
{
	char ch = getchar();
	LL w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w;
} 
void Init()
{
	n = read() , nbit = 0;//多测清空，尤其是下标一类 
	LL temp = n;
	while(temp)
	{
		int x = temp % 10;
		A[++ nbit] = x;
		temp /= 10;
	}
}
void dfsT(int c,int x,int lim)
{
	if(c == lim)//个数达到 
	{
		wyy cur;
		for(int i = 0 ; i < lim ; i ++) cur.d[i] = Tmp[i];//将组合压在一起。 
		t[lim].push_back(cur);//进链表。 
		return;
	}
	if(x > num)	return;
	Tmp.push_back(x);//目前收集到的（记录组合的下标） 
	dfsT(c + 1,x + 1,lim);
	Tmp.pop_back();
	dfsT(c,x + 1,lim);
}
void getCmb()
{
	for(int i = 0 ; i <= 9 ; i ++)
		for(int j = i ; j <= 9 ; j ++)
			g[++ num] = make_pair(i,j);
	for(int i = 1 ; i <= 3 ; i ++)
		dfsT(0,1,i); //收集i个的组合 
}
void DFS(int c,int lim,int s,int had,int bit)
{
	if(c == lim)
	{
		int up = had / 10;
		had -= up * 10;
		if(had == A[bit])
		{
			for(int i = s ;  ; i = (i - 1) & s)
			{
				f[bit + 1][up][i] = 1;
				if(i == 0)	break;
			}
		}
		return;
	}
	if(s & (1 << c))	
	{
		pair<int,int> tmp = g[cur.d[c]];
		int x = tmp.first , y = tmp.second;
		DFS(c + 1,lim,s,had + x,bit);
		DFS(c + 1,lim,s,had + y,bit);
	}
	else	DFS(c + 1,lim,s,had,bit);
}
bool Dp(int lim)//组合个数为lim 
{
	memset(f[1],0,sizeof(f[1]));
	
	int maxs = (1 << lim) - 1;	
	f[1][0][maxs] = 1;
	for(int i = 1 ; i <= nbit ; i ++)
	{
		int ok = 0;
		memset(f[i + 1],0,sizeof(f[i + 1]));
		
		for(int had = 0 ; had <= lim - 1 ; had ++)//进位最多位 = 数的个数 - 1 
		{
			for(int s = 0 ; s <= maxs ; s ++)
			{
				if(!f[i][had][s])	continue;	
				else	ok = 1;			
				DFS(0,lim,s,had,i);//从d[0]~d[lim-1] 
			}
		}
		if(!ok)	return false;//剪枝 
	}
	for(int s = 0 ; s <= maxs ; s ++)	
		if(f[nbit + 1][0][s])	
			return true;
	return false;
}
bool Judge(int lim)
{
	int size = t[lim].size();
	for(int i = 0 ; i < size ; i ++)
	{
		cur = t[lim][i];//枚举选择的组合。 cur.d[0] ~ cur.d[lim - 1]:取的lim个组合。 
		if(Dp(lim))
			return true;
	}
	return false;
}
void Calc()
{
	int i;
	for(i = 1 ; i <= 3 ; i ++)
		if(Judge(i))	break;
	printf("%d\n",i);//3种情况可以化归来做。 
}
int main()
{
	freopen("2939.in","r",stdin);
	freopen("2939.out","w",stdout);
	getCmb();
	T = read();
	while(T --)
	{
		Init();
		Calc();
	}
	return 0;
}
//膜了一发硕奋的程序写法。果然是自己写丑了。三种情况要懂化归；另外选x个的组合应进行预处理，存起来。 
