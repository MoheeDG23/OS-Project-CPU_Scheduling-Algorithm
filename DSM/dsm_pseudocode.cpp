#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

struct request{

    int C;
    int P;
    int mode;
};

typedef struct request req;

set<int> cache[100];
deque<req*> MQ;
vector<pair<int,int>> PCM[100]; // client, mode
set<int> cps_cache[100];
vector<int> POM(100,-1);

int owner_of(int page)
{
    if(PCM[page].size() == 0)
    {
        return -1;
    }
    return PCM[page][0].first;
}

int replicate(int client, int page, int owner, int Mode)
{
    cache[client].insert(page);
    cps_cache[client].insert(page);
    if(PCM[page].size() == 0)
        POM[page] = client;
    PCM[page].push_back({client,Mode});
    return 0;
}

int get_ownership(int page, int client)
{
    POM[page] = client;
    return 0;
}

vector<int> find_clients(int page)
{
    vector<int> clients;
    for(int i=0;i<PCM[page].size();i++)
    {
        clients.push_back(PCM[page][i].first);
    }
    return clients;
}

int invalidate(int page, vector<int> &clients)
{
    int owner = POM[page];
    set<int>:: iterator itr;
    for(int i=0;i<clients.size();i++)
    {
        if(clients[i] != owner)
        {
            itr = cache[clients[i]].find(page);
            cache[clients[i]].erase(itr);
        }
    }
    return 0;
}

int update_cpm(int page, vector<int> &clients)
{
    set<int>:: iterator itr;
    int owner = POM[page];
    for(int i=0;i<clients.size();i++)
    {
        if(clients[i] != owner)
        {
            itr = cps_cache[clients[i]].find(page);
            cps_cache[clients[i]].erase(itr);
        }
    }
    PCM[page].clear();
    PCM[page].push_back({owner,1});
    return 0;
}

int doRead(int client, int page, int MODE)
{
    if(cache[client].find(page) != cache[client].end())
    {
        cout<<"Operation successfully completed!"<<endl;
    }
    else
    {
        req* new_req = new req;
        new_req->C = client;
        new_req->P = page;
        new_req->mode = MODE;
        MQ.push_back(new_req);
    }
    return 0;
}

int doWrite(int client, int page, int MODE)
{
    req* new_req = new req;
    new_req->C = client;
    new_req->P = page;
    new_req->mode = MODE;
    MQ.push_back(new_req);
    return 0;
}

int execute_processes()
{

    while(MQ.empty())
    {
        // Do nothing
    }

    int pid = fork();

    if(pid == 0)
    {
        req* temp = MQ.front();
        int client = temp->C;
        int page = temp->P;
        int Mode = temp->mode;

        if(Mode == 0)
        {
            int owner = POM[page];
            replicate(client,page,owner,Mode);
            doRead(client,page,Mode);
        }
        else
        {
            vector<int> clients_list;
            clients_list = find_clients(page);
            int owner = POM[page];
            if(owner == -1)
                POM[page] = client;
            invalidate(page,clients_list);
            if(client == owner)
            {
                update_cpm(page,clients_list);
            }
            else
            {
                get_ownership(page,client);
                replicate(client,page,owner,1);
                
                set<int>::iterator itr;
                itr = cache[owner].find(page);
                if(itr != cache[owner].end())
                    cache[owner].erase(itr);
                itr = cps_cache[owner].find(page);
                if(itr != cps_cache[owner].end())
                    cps_cache[owner].erase(itr);
                
                for(auto itr_1=PCM[page].begin();itr_1!=PCM[page].end();itr_1++)
                {
                    if((*itr_1).first == owner)
                    {
                        PCM[page].erase(itr_1);
                        break;
                    }
                }
            }
        }

        MQ.pop_front();
    }
    else
    {
        execute_processes();
    }
    return 0;
}

int main()
{
    char op;
    int page_no, client_no;
    int pid = fork();
    if(pid == 0)
        execute_processes();
    else
    {
        while(1)
        {
            cout<<"Enter R or W for Read or Write operations: ";
            cin>>op;
            if(op == 'R')
            {
                cout<<"Enter Client number: ";
                cin>>client_no;
                cout<<"Enter Page number: ";
                cin>>page_no;
                doRead(client_no,page_no,0);
            }
            else if(op == 'W')
            {
                cout<<"Enter Client number: ";
                cin>>client_no;
                cout<<"Enter Page number: ";
                cin>>page_no;
                doWrite(client_no,page_no,1);
            }
        }
    }
    return 0;
}