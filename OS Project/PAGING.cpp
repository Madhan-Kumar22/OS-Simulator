#include <iostream>
#include <queue>

using namespace std;


int main(){
    int v_mem, p_mem, pg_size;
    cout<<"\t------ACCESSING PHYSICAL MEMORY-------\n";
    cout<<"\n\tEnter the virtual memory size: ";
    cin>>v_mem;
    cout<<"\tEnter the physical memory size: ";
    cin>>p_mem;
    cout<<"\tEnter the page size: ";
    cin>>pg_size;
    getchar();
    int v_pg = v_mem/pg_size;
    int p_pg = p_mem/pg_size;
    cout<<"\n\tNumber of pages in virtual memory: "<<v_pg;
    cout<<"\n\tNumber of frames in physical memory: "<<p_pg;
    getchar(); 
    int virt[v_pg], phy[p_pg];
    int pg_faults = 0, requests = 0, opt, i = 0, entries = 0;
    for(int i=0; i<v_pg; i++)
        virt[i] = -1;   //not assigned to any frame in the physical memory
    for(int i=0; i<p_pg; i++)
        phy[i] = -1;

    while(1){
        system("cls");
        cout<<"\t-------ACCESSING PHYSICAL MEMORY-------\n";
        cout<<"\n\tMENU: \n\t1. ENTER VIRTUAL ADDRESS\n\t2. END\n";
        cout<<"\tEnter option: ";
        cin>>opt;
        getchar();
        if(opt==1){
            int pg_no, offset;
            cout<<"\n\tEnter VA (format: [page_no] [offset]): ";
            cin>>pg_no>>offset;
            getchar();
            if(virt[pg_no] == -1){
                cout<<"\n\tPage "<<pg_no<<" is not in any frame!\n";
                if(offset < (pg_size/2)*1024){
                    cout<<"\tThe offset is within bounds, page "<<pg_no<<" will be assigned to frame "<<i;
                    virt[pg_no] = i;
                    if(entries < p_pg){
                        entries++;
                        cout<<"!\n";
                    }
                    else{
                        cout<<" after removing page "<<phy[i]<<"!\n";
                        virt[phy[i]] = -1;
                    }
                    //update frame
                    phy[i] = pg_no;
                    i = (i + 1)%p_pg;
                 }
                 else{
                     cout<<"\tThe page cannot be accommodated in any frame as the offset is out of bounds!\n";
                 }
                 pg_faults++;
            }
            else{
                cout<<"\n\tPage "<<pg_no<<" is present in frame "<<virt[pg_no]<<"!\n";
                if(offset < (pg_size/2)*1024)
                    cout<<"\tPhysical Address: | "<<virt[pg_no]<<" | "<<offset<<" |";
                else
                    cout<<"\tThe offset is out of bounds!\n";
            }
            requests++;
            getchar();
        }
        else{
            break;
        }
    }
    cout<<"\n\n\tNumber of page faults: "<<pg_faults;
    cout<<"\n\tPage Fault Ratio: "<<(float)pg_faults/requests;
    cout<<"\n\n\tPage Table: \n\tPage\tFrame\n";
    for(int i=0; i<v_pg; i++){
        cout<<"\t"<<i<<"\t"<<virt[i]<<"\n";
    }
    cout<<"\n\n\tPhysical Memory:\n\tFrame\tPage\n";
    for(int i=0; i<p_pg; i++){
        cout<<"\t"<<i<<"\t"<<phy[i]<<"\n";
    }
    getchar();
    getchar();
}


