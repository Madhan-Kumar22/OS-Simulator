#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

struct tasks
{
    float id,at,bt,ct,tat,wt;
    bool key;
    //key=true is Writer and false is Reader
};
tasks *t,temp;
sem_t semaphore;
int total_time;

void sort_tasks(int n){
    //selection sort is implemented to sort according to arrival times
    //if Writer and Reader come at same time, \tWriter is put first
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

void relocate(int index,int pos,int n){
    int j;
    temp=t[index];
    for(j=index;j>pos;j--){
        t[j]=t[j-1];
    }
    t[pos]=temp;
}

void get_times(int n,int buffer){
    int i=0,j,capacity=0,work_id=0;total_time=0;
    bool check;
    for(i=0;i<n;i++){
        if(t[i].key==true){
            total_time=(t[i].at>total_time)?t[i].at:total_time;
            if(capacity<buffer){
                sem_wait(&semaphore);

                cout<<"\n\tWriter "<<t[i].id<<" is writing\n";
                if(t[i].at>t[work_id].ct) t[i].ct=t[i].at;
                else t[i].ct=t[work_id].ct;
                t[i].ct+=t[i].bt;
                t[i].tat=t[i].ct-t[i].at;
                t[i].wt=t[i].tat-t[i].bt;
                for(j=i+1;j<n&&t[j].at<t[i].ct;j++){
                    if(t[j].key==true)  cout<<"\tWriter "<<t[j].id<<" has to wait because Writer "<<t[i].id<<" is writing\n";
                    else  cout<<"\tReader "<<t[j].id<<" has to wait because Writer "<<t[i].id<<" is writing\n";
                }
                work_id=i;
                capacity++;

                sem_post(&semaphore);
            }
            else{
                cout<<"\n\tFile is full\n";
                cout<<"\tWriter "<<t[i].id<<" cannot write\n\n";
            }
        }
        else{
            if(capacity>0){
                sem_wait(&semaphore);

                cout<<"\n\tReader "<<t[i].id<<" is reading\n";
                if(t[work_id].key==false){
                    t[i].ct=t[i].at+t[i].bt;
                    t[i].tat=t[i].ct-t[i].at;
                    t[i].wt=t[i].tat-t[i].bt;
                    if(t[i].ct>t[work_id].ct) work_id=i;
                }
                else{
                    if(t[i].at>t[work_id].ct) t[i].ct=t[i].at;
                    else t[i].ct=t[work_id].ct;
                    t[i].ct+=t[i].bt;
                    t[i].tat=t[i].ct-t[i].at;
                    t[i].wt=t[i].tat-t[i].bt;
                    int p=i+1;//this is the position to where we might need to bring a \treader
                    for(j=i+1;j<n&&t[j].at<t[i].ct;j++){
                        if(t[j].key==true)  cout<<"\tWriter "<<t[j].id<<" has to wait because Reader "<<t[i].id<<" is reading\n";
                        else  {relocate(j,p,n);p++;}//We are bringing the \treader next to this \treader as it is getting executed
                    }
                    work_id=i;
                }


                sem_post(&semaphore);
            }
            else{
                cout<<"\n\tFile is empty and Reader "<<t[i].id<<" is made to wait till a writer arrives\n";
                int k;for(k=i+i;k<n;k++){if(t[k].key==true) break;}
                if(k==n) "\tNo writer has arrived\n";
                else {relocate(k,i,n);i--;}
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
          cout<<"\t             READERS WRITERS           \n";
    cout<<"\t---------------------------------------\n\n";
    int i,n,m,buffer;
    cout<<"\tEnter file size : ";
    cin>>buffer;
    cout<<"\tEnter no of Writers : ";
    cin>>n;
    cout<<"\tEnter no of Readers : ";
    cin>>m;
    t= (tasks*)malloc((n+m)*sizeof(tasks));
    cout<<"\tGive arrival time of each Writer : ";
    for(i=0;i<n;i++){
        t[i].id=i+1;
        cin>>t[i].at;
        t[i].key=true;
    }
    cout<<"\tGive arrival time of each Reader : ";
    for(;i<m+n;i++){
        t[i].id=i-n+1;
        cin>>t[i].at;
        t[i].key=false;
    }
    cout<<"\tGive burst time of each Writer   : ";
    for(i=0;i<n;i++){
        cin>>t[i].bt;
    }
    cout<<"\tGive burst time of each Reader   : ";
    for(;i<m+n;i++){
        cin>>t[i].bt;
    }

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

