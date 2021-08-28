#include <bits/stdc++.h>
using namespace std;

struct Process {
    int arr, burst, turn_around, waiting_time, id, complete, priority, rem, start;
};



void sort1(int n, struct Process p[]) {
	//Sort according to arrival time
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++) {
			if(p[i].arr > p[j].arr || (p[i].arr == p[j].arr && p[j].id < p[i].id)) {
				int temp_pid = p[i].id;
				int temp_arrival_time = p[i].arr;
				int temp_burst_time = p[i].burst;
				p[i].id = p[j].id;
				p[i].arr = p[j].arr;
				p[i].burst = p[j].burst;
				p[j].id = temp_pid;
				p[j].arr = temp_arrival_time;
				p[j].burst = temp_burst_time;
			}
		}
	}
}


void sort2(int n, struct Process p[]) {
	//Sort according to arrival time and if they are same sort according to burst time.
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++) {
			if(p[i].arr > p[j].arr || (p[i].arr == p[j].arr && p[j].burst < p[i].burst)) {
				int temp_pid = p[i].id;
				int temp_arrival_time = p[i].arr;
				int temp_burst_time = p[i].burst;
				p[i].id = p[j].id;
				p[i].arr = p[j].arr;
				p[i].burst = p[j].burst;
				p[j].id = temp_pid;
				p[j].arr = temp_arrival_time;
				p[j].burst = temp_burst_time;
			}
		}
	}
}




void findCompletionTime(int n, struct Process p[]) {
    p[0].complete = p[0].arr + p[0].burst;
    for(int i = 1; i < n; ++i) {
        if(p[i].arr > p[i - 1].complete) {
            p[i].complete = p[i].arr + p[i].burst;
        } else {
            p[i].complete = p[i - 1].complete + p[i].burst;
        }
    }
}


void findTurnAroundTime(int n, struct Process p[]) {
    for(int i = 0; i < n; ++i) {
        p[i].turn_around = p[i].complete - p[i].arr;
    }
}

void findWaitingTime(int n, struct Process p[]) {
    for(int i = 0; i < n; ++i) {
        p[i].waiting_time = p[i].turn_around - p[i].burst;
    }
}


void fcfs() {
    system("cls");
    cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        FCFS SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";
    int n;
    printf("\tEnter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    for(int i = 0; i < n; ++i) {
        printf("\n\tProcess %d:\n", i + 1);
        printf("\tEnter the arrival time: ");
        scanf("%d", &processes[i].arr);
        printf("\tEnter the burst time: ");
        scanf("%d", &processes[i].burst);
        processes[i].id = i + 1;
    }
    sort1(n, processes);
    findCompletionTime(n, processes);
    findTurnAroundTime(n, processes);
    findWaitingTime(n, processes);
    int total_waiting_time = 0, total_tat = 0;
    cout<<"\n\t---------TABLE--------\n";
    printf("\n\tProcess \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time\n");
    for(int i = 0; i < n; ++i) {
        printf("\n\t%d \t\t %d \t\t %d \t\t %d \t\t\t %d \t\t   %d\n", processes[i].id ,processes[i].arr, processes[i].burst, processes[i].complete, processes[i].waiting_time, processes[i].turn_around);
    }
    for(int i = 0; i < n; ++i) {
        total_waiting_time += processes[i].waiting_time;
        total_tat += processes[i].turn_around;
    }
    printf("\n\tTotal Waiting Time: %d\n", total_waiting_time);
    printf("\tTotal Turn around Time: %d\n", total_tat);
    printf("\tAverage Waiting time: %f\n", (float)total_waiting_time/(float)n);
    printf("\tAverage Turn around time: %f\n", (float)total_tat/(float)n);
}


