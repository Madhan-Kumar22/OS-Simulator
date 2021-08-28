#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

struct tasks
{
    float id,at,bt,ct,tat,wt;
    bool key;
    //key=true is producer and false is consumer
};
tasks *t,temp;
sem_t semaphore;
int total_time;

void sort_tasks(int n){
    //selection sort is implemented to sort according to arrival times
    //if producer and consumer come at same time, producer is put first
    tasks temp;
    int i,j,min;
    for(i=0;i<n-1;i++){
        min=i;
        for(j=i+1;j<n;j++){
            if(t[j].at<t[min].at){
                min=j;
            }
            else if(t[j].at==t[min].at&&t[min].key==false&&t[j].key==true){
                min=j;
            }
        }
        temp=t[min];
        t[min]=t[i];
        t[i]=temp;
    }
}

bool relocate(int pos,int n){
    int j,index;
    if(t[pos].key==true){
        cout<<"\tProducer "<<t[pos].id<<"has wait for a Consumer and is being moved back\n";
        for(j=pos+1;j<n;j++){
            if(t[j].key==false) {index=j;break;}
        }
        if(j==n) {cout<<"\tProducer "<<t[pos].id<<" cannot be executed\n"; return false;}
        temp=t[index];
        for(j=index;j>pos;j--){
            t[j]=t[j-1];
        }
        t[pos]=temp;
        return true;
    }
    else{
        cout<<"\tConsumer "<<t[pos].id<<"has wait for a Producer and is being moved back\n";
        for(j=pos+1;j<n;j++){
            if(t[j].key==true) {index=j;break;}
        }
        if(j==n) {cout<<"\tConsumer "<<t[pos].id<<" cannot be executed\n"; return false;}
        temp=t[index];
        for(j=index;j>pos;j--){
            t[j]=t[j-1];
        }
        t[pos]=temp;
        return true;
    }
}

void get_times(int n,int buffer){
    int i=0,j,capacity=0,work_id=0;total_time=0;
    bool check;
    for(i=0;i<n;i++){
        if(t[i].key==true){
            if(capacity<buffer){
                sem_wait(&semaphore);

                cout<<"\tProducer "<<t[i].id<<" is producing\n";
                if(t[i].at>t[work_id].ct) t[i].ct=t[i].at;
                else t[i].ct=t[work_id].ct;
                t[i].ct+=t[i].bt;
                t[i].tat=t[i].ct-t[i].at;
                t[i].wt=t[i].tat-t[i].bt;
                for(j=i+1;j<n&&t[j].at<t[i].ct;j++){
                    if(t[j].key==true)  cout<<"\tProducer "<<t[j].id<<" has to wait because Producer "<<t[i].id<<" is producing\n";
                    else  cout<<"\tConsumer "<<t[j].id<<" has to wait because Producer "<<t[i].id<<" is producing\n";
                }
                work_id=i;
                capacity++;

                sem_post(&semaphore);
                cout<<"\n";
            }
            else{
                cout<<"\tBuffer is full\n";
                check=relocate(i,n);cout<<"\n";
                if(check==true) i--;
            }
        }
        else{
            if(capacity>0){
                sem_wait(&semaphore);

                cout<<"\tConusmer "<<t[i].id<<" is consuming\n";
                if(t[i].at>t[work_id].ct) t[i].ct=t[i].at;
                else t[i].ct=t[work_id].ct;
                t[i].ct+=t[i].bt;
                t[i].tat=t[i].ct-t[i].at;
                t[i].wt=t[i].tat-t[i].bt;
                for(j=i+1;j<n&&t[j].at<t[i].ct;j++){
                    if(t[j].key==true)  cout<<"\tProducer "<<t[j].id<<" has to wait because Consumer "<<t[i].id<<" is consuming\n";
                    else  cout<<"\tConsumer "<<t[j].id<<" has to wait because Consumer "<<t[i].id<<" is consuming\n";
                }
                work_id=i;
                capacity--;

                sem_post(&semaphore);
                cout<<"\n";
            }
            else{
                cout<<"\tBuffer is empty\n";
                check=relocate(i,n);cout<<"\n";
                if(check==true) i--;
            }
        }

    }

}


void print_table(int n){
    cout<<"\tprod\tid\tat\tbt\tct\ttat\twt\n";
    for(int i=0;i<n;i++){
        cout<<"\t"<<t[i].key<<"\t"<<t[i].id<<"\t"<<t[i].at<<"\t"<<t[i].bt<<"\t"<<t[i].ct<<"\t"<<t[i].tat<<"\t"<<t[i].wt<<"\n";
    }
}
int main()
{
    system("cls");
    cout<<"\n\n\n\t---------------------------------------\n";
    cout<<      "\t            PRODUCER CONSUMER          \n";
    cout<<"\t---------------------------------------\n\n";
    int i,n,m,buffer;
    cout<<"\tEnter buffer size : ";
    cin>>buffer;
    cout<<"\tEnter no of producers : ";
    cin>>n;
    cout<<"\tEnter no of consumers : ";
    cin>>m;
    t= (tasks*)malloc((n+m)*sizeof(tasks));
    cout<<"\tGive arrival time of each producer : ";
    for(i=0;i<n;i++){
        t[i].id=i+1;
        cin>>t[i].at;
        t[i].key=true;
    }
    cout<<"\tGive arrival time of each consumer : ";
    for(;i<m+n;i++){
        t[i].id=i-n+1;
        cin>>t[i].at;
        t[i].key=false;
    }
    cout<<"\tGive burst time of each producer   : ";
    for(i=0;i<n;i++){
        cin>>t[i].bt;
    }
    cout<<"\tGive burst time of each consumer   : ";
    for(;i<m+n;i++){
        cin>>t[i].bt;
    }
    
    cout<<"\n";
    sort_tasks(n+m);
    //Using selection sort we sort all tasks in increasing order of arrival time
    //print_table(n+m);

    get_times(n+m,buffer);
    //snippet for telling which task was active
    //print_table(n+m);
    cout<<"\n\tAll tasks were addressed\n";
    cout<<"\n\t          Press any key to continue! ";
    getchar();
    getchar();
    return 0;
}

