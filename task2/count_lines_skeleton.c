#include <stdio.h>
#include <stdlib.h>

/*
    * Helper Function: count_lines
    * ----------------------------
    *   Opens a file and counts the number of lines with text (including empty lines).
    *
    *   filepath: The path to the file.
    *
    *   returns: int  (number of lines), or -1 on error
    */
int count_lines(const char *filepath)
{
    // your code here
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