void sjf() {
    system("cls");
    cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        SJF SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";
    int n;
    printf("\tEnter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    for(int i = 0; i < n; ++i) {
        printf("\n\tProcess %d:\n", i + 1);
        printf("\tEnter the arrival time: ");
        scanf("%d", &processes[i].arr);
        printf("\tEnter the burst time: ");
        scanf("%d", &processes[i].burst);
        processes[i].id = i + 1;
    }
    sort2(n, processes);
    int time = 0;
    int done[n];
    // memset(done, 0, n * sizeof(done[0]));
    for(int i = 0; i < n; ++i) done[i] = 0;
    int remaining = n;
    while(remaining != 0) {
        int min_burst = 1e9;
        int min_idx = -1;
        for(int i = 0; i < n; ++i) {
            if(processes[i].arr <= time && done[i] == 0 && min_burst > processes[i].burst) {
                min_burst = processes[i].burst;
                min_idx = i;
            }
        }
        if(min_idx != -1) {
            done[min_idx] = 1;
            remaining--;
            processes[min_idx].complete = time + min_burst;
            time += min_burst;
        } else {
            time++;
        }
    }
    findTurnAroundTime(n, processes);
    findWaitingTime(n, processes);
    int total_waiting_time = 0, total_tat = 0;
    cout<<"\n\t---------TABLE--------\n";
    printf("\tProcess \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time\n");
    for(int i = 0; i < n; ++i) {
        printf("\n\t%d \t\t %d \t\t %d \t\t %d \t\t\t %d \t\t   %d\n", processes[i].id ,processes[i].arr, processes[i].burst, processes[i].complete, processes[i].waiting_time, processes[i].turn_around);
    }
    for(int i = 0; i < n; ++i) {
        total_waiting_time += processes[i].waiting_time;
        total_tat += processes[i].turn_around;
    }
    printf("\n\tTotal Waiting Time: %d\n", total_waiting_time);
    printf("\tTotal Turn around Time: %d\n", total_tat);
    printf("\tAverage Waiting time: %f\n", (float)total_waiting_time/(float)n);
    printf("\tAverage Turn around time: %f\n", (float)total_tat/(float)n);
}


void calcWaitingTime(int n, struct Process p[],int quantum) {
    int remaining_burst[n];
    for(int i = 0; i < n; ++i) {
        remaining_burst[i] = p[i].burst;
    }
    int time = 0;
    int arrival_time = 0;
    while(1) {
        int over = 0;
        for(int i = 0; i < n; ++i) {
            if(remaining_burst[i] > 0) {
                if(remaining_burst[i] > quantum) {
                    if(p[i].arr <= arrival_time) {
                        time += quantum;
                        remaining_burst[i] -= quantum;
                        arrival_time++;
                    }
                } else {
                    if(p[i].arr <= arrival_time) {
                        arrival_time++;
                        time += remaining_burst[i];
                        remaining_burst[i] = 0;
                        p[i].complete = time;
                    }
                }
                over = 1;
            }
        }
        if(over == 0) break;
    }
}

struct tasks
{
    float id,at,bt,ct,tat,wt,rbt,p;
    bool done;
};
tasks *t;
//float tat,wt;
float tat_hrrn,wt_hrrn,tat_rr,wt_rr,tat_ljf,wt_ljf;
queue <int> q;
//int total_time;
float t_slice;

