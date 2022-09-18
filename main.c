#include "main.h"

int main(int argc, char **argv)
{
	FILE *inFile;
	FILE *outFile;

	char* inFileName = NULL;
	char* outFileName = NULL;

	int opt; 
	while ((opt = getopt(argc, argv, "hi:o:")) != 1)
	{
		switch(opt)
		{
			case 'h':
				printf("ADD HELP msg tomorrow");
				break;
			case 'i':
				inFileName = optarg;
				break;
			case 'o':
				outFileName = optarg;
				break;
		}
	}

	if (outFileName == NULL && inFileName == NULL)
	{
		inFileName = "input.dat";
		outFileName = "output.dat";
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

	//pid_t parentProcessID = getpid();
	//int numOfChildren;
	

