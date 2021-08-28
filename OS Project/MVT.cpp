//Memory management with variable processes and variable partitions
#include <bits/stdc++.h>
using namespace std;

struct process
{
    int id,size,starts,ends;
    //Starts and ends will keep markers of where the process starts and ends in CPU
};

vector <process> proc_list;//List that contains all the processes in the cpu
int proc_count;//Keeps count of all the processes that arrive
int total_mem;//This is the total memory in CPU
int fit;//To know which kind of technique we are using
int next_pointer;//For next process

void DeleteProcess(){
    cout<<"\tEnter process id to be deleted : ";
    int delete_id;cin>>delete_id;
    int i,list_size=proc_list.size();
    for(i=0;i<list_size;i++){
        if(proc_list[i].id==delete_id){
            proc_list.erase(proc_list.begin()+i);
            cout<<"\tProcess "<<delete_id<<" deleted successfully\n";
            return;//Deletion is done
        }
    }
    //If we reached here that means we didnt find that process
    cout<<"\tProcess "<<delete_id<<" wasn\'t found in CPU\n";
    return;
}

void InsertNextFit(){
    proc_count++;
    struct process arrived;//This is the new process that arrived
    arrived.id=proc_count;//We give this process a id
    cout<<"\n\tEnter the size of Process "<<proc_count<<" : ";
    cin>>arrived.size;
    int list_size=proc_list.size();
    if(list_size==0){
        //This means list and total memory are fully empty
        if(arrived.size<=total_mem){
            cout<<"\tProcess "<<arrived.id<<" inserted at beginning\n";
            arrived.starts=0;arrived.ends=arrived.starts+arrived.size;
            proc_list.push_back(arrived);
        }
        else{
            cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted as only "<<total_mem<<"KB is remaining\n";
        }
        return;
    }
    int i=0,starting=0,space=0,total_space=0;
    if(next_pointer!=0){
        i=next_pointer;starting=proc_list[next_pointer-1].ends;
    }
    while(i<list_size){
        space=proc_list[i].starts-starting;//This is the available space before process i in memory
        if(space>=arrived.size){
            //This means the space here is sufficient for inserting this process
            cout<<"\tProcess "<<arrived.id<<" inserted in space before Process "<<proc_list[i].id<<"\n";
            arrived.starts=starting;arrived.ends=arrived.starts+arrived.size;
            proc_list.insert(proc_list.begin()+i,arrived);
            next_pointer=i;
            return;//We are done with insertion
        }
        else{
            total_space+=space;//Total space is used to know external fragmentation
            starting=proc_list[i].ends;//We updating starting point for next space
            i++;//We check for next process
        }
    }
    //We now check if there is space to insert after last process
    starting=proc_list[i-1].ends;//Now starting of space points to the ending of last process in list
    space=total_mem-starting;
    if(space>=arrived.size){
        //This means there is sufficient space after the last process
        cout<<"\tProcess "<<arrived.id<<" inserted at the end of all processes\n";
        arrived.starts=starting;arrived.ends=arrived.starts+arrived.size;
        proc_list.insert(proc_list.end(),arrived);
        next_pointer=list_size;
        return;//We are done with insertion
    }
    else total_space+=space;//Update total space

    if(next_pointer!=0){
        //This means we started somewhere in the middle
        i=0;starting=0;
        while(i<next_pointer){
        space=proc_list[i].starts-starting;//This is the available space before process i in memory
        if(space>=arrived.size){
            //This means the space here is sufficient for inserting this process
            cout<<"\tProcess "<<arrived.id<<" inserted in space before Process "<<proc_list[i].id<<"\n";
            arrived.starts=starting;arrived.ends=arrived.starts+arrived.size;
            proc_list.insert(proc_list.begin()+i,arrived);
            next_pointer=i;
            return;//We are done with insertion
        }
        else{
            total_space+=space;//Total space is used to know external fragmentation
            starting=proc_list[i].ends;//We updating starting point for next space
            i++;//We check for next process
        }
    }
    }

    //Now we know that the process wasnt inserted
    if(total_space<arrived.size){
        //This means that there wasnt enough space overall in the CPU
        cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted as only "<<total_space<<"KB is remaining\n";
    }
    else{
        //This means space was present but it is spread over different fragments
        cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted due to external fragmentation\n";
    }

    return;
}