void sort_tasks(int n){
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



void get_times_hrrn(int n){
    int i=0,j,best,next_arr,temp,count=0,best_rrn,i_rrn;
    int total_time_hrrn = 0;
    tat_hrrn=0,wt_hrrn=0;
    while(count<n){
        best=0;
        for(i=0;i<n;i++){if(t[i].done==false){best=i;break;}}
        //Best will contain the index of first unfinished process
        if(total_time_hrrn<t[best].at){
            cout<<"\tAt t = "<<total_time_hrrn<<", CPU is idle\n";
            total_time_hrrn=t[best].at;
        }
        best_rrn=(total_time_hrrn-t[best].at+t[best].rbt)/t[best].rbt;
        //This has rrn of best process
        for(;i<n;i++){
            i_rrn=(total_time_hrrn-t[i].at+t[i].rbt)/t[i].rbt;
            //This has rrn of current process
            if(t[i].at<=total_time_hrrn&&t[i].done==false&&(i_rrn>best_rrn)){
                best=i;//Best will be process with highest response ratio
            }
            else if(t[i].at>total_time_hrrn){break;}//The processes after this have anyway not arrived yet
        }
            //Now best can be fully executed as it wont be interrupted
            cout<<"\tAt t = "<<total_time_hrrn<<", Process "<<t[best].id<<" is using cpu\n";
            total_time_hrrn+=t[best].rbt;
            t[best].rbt=0;
            t[best].done=true;count++;
            t[best].ct=total_time_hrrn;
            cout<<"\tAt t = "<<total_time_hrrn<<", Process "<<t[best].id<<" finished executing\n";
            t[best].tat=t[best].ct-t[best].at;
            t[best].wt=t[best].tat-t[best].bt;
            tat_hrrn+=t[best].tat;
            wt_hrrn+=t[best].wt;
    }

}

void get_times_rr(int n){
    int i,count=0,exec;
    int total_time_rr=0;
    tat_rr=0,wt_rr=0;
    q.push(0);//We push the first process into queue
    t[0].done=true;//It will eventually be completed
    if(t[0].at>total_time_rr){
        cout<<"\tAt t = "<<total_time_rr<<", CPU is idle\n";
        total_time_rr=t[exec].at;
    }
    while(!q.empty()){
        exec=q.front();//This process will get executed
        q.pop();
        if(t[exec].rbt>t_slice){
            cout<<"\tAt t="<<total_time_rr<<" ";
            total_time_rr+=t_slice;
            t[exec].rbt-=t_slice;
            cout<<t[exec].id<<" is in cpu\n";
        }
        else{
            cout<<"\tAt t = "<<total_time_rr<<", process "<<t[exec].id<<" is in CPU\n";
            total_time_rr+=t[exec].rbt;
            t[exec].rbt=0;count++;
            t[exec].ct=total_time_rr;
            t[exec].tat=t[exec].ct-t[exec].at;
            t[exec].wt=t[exec].tat-t[exec].bt;
            tat_rr+=t[exec].tat;
            wt_rr+=t[exec].wt;
            cout<<"\tAt t = "<<total_time_rr<<", process ";
            cout<<t[exec].id<<" finishes\n";

        }
        for(i=0;i<n;i++){
            if(t[i].done==false&&t[i].at<=total_time_rr){q.push(i);t[i].done=true;}
            //We push all the process which have newly arrived into queue
        }
        if(t[exec].rbt!=0){q.push(exec);}//We push exec also if it still hasnt completed
        if(q.empty()&&count<n){
            cout<<"\tAt t = "<<total_time_rr<<", CPU is idle\n";
            for(i=0;i<n;i++){
                if(t[i].done==false){
                    q.push(i);t[i].done=true;
                    //We push the next arriving unfinished process into queue
                    total_time_rr=t[i].at;break;
                }
            }
        }
    }
}

void get_times_ljf(int n){
    int i=0,j,best,next_arr,temp,count=0;
    int total_time_ljf = 0;
    tat_ljf=0,wt_ljf=0;
    while(count<n){
        best=0;
        for(i=0;i<n;i++){if(t[i].done==false){best=i;break;}}
        //Best will contain the index of first unfinished process
        if(total_time_ljf<t[best].at){
            //This means that no process is present and cpu is idle for some time
            cout<<"\tAt t = "<<total_time_ljf<<", CPU is idle\n";
            total_time_ljf=t[best].at;//We advance time till the process arrives
        }
        for(;i<n;i++){
            if(t[i].at<=total_time_ljf&&t[i].done==false&&t[i].rbt>t[best].rbt){
                best=i;//Best will be process with longest remaining time
            }
            else if(t[i].at>total_time_ljf){break;}//The processes after this have anyway not arrived yet
        }
            //Now best can be fully executed as it wont be interrupted
            cout<<"\tAt t = "<<total_time_ljf<<", Process "<<t[best].id<<" is using CPU\n";
            total_time_ljf+=t[best].rbt;
            t[best].rbt=0;
            t[best].done=true;count++;
            t[best].ct=total_time_ljf;
            cout<<"\tAt t = "<<total_time_ljf<<", Process "<<t[best].id<<" finished executing\n";
            t[best].tat=t[best].ct-t[best].at;
            t[best].wt=t[best].tat-t[best].bt;
            tat_ljf+=t[best].tat;
            wt_ljf+=t[best].wt;
    }

}

void print_table(int n){
    cout<<"\tID\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i=0;i<n;i++){
        cout<<"\t"<<t[i].id<<"\t"<<t[i].at<<"\t"<<t[i].bt<<"\t"<<t[i].ct<<"\t"<<t[i].tat<<"\t"<<t[i].wt<<"\n";
    }
}

// struct tasks
// {
//     float id,at,bt,ct,tat,wt,rbt,p;
//     bool done;
// };

