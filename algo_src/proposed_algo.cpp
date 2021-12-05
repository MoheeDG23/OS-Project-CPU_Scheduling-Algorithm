#include<bits/stdc++.h>
using namespace std;

void reorder(vector<int> &a, vector<int> &b){
	// int k,j,key1,key2;
    int n=a.size();
	vector< pair<int,int>> temp;

	for(int i=0; i<n; i++) {
		temp.push_back({a[i],b[i]});
	}

	sort(temp.begin(), temp.end());

	for(int i=0; i<n; i++) {
		a[i]=temp[i].first;
		b[i]=temp[i].second;
	}
}

void optimised_round_robin(vector<int> &arrival_time, vector<int> &burst_time,vector<int> &completion_time)
{
    int idx, c, r=0, f=0, rq[100][2];
    int num_proc=arrival_time.size();

    int time_quant=0;
    for(auto i:burst_time) time_quant+=i;
	// cout << time_quant << " " << num_proc << endl;
	time_quant =  time_quant/num_proc;
	// cout << time_quant << " " << num_proc << endl;

    if(burst_time[0]>time_quant){
		c=arrival_time[0]+time_quant;
		burst_time[0]=burst_time[0]-time_quant;
		completion_time[0]=c;
		rq[r][0]=c;
		rq[r][1]=0;
		r++;
		// cout << "1" << endl;
	}
	else{
		c=arrival_time[0]+burst_time[0];
		completion_time[0]=c;
		// cout << "2" << endl;
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
				// cout << "3" << endl;
			}
			else{
				c=c+burst_time[i];
				completion_time[i]=c;
				// cout << "4" << endl;
			}
			i++;
			// cout << "5" << endl;
		}
		else if(r==0){
			if(burst_time[i]>time_quant){
				c=c+time_quant;
				burst_time[i]=burst_time[i]-time_quant;
				rq[r][0]=completion_time[i];
				rq[r][1]=i;
				r++;
				// cout << "6" << endl;
			}
			else{
				c=c+burst_time[i];
				completion_time[i]=c;
				// cout << "7" << endl;
			}
			i++;
			// cout << "8" << endl;
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
				// cout << "9" << endl;
			}
			else{
				c=c+burst_time[idx];
				completion_time[idx]=c;
				// cout << "10" << endl;
			}
			// cout << "11" << /endl;
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
				// cout << "12" << e/ndl;
		}
		else{
				c=c+burst_time[idx];
				completion_time[idx]=c;
				// cout << "13" << endl;/
		}
		// cout << "14" << endl;
	}

    
}

pair<double, double> calculate(vector<int> &arrival_time, vector<int> &burst_copy,vector<int> &completion_time)
{
    int num_proc=arrival_time.size();
    vector<int> tat(num_proc), wait_time(num_proc);
    double avg_tat=0.0, avg_wait=0.0;


    for(int i=0; i<num_proc; i++)
    {
        tat[i]=completion_time[i]-arrival_time[i];
        wait_time[i]=tat[i]-burst_copy[i];
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
        printf("%d\t%d\t%d\t%d\t%d\n",arrival_time[i],burst_copy[i],completion_time[i],tat[i],wait_time[i]);
    }

    return ans;
}


int main()
{
    int num_proc;
    cout<<"Enter no. of processes: ";cin>>num_proc;cout<<endl;

    vector<int> arrival_time(num_proc);
    vector<int> burst_time(num_proc);
    vector<int> burst_copy(num_proc);
    vector<int> completion_time(num_proc);

    
    for(int i=0; i<num_proc; i++)
    {
        cout<<"For Process "<<i+1<<":"<<endl<<endl;
        cout<<"Arrival Time: ";cin>>arrival_time[i];
        cout<<"Burst Time: ";cin>>burst_time[i];cout<<endl;
    }

    cout<<endl<<endl;

    reorder(arrival_time, burst_time);

    burst_copy=burst_time;

    optimised_round_robin(arrival_time, burst_time, completion_time);
    pair<double, double> results = calculate(arrival_time, burst_copy, completion_time);

    double avg_tat, avg_wait;

    avg_tat=results.first;
	avg_wait=results.second;

    cout<<"Avg TAT: "<<avg_tat<<endl<<"Avg Wait Time: "<<avg_wait<<endl;

    
}