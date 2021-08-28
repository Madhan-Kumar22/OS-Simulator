#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

int main(){

    int opt;
    while(1){
        system("cls");
        cout<<"\n\n\n\t---------------------------------------\n";
        cout<<"\t        PROCESS SYNCHRONISATION        \n";
        cout<<"\t---------------------------------------\n\n";
        cout<<"\t         1. READERS-WRITERS          \n";
        cout<<"\t         2. PRODUCER-CONSUMER        \n";
        cout<<"\t         3. DINING-PHILOSOPHERS      \n";
        cout<<"\t         4. SLEEPING-BARBERS         \n";
        cout<<"\t         5. EXIT                     \n\n";
        cout<<"\t---------------------------------------\n\n";
        cout<<"\t         CHOOSE THE OPTION: ";
        cin>>opt;

        STARTUPINFO si = {sizeof (STARTUPINFO)};
        PROCESS_INFORMATION pi;
        switch(opt){
            case 1:
                
                CreateProcess("ReadWrite.exe", NULL, 0, 0, 0, 0, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE);
                break;
            case 2:
                
                CreateProcess("ProdCons.exe", NULL, 0, 0, 0, 0, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE);
                break;
            case 3:
                
                CreateProcess("DinPhil.exe", NULL, 0, 0, 0, 0, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE);
                break;
            case 4:
                
                CreateProcess("SleepBarb.exe", NULL, 0, 0, 0, 0, 0, 0, &si, &pi );
                WaitForSingleObject( pi.hProcess, INFINITE);
                break;
            case 5:
                exit(0);
        }
    }
    return 0;
}