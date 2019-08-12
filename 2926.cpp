#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 5E4 + 5,MAXL = 35;
int T,n,p;
int A[MAXN],Root[2];
int Trie[2][MAXN * MAXL][2],Siz[MAXN * MAXL];
LL ans,f[MAXL][2];
void Read()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)	scanf("%d",&A[i]);
}
void Save(int x,int type)
{
	int node = Root[type];
	for(int i = 29 ; i >= 0 ; i --)
	{
		int cur = ((1 << i) & x) ? 1 : 0;
		if(!Trie[type][node][cur])	Trie[type][node][cur] = ++ p;
		node = Trie[type][node][cur];
		Siz[node] ++;//�µ㡣 
	}
}
void DFS(int bit,int x,int y)
{
	//�˷���LL�� 
	if(Trie[0][x][0] && Trie[1][y][1])	f[bit + 1][0] += LL(Siz[Trie[0][x][0]])* Siz[Trie[1][y][1]];
	if(Trie[0][x][1] && Trie[1][y][0])	f[bit + 1][1] += LL(Siz[Trie[0][x][1]])* Siz[Trie[1][y][0]];
	if(Trie[0][x][0] && Trie[1][y][0])	DFS(bit + 1,Trie[0][x][0],Trie[1][y][0]);
	if(Trie[0][x][1] && Trie[1][y][1])	DFS(bit + 1,Trie[0][x][1],Trie[1][y][1]);
}
void getAns(int id)
{
	LL temp = 0;
	for(int i = 29 ; i >= 0 ; i --)	
	{
		int cur = ((1 << i) & A[id]) ? 1 : 0;
		temp += f[30 - i][cur];//��ŴӸ�λ����λ��1~30 
	}
	//printf("%lld\n",temp);
	ans += temp;
}
void Init()
{
	memset(Trie,0,sizeof(Trie));
	memset(f,0,sizeof(f));
	memset(Siz,0,sizeof(Siz));
	
	p = 1;
	Root[0] = 1 , Save(A[1],0);
	Root[1] = ++ p;
	for(int i = 3 ; i <= n ; i ++)	Save(A[i],1);
	DFS(0,Root[0],Root[1]);
	
	ans = 0;
	getAns(2);
	//printf("%lld\n",ans);
}
void Update(int type,int bit,int upd,int x,int y)
{
	//�Ӹ�λ����λ��Ӧ1~30λ 
	int cur = ((1 << (29 - bit)) & upd) ? 1 : 0;
	if(type == 0)//������ǰ�� 
	{
		int next1 = Trie[0][x][cur] , next2 = Trie[1][y][cur ^ 1];
		if(next1 == 0)	Trie[0][x][cur] = ++ p , next1 = p;
		if(next2 > 0)
		{
			if(cur == 0)	f[bit + 1][0] += Siz[next2];
			else	f[bit + 1][1] += Siz[next2];
		}	
		Siz[next1] ++;
	}
	else//ɾ�� 
	{
		int next1 = Trie[0][x][cur ^ 1] , next2 = Trie[1][y][cur];
		if(next1 > 0)
		{
			if(cur == 0)	f[bit + 1][1] -= Siz[next1];
			else	f[bit + 1][0] -= Siz[next1];
		}
		Siz[next2] --;
	}
	int xx = Trie[0][x][cur] , yy = Trie[1][y][cur];
	//if(xx > 0 && yy > 0)	Update(type,bit + 1,upd,xx,yy);	
	//������һ������û�У���ҪǱ��ȥ��siz�޸��ˡ�û�о���0������Ҳ����Ӱ��𰸣���Ϊ0û���κ���Ϣ���������С� 
	//ϸ�ڣ����û����һ������Ϊ������ѭ�����жϲ����� 
	if(bit <= 29)	Update(type,bit + 1,upd,xx,yy); 
}
void Ask()
{
	for(int i = 3 ; i <= n - 1 ; i ++)
	{
		Update(0,0,A[i - 1],Root[0],Root[1]);//�� 
		//���⣺��Ϊ����ַ�����Ӧ֧����ӽڵ㣻�����ǽ�������Siz�� 
		Update(1,0,A[i],Root[0],Root[1]);//ɾ 
		getAns(i);
	}
	printf("%lld\n",ans);
}
void Calc()
{
	Init();
	Ask();
}
int main()
{
	freopen("2926.in","r",stdin);
	freopen("2926.out","w",stdout);
	scanf("%d",&T);
	while(T --)
	{
		Read();
		Calc();
	}
	return 0;
}
/*
1
6
6 3 3 8 1 8 
*/