void InsertBestFit(){
    proc_count++;
    struct process arrived;//This is the new process that arrived
    arrived.id=proc_count;//We give this process a id
    cout<<"\n\tEnter the size of Process "<<proc_count<<" : ";
    cin>>arrived.size;
    int list_size=proc_list.size();
    if(list_size==0){
        //This means list and total memory are fully empty
        if(arrived.size<=total_mem){
            cout<<"\tProcess "<<arrived.id<<" inserted at beginning\n";
            arrived.starts=0;arrived.ends=arrived.starts+arrived.size;
            proc_list.push_back(arrived);
        }
        else{
            cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted as only "<<total_mem<<"KB is remaining\n";
        }
        return;
    }
    int i=0,starting=0,space=0,total_space=0;
    int final_space=INT_MAX;//This will hold the final amount of space that we are going to use
    bool found=false;//This shows if we found the place to insert
    int pos=0;//This hold position of where it can be inserted
    while(i<list_size){
        space=proc_list[i].starts-starting;//This is the available space before process i in memory
        if(space>=arrived.size){
            //This means the space here is sufficient for inserting this process
            if(found==false) {pos=i;final_space=space;}//We just update if this is the first free space we found
            else if(space<final_space){
                //This means we found a better place to fit our process
                final_space=space;
                pos=i;
            }
            found=true;
            starting=proc_list[i].ends;//We updating starting point for next space
            i++;//We check for next process
        }
        else{
            total_space+=space;//Total space is used to know external fragmentation
            starting=proc_list[i].ends;//We updating starting point for next space
            i++;//We check for next process
        }
    }
    //We now check if there is space to insert after last process
    starting=proc_list[i-1].ends;//Now starting of space points to the ending of last process in list
    space=total_mem-starting;
    if(space>=arrived.size){
        //This means there is sufficient space after the last process
        if(found==false) {pos=i;final_space=space;}//We just update if this is the first free space we found
            else if(space<final_space){
                //This means we found a better place to fit our process
                final_space=space;
                pos=i;
            }
        found=true;
    }
    else total_space+=space;//Update total space

    if(found==true){
        //We found a place to fit and it is before pos process in list
        if(pos==list_size){
            //This means we are inserting at the end
            arrived.starts=proc_list[list_size-1].ends;arrived.ends=arrived.starts+arrived.size;
            cout<<"\tProcess "<<arrived.id<<" inserted at the end of all processes\n";
            proc_list.insert(proc_list.end(),arrived);
            return;//We are done with insertion
        }
        arrived.starts=proc_list[pos].starts-final_space;arrived.ends=arrived.starts+arrived.size;
        cout<<"\tProcess "<<arrived.id<<" inserted in space before Process "<<proc_list[pos].id<<"\n";
        proc_list.insert(proc_list.begin()+pos,arrived);// We insert before pos
        return;//We are done with insertion
    }
    //Now we know that the process wasnt inserted
    if(total_space<arrived.size){
        //This means that there wasnt enough space overall in the CPU
        cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted as only "<<total_space<<"KB is remaining\n";
    }
    else{
        //This means space was present but it is spread over different fragments
        cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted due to external fragmentation\n";
    }

    return;
}

