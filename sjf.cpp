#include<bits/stdc++.h>
using namespace std;

void reorder(vector<int> &a, vector<int> &b, int idx){
	int k,j,key1,key2;
    int n=a.size();
	for(int i=0; i<n; i++){
		j=i-1;
		k=i-1;
		key1=a[i];
		key2=b[i];
		while(j>=idx && key1<a[j]){
			a[j+1]=a[j];
			b[k+1]=b[k];
			j--;
			k--;
		}
		a[j+1]=key1;
		b[k+1]=key2;
	}
}


void sjf(vector<int> &arrival_time, vector<int> &burst_time,vector<int> &completion_time)
{
    int num_proc=arrival_time.size();
    completion_time[0]=arrival_time[0]+burst_time[0];
	for(int i=1;i<num_proc;i++)
    {
		if(completion_time[i-1]>arrival_time[i])
        {
			completion_time[i]=burst_time[i]+completion_time[i-1];
            reorder(arrival_time, burst_time, i);
        }
        else
			completion_time[i]=arrival_time[i]+burst_time[i];
	}
}

pair<double, double> calculate(vector<int> &arrival_time, vector<int> &burst_time,vector<int> &completion_time)
{
    int num_proc=arrival_time.size();
    vector<int> tat(num_proc), wait_time(num_proc);
    double avg_tat=0.0, avg_wait=0.0;


    for(int i=0; i<num_proc; i++)
    {
        tat[i]=completion_time[i]-arrival_time[i];
        wait_time[i]=tat[i]-burst_time[i];
        avg_tat+=tat[i];
        avg_wait+=wait_time[i];
    }

    avg_wait/=num_proc;
    avg_tat/=num_proc;

    pair<double,double> ans;
    ans={avg_tat,avg_wait};

    cout<<endl<<"at     bt      ct       tat    wt"<<endl;
    for(int i=0; i<num_proc; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",arrival_time[i],burst_time[i],completion_time[i],tat[i],wait_time[i]);
    }

    return ans;
}



int main()
{
    int num_proc;
    cout<<"Enter no. of processes: ";cin>>num_proc;cout<<endl;

    vector<int> arrival_time(num_proc);
    vector<int> burst_time(num_proc);
    vector<int> completion_time(num_proc);

    
    for(int i=0; i<num_proc; i++)
    {
        cout<<"For Process "<<i+1<<":"<<endl<<endl;
        cout<<"Arrival Time: ";cin>>arrival_time[i];
        cout<<"Burst Time: ";cin>>burst_time[i];cout<<endl;
    }

    cout<<endl<<endl;

    reorder(arrival_time, burst_time, 0);


    sjf(arrival_time, burst_time, completion_time);
    pair<double, double> results = calculate(arrival_time, burst_time, completion_time);

    double avg_tat, avg_wait;

    avg_tat=results.first;
    avg_wait=results.second;

    cout<<"Avg TAT: "<<avg_tat<<endl<<"Avg Wait Time: "<<avg_wait<<endl;

    
}