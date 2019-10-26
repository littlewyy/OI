#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2E6 + 5;
int r,p,s,n;
char nans[MAXN],ans[MAXN];
void Read()
{
	scanf("%d%d%d",&r,&p,&s);
	n = r + p + s;
}
bool CheckMax(int s1,int t1,int s2,int t2)//a > b£¿ 
{
	for(int i = s1 , j = s2 ; i <= t1 , j <= t2 ; i ++ , j ++)
	{
		if(nans[i] < nans[j])
			return false;
		if(nans[i] > nans[j])
			return true;
	}
	return false;
}
bool CheckMin()
{
	for(int i = 0 ; i < n ; i ++)	
	{
		if(nans[i] < ans[i])	
			return true;
		if(nans[i] > ans[i])
			return false;
	}
	return false;
}
void Swap(int s1,int t1,int s2,int t2)
{
	for(int i = s1 , j = s2 ; i <= t1 , j <= t2 ; i ++ , j ++)
	{
		char temp = nans[i];
		nans[i] = nans[j];
		nans[j] = temp;
	}
}
void Check(int res,int st,int end,int &ur,int &up,int &us)
{
	if(end == st)	
	{
		if(res == 1)	ur = 0 , up = 1 , us = 0 , nans[st] = 'P';
		if(res == 2)	ur = 0 , up = 0 , us = 1 , nans[st] = 'S';
		if(res == 3)	ur = 1 , up = 0 , us = 0 , nans[st] = 'R';
		return;
	}
	int lr,lp,ls,rr,rp,rs,mid = (st + end) >> 1;
	if(res == 1)
	{
		Check(1,st,mid,lr,lp,ls);
		Check(3,mid + 1,end,rr,rp,rs);
	}
	if(res == 2)
	{
		Check(1,st,mid,lr,lp,ls);
		Check(2,mid + 1,end,rr,rp,rs);
	}
	if(res == 3)
	{
		Check(3,st,mid,lr,lp,ls);
		Check(2,mid + 1,end,rr,rp,rs);
	}
	if(CheckMax(st,mid,mid + 1,end))//a > b
		Swap(st,mid,mid + 1,end);
	ur = lr + rr , up = lp + rp , us = ls + rs;
}
void Calc()
{
	for(int i = 0 ; i < n ; i ++)	ans[i] = 'Z';
	int ok = 0;
	for(int i = 1 ; i <= 3 ; i ++)
	{
		int ur,up,us;
		Check(i,0,n - 1,ur,up,us);
		if(ur == r && up == p && us == s)
		{
			if(CheckMin())
			{
				for(int j = 0 ; j < n ; j ++)
					ans[j] = nans[j];
				ok = 1;
			}			
		}
	}
	if(ok == 1)	for(int i = 0 ; i < n ; i ++)	putchar(ans[i]);
	else	printf("IMPOSSIBLE\n");
}
int main()
{
	freopen("2991.in","r",stdin);
	freopen("2991.out","w",stdout);
	Read();
	Calc();
	return 0;
}
