//Sleeping Barber Problem
#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

struct tasks
{
    int id,at,bt;
    bool done=false;// To show if customer was addressed
};

tasks *t;
int n,chairs;
int total_time;
sem_t semaphore;
int *chop;
queue <int> q;

void sort_tasks(int n){
    //selection sort is implemented to sort according to arrival times
    tasks temp;
    int i,j,min;
    for(i=0;i<n-1;i++){
        min=i;
        for(j=i+1;j<n;j++){
            if(t[j].at<t[min].at){
                min=j;
            }
        }
        temp=t[min];
        t[min]=t[i];
        t[i]=temp;
    }
}

void get_times(){
    int i=0,total_time=0,count=0,exec;
    if(t[i].at!=total_time) cout<<"\tAt t="<<total_time<<" barber sleeps\n";
    //Barber sleeps until this first customer arrives
    total_time=t[i].at;
    //Now this customer will be definetely executed
    count++;t[i].done=true;
    total_time+=t[i].bt;
    cout<<"\tAt t="<<total_time<<" customer "<<t[i].id<<" finished his cutting\n";
    bool barb=false;//To show if barber is sleeping
    while(count<n){
        barb=false;
        for(i=0;i<n;i++){
            if(t[i].at<=total_time&&t[i].done==false){
                barb=true;//This means that some customer is here and barber cant be asleep
                if(q.size()<chairs){
                    q.push(i);//We push customer into shop
                    t[i].done=true;//It will be eventually completed
                    count++;
                }
                else{
                    t[i].done=true;
                    count++;
                    cout<<"\t"<<t[i].id<<" left the shop as there was no vacany\n";
                }    
            }
        }
        //We can surely say barber goes to sleep only if there is no person waiting 
        if(barb==false&&q.empty()){
            cout<<"\tAt t="<<total_time<<" barber sleeps\n";
            for(i=0;i<n;i++){
                if(t[i].done==false) break;
                //i contains index of upcoming customer
            }
            //Barber sleeps until this customer arrives
            total_time=t[i].at;
            q.push(i);count++;t[i].done=true;//As i will be eventually executed
        }
        exec=q.front();q.pop();
        //This customer will have cutting until its done
        total_time+=t[exec].bt;
        cout<<"\tAt t="<<total_time<<" customer "<<t[exec].id<<" finished his cutting\n";
    }
    while(!q.empty()){
        exec=q.front();q.pop();
        total_time+=t[exec].bt;
        cout<<"\tAt t="<<total_time<<" customer "<<t[exec].id<<" finished his cutting\n";
    }
}

void print_table(int n){
    cout<<"\tid\tat\tbt\n";
    for(int i=0;i<n;i++){
        cout<<"\t"<<t[i].id<<"\t"<<t[i].at<<"\t"<<t[i].bt<<"\t"<<"\n";
    }
}

int main()
{
    system("cls");
    cout<<"\n\n\n\t---------------------------------------\n";
    cout<<"\t            SLEEPING BARBERS           \n";
    cout<<"\t---------------------------------------\n\n";
    int i;
    cout<<"\tEnter no of customer chairs in shop : ";cin>>chairs;
    cout<<"\tEnter no of customers : ";
    cin>>n;
    t = (tasks*)malloc((n)*sizeof(tasks));
    cout<<"\tGive arrival time of each customer : ";
    for(i=0;i<n;i++){
        t[i].id=i+1;
        t[i].done=false;
        cin>>t[i].at;
    }
    cout<<"\tGive burst time of each customer   : ";
    for(i=0;i<n;i++){
        cin>>t[i].bt;
    }

    sort_tasks(n);
    //Using selection sort we sort all tasks in increasing order of arrival time
    //print_table(n);
    cout<<"\n\t --- TIMELINE --- \n";
    get_times();
    //snippet for telling which task was active
    //print_table(philno);
    cout<<"\n\tAll tasks were addressed\n";
    cout<<"\n\t          Press any key to continue! ";
    getchar();
    getchar();
    return 0;
}
