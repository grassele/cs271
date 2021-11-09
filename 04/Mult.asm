// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Add R0 to R2 R1 times

// test 4*5
    @4
    D=A
    @R0
    M=D
    @5
    D=A
    @R1
    M=D

// initialize R2 to make sure we start from 0
    @0
    D=A
    @R2
    M=D

// add R0 to R2
(ADD_LOOP)
    @R0
    D=M
    @R2
    M=M+D
    @EXIT_CONDITION_LOOP
    0;JMP

// decrement R1 until it equals 0 (program has added R0 to R2 R1 times), then end the program
(EXIT_CONDITION_LOOP)
    @R1
    M=M-1
    @ADD_LOOP
    M;JGT
    @END
    M;JEQ

(END)
    @END
    0;JMP