void InsertWorstFit(){
    proc_count++;
    struct process arrived;//This is the new process that arrived
    arrived.id=proc_count;//We give this process a id
    cout<<"\n\tEnter the size of Process "<<proc_count<<" : ";
    cin>>arrived.size;
    int list_size=proc_list.size();
    if(list_size==0){
        //This means list and total memory are fully empty
        if(arrived.size<=total_mem){
            cout<<"\tProcess "<<arrived.id<<" inserted at beginning\n";
            arrived.starts=0;arrived.ends=arrived.starts+arrived.size;
            proc_list.push_back(arrived);
        }
        else{
            cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted as only "<<total_mem<<"KB is remaining\n";
        }
        return;
    }
    int i=0,starting=0,space=0,total_space=0;
    int final_space=0;//This will hold the final amount of space that we are going to use
    bool found=false;//This shows if we found the place to insert
    int pos=0;//This hold position of where it can be inserted
    while(i<list_size){
        space=proc_list[i].starts-starting;//This is the available space before process i in memory
        if(space>=arrived.size){
            //This means the space here is sufficient for inserting this process
            if(found==false) {pos=i;final_space=space;}//We just update if this is the first free space we found
            else if(space>final_space){
                //This means we found a better place to fit our process
                final_space=space;
                pos=i;
            }
            found=true;
            starting=proc_list[i].ends;//We updating starting point for next space
            i++;//We check for next process
        }
        else{
            total_space+=space;//Total space is used to know external fragmentation
            starting=proc_list[i].ends;//We updating starting point for next space
            i++;//We check for next process
        }
    }
    //We now check if there is space to insert after last process
    starting=proc_list[i-1].ends;//Now starting of space points to the ending of last process in list
    space=total_mem-starting;
    if(space>=arrived.size){
        //This means there is sufficient space after the last process
        if(found==false) {pos=i;final_space=space;}//We just update if this is the first free space we found
            else if(space>final_space){
                //This means we found a better place to fit our process
                final_space=space;
                pos=i;
            }
        found=true;
    }
    else total_space+=space;//Update total space

    if(found==true){
        //We found a place to fit and it is before pos process in list
        if(pos==list_size){
            //This means we are inserting at the end
            arrived.starts=proc_list[list_size-1].ends;arrived.ends=arrived.starts+arrived.size;
            cout<<"\tProcess "<<arrived.id<<" inserted at the end of all processes\n";
            proc_list.insert(proc_list.end(),arrived);
            return;//We are done with insertion
        }
        arrived.starts=proc_list[pos].starts-final_space;arrived.ends=arrived.starts+arrived.size;
        cout<<"\tProcess "<<arrived.id<<" inserted in space before Process "<<proc_list[pos].id<<"\n";
        proc_list.insert(proc_list.begin()+pos,arrived);// We insert before pos
        return;//We are done with insertion
    }
    //Now we know that the process wasnt inserted
    if(total_space<arrived.size){
        //This means that there wasnt enough space overall in the CPU
        cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted as only "<<total_space<<"KB is remaining\n";
    }
    else{
        //This means space was present but it is spread over different fragments
        cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted due to external fragmentation\n";
    }

    return;
}

void InsertFirstFit(){
    proc_count++;
    struct process arrived;//This is the new process that arrived
    arrived.id=proc_count;//We give this process a id
    cout<<"\n\tEnter the size of Process "<<proc_count<<" : ";
    cin>>arrived.size;
    int list_size=proc_list.size();
    if(list_size==0){
        //This means list and total memory are fully empty
        if(arrived.size<=total_mem){
            cout<<"\tProcess "<<arrived.id<<" inserted at beginning\n";
            arrived.starts=0;arrived.ends=arrived.starts+arrived.size;
            proc_list.push_back(arrived);
        }
        else{
            cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted as only "<<total_mem<<"KB is remaining\n";
        }
        return;
    }
    int i=0,starting=0,space=0,total_space=0;
    while(i<list_size){
        space=proc_list[i].starts-starting;//This is the available space before process i in memory
        if(space>=arrived.size){
            //This means the space here is sufficient for inserting this process
            cout<<"\tProcess "<<arrived.id<<" inserted in space before Process "<<proc_list[i].id<<"\n";
            arrived.starts=starting;arrived.ends=arrived.starts+arrived.size;
            proc_list.insert(proc_list.begin()+i,arrived);
            return;//We are done with insertion
        }
        else{
            total_space+=space;//Total space is used to know external fragmentation
            starting=proc_list[i].ends;//We updating starting point for next space
            i++;//We check for next process
        }
    }
    //We now check if there is space to insert after last process
    starting=proc_list[i-1].ends;//Now starting of space points to the ending of last process in list
    space=total_mem-starting;
    if(space>=arrived.size){
        //This means there is sufficient space after the last process
        cout<<"\tProcess "<<arrived.id<<" inserted at the end of all processes\n";
        arrived.starts=starting;arrived.ends=arrived.starts+arrived.size;
        proc_list.insert(proc_list.end(),arrived);
        return;//We are done with insertion
    }
    else total_space+=space;//Update total space

    //Now we know that the process wasnt inserted
    if(total_space<arrived.size){
        //This means that there wasnt enough space overall in the CPU
        cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted as only "<<total_space<<"KB is remaining\n";
    }
    else{
        //This means space was present but it is spread over different fragments
        cout<<"\tProcess "<<arrived.id<<" of size "<<arrived.size<<"KB couldnt be inserted due to external fragmentation\n";
    }

    return;
}

