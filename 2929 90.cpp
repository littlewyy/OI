#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E5 + 5 , inf = 0x7fffffff;
int n,dow = inf,up,lef = inf,rig;
int Up[5],Dow[5],Lef[5],Rig[5];
struct wyy
{
	int x,y;
}A[MAXN];
bool cmp(wyy a,wyy b)
{
	return a.x < b.x;
}
void Read()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)	
	{
		scanf("%d%d",&A[i].x,&A[i].y);
		dow = min(dow,A[i].y);
		up  = max(up,A[i].y);
		lef = min(lef,A[i].x);
		rig = max(rig,A[i].x);
	}
	sort(A + 1 , A + 1 + n , cmp);
}
bool RigUp(int t)
{
	int num = 1 , ans = 0;//已有矩形个数。
	Up[1] = up , Dow[1] = up - t , Rig[1] = rig , Lef[1] = rig - t;
	for(int i = n ; i >= 1 ; i --) 
	{
		int x = A[i].x , y = A[i].y;
		if(num == 1)
		{
			if(x >= Lef[1] && x <= Rig[1] && y >= Dow[1] && y <= Up[1])	ans ++;
			else
			{
				if(y >= dow && y <= dow + t)
				{
					num ++;
					Up[2] = dow + t , Dow[2] = dow , Rig[2] = x , Lef[2] = x - t;
					ans ++;
				}
			}
		}
		else
		{
			for(int j = 1 ; j <= num ; j ++)
			{
				if(x >= Lef[j] && x <= Rig[j] && y >= Dow[j] && y <= Up[j])
				{
					ans ++;
					break;
				}
			}
		}
	}
	int minh = inf , maxh = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = A[i].x , y = A[i].y;
		int ok = 0;
		for(int j = 1 ; j <= num ; j ++)
		{
			if(x >= Lef[j] && x <= Rig[j] && y >= Dow[j] && y <= Up[j])
			{
				ok = 1;
				break;
			}
		}
		if(ok == 1)	continue;//没被另外两个收治。 
		if(x >= lef && x <= lef + t)//没人要且在左区间内，考虑收治。	
		{
			ans ++;
			minh = min(minh,y);
			maxh = max(maxh,y);
		}
	}
	if(ans < n)	return false;//怎样都包不完包不完。
	if(minh != inf && maxh - minh > t)	return false;//假的包完收治。 
	return true; 
}
bool RigDow(int t)
{
	int num = 1 , ans = 0;//已有矩形个数。
	Up[1] = dow + t, Dow[1] = dow , Rig[1] = rig , Lef[1] = rig - t;
	for(int i = n ; i >= 1 ; i --) 
	{
		int x = A[i].x , y = A[i].y;
		if(num == 1)
		{
			if(x >= Lef[1] && x <= Rig[1] && y >= Dow[1] && y <= Up[1])	ans ++;
			else
			{
				if(y >= up - t && y <= up)
				{
					num ++;
					Up[2] = up , Dow[2] = up - t , Rig[2] = x , Lef[2] = x - t;
					ans ++;
				}
			}
		}
		else
		{
			for(int j = 1 ; j <= num ; j ++)
			{
				if(x >= Lef[j] && x <= Rig[j] && y >= Dow[j] && y <= Up[j])
				{
					ans ++;
					break;
				}
			}
		}
	}
	int minh = inf , maxh = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = A[i].x , y = A[i].y;
		int ok = 0;
		for(int j = 1 ; j <= num ; j ++)
		{
			if(x >= Lef[j] && x <= Rig[j] && y >= Dow[j] && y <= Up[j])
			{
				ok = 1;
				break;
			}
		}
		if(ok == 1)	continue;//没被另外两个收治。 
		if(x >= lef && x <= lef + t)//没人要且在左区间内，考虑收治。	
		{
			ans ++;
			minh = min(minh,y);
			maxh = max(maxh,y);
		}
	}
	if(ans < n)	return false;//怎样都包不完包不完。
	if(minh != inf && maxh - minh > t)	return false;//假的包完。 
	return true; 
}
bool LefDow(int t)
{
	int num = 1 , ans = 0;//已有矩形个数。
	Up[1] = dow + t, Dow[1] = dow , Rig[1] = lef + t , Lef[1] = lef;
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = A[i].x , y = A[i].y;
		if(num == 1)
		{
			if(x >= Lef[1] && x <= Rig[1] && y >= Dow[1] && y <= Up[1])	ans ++;
			else
			{
				if(y >= up - t && y <= up)
				{
					num ++;
					Up[2] = up , Dow[2] = up - t , Rig[2] = x + t , Lef[2] = x;
					ans ++;
				}
			}
		}
		else
		{
			for(int j = 1 ; j <= num ; j ++)
			{
				if(x >= Lef[j] && x <= Rig[j] && y >= Dow[j] && y <= Up[j])
				{
					ans ++;
					break;
				}
			}
		}
	}
	int minh = inf , maxh = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = A[i].x , y = A[i].y;
		int ok = 0;
		for(int j = 1 ; j <= num ; j ++)
		{
			if(x >= Lef[j] && x <= Rig[j] && y >= Dow[j] && y <= Up[j])
			{
				ok = 1;
				break;
			}
		}
		if(ok == 1)	continue;//没被另外两个收治。 
		if(x >= rig - t && x <= rig)//没人要且在左区间内，考虑收治。	
		{
			ans ++;
			minh = min(minh,y);
			maxh = max(maxh,y);
		}
	}
	if(ans < n)	return false;//怎样都包不完包不完。
	if(minh != inf && maxh - minh > t)	return false;//假的包完收治。 
	return true; 
}
bool LefUp(int t)
{
	int num = 1 , ans = 0;//已有矩形个数。
	Up[1] = up , Dow[1] = up - t , Rig[1] = lef + t , Lef[1] = lef;
	for(int i = n ; i >= 1 ; i --) 
	{
		int x = A[i].x , y = A[i].y;
		if(num == 1)
		{
			if(x >= Lef[1] && x <= Rig[1] && y >= Dow[1] && y <= Up[1])	ans ++;
			else
			{
				if(y >= dow && y <= dow + t)
				{
					num ++;
					Up[2] = dow + t , Dow[2] = dow , Rig[2] = x + t , Lef[2] = x;
					ans ++;
				}
			}
		}
		else
		{
			for(int j = 1 ; j <= num ; j ++)
			{
				if(x >= Lef[j] && x <= Rig[j] && y >= Dow[j] && y <= Up[j])
				{
					ans ++;
					break;
				}
			}
		}
	}
	int minh = inf , maxh = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = A[i].x , y = A[i].y;
		int ok = 0;
		for(int j = 1 ; j <= num ; j ++)
		{
			if(x >= Lef[j] && x <= Rig[j] && y >= Dow[j] && y <= Up[j])
			{
				ok = 1;
				break;
			}
		}
		if(ok == 1)	continue;//没被另外两个收治。 
		if(x >= rig - t && x <= rig)//没人要且在左区间内，考虑收治。	
		{
			ans ++;
			minh = min(minh,y);
			maxh = max(maxh,y);
		}
	}
	if(ans < n)	return false;//怎样都包不完包不完。
	if(minh != inf && maxh - minh > t)	return false;//假的包完收治。 
	return true; 
}
bool Check(int t)
{
	if(RigUp(t))	return true;
	if(RigDow(t))	return true;
	if(LefDow(t))	return true;
	if(LefUp(t))	return true;
	return false;
}
void Calc()
{
	int lo = 0 , hi = 1e9;
	//左开右闭 
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		if(Check(mid))	hi = mid;
		else	lo = mid;
	}
	printf("%d\n",hi);
}
int main()
{
	freopen("2929.in","r",stdin);
	freopen("2929.out","w",stdout);
	Read();
	Calc();
	return 0;
}
