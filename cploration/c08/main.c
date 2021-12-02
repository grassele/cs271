#include "parser.h"

int main(int argc, const char *argv[]) {
    
    // check that user entered exactly one argument
    if (argc != 2) {  // incorrect number of arguments
      exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    // open the argument passed as a file and save it as a file pointer
    FILE *file = fopen( argv[1], "r" );
    
    // check if your file pointer is NULL, and if so, print error and exit w a failure
    if (file == NULL) {
        perror("Unable to open file!");
        exit(EXIT_FAILURE);
     }
    
    // call function parse and pass it the file pointer
    parse(file);

    // close file pointer
    fclose(file);

}