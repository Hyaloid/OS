/*使用动态优先权的进程的调度算法的模拟20169009*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int Ready[5];
int Block[5];
int runningID;

struct PCB
{
	int id;//进程标识数
	int priority;//优先数
	int cputime;//已经占用cpu时间
	int alltime;//还需占用cpu时间
	int startblock;//进程的阻塞时间
	int blocktime;//进程被阻塞时间
	string  state;//当前状态
	PCB* next;//下一个进程的指针
};

void printf(PCB t[]); //输出进程
void readyList(PCB t[]);  //就绪列表
int main()
{
	//给进程赋值
	PCB thread1= {0,9,0,3,2,3,"Ready"};
	PCB thread2= {1,38,0,3,-1,0,"Ready"};
	PCB thread3= {2,30,0,6,-1,0,"Ready"};
	PCB thread4= {3,29,0,3,-1,0,"Ready"};
	PCB thread5= {4,0,0,4,-1,0,"Ready"};

	PCB thread[5] = {thread1,thread2,thread3,thread4,thread5};
	int countEnd=0,Time=0;//当前结束的进程数量,时间
	int runningID;//正在运行的进程的ID
	//先打印初值
	printf(thread);
	while(countEnd<5)
	{
		//就绪列表第一个即正在运行的进程
		runningID =Ready[0];
		//修改正在运行的进程的情况
		thread[runningID].alltime-=1;
		thread[runningID].cputime+=1;
		//判断是否结束
		if(thread[runningID].alltime==0)
		{
			thread[runningID].priority=0;
			thread[runningID].state="End";
			countEnd++;
			//cout<<"PROG OVER:"<<countEnd<<endl;
		}
		else
		{
			thread[runningID].priority-=3;
			thread[runningID].state="Running";
		}
		//判断是否进行阻塞
		if(thread[runningID].startblock>0&&thread[runningID].blocktime>0)
		{
			//阻塞时间减到0就阻塞
			thread[runningID].startblock--;
			if(thread[runningID].startblock==0)
			{
				thread[runningID].state="Block";
			}
		}

		//修改不在运行的线程情况
		for(int i=0; i<5; i++)
		{
			if(i!=runningID&&thread[i].state!="End"&&thread[i].state!="Block")
			{
				thread[i].priority++;
				thread[i].state="Ready";
			}
			//被阻塞时间为0时解除阻塞
			if(thread[i].state=="Block")
			{
				thread[i].blocktime--;
				if(thread[i].blocktime==0)
				{
					thread[i].state="Ready";
				}
			}
		}
		Time++;
		cout<<"Time:"<<Time<<endl;
		//打印
		printf(thread);

	}

}

//打印函数
void printf(PCB t[])
{
	//找到就绪队列
	readyList(t);
	//找到阻塞队列
	int Block[5];
	for(int i=0; i<5; i++)
	{
		Block[i]=-1;
	}
	int j=0;
	for(int i=0; i<5; i++)
	{
		if(t[i].state=="Block")
			Block[j++]=i;
	}
	//开始打印部分
	cout<<"RUNNING PROG:";
	for(int i=0; i<5; i++)
	{
		if(t[i].state=="Running")
			cout<<i;
	}
	cout<<endl<<"READY_QUEUE:";
	for(int i=0; i<5; i++)
	{
		if(Ready[i]!=-1&&t[Ready[i]].state!="Running")cout<<"->"<<Ready[i];
	}
	cout<<endl<<"BLOCK_QUEUE:";
	for(int i=0; i<5; i++)
	{
		if(Block[i]!=-1)cout<<"->"<<Block[i];
	}
	cout<<endl<<"======================================================="<<endl;
	cout<<"ID\t";
	for(int i=0; i<5; i++)
	{
		cout<<"\t"<<i;
	}
	cout<<endl<<"PRIORITY";
	for(int i=0; i<5; i++)
	{
		cout<<"\t"<<t[i].priority;
	}
	cout<<endl<<"CPUTIME\t";
	for(int i=0; i<5; i++)
	{
		cout<<"\t"<<t[i].cputime;
	}
	cout<<endl<<"ALLTIME\t";
	for(int i=0; i<5; i++)
	{
		cout<<"\t"<<t[i].alltime;
	}
	cout<<endl<<"STARTBLOCK";
	for(int i=0; i<5; i++)
	{
		cout<<"\t"<<t[i].startblock;
	}
	cout<<endl<<"BLOCKTIME";
	for(int i=0; i<5; i++)
	{
		cout<<"\t"<<t[i].blocktime;
	}
	cout<<endl<<"STATE\t";
	for(int i=0; i<5; i++)
	{
		cout<<"\t"<<t[i].state;
	}
	cout<<endl<<"*******************************************************"<<endl;

}
//寻找并排序就绪列表
void readyList(PCB t[])
{
	int j=0;
	//重置队列
	for(int i=0; i<5; i++)
	{
		Ready[i]=-1;
	}
	//添加元素
	for(int i=0; i<5; i++)
	{
		if(t[i].state=="Ready"||t[i].state=="Running")
			Ready[j++]=i;
	}
	//逆序排序
	for(int i=0; i<4; i++)
	{
		for(int k=i+1; k<5; k++)
		{
			if(t[Ready[i]].priority<t[Ready[k]].priority)
			{
				int tmp = Ready[k];
				Ready[k]=Ready[i];
				Ready[i]=tmp;
			}
		}
	}
}



