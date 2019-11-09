#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,a[100005],mod,times,m;
long long ans;
priority_queue<long long>s;
void step1()
{
	for(int i=1;i<=times;i++)
	{
		long long  sum=0;
		for(int j=1;j<=m;j++)
		{
			long long now=s.top()*-1;
			s.pop();
			ans+=now;
			sum+=now;
		}
		s.push(-sum);
	}
}
void step2()
{
	for(int i=1;i<=mod;i++)	
	{
		ans+=s.top()*-1;
		s.pop();
	}
	s.push(-ans);
	int now=mod+1;
	for(int i=1;i<=times;i++)
	{
		long long  sum=0;
		for(int j=1;j<=m;j++)
		{
			long long now=s.top()*-1;
			s.pop();
			ans+=now;
			sum+=now;
		}
		s.push(-sum);
	}	
}
int main()
{
	freopen("1757.in","r",stdin);
	freopen("1757.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)	
	{
		cin>>a[i];
		s.push(-a[i]);
	}
    mod=n%(m-1),times=n/(m-1);
	if(mod==1)	step1();
	else step2();	
	cout<<ans<<endl;
	return 0;
}
