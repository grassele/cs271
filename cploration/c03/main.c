#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH  200


int main(int argc, const char *argv[]) {
    
    // exercise 2: working with arguments
    if (argc != 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE); 
    }

    // exercise 3: open the input file
    FILE *fin = fopen( argv[1], "r" );
    if (fin == NULL) {
        perror("Unable to open file!");
        exit(EXIT_FAILURE);
    }
    
    // exercise 4: open the output file
    char out_file[] = " ";
    strcpy(out_file, argv[1]);
    strcat(out_file, ".echo");
    FILE *fout = fopen(out_file, "w+");

    // exercise 5: reading in the file
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_num = 0;
    while (fgets(line, sizeof(line), fin)) {
        line_num ++;
        printf("%04d", line_num);
        fprintf(fout, "%s", line);
    }

    fclose(fin);
    fclose(fout);

}