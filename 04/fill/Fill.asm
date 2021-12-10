// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Elizabeth Grassel

(INFINITE_LOOP)

    // save start location of screen memory
    @SCREEN 
    D=A
    @R0
    M=D

    // temporarily save start location of keyboard memory in D
    @KBD
    D=M

    // completely blacken screen
    @BLACKEN
    D; JEQ

    // completely whiten screen
    @WHITEN
    D; JGT

    (BLACKEN)
        @R1
        M=-1
        @DRAW
        0;JMP

    (WHITEN)
        @R1
        M=0
        @DRAW
        0;JMP
        
    (DRAW)
        @R1
        D=M
        @R0
        A=M
        M=D

    @R0
    M=M+1
    D=M

    @KBD
    D=A-D
    @DRAW
    D; JGT
    
    @INFINITE_LOOP
    0;JMP