void roundrobin() {
    system("cls");

    cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        ROUND ROBIN SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";
    int i,n;
    cout<<"\tEnter time slice: ";
    cin>>t_slice;
    cout<<"\tEnter number of tasks for round robin scheduling: ";
    cin>>n;
    t= (tasks*)malloc(n*sizeof(tasks));

    for(i=0;i<n;i++){
        cout<<"\n\tEnter ID, arrival time and burst time of task "<<i<<": \n";
        cout<<"\t";
        cin>>t[i].id>>t[i].at>>t[i].bt;
        t[i].rbt=t[i].bt;
        t[i].done=false;
    }
    sort_tasks(n);
    cout<<"\n\t -- TIMELINE OF PROCESS EXECUTION -- \n";
    //Using selection sort we sort all tasks in increasing order of arrival time
    get_times_rr(n);
    //This function gives tat and wt for tasks
    cout<<"\n\tThe final table: \n\n";
    print_table(n);
    cout<<"\n\tAverage turn around time is"<<" "<<tat_rr/n<<"\n";
    cout<<"\tAverage waiting time is"<<" "<<wt_rr/n<<"\n";
    free(t);
}


void priority_preempt() {
    system("cls");
    cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        PRIORITY PREEMPTIVE SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";
    int n;
    float total_tat=0, total_wt=0;
    printf("\tEnter no. of processes: ");
    printf("\t");
    scanf("%d",&n);
    int at[n],bt[n],rt[n],wt[n],tat[n],prio[n];
    for(int i=0;i<n;i++)
    {
        printf("\n\tEnter arrival time process %d:",i+1);
        scanf("%d",&at[i]);
        printf("\tEnter burst time process %d:",i+1);
        scanf("%d",&bt[i]);
        rt[i]=bt[i];
        printf("\tEnter priority of process %d:",i+1);
        scanf("%d",&prio[i]);
    }
   // printf("\nGantt chart:\n\n");
    // prio[9]=9999;
    int time=0;
    int idt=0;
    int endtime=0;
    int done=0;

    while(done!=n)
    {
        int smallest=1e9, pid = -1;
        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && prio[i]<smallest && rt[i]>0)
            {
                smallest=prio[i];
                pid = i;
            }
        }

        if(smallest==1e9)
        {
            idt++;
           // printf("%d IDLE ",time);
        }

        else
        {
            rt[pid]--;
            //printf("Process %d from %d to %d\n",smallest+1,time,time+1);
           // printf("%d P%d ",time,smallest+1);
            if(rt[pid]==0)
            {
                done++;
                endtime=time+1;
                tat[pid]=endtime-at[pid];
                wt[pid]=endtime-at[pid]-bt[pid];
            }
        }
        time+=1;
    }
    //printf("%d",time);
    cout<<"\n\t---------TABLE--------\n";
    printf("\n\n\tPID\tAT\tBT\tTAT\tWT\n\n");
    for(int i=0;i<n;i++)
    {
        printf("\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],tat[i],wt[i]);
    }

     for(int i=0;i<n;i++)
    {
        total_tat=total_tat+tat[i];
        total_wt=total_wt+wt[i];
    }

    printf("\n\tAverage turn around time=%f\n",total_tat/n);
    printf("\tAverage waiting time=%f\n",total_wt/n);


}

void priority() {
    system("cls");
    cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t    PRIORITY NON PREEMPTIVE SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";
    int n;
    float total_tat=0,total_wt=0;
    printf("\tEnter no. of processes\n");
    printf("\t");
    scanf("%d",&n);
    int at[n],bt[n],rt[n],wt[n],tat[n],prio[n];
    for(int i=0;i<n;i++)
    {
        printf("\n\tEnter arrival time of process %d:",i+1);
        scanf("\t%d",&at[i]);
        printf("\tEnter burst time of process %d:",i+1);
        scanf("\t%d",&bt[i]);
        printf("\tEnter priority of process %d:",i+1);
        scanf("\t%d",&prio[i]);
    }
  //  printf("\nGantt chart:\n\n");
    // prio[9]=9999;
    int time=0;
    int idt=0;
    int endtime=0;
    int done=0;
    int finished[n]={0};
    while(done!=n)
    {

        int smallest=1e9, pid = -1;
        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && prio[i]<smallest && finished[i]==0)
            {
                smallest=prio[i];
                pid = i;
            }
        }
        if(smallest==1e9)
        {
                idt++;
                //printf("\t%d IDLE ",time);
                time+=1;
        }
        else
        {
            //printf("Process %d from %d to %d\n",smallest+1,time,time+bt[smallest]);
           // printf("%d P%d ",time,smallest+1);
            done++;
            finished[pid]=1;
            endtime=time+bt[pid];
            tat[pid]=endtime-at[pid];
            wt[pid]=endtime-at[pid]-bt[pid];
            time+=bt[pid];
        }

    }
   //  printf("%d",time);
    cout<<"\n\t---------TABLE--------\n";
    printf("\n\n\tPID\tAT\tBT\tTAT\tWT\n\n");
    for(int i=0;i<n;i++)
    {
        printf("\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],tat[i],wt[i]);
    }
    for(int i=0;i<n;i++)
    {
        total_tat=total_tat+tat[i];
        total_wt=total_wt+wt[i];
    }

    printf("\n\tAverage turn around time=%f\n",total_tat/n);
    printf("\tAverage waiting time=%f\n",total_wt/n);
}





