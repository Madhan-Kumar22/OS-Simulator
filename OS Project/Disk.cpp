#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void swap(int a[], int i, int j)
{
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void sort(int a[], int n)
{
  for(int i=0; i<n-1; i++)
    for(int j=i+1; j<n; j++)
      if(a[i] > a[j])
        swap(a, i, j);
}
void look(){
  system("cls");
  int n, numberOfTracks, choice;
  string dir;
  string left = "left", right = "right";

  cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        LOOK DISK SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";

  printf("\tEnter number of tracks : ");
  scanf("%d", &numberOfTracks);


  printf("\tEnter number of requests : ");
  scanf("%d", &n);

  int request[n];
  printf("\tEnter current track position : ");
  scanf("%d", &request[0]);

  printf("\n\tEnter the requests:");
  for(int i=1; i<=n; i++)
    scanf("%d", &request[i]);
  n++;

  printf("\n\tEnter the direction : ");
  cin>>dir;
  int ans, pos, firstRequest = request[0];
  sort(request, n);

  //Find position of first request
  for(int i=0; i<n; i++)
    if(request[i] == firstRequest)
    {
      pos = i;
      break;
    }
  transform(dir.begin(), dir.end(), dir.begin(), ::tolower);
  printf("\n\tHead movement\n");

  if(dir.compare(right) == 0){
      for(int i=pos+1; i<n; i++)
      printf("\t%d -> %d\n", request[i-1], request[i]);

    //Backward
    if(pos>0)
      printf("\t%d -> %d\n", request[n-1], request[pos-1]);
    for(int i=pos-2; i>=0; i--)
      printf("\t%d -> %d\n", request[i+1], request[i]);

    ans = request[n-1] - request[pos];
    if(pos>0)
      ans += request[n-1] - request[0];
  }

  else if(dir.compare(left) == 0){
      for(int i = pos-1; i>=0; i--)
        printf("\t%d -> %d\n", request[i+1], request[i]);
      if(pos < n-1){
          printf("\t%d -> %d\n", request[0], request[pos+1]);
      }
      for(int i=pos+2; i<n; i++){
          printf("\t%d -> %d\n", request[i-1], request[i]);
      }

      ans = request[pos] - request[0];
      if(pos < n-1)
        ans += request[n-1] - request[0];
  }
    //Forward


  printf("\n\tTotal seek time/Head Movement : %d\n\n", ans);
}

void clook(){
  system("cls");
  int n, numberOfTracks, choice, temp;
  string left = "left", right = "right", dir;

  cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        CLOOK DISK SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";

  cout<<"\tEnter number of tracks : ";
  cin>>numberOfTracks;


  cout<<"\tEnter number of requests : ";
  cin>>n;
  vector <int> request;

  cout<<"\tEnter current track position : ";
  cin>>temp;
  request.push_back(temp);

  cout<<"\n\tEnter the requests\n";
  cout<<"\t";
  for(int i=1; i<=n; i++){
    cin>>temp;
    request.push_back(temp);
  }
  n++;

  cout<<"\n\tEnter the direction: ";
  cin>>dir;

  transform(dir.begin(), dir.end(), dir.begin(), ::tolower);
  int ans, pos, firstRequest = request[0];
  sort(request.begin(), request.end());

  vector<int> l, r;
  int seek_time = 0, curr_tr;
  for(int i=0; i < request.size(); i++){
        if(request[i] < firstRequest)
            l.push_back(request[i]);
        else if (request[i] > firstRequest)
            r.push_back(request[i]);
  }
  sort(l.begin(), l.end());
  sort(r.begin(), r.end());

  cout<<"\n\tHead Movement: \n";
  if(dir.compare(left) == 0){
    for(int i = l.size()-1; i>=0; i--){
        curr_tr = l[i];
        seek_time += abs(curr_tr - firstRequest);
        cout<<"\t"<<firstRequest<<" -> "<<curr_tr<<"\n";
        firstRequest = curr_tr;
    }

    if(!r.empty()){
      seek_time += abs(firstRequest - r[r.size()-1]);
      cout<<"\t"<<firstRequest<<" -> "<<r[r.size()-1]<<"\n";
      firstRequest = r[r.size()-1];
    }

    for(int i=r.size()-2; i>=0; i--){
        curr_tr = r[i];
        seek_time += abs(curr_tr - firstRequest);
        cout<<"\t"<<firstRequest<<" -> "<<curr_tr<<"\n";
        firstRequest = curr_tr;
    }
  }
  else if(dir.compare(right) == 0){
    for(int i = 0; i<r.size(); i++){
        curr_tr = r[i];
        seek_time += abs(curr_tr - firstRequest);
        cout<<"\t"<<firstRequest<<" -> "<<curr_tr<<"\n";
        firstRequest = curr_tr;
    }

    if(!l.empty()){
      seek_time += abs(firstRequest - l[0]);
      cout<<"\t"<<firstRequest<<" -> "<<l[0]<<"\n";
      firstRequest = l[0];
    }

    for(int i=1; i<l.size(); i++){
        curr_tr = l[i];
        seek_time += abs(curr_tr - firstRequest);
        cout<<"\t"<<firstRequest<<" -> "<<curr_tr<<"\n";
        firstRequest = curr_tr;
    }
  }
  cout<<"\n\tTotal Head Movement: "<<seek_time<<"\n\n";
}

void scan(){
  system("cls");
  int n, numberOfTracks, choice, temp;
  string left = "left", right = "right", dir;

  cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        SCAN DISK SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";

  cout<<"\tEnter number of tracks : ";
  cin>>numberOfTracks;


  cout<<"\tEnter number of requests : ";
  cin>>n;
  vector <int> request;

  cout<<"\tEnter current track position : ";
  cin>>temp;
  request.push_back(temp);

  cout<<"\n\tEnter the requests: ";
  for(int i=1; i<=n; i++){
    cin>>temp;
    request.push_back(temp);
  }
  n++;

  cout<<"\n\tEnter the direction: ";
  cin>>dir;
  transform(dir.begin(), dir.end(), dir.begin(), ::tolower);
  int ans, pos, firstRequest = request[0];
  sort(request.begin(), request.end());

  vector<int> l, r;
  int seek_time = 0, curr_tr;
  for(int i=0; i < request.size(); i++){
      if(request[i] < firstRequest)
          l.push_back(request[i]);
      else if (request[i] > firstRequest)
          r.push_back(request[i]);
  }
  sort(l.begin(), l.end());
  sort(r.begin(), r.end());

  cout<<"\n\tHead Movement: \n";
  if(dir.compare(left)==0){
    for(int i = l.size()-1; i>=0; i--){
        curr_tr = l[i];
        seek_time += abs(curr_tr - firstRequest);
        cout<<"\t"<<firstRequest<<" -> "<<curr_tr<<"\n";
        firstRequest = curr_tr;
    }
    if(firstRequest != 0){
      seek_time += abs(firstRequest - 0);
      cout<<"\t"<<firstRequest<<" -> "<<0<<"\n";
      firstRequest = 0;
    }
    for(int i=0; i<r.size(); i++){
        curr_tr = r[i];
        seek_time += abs(curr_tr - firstRequest);
        cout<<"\t"<<firstRequest<<" -> "<<curr_tr<<"\n";
        firstRequest = curr_tr;
    }
  }
  else if(dir.compare(right) == 0){
    for(int i=0; i<r.size(); i++){
        curr_tr = r[i];
        seek_time += abs(curr_tr - firstRequest);
        cout<<"\t"<<firstRequest<<" -> "<<curr_tr<<"\n";
        firstRequest = curr_tr;
    }
    if(firstRequest != numberOfTracks-1){
      seek_time += abs(firstRequest - numberOfTracks + 1);
      cout<<"\t"<<firstRequest<<" -> "<<numberOfTracks-1<<"\n";
      firstRequest = numberOfTracks-1;
    }
    for(int i = l.size()-1; i>=0; i--){
        curr_tr = l[i];
        seek_time += abs(curr_tr - firstRequest);
        cout<<"\t"<<firstRequest<<" -> "<<curr_tr<<"\n";
        firstRequest = curr_tr;
    }
  }

  cout<<"\n\tTotal Head Movement: "<<seek_time<<"\n\n";
}

void cscan(){
  system("cls");
  int n, numberOfTracks, choice;
  string dir;
  string left = "left", right = "right";

  cout<<"\n\n\t---------------------------------------\n";
  cout<<"\t        CSCAN DISK SCHEDULING           \n";
  cout<<"\t---------------------------------------\n\n";

  printf("\tEnter number of tracks : ");
  scanf("%d", &numberOfTracks);

  printf("\tEnter number of requests : ");
  scanf("%d", &n);

  int request[n+1];

  printf("\tEnter current track position : ");
  scanf("%d", &request[0]);

  printf("\n\tEnter the requests\n");
  printf("\t");
  for(int i=1; i<=n; i++)
    scanf("%d", &request[i]);
  n++;

  printf("\n\tEnter the direction : ");
  cin>>dir;

  int ans, pos, firstRequest = request[0];
  sort(request, n);

  //Find position of first request
  for(int i=0; i<n; i++)
    if(request[i] == firstRequest)
    {
      pos = i;
      break;
    }

  transform(dir.begin(), dir.end(), dir.begin(), ::tolower);

  printf("\n\tHead movement:\n");

  if(dir.compare(left) == 0){
    for(int i = pos; i > 0; i--){
      printf("\t%d -> %d\n", request[i], request[i-1]);
    }
    if(request[0] != 0)
      printf("\t%d -> 0\n", request[0]);

    if(pos < n-1){
      //printf("\t");
      printf("\t0 -> %d\n\t%d -> %d\n", numberOfTracks-1, numberOfTracks-1, request[n-1]);
    }

    for(int i = n-2; i>pos; i--){
      printf("\t%d -> %d\n", request[i+1], request[i]);
    }

    ans = request[pos];
    if(pos < n-1)
      ans += (numberOfTracks - 1 - request[pos+1]);
  }

  else if(dir.compare(right) == 0){
    for(int i=pos+1; i<n; i++)
      printf("\t%d -> %d\n", request[i-1], request[i]);
    if(request[n-1] != numberOfTracks)
      printf("\t%d -> %d\n", request[n-1], numberOfTracks -1);

    if(pos>0)
      printf("\t%d -> 0\n\t0 -> %d\n", numberOfTracks -1, request[0]);
    for(int i=1; i<pos; i++)
      printf("\t%d -> %d\n", request[i-1], request[i]);

    ans = numberOfTracks - request[pos] -1;
    if(pos>0)
      ans += request[pos-1]+ numberOfTracks -1;
  }
  printf("\n\tTotal Head Movement : %d\n\n", ans);
}

void sstf(){
  system("cls");
    int i,j,sum=0,n,pos,trc,ind,temp;

	cout<<"\n\n\t---------------------------------------\n";
	cout<<"\t        SSTF DISK SCHEDULING           \n";
	cout<<"\t---------------------------------------\n\n";
    printf("\tEnter number of tracks: ");
    scanf("%d",&n);
    printf("\tEnter position of head: ");
    scanf("%d",&pos);
    printf("\tEnter the no of tracks you want to traverse: ");
    scanf("%d",&trc);

    int ar[trc]; //ar is the queue
    printf("\tEnter tracks of disk queue: ");
    for(i=0;i<trc;i++)
        scanf("%d",&ar[i]);


    for(i=0;i<trc;i++)
    {
    int st = 1000;
    for(j=0;j<trc;j++)
    {
        if((abs(pos-ar[j])) == st)
        {
          if(ar[j]>ar[ind])
            ind =j;
          else
            ind =ind;
        }

      if( (abs(pos-ar[j])) < st && st>0)
      {
        st=abs(pos-ar[j]);
        ind =j;
        }
      }

      pos=ar[ind];
      ar[ind]=10000;
      printf("\tNew pos is %d\n",pos);
      sum+=st;

    }
    printf("\n\tSeek Time is %d units",sum);
}
void fcfs(){
    system("cls");
    int n, numberOfTracks, choice, seek = 0;

	cout<<"\n\n\t---------------------------------------\n";
    cout<<"\t        FCFS DISK SCHEDULING           \n";
    cout<<"\t---------------------------------------\n\n";

    printf("\tEnter number of tracks : ");
    scanf("%d", &numberOfTracks);


    printf("\tEnter number of requests : ");
    scanf("%d", &n);

    int request[n+1];

    printf("\tEnter current track position : ");
    scanf("%d", &request[0]);

    printf("\n\tEnter the requests: ");
    for(int i=1; i<=n; i++)
        scanf("%d", &request[i]);

    for(int j=0; j<n; j++){
        int diff = abs(request[j]-request[j+1]);
        seek += diff;
        printf("\tMove from %d to %d with Seek %d\n",request[j],request[j+1],diff);//100-88->2tracks
    }

    cout<<"\n\tTotal seek time/head movement: "<<seek<<endl;
}

int main(){
  int opt;
  while(1){
    system("cls");
    cout<<"\n\n\n\t---------------------------------------\n";
    cout<<"\t             DISK SCHEDULING           \n";
    cout<<"\t---------------------------------------\n\n";
    cout<<"\t               1. FCFS                \n";
    cout<<"\t               2. SSTF                \n";
    cout<<"\t               3. SCAN                \n";
    cout<<"\t               4. C-SCAN              \n";
    cout<<"\t               5. LOOK                \n";
    cout<<"\t               6. C-LOOK              \n";
    cout<<"\t               7. EXIT              \n\n";
    cout<<"\t---------------------------------------\n\n";
    cout<<"\t          CHOOSE THE OPTION: ";
    cin>>opt;
    getchar();
    switch(opt){
      case 1:
        fcfs();
        break;
      case 2:
        sstf();
        break;
      case 3:
        scan();
        break;
      case 4:
        cscan();
        break;
      case 5:
        look();
        break;
      case 6:
        clook();
        break;
      case 7:
        exit(0);
    }
    cout<<"\n\tPress any key to continue!\n";
    getchar();
    getchar();
  }
}
