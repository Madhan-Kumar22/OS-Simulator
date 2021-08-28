#include <cstdio>
#include <cstdlib>

#define N 1000

void printMemoryTable(int memoryTable[], int numberOfFrames)
{
	for(int i=0; i<numberOfFrames; i++)
	{
		if(memoryTable[i] == -1)                    //printing dash if frame is empty
			printf("-- ");
		else
			printf("%2d ", memoryTable[i]);         //printing respective pages in frame
	}
	printf(" |");
}

int exists(int memoryTable[], int numberOfFrames, int target)
{
	int i;
	for(i=0;i<numberOfFrames;i++)
	{
		if(memoryTable[i]==target)                  //if page exists in the current set of frames , we skip page fault
			return 1;
	}
	return 0;
}

int getPosLRU(int memoryTable[],int numberOfFrames, int pages[], int m , int target)
{
    for(int i=0; i<numberOfFrames; i++)
		if(memoryTable[i] == -1)
			return i;

    int used[N] = {0};
	for(int i=0; i<numberOfFrames; i++)
	{
		used[i] = -100000000;
		for(int j=m-1; j>=0; j--)
			if(pages[j] == memoryTable[i])
			{
				used[i] = j;                    //stores page index in a different array(used[]) which already exists in the current frame
				break;
			}
	}


    int minTime = 1000000, pos = -1;
	for(int i=0; i<numberOfFrames; i++)
		if(used[i]< minTime  )                  //finds minimum index in that particular array (used[])
		{
			minTime = used[i];
			pos = i;
		}

	return pos;
}


int getPosMRU(int memoryTable[],int numberOfFrames, int pages[], int m , int target)
{
    for(int i=0; i<numberOfFrames; i++)
		if(memoryTable[i] == -1)
			return i;

    int used[N] = {0};
	for(int i=0; i<numberOfFrames; i++)
	{
		used[i] = -100000000;
		for(int j=m-1; j>=0; j--)
			if(pages[j] == memoryTable[i])
			{
				used[i] = j;                    //stores page index in a different array(used[]) which already exists in the processes order before it
				break;
			}
	}


    int max = -1, pos = -1;
	for(int i=0; i<numberOfFrames; i++)
		if(max <used[i])                  //finds maximum index in that particular array (used[])
		{
			max = used[i];
			pos = i;
		}

	return pos;
}

int getposOPT(int memoryTable[], int numberOfFrames, int pages[], int m, int n)
{
	for(int i=0; i<numberOfFrames; i++)
		if(memoryTable[i] == -1)
			return i;

	int used[N] = {0};
	for(int i=0; i<numberOfFrames; i++)
	{
		used[i] = 100000000;
		for(int j=m+1; j<n; j++)
			if(pages[j] == memoryTable[i])
			{
				used[i] = j;						 //stores page index in a different array(used[]) which already exists in the processes order after it
				break;
			}
	}

	int max = -1, pos = -1;
	for(int i=0; i<numberOfFrames; i++)
		if(max < used[i])							//finds maximum index in that particular array (used[])
		{
			max = used[i];
			pos = i;
		}

	return pos;
}



int main()
{
    int pages[N];
	int numberOfFrames, pos,n,pageFault,i,j,memoryTable[N],choice;
	while(1)
	{
	system("cls");

	pos=0;
	pageFault=0;
	for(int i=0; i<N; i++)
		memoryTable[i] = -1;                        //Initializing memoryTable with -1 for all the frames
	//system("clear");
	printf("\n\n\n\t---------------------------------------\n");
    printf("\t             PAGE REPLACEMENT           \n");
    printf("\t---------------------------------------\n\n");
    printf("\t               1. FIFO                \n");
	printf("\t               2. LRU                \n");
	printf("\t               3. MRU                \n");
	printf("\t               4. OPTIMAL                \n");
	printf("\t               5. Exit                \n\n");
	printf("\t---------------------------------------\n\n");
	printf("\t          CHOOSE THE OPTION: ");
	scanf("%d", &choice);


    system("cls");
    switch(choice)
			{
			case 1: printf("\n\n\t---------------------------------------\n");
                    printf("\t        FIFO PAGE REPLACEMENT            \n");
                    printf("\t---------------------------------------\n\n");
                break;
			case 2: printf("\n\n\t---------------------------------------\n");
                    printf("\t        LRU PAGE REPLACEMENT            \n");
                    printf("\t---------------------------------------\n\n");
                break;
            case 3: printf("\n\n\t---------------------------------------\n");
                    printf("\t        MRU PAGE REPLACEMENT            \n");
                    printf("\t---------------------------------------\n\n");
                break;
            case 4: printf("\n\n\t---------------------------------------\n");
                    printf("\t        OPTIMAL PAGE REPLACEMENT            \n");
                    printf("\t---------------------------------------\n\n");
                break;
			case 5:
				exit(0);
            default:printf("\n\t        Enter correct option");
                break;

			}


	printf("\n\tEnter the number of frames: ");
	scanf("%d", &numberOfFrames);
	printf("\n\tEnter number of page requests: ");
	scanf("%d", &n);
	printf("\n\tEnter the list of page requests: ");
	for(i=0;i<n;i++)
	{
		scanf("%d", &pages[i]);
	}
	for(int i=0; i<n; i++)
	{
		printf("\n\tTable after request %2d | ", pages[i]);

		if(!exists(memoryTable, numberOfFrames, pages[i]))              //if exists is 1 -> no page fault ,else page fault
		{
			switch(choice)
			{
			case 1:memoryTable[pos] = pages[i];
			    pos = (pos +1)%numberOfFrames;                              // follows FIFO order (i.e. cycles through the no of frames)
                break;
			case 2:pos = getPosLRU(memoryTable,numberOfFrames, pages,i,pages[i]);
                break;
            case 3:pos = getPosMRU(memoryTable,numberOfFrames, pages,i,pages[i]);
                break;
            case 4:pos = getposOPT(memoryTable, numberOfFrames, pages, i, n);
                break;
            default:printf("\n\tEnter correct option");
                break;

			}



            if(choice!=1)
                memoryTable[pos] = pages[i];
			printMemoryTable(memoryTable, numberOfFrames);
			printf("\tPage Fault\n");
			pageFault++;
			continue;
		}

		printMemoryTable(memoryTable, numberOfFrames);
		printf("\n");
	}
	printf("\n\tNumber of Page Faults: %d\n", pageFault);
	printf("\n\tPage Fault Ratio: %f\n", (float)pageFault/n);


	printf("\n\tPress any key to continue!\n");
    getchar();
    getchar();
	}

}
