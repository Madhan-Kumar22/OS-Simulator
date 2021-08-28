//Bankers Algorithm
#include <bits/stdc++.h>
using namespace std;

int n,m;


int main(){
    system("cls");
    cout<<"\n\n\n\t---------------------------------------\n";
    cout<<"\t         BANKER\'S ALGORITHM             \n";
    cout<<"\t---------------------------------------\n\n";
    int i,j;
    cout<<"\tEnter the no of processes : ";cin>>n;
    cout<<"\tEnter the no of resources : ";cin>>m;
    int max[m],total_need[n][m],ava[m],allot[n][m],rem_need[n][m],check[n]={0};
    //max holds maximum amount of resource available
    //total_need is total need of each resource for each process
    //allot holds initial resource allotment for each process
    //rem_need holds remaining need of each resource after allotment for each process
    //ava hold availability of each resource at any instant
    //check is used later to know if a process is completed or not
    cout<<"\tEnter the total available resources of each type : ";
    for(i=0;i<m;i++){cin>>max[i];ava[i]=max[i];}
    // cout<<"\tEnter the total need of each resource for each process one after another\n";
    for(i=0;i<n;i++){
        cout<<"\n\tEnter total need of each resource for Process "<<i+1<<" :\n\t";
        for(j=0;j<m;j++){
            cin>>total_need[i][j];
            /*if(total_need[i][j]>max[j]){
                cout<<"Process "<<i<<" requires greater amount of resource "<<j<<" than available\n";
                cout<<"Deadlock will be formed\n";return 0;
            }*/
        }
    }
    cout<<"\n";
    cout<<"\tEnter the alloted resources of each type for each process\n";
    cout<<"\tThe total allotment should be less than what is totally available\n";
    for(i=0;i<n;i++){
        cout<<"\n\tEnter alloted resources of Process "<<i+1<<"\n";
        for(j=0;j<m;j++){
            cout<<"\tResource "<<j+1<<" : "; cin>>allot[i][j];
            if(allot[i][j]>ava[j]){
                cout<<"\tAllotment cannot be more than available\n\tEnter another value for this resource\n";
                j--;
            }
            else if(allot[i][j]>total_need[i][j]){
                cout<<"\tAlloting more than required leads to wastage of resources\n\tEnter another value for this resource\n";
                j--;
            }
            else{
                ava[j]=ava[j]-allot[i][j];
                rem_need[i][j]=total_need[i][j]-allot[i][j];
            }
        }
    }
    system("cls");
    cout<<"\n\t------OUTPUT------\n";
    cout<<"\tResources remaining now are : \n";
    for(j=0;j<m;j++){
        cout<<"\tResource "<<j+1<<" : "<<ava[j]<<"\n";
    }
    cout<<"\n\n";
    
    //completed keeps count of completed process
    //flag is used to know if at least one process gets executed
    //Code to print table
    cout<<"\tAllotted\tTotal Need\tRemaining Need\n";
    for(i=0;i<n;i++){
        cout<<"\t";
        for(j=0;j<m;j++) cout<<allot[i][j]<<" ";
        cout<<"\t\t";
        for(j=0;j<m;j++) cout<<total_need[i][j]<<" ";
        cout<<"\t\t";
        for(j=0;j<m;j++) cout<<rem_need[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";
    bool flag[n] = {false};
    int count = 0;
    int order[n], order_in=0;

    cout<<"\n\tChecking for possibility of a safe state....\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            bool fl = false;
            if(!flag[j]){
                for(int k = 0; k < m; k++){
                    if(rem_need[j][k] > ava[k]){
                        fl = true;
                        break;
                    }
                }
                if(!fl){
                    count++;
                    for(int k=0; k<m; k++){
                        ava[k] += allot[j][k];
                    }
                    order[order_in++] = j+1;
                    flag[j] = true;
                }
            }
        }
    }

    if(count < n){
        cout<<"\n\tThere is no safe state possible.\n";
    }
    else{
        cout<<"\n\tWe can arrive at a safe state!\n\n\tSafe sequence:\n\t";
        for(int i=0; i<n-1; i++){
            cout<<"Process "<<order[i]<<", ";
        }
        cout<<"Process "<<order[n-1]<<"\n";
    }
    cout<<"\n\t          Press any key to continue! ";
    getchar();
    getchar();
    return 0;
}