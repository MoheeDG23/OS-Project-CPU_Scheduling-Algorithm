#include<bits/stdc++.h>
using namespace std;

void reorder(vector<int> &a, vector<int> &b){
	int k,j,key1,key2;
    int n=a.size();
	for(int i=0; i<n; i++){
		j=i-1;
		k=i-1;
		key1=a[i];
		key2=b[i];
		while(j>=0 && key1<a[j]){
			a[j+1]=a[j];
			b[k+1]=b[k];
			j--;
			k--;
		}
		a[j+1]=key1;
		b[k+1]=key2;
	}
}

int main()
{
    int num_proc;
    cout<<"Enter no. of processes: ";cin>>num_proc;cout<<endl;

    vector<int> arrival_time(num_proc);
    vector<int> burst_time(num_proc);
    vector<int> bt1(num_proc);
    vector<int> completion_time(num_proc);

    int idx, time_quant, c, r=0, f=0;
    int rq[100][2];

    cout<<"Enter time quantum: ";cin>>time_quant;cout<<endl;

    for(int i=0; i<num_proc; i++)
    {
        cout<<"For Process "<<i+1<<":"<<endl;
        cout<<"Arrival Time: ";cin>>arrival_time[i];cout<<endl;
        cout<<"Burst Time: ";cin>>burst_time[i];cout<<endl;
    }

    cout<<endl<<endl;

    reorder(arrival_time, burst_time);

    bt1=burst_time;


    if(burst_time[0]>time_quant){
		c=arrival_time[0]+time_quant;
		burst_time[0]=burst_time[0]-time_quant;
		completion_time[0]=c;
		rq[r][0]=c;
		rq[r][1]=0;
		r++;
	}
	else{
		c=arrival_time[0]+burst_time[0];
		completion_time[0]=c;
	}
	int i=1;
	while(i<num_proc){
		if(r!=0 && arrival_time[i]<=rq[f][0]){ // 
			if(burst_time[i]>time_quant){
				c=c+time_quant;
				completion_time[i]=c;
				burst_time[i]=burst_time[i]-time_quant;
				rq[r][0]=c;
				rq[r][1]=i;
				r++;
			}
			else{
				c=c+burst_time[i];
				completion_time[i]=c;
			}
			i++;
		}
		else if(r==0){
			if(burst_time[i]>time_quant){
				c=c+time_quant;
				burst_time[i]=burst_time[i]-time_quant;
				rq[r][0]=completion_time[i];
				rq[r][1]=i;
				r++;
			}
			else{
				c=c+burst_time[i];
				completion_time[i]=c;
			}
			i++;
		}
		else{
			idx=rq[f][1];
			f++;
			if(burst_time[idx]>time_quant){
				c=c+time_quant;
				completion_time[idx]=c;
				burst_time[idx]=burst_time[idx]-time_quant;
				rq[r][0]=completion_time[idx];
				rq[r][1]=idx;
				r++;
			}
			else{
				c=c+burst_time[idx];
				completion_time[idx]=c;
			}
		}
	}
	while(f<r){
		idx=rq[f][1];
		f++;
		if(burst_time[idx]>time_quant){
				c=c+time_quant;
				completion_time[idx]=c;
				burst_time[idx]=burst_time[idx]-time_quant;
				rq[r][0]=completion_time[idx];
				rq[r][1]=idx;
				r++;
		}
		else{
				c=c+burst_time[idx];
				completion_time[idx]=c;
		}
	}

    vector<int> tat(num_proc), wait_time(num_proc);
    double avg_tat=0.0, avg_wait=0.0;


    for(int i=0; i<num_proc; i++)
    {
        tat[i]=completion_time[i]-arrival_time[i];
        wait_time[i]=tat[i]-bt1[i];
        avg_tat+=tat[i];
        avg_wait+=wait_time[i];
    }

    avg_wait/=num_proc;
    avg_tat/=num_proc;

    cout<<"Avg TAT: "<<avg_tat<<endl<<"Avg Wait Time: "<<avg_wait<<endl;

    cout<<endl<<"at     bt      ct       tat    wt"<<endl;
    for(int i=0; i<num_proc; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",arrival_time[i],bt1[i],completion_time[i],tat[i],wait_time[i]);
    }
}