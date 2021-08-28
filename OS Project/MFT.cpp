// implementation Fixed Size partition
#include <cstdio>
#include <cstdlib>
//#include <unistd.h>
void firstFit(int blockSize[], int m,
			int processSize[], int n)
{
	int allocation[n], i, j, done[m];

	for(i=0;i<n;i++)
	    allocation[i]=-1;
    for(i=0;i<m;i++)
	    done[i]=0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (blockSize[j] >= processSize[i] && done[j]==0)
			{
				allocation[i] = j;
				done[i]=1;
				// Reduce available memory in this block.
				blockSize[j] -= processSize[i];

				break;
			}
		}
	}

	printf("\n\t-------------TABLE------------------\n");
	printf("\tProcess No.\tProcess Size\tBlock no.\n");
	for (i = 0; i < n; i++)
	{
		printf("\n\t%d\t\t%d\t\t", i+1 ,processSize[i]);
		if (allocation[i] != -1)
			printf("\t%d\n",allocation[i] + 1);
		else
			printf("\tNot Allocated\n");
	}
}
void bestFit(int blockSize[], int m, int processSize[], int n)
{
	int allocation[n],i,j, done[m];

	for(i=0;i<n;i++)
	    allocation[i]=-1;
    for(i=0;i<m;i++)
	    done[i]=0;
    for (i=0; i<n; i++)
    {
        // Find the best fit block for current process
        int bestIdx = -1;
        for (j=0; j<m; j++)
        {
            if (blockSize[j] >= processSize[i] && done[j]==0)
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;

            }
        }

        // If we could find a block for current process
        if (bestIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = bestIdx;

            // Reduce available memory in this block.
            blockSize[bestIdx] -= processSize[i];
			 done[bestIdx]=1;
        }
    }

	printf("\n\t-------------TABLE------------------\n");
	printf("\tProcess No.\tProcess Size\tBlock no.\n");
	for (i = 0; i < n; i++)
	{
		printf("\t%d\t\t%d\t\t", i+1 ,processSize[i]);
		if (allocation[i] != -1)
			printf("\t%d\n",allocation[i] + 1);
		else
			printf("\tNot Allocated\n");
	}
}
void worstFit(int blockSize[], int m, int processSize[], int n)
{
	int allocation[n],i,j, done[m];

	for(i=0;i<n;i++)
	    allocation[i]=-1;
    for(i=0;i<m;i++)
	    done[i]=0;
    for (i=0; i<n; i++)
    {
        // Find the worst fit block for current process
        int worstIdx = -1;
        for (j=0; j<m; j++)
        {
            if (blockSize[j] >= processSize[i]  && done[j]==0)
            {
                if (worstIdx == -1)
                    worstIdx = j;
                else if (blockSize[worstIdx] < blockSize[j])
                    worstIdx = j;
            }
        }

        // If we could find a block for current process
        if (worstIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = worstIdx;

            // Reduce available memory in this block.
            blockSize[worstIdx] -= processSize[i];
            done[worstIdx]=1;
        }
    }

	printf("\n\t-------------TABLE------------------\n\n");
	printf("\tProcess No.\tProcess Size\tBlock no.\n");
	for (i = 0; i < n; i++)
	{
		printf("\t%d\t\t%d\t\t", i+1 ,processSize[i]);
		if (allocation[i] != -1)
			printf("\t%d\n",allocation[i] + 1);
		else
			printf("\tNot Allocated\n");
	}
}
int main()
{
    int n2,m,n,i,j=0;

	while(1)
	{
    system("cls");
	printf("\n\n\n\t---------------------------------------\n");
    printf("\t          MFT MEMORY MANAGEMENT          \n");
    printf("\t---------------------------------------\n\n");
    printf("\t             1. FIRST FIT                \n");
	printf("\t             2. BEST FIT                \n");
	printf("\t             3. WORST FIT                 \n");
	printf("\t             4. Exit                \n\n");
	printf("\t---------------------------------------\n\n");
	printf("\t         CHOOSE THE OPTION: ");
	scanf("%d",&n2);

	system("cls");
	switch(n2) {
        case 1:
            printf("\n\n\t---------------------------------------\n");
            printf("    \t    FIRST FIT FIXED ALLOCATION      \n");
            printf("\t---------------------------------------\n\n");

            break;
        case 2:
            printf("\n\n\t---------------------------------------\n");
            printf("    \t    BEST FIT FIXED ALLOCATION      \n");
            printf("\t---------------------------------------\n\n");

            break;
        case 3:
            printf("\n\n\t---------------------------------------\n");
            printf("    \t    WORST FIT FIXED ALLOCATION      \n");
            printf("\t---------------------------------------\n\n");
            break;
		case 4:
			exit(0);
        default:
            printf("\n\tEnter a valid input!");
    }


	printf("\n\tEnter number of blocks: ");
	scanf("%d",&m);
	printf("\tEnter number of processes: ");
	scanf("%d",&n);

	int blk[m],p[n];
	printf("\n\tEnter block sizes: ");
	for(i=0;i<m;i++)
        scanf("%d",&blk[i]);
	printf("\n\tEnter process sizes: ");
	for(i=0;i<n;i++)
	   scanf("%d",&p[i]);

    switch(n2)
			{
			case 1:firstFit(blk, m, p, n);
                break;
            case 2:bestFit(blk, m, p, n);
                break;
            case 3:worstFit(blk, m, p, n);
                break;
            default:printf("\n\tEnter correct option");
                break;

			}
    printf("\n\tPress any key to continue!\n");
	getchar();
    getchar();

	}

	return 0 ;
}