void ljf(){
    system("cls");
    int i,n;
	
	cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        LJF SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";
    cout<<"\tEnter number of tasks : ";
    cin>>n;
    t= (tasks*)malloc(n*sizeof(tasks));
    for(i=0;i<n;i++){
        cout<<"\n\tEnter ID, arrival time and burst time of task "<<i<<": \n";
        cout<<"\t";
        cin>>t[i].id>>t[i].at>>t[i].bt;
        t[i].rbt=t[i].bt;
        t[i].done = false;
    }
    //print_table(n);

    sort_tasks(n);
    
    cout<<"\n\t -- TIMELINE OF PROCESS EXECUTION -- \n";
    //Using selection sort we sort all tasks in increasing order of arrival time
    //And if they have same arrival time shorter burst time will be put first
    //print_table(n);
    get_times_ljf(n);
    //This function gives tat and wt for tasks
    cout<<"\n\tThe final table: \n";
    print_table(n);
    cout<<"\n\tAverage turn around time is"<<" "<<tat_ljf/n<<"\n";
    cout<<"\tAverage waiting time is"<<" "<<wt_ljf/n<<"\n";
    free(t);
}

void hrrn(){
	int i,n;
	system("cls");
	
	cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t            HRRN SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";
    cout<<"\tEnter number of tasks for HRRN scheduling: ";
    cin>>n;
    t= (tasks*)malloc(n*sizeof(tasks));

    for(i=0;i<n;i++){
		cout<<"\n\tEnter ID, arrival time and burst time of task "<<i<<": \n";
		cout<<"\t";
        cin>>t[i].id>>t[i].at>>t[i].bt;
        t[i].rbt=t[i].bt;
        t[i].done = false;
    }
    //print_table(n);

    sort_tasks(n);
    cout<<"\n\t -- TIMELINE OF PROCESS EXECUTION -- \n";
    //Using selection sort we sort all tasks in increasing order of arrival time
    //And if they have same arrival time shorter burst time will be put first
    //print_table(n);
    get_times_hrrn(n);
    //This function gives tat and wt for tasks
    cout<<"\n\tThe final table: \n";
    print_table(n);
    cout<<"\n\tAverage turn around time is"<<" "<<tat_hrrn/n<<"\n";
    cout<<"\tAverage waiting time is"<<" "<<wt_hrrn/n<<"\n";
    free(t);

}

template<typename ValueType>
std::string stringulate(ValueType v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
}



