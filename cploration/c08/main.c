#include "parser.h"
#include "error.h"

int main(int argc, const char *argv[]) {
    
    // check that user entered exactly one argument
    if (argc != 2) {  // incorrect number of arguments
      exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    // open the argument passed as a file and save it as a file pointer
    FILE *file = fopen( argv[1], "r" );
    
    // replaced by Exercise 6
    // // check if your file pointer is NULL, and if so, print error and exit w a failure
    // if (file == NULL) {
    //     perror("Unable to open file!");
    //     exit(EXIT_FAILURE);
    //  }

    if(file == NULL) {   // should this have "fin" or "file"? changed to "file" from "fin"
      exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }
    
    // call function parse and pass it the file pointer
    parse(file);

    // close file pointer
    fclose(file);

}