#include <bits/stdc++.h>
#include <termio.h>
#define RESET   "\033[0m"
#define ITALIC  "\033[3m"
#define CYAN    "\033[36m"
#define RED_BACK     "\033[41m"
#define GREEN_BACK   "\033[42m"
#define YELLOW_BACK  "\033[43m"
#define BLUE_BACK    "\033[44m"
#define WHITE_BACK   "\033[47m"
using namespace std;
int mp[105][105],x=8,y=8,star,n='d',maxn,m,high;
bool flag=false;
int scanKeyboard()
{
    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings=stored_settings;
    new_settings.c_lflag&=(~ICANON);
    new_settings.c_cc[VTIME]=0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0,TCSANOW,&new_settings);
    in=getchar();
    tcsetattr(0,TCSANOW,&stored_settings);
    return in;
}
int suiji(int minn,int maxn)
{
	random_device seed;
	ranlux48 engine(seed());
	uniform_int_distribution<> distrib(minn, maxn);
    return(distrib(engine));
}
void p()
{
	if(mp[x][y]==-1)
	{
		flag=false;
		star++;
		if(star>high)
		{
			high=star;
		}
	}
	if(!flag)
	{
		for(int i=1;i<=16;i++)
		{
			for(int j=1;j<=16;j++)
			{
				if(mp[i][j]>=1)
				{
					mp[i][j]++;
				}
			}	
		}
		mp[x][y]=1;
	}
	else
	{
		if(x==0)
		{
			x=16;
		}
		if(x==17)
		{
			x=1;
		}
		if(y==0)
		{
			y=16;
		}
		if(y==17)
		{
			y=1;
		}
		if(mp[x][y]>1)
		{
			fstream hi("data/highest.txt");
			hi<<high;
			hi.close();
			cout<<"游戏结束！"<<endl;
			exit(0);
		}
		maxn=-1;
		for(int i=1;i<=16;i++)
		{
			for(int j=1;j<=16;j++)
			{
				maxn=max(maxn,mp[i][j]);
			}
		}
		for(int i=1;i<=16;i++)
		{
			for(int j=1;j<=16;j++)
			{
				if(mp[i][j]==maxn)
				{
					mp[i][j]=0;
				}
				else if(mp[i][j]>=1)
				{
					mp[i][j]++;
				}
			}
		}
		mp[x][y]=1;
	}
	while(!flag)
	{
		int xx=suiji(1,16);
		int yy=suiji(1,16);
		if(mp[xx][yy]==0)
		{
			mp[xx][yy]=-1;
			flag=true;
		}
	}
	system("clear");
	cout<<"得 分： "<<CYAN<<star<<RESET<<"                            "<<"最 高 得 分： "<<ITALIC<<CYAN<<high<<RESET<<endl;
	cout<<YELLOW_BACK<<"                                                      "<<RESET<<endl;
	for(int i=1;i<=16;i++)
	{
		cout<<YELLOW_BACK<<"   "<<RESET;
		for(int j=1;j<=16;j++)
		{
			if(mp[i][j]==1)
			{
				cout<<BLUE_BACK<<"   "<<RESET;
			}
			else if(mp[i][j]>1)
			{
				cout<<GREEN_BACK<<"   "<<RESET;
			}
			else if(mp[i][j]==-1)
			{
				cout<<RED_BACK<<"   "<<RESET;
			}
			else
			{
				cout<<WHITE_BACK<<"   "<<RESET;
			}
		}
		cout<<YELLOW_BACK<<"   "<<RESET<<endl;
	}
	cout<<YELLOW_BACK<<"                                                      "<<RESET<<endl;
}
void f()
{
	while(1)
	{
		m=n;
		n=scanKeyboard();
		if(n!='w'&&n!='a'&&n!='s'&&n!='d'&&n!=27)
		{
			n=m;
			continue;
		}
		else if(n=='w'&&m=='s')
		{
			n=m;
			continue;
		}
		else if(n=='a'&&m=='d')
		{
			n=m;
			continue;
		}
		else if(n=='s'&&m=='w')
		{
			n=m;
			continue;
		}
		else if(n=='d'&&m=='a')
		{
			n=m;
			continue;
		}
		else if(n!=27)
		{
			continue;
		}
		int a=scanKeyboard();
		if(a!=91)
		{
			continue;
		}
		int b=scanKeyboard();
		if(n==27&&a==91)
		{
			if(b==65)
			{
				if(m=='s')
				{
					n=m;
				}
				else
				{
					n='w';
				}
			}
			else if(b==66)
			{
				if(m=='w')
				{
					n=m;
				}
				else
				{
					n='s';
				}
			}
			else if(b==67)
			{
				if(m=='a')
				{
					n=m;
				}
				else
				{
					n='d';
				}
			}
			else if(b==68)
			{
				if(m=='d')
				{
					n=m;
				}
				else
				{
					n='a';
				}
			}
			else
			{
				n=m;
			}
		}
	}
}
int main()
{
	printf("\033[?25l");
	fstream hi("data/highest.txt");
	hi>>high;
	hi.close();
	mp[x][y]=1;
	mp[x][y-1]=2;
	thread t(f);
    t.detach();
	while(1)
	{
		if(n=='w')
		{
			if(x>=1)
			{
				x--;
			}
			p();
		}
		else if(n=='a')
		{
			if(y>=1)
			{
				y--;
			}
			p();
		}
		else if(n=='s')
		{
			if(x<=16)
			{
				x++;
			}
			p();
		}
		else if(n=='d')
		{
			if(y<=16)
			{
				y++;
			}
			p();
		}
		usleep(100000);
	}
}