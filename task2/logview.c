#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// place your count_lines helper function from Part A here
int count_lines(const char *filepath) {
	int line_count = 0;
	FILE* pfile = fopen(filepath, "r");

	if (pfile == NULL) {
		return -1;
	}

	//find file size
	fseek(pfile, 0L, SEEK_END);
	long int res = ftell(pfile);
	fseek(pfile, 0L, SEEK_SET);

	char data[res + 1];

	fread(data, 1, res, pfile);
	data[res] = '\0';

	char *line = strtok(data, "\n");


	while (line != NULL) {
	line = strtok(NULL, "\n");
	line_count++;
	}

	fclose(pfile);
	return line_count;

}

/*
    * Function: logview
    * ----------------------------
    *   Opens a file and prints the last n lines of the file.
    *
    *   filepath: The path to the file to logview.
    *   n: The number of lines to print.
    *
    *   returns: void
    */
void logview(const char *filepath, int n)
{
	int m = count_lines(filepath);


	FILE* pfile;
	char data[512];
	pfile = fopen(filepath, "r");
	char* lines[m];

	int i = 0;
	while (fgets(data, sizeof(data), pfile)) {
		//lines[i] = strdup(data);
		lines[i] = malloc(strlen(data) + 1);
		strcpy(lines[i], data);
		i++;

	}

	for (int j = m-n; j < m; j++) {
		printf("%s", lines[j]);
	}
	fclose(pfile);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
	{
        printf("Usage: %s <filepath> <output_lines>\noutput_lines should be integer and larger than 0.\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[2]);  // atoi() converts a string to an integer

    logview(argv[1], n);

    return 0;

}
