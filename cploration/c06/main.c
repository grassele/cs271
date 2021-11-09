#include "parser.h" // use quotes instead of <> for custom file instead of built-in library

// test if this uploads a new version to GitHub now

int main(int argc, const char *argv[]) {
    
    // check that user entered exactly one argument
    if (argc != 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE); 
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
