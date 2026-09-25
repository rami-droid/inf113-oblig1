#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    * Helper Function: count_lines
    * ----------------------------
    *   Opens a file and counts the number of lines with text (including empty lines).
    *
    *   filepath: The path to the file.
    *
    *   returns: int  (number of lines), or -1 on error
    */
int count_lines(char *filepath) {
	int line_count = 0;
	FILE* pfile = fopen(filepath, "r");

	//find file size
	fseek(pfile, 0L, SEEK_END);
	long int res = ftell(pfile);
	fseek(pfile, 0L, SEEK_SET);

	char data[res];

	fread(data, 1, res, pfile);

	char *line = strtok(data, "\n");


	while (line != NULL) {
	line = strtok(NULL, "\n");
	line_count++;
	}

	fclose(pfile);
	return line_count;

}
int main(int argc, char *argv[])
{
    if (argc != 2)
	{
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    int total_lines = count_lines(argv[1]);
    
    if (total_lines == -1)
	{
        // count_lines already printed an error message
        return 1;
    }

    printf("The file '%s' contains %d lines of text.\n", argv[1], total_lines);
    
    return 0;
}

