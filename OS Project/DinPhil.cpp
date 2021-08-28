#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

struct tasks
{
    int id,at,bt;
    int status=0;// 0 means waiting for fork,1 means eating, 2 means completed eating
};

tasks *t;
int n,done;
int total_time;
sem_t semaphore;
int *chop;

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
    int i=0;total_time=-1;done=0;
    while(done<n){
        cout<<"\n";total_time++;//cout<<"Chopstick situation ";for(i=0;i<n;i++){cout<<chop[i];}cout<<"\n";
        cout<<"\tTime: "<<total_time<<"s\n";
        for(i=0;i<n;i++){
            if(t[i].status!=2&&t[i].at<=total_time){
                if(t[i].status==0){
                    if(chop[t[i].id-1]==0&&chop[(t[i].id)%(n)]==0){
                        cout<<"\tPhilosopher "<<t[i].id<<" starts eating\n";
                        chop[t[i].id-1]=t[i].bt;chop[(t[i].id)%(n)]=t[i].bt;t[i].status=1;
                    }
                    else{cout<<"\tPhilosopher "<<t[i].id<<" is waiting for chopsticks\n";}
                }
                else{
                    chop[t[i].id-1]--;chop[(t[i].id)%(n)]--;
                    if(chop[t[i].id-1]==0){
                        cout<<"\tPhilosopher "<<t[i].id<<" finished eating\n";
                        done++;t[i].status=2;
                    }
                    else cout<<"\tPhilosopher "<<t[i].id<<" is eating\n";
                }
            }
        }
    }
}

void print_table(int n){
    cout<<"\n\t----TABLE-----\n";
    cout<<"\tID\tAT\tBT\n";
    for(int i=0;i<n;i++){
        cout<<"\t"<<t[i].id<<"\t"<<t[i].at<<"\t"<<t[i].bt<<"\t"<<"\n";
    }
}

int main()
{
    system("cls");
    cout<<"\n\n\n\t---------------------------------------\n";
    cout<<"\t           DINING PHILOSOPHERS         \n";
    cout<<"\t---------------------------------------\n\n";
    int i;
    cout<<"\tEnter no of philosophers : ";
    cin>>n;
    t= (tasks*)malloc((n)*sizeof(tasks));
    chop=(int*)malloc((n)*sizeof(int));
    cout<<"\tGive arrival time of each philosopher : ";
    for(i=0;i<n;i++){
        t[i].id=i+1;
        t[i].status=0;
        chop[i]=0;
        cin>>t[i].at;
    }
    cout<<"\tGive burst time of each philosopher   : ";
    for(i=0;i<n;i++){
        cin>>t[i].bt;
    }

    sort_tasks(n);
    //Using selection sort we sort all tasks in increasing order of arrival time
    // print_table(n);

    get_times();
    //snippet for telling which task was active
    //print_table(philno);
    cout<<"\n";
    cout<<"\tAll philosophers were addressed\n";
    cout<<"\n\t          Press any key to continue! ";
    getchar();
    getchar();
    return 0;
}
