//Author: Amal Presingu
//Date:   9/18/2022

#include "main.h"

int main(int argc, char **argv)
{
	//creating files and filename variables for read/write
	FILE *inFile;
	FILE *outFile;

	char* inFileName = NULL;
	char* outFileName;

	//getopt(3) for command line args
	int opt; 
	while ((opt = getopt(argc, argv, "hi:o:")) != -1)
	{
		switch(opt)
		{
			//help message
			case 'h':
				printf("\n-------Command Line Help-------\n\n");
        		        printf("./chain -h                    Helps with command line arguments.\n");
	           	        printf("./chain -i [INPUTFILENAME]    Takes in a file name and reverses the intergers into output file.\n");
           			printf("./chain -o [OUTPUTFILENAME]   If user specifies filename, the output will be printed to that file.\n\n");
				exit(0);
				break;
			// -i [inputfilename] 
			case 'i':
				inFileName = optarg;
				break;
			// -o [outputfilename]
			case 'o':
				outFileName = optarg;
				break;
		}
	}

	//if no filenames are specified for input and output, defaults are .dat files
	if (outFileName == NULL && inFileName == NULL)
	{
		inFileName = "input.dat";
		outFileName = "output.dat";
	}
	
	//if no output filename is entered, output.dat by default
	else if (outFileName == NULL)
	{
		outFileName = "output.dat";
	}
	
	inFile = fopen(inFileName, "r");

	//using perror to print error msg for no inputfilename
	if (inFile == NULL)
	{
		perror ("INPUTFILENAME does not exist.\n");
		return -1;
	}

	//opening outputfile to write
	outFile = fopen(outFileName, "w");

	//getpid() system call
	pid_t parentProcessID = getpid();
	int numOfChildren;
	fscanf(inFile, "%d", &numOfChildren);
	
	//storing Child Process IDS & creating children
	pid_t childProcessID[numOfChildren];

	int i;
	for (i = 0; i < numOfChildren; i++)
	{
		//passing pid_t and pid to fork(2)
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
				//using getline instead of fgets here (was having issues with c99 but seems to with with c11)
				ssize_t read = getline(&line, &len, inFile);
			}

			fscanf(inFile, "%d", &size);
			int arr[size];

			//parsing inputfile and printing to outputfile
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


