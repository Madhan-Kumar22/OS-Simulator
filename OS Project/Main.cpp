#include <iostream>
#include <windows.h>

using namespace std;

int main(){
    int opt;
    while(1){
        system("cls");
        cout<<"\n\n\t---------------------------------------------\n";
        cout<<"\t             OS SIMULATOR\n";
        cout<<"\t----------------------------------------------\n\n";
        cout<<"\t        1. PROCESS SCHEDULING\n";
        cout<<"\t        2. PROCESS SYNCHRONIZATION\n";
        cout<<"\t        3. BANKER\'S ALGORITHM\n";
        cout<<"\t        4. MFT\n";
        cout<<"\t        5. MVT\n";
        cout<<"\t        6. PAGE REPLACEMENT\n";
        cout<<"\t        7. DISK SCHEDULING\n";
        cout<<"\t        8. PAGE TABLE\n";
        cout<<"\t        9. EXIT\n\n";
        cout<<"\t----------------------------------------------\n\n";
        cout<<"\t            CHOOSE THE OPTION: ";
        cin>>opt;

        STARTUPINFO si = {sizeof (STARTUPINFO)};
        PROCESS_INFORMATION pi;

        switch(opt){
            case 1:
                CreateProcess("Scheduling.exe", NULL, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE );
                break;
            case 2:
                CreateProcess("ProcessSync.exe", NULL, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE );
                break;
            case 3:
                CreateProcess("Bank.exe", NULL, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE );
                break;
            case 4:
                CreateProcess("MFT.exe", NULL, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE );
                break;
            case 5:
                CreateProcess("MVT.exe", NULL, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE );
                break;
            case 6:
                CreateProcess("PageRep.exe", NULL, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE );
                break;
            case 7:
                CreateProcess("Disk.exe", NULL, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE );
                break;
            case 8:
                CreateProcess("PAGING.exe", NULL, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE );
                break;
            case 9:
                exit(0);
        }
        cout<<"\n\t          Press any key to continue! ";
        getchar();
        getchar();
    }
}