void srtf() {
    system("cls");
    cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        SRTF SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";
    int n;
    Process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_idle_time = 0;
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(2) << fixed;

    cout<<"\tEnter the number of processes: ";
    cin>>n;

    for(int i = 0; i < n; i++) {
        cout<<"\n\tEnter arrival time of process "<<i+1<<": ";
        cin>>p[i].arr;
        cout<<"\tEnter burst time of process "<<i+1<<": ";
        cin>>p[i].burst;
        p[i].id = i+1;
        p[i].rem = p[i].burst;
        cout<<endl;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arr <= current_time && is_completed[i] == 0) {
                if(p[i].rem < mn) {
                    mn = p[i].rem;
                    idx = i;
                }
                if(p[i].rem == mn) {
                    if(p[i].arr < p[idx].arr) {
                        mn = p[i].rem;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(p[idx].rem == p[idx].burst) {
                p[idx].start = current_time;
                total_idle_time += p[idx].start - prev;
            }
            p[idx].rem -= 1;
            current_time++;
            prev = current_time;

            if(p[idx].rem == 0) {
                p[idx].complete = current_time;
                p[idx].turn_around = p[idx].complete - p[idx].arr;
                p[idx].waiting_time = p[idx].turn_around - p[idx].burst;

                total_turnaround_time += p[idx].turn_around;
                total_waiting_time += p[idx].waiting_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arr);
        max_completion_time = max(max_completion_time,p[i].complete);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    cout<<endl<<endl;

    cout<<"\t---------TABLE--------\n";
    cout<<"\tPID\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<"\t"<<p[i].id<<"\t"<<p[i].arr<<"\t"<<p[i].burst<<"\t"<<p[i].start<<"\t"<<p[i].complete<<"\t"<<p[i].turn_around<<"\t"<<p[i].waiting_time <<"\t"<<"\n"<<endl;
    }
    cout<<"\n\tAverage Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"\tAverage Waiting Time = "<<avg_waiting_time<<endl;
}



void lrtf() {
    system("cls");
    cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        LRTF SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";
    int n;
    Process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_idle_time = 0;
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(2) << fixed;

    cout<<"\tEnter the number of processes: ";
    cin>>n;

    for(int i = 0; i < n; i++) {
        cout<<"\tEnter arrival time of process "<<i+1<<": ";
        cin>>p[i].arr;
        cout<<"\tEnter burst time of process "<<i+1<<": ";
        cin>>p[i].burst;
        p[i].id = i+1;
        p[i].rem = p[i].burst;
        cout<<endl;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mx = -10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arr <= current_time && is_completed[i] == 0) {
                if(p[i].rem > mx) {
                    mx = p[i].rem;
                    idx = i;
                }
                if(p[i].rem == mx) {
                    if(p[i].arr < p[idx].arr) {
                        mx = p[i].rem;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(p[idx].rem == p[idx].burst) {
                p[idx].start = current_time;
                total_idle_time += p[idx].start - prev;
            }
            p[idx].rem -= 1;
            current_time++;
            prev = current_time;

            if(p[idx].rem == 0) {
                p[idx].complete = current_time;
                p[idx].turn_around = p[idx].complete - p[idx].arr;
                p[idx].waiting_time = p[idx].turn_around - p[idx].burst;

                total_turnaround_time += p[idx].turn_around;
                total_waiting_time += p[idx].waiting_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arr);
        max_completion_time = max(max_completion_time,p[i].complete);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    cout<<endl<<endl;

    cout<<"\t---------TABLE--------\n";
    cout<<"\tPID\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<"\t"<<p[i].id<<"\t"<<p[i].arr<<"\t"<<p[i].burst<<"\t"<<p[i].start<<"\t"<<p[i].complete<<"\t"<<p[i].turn_around<<"\t"<<p[i].waiting_time <<"\t"<<"\n"<<endl;
    }
    cout<<"\tAverage Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"\tAverage Waiting Time = "<<avg_waiting_time<<endl;

}

int main() {
    int choice;
    //printf("Enter \n 1 for FCFS \n 2 for SJF \n 3 for Round Robin \n 4 for Priority (Non preemptive)\n 5 for Priority (preemptive)\n 6 for SRTF\n 7 for LRTF\n");
	 while(1){
	system("cls");
    cout<<"\n\n\n\t---------------------------------------\n";
    cout<<"\t             JOB SCHEDULING           \n";
    cout<<"\t---------------------------------------\n\n";
    cout<<"\t        1. FCFS                \n";
    cout<<"\t        2. SJF                \n";
    cout<<"\t        3. Round Robin               \n";
    cout<<"\t        4. SRTF             \n";
    cout<<"\t        5. LRTF             \n";
    cout<<"\t        6. LJF             \n";
    cout<<"\t        7. HRRN             \n";
    cout<<"\t        8. Priority(Non Preemptive)             \n";
    cout<<"\t        9. Priority(Preemptive)            \n";
    cout<<"\t        10. Exit             \n\n";
    cout<<"\t---------------------------------------\n\n";
    cout<<"\t          CHOOSE THE OPTION: ";
	scanf("%d", &choice);

    switch(choice)
			{
			case 1: fcfs();
                break;
			case 2: sjf();
                break;
            case 3: roundrobin();
                break;
            case 4: srtf();
                break;
            case 5: lrtf();
                break;
            case 6:
                ljf();
                break;
            case 7:
                hrrn();
                break;
            case 8:
                priority();
                break;
            case 9:
                priority_preempt();
                break;
            case 10:
                exit(0);
                break;
            default:printf("\n\tEnter correct option\n");
                break;

			}
    cout<<"\n\tPress any key to continue!\n";
    getchar();
    getchar();
  }

}