void AllFits(){
    system("cls");
    int choice = 1;
    proc_list.clear(); // We first clear our list
    if(fit==1){
        cout<<"\n\n\t---------------------------------------\n";
        cout<<    "\t    FIRST FIT VARIABLE ALLOCATION      \n";
        cout<<"\t---------------------------------------\n\n";
    }
    else if(fit==2){
        cout<<"\n\n\t---------------------------------------\n";
        cout<<    "\t    BEST FIT VARIABLE ALLOCATION      \n";
            cout<<"\t---------------------------------------\n\n";
    }
    else if(fit==3){
        cout<<"\n\n\t---------------------------------------\n";
        cout<<    "\t    WORST FIT VARIABLE ALLOCATION      \n";
            cout<<"\t---------------------------------------\n\n";
    }
    else{
        exit(0);
    }
    cout<<"\t Enter total memory in the processor: ";
    cin>>total_mem;
    proc_count = 0;
    while(choice!=3){
    system("cls");
    if(fit==1){
        cout<<"\n\n\t---------------------------------------\n";
        cout<<    "\t    FIRST FIT VARIABLE ALLOCATION      \n";
        cout<<"\t---------------------------------------\n\n";
    }
    else if(fit==2){
        cout<<"\n\n\t---------------------------------------\n";
        cout<<    "\t    BEST FIT VARIABLE ALLOCATION      \n";
            cout<<"\t---------------------------------------\n\n";
    }
    else if(fit==3){
        cout<<"\n\n\t---------------------------------------\n";
        cout<<    "\t    WORST FIT VARIABLE ALLOCATION      \n";
            cout<<"\t---------------------------------------\n\n";
    }
    else{
        exit(0);
    }
    // proc_list.clear(); // We first clear our list
    // // int choice=1;
    // int proc_count=0;//There are zero processes initially
    // while(choice!=3){
        cout<<"\n";
        cout<<"\t          1. INSERT PROCESS               \n";
        cout<<"\t          2. DELETE PROCESS               \n";
        cout<<"\t          3. EXIT                   \n\n";
        cout<<"\t          CHOOSE THE OPTION: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            if(fit==1) InsertFirstFit();
            else if(fit==2) InsertBestFit();
            else if(fit==3) InsertWorstFit();
            break;
        case 2:
            DeleteProcess();
            break;
        case 3:
            break;
        default:
            cout<<"\tWrong Input\n";
            break;
        }
        getchar();
        getchar();
    }
    cout<<"\n";
    int i,partition_count=0,list_size=proc_list.size();
    if(proc_list[0].starts!=0){
        //This means there is empty space at the beginning
        partition_count++;
        cout<<"\tPartition "<<partition_count<<" is empty with space "<<proc_list[0].starts-0<<"KB\n";
    }
    for(i=0;i<list_size;i++){
        partition_count++;
        cout<<"\tPartition "<<partition_count<<" has Process "<<proc_list[i].id<<" with size "<<proc_list[i].size<<"KB\n";
        if(i!=list_size-1&&proc_list[i].ends!=proc_list[i+1].starts){
            //This means there is empty space after process i
            partition_count++;
            cout<<"\tPartition "<<partition_count<<" is empty with space "<<proc_list[i+1].starts-proc_list[i].ends<<"KB\n";
        }
    }
    if(proc_list[list_size-1].ends!=total_mem){
        //This means there is empty space at the end
        partition_count++;
        cout<<"\tPartition "<<partition_count<<" is empty with space "<<total_mem-proc_list[list_size-1].ends<<"KB\n";
    }
}



int main(){
    while(1){
        system("cls");
    cout<<"\n\n\n\t---------------------------------------\n";
    cout<<"\t           MVT MEMORY MANAGEMENT       \n";
    cout<<"\t---------------------------------------\n\n";
    cout<<"\t             1. FIRST FIT                \n";
    cout<<"\t             2. BEST FIT                 \n";
    cout<<"\t             3. WORST FIT                \n";
    cout<<"\t             4. EXIT                   \n\n";
    cout<<"\t---------------------------------------\n\n";
    cout<<"\t          CHOOSE THE OPTION: ";
    cin>>fit;
    getchar();
    AllFits();
    cout<<"\n\t          Press any key to continue!";
    getchar();
    getchar();
    }
    //Same basic code for all fits as fit comes into play only during insertion
    return 0;
}