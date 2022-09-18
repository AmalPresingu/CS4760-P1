//Author: Amal Presingu
//Date:   9/18/2022

#include "main.h"

int main(int argc, char **argv)
{
	FILE *inFile;
	FILE *outFile;

	char* inFileName = NULL;
	char* outFileName = NULL;

	int opt; 
	while ((opt = getopt(argc, argv, "hi:o:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				printf("\n-------Command Line Help-------\n\n");
        		        printf("./chain -h                    Helps with command line arguments.\n");
	           	        printf("./chain -i [INPUTFILENAME]    Takes in a file name and reverses the intergers into output file.\n");
           			printf("./chain -o [OUTPUTFILENAME]   If user specifies filename, the output will be printed to that file.\n\n");
				exit(0);
				break;
			case 'i':
				inFileName = optarg;
				break;
			case 'o':
				outFileName = optarg;
				break;
			default:
				printf("Invalid argument. Please type ./chain -h");
		}
	}
	
	if (outFileName == NULL && inFileName == NULL)
	{
		inFileName = "input.dat";
		outFileName = "output.dat";
	}
	
	//input filename is still going to null condition
	else if (outFileName == NULL && inFileName != "input.dat")
	{
		outFileName = inFileName;
        	strcat(outFileName,".out");
	}

	else if (outFileName == NULL)
	{
		outFileName = "output.dat";
	}

	inFile = fopen(inFileName, "r");

	if (inFile == NULL)
	{
		perror ("INPUTFILENAME does not exist.");
		return -1;
	}

	outFile = fopen(outFileName, "w");

	pid_t parentProcessID = getpid();
	int numOfChildren;
	fscanf(inFile, "%d", &numOfChildren);
	
	//storing Child Process IDS & creating children
	pid_t childProcessID[numOfChildren];

	int i;
	for (i = 0; i < numOfChildren; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			fprintf(outFile, "%d: ", getpid());
			int j, size;
			//printing the same integers if I don't skip line
			for (j = 0; j < (2 * i + 1); j++)
			{
				char* line = NULL;
				size_t len = 0;
				ssize_t read = getline(&line, &len, inFile);
			}

			fscanf(inFile, "%d", &size);
			int arr[size];

			int r; 
			for (r = 0; r < size; r++)
			{
				int input;
				fscanf(inFile, "%d", &input);
				arr[r] = input;
			}

			int p;
			for (p = size - 1; p >= 0; p--)
			{
				fprintf(outFile, "%d ", arr[p]);
			}
			fprintf(outFile, "\n");
			exit(0);
		}
		//using waitpid system call to wait for changed state
		else if (pid > 0)
		{
			childProcessID[i] = pid;
			int childExitStatus;
			waitpid(pid, &childExitStatus, 0);
		}
		//outlier error case
		else 
		{
			perror("Cannot fork process.\n");
		}
	}
	
	//formatting output file
	fprintf(outFile, "All children were: ");

	int v;
	for (v = 0; v < numOfChildren; v++)
	{
		fprintf(outFile, "%d ", childProcessID[v]);
	}

	fprintf(outFile, "\nParent PID: %d", parentProcessID);

	fclose(inFile);
	fclose(outFile);
	return 0;
}


