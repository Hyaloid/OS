/*ʹ�ö�̬����Ȩ�Ľ��̵ĵ����㷨��ģ��20169009*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int Ready[5];
int Block[5];
int runningID;

struct PCB
{
	int id;//���̱�ʶ��
	int priority;//������
	int cputime;//�Ѿ�ռ��cpuʱ��
	int alltime;//����ռ��cpuʱ��
	int startblock;//���̵�����ʱ��
	int blocktime;//���̱�����ʱ��
	string  state;//��ǰ״̬
	PCB* next;//��һ�����̵�ָ��
};

void printf(PCB t[]); //�������
void readyList(PCB t[]);  //�����б�
int main()
{
	//�����̸�ֵ
	PCB thread1= {0,9,0,3,2,3,"Ready"};
	PCB thread2= {1,38,0,3,-1,0,"Ready"};
	PCB thread3= {2,30,0,6,-1,0,"Ready"};
	PCB thread4= {3,29,0,3,-1,0,"Ready"};
	PCB thread5= {4,0,0,4,-1,0,"Ready"};

	PCB thread[5] = {thread1,thread2,thread3,thread4,thread5};
	int countEnd=0,Time=0;//��ǰ�����Ľ�������,ʱ��
	int runningID;//�������еĽ��̵�ID
	//�ȴ�ӡ��ֵ
	printf(thread);
	while(countEnd<5)
	{
		//�����б��һ�����������еĽ���
		runningID =Ready[0];
		//�޸��������еĽ��̵����
		thread[runningID].alltime-=1;
		thread[runningID].cputime+=1;
		//�ж��Ƿ����
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
		//�ж��Ƿ��������
		if(thread[runningID].startblock>0&&thread[runningID].blocktime>0)
		{
			//����ʱ�����0������
			thread[runningID].startblock--;
			if(thread[runningID].startblock==0)
			{
				thread[runningID].state="Block";
			}
		}

		//�޸Ĳ������е��߳����
		for(int i=0; i<5; i++)
		{
			if(i!=runningID&&thread[i].state!="End"&&thread[i].state!="Block")
			{
				thread[i].priority++;
				thread[i].state="Ready";
			}
			//������ʱ��Ϊ0ʱ�������
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
		//��ӡ
		printf(thread);

	}

}

//��ӡ����
void printf(PCB t[])
{
	//�ҵ���������
	readyList(t);
	//�ҵ���������
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
	//��ʼ��ӡ����
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
//Ѱ�Ҳ���������б�
void readyList(PCB t[])
{
	int j=0;
	//���ö���
	for(int i=0; i<5; i++)
	{
		Ready[i]=-1;
	}
	//���Ԫ��
	for(int i=0; i<5; i++)
	{
		if(t[i].state=="Ready"||t[i].state=="Running")
			Ready[j++]=i;
	}
	//��������
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



