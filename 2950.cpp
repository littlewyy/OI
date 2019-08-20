#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005 , MAXB = 35;
int q,n,m;
int A[MAXN];
int Tmp[MAXB],Vis[MAXB];
int read()
{
	char ch = getchar();
	int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w;
}
void Read()
{
	n = read() , m = read();
	for(int i = 1 ; i <= n ; i ++)	A[i] = read();
}
bool Check(int bit)
{
	memset(Tmp,0,sizeof(Tmp));
	int group = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		int ok = 0;
		for(int j = 30 ; j >= bit ; j --)
		{
			if(Vis[j])	continue;
			if(A[i] & (1 << (j - 1)))	Tmp[j] ^= 1;	
			if(!Tmp[j])	ok = 1;//该位异或不为1。 
		}
		if(ok == 0)	//一组 
		{
			group ++;
			for(int j = 30 ; j >= bit ; j --)	Tmp[j] = 0;
		}
	}
	for(int i = 30 ; i >= bit ; i --)	if(Tmp[i])	return false;
	return group >= m;
}
void Calc()
{
	memset(Vis,0,sizeof(Vis));
	
	int ans = 0;
	for(int i = 30 ; i >= 1 ; i --)
	{
		if(Check(i))	ans += 1 << (i - 1);
		else	Vis[i] = 1;
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("2950.in","r",stdin);
	freopen("2950.out","w",stdout);
	q = read();
	while(q --)
	{
		Read();
		Calc();
	}
	return 0;
}
