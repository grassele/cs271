#include "parser.h"
#include "error.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[]) {

    // check that user entered exactly one argument
    if (argc != 2) {
      exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    // open the argument passed as a file and save it as a file pointer
    FILE *file = fopen( argv[1], "r" );

    if(file == NULL) {
      exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }
    
    instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));

    int num_instructions = parse(file, instructions);

    // close file pointer
    fclose(file);

    free(instructions);

}