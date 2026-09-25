#include <stdio.h>
#include <stdlib.h>

// place your count_lines helper function from Part A here

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
	
	// your code here
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
