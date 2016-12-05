# Ccompiler                                                                    
                                                                               
A (very) minimal C compiler built with Lex and Yacc. This is an educational    
project done a while ago with another student, Maël Zoungrana.                 
                                                                               
Features                                                                       
--------                                                                       
                                                                               
- Integers support (only :) ).                                                 
- `if/else` structures, `while` and `for` loops.                               
- Arrays and pointers.                                                         
- (Recursive) function calls, with parameters.                                 
                                                                               
                                                                               
All lexical analysis and parsing are done using Lex and Yacc. The C source is  
compiled to a minimal assembly language which is itself interpreted.           
                                                                               
The virtual machine of the interpreter is a very basic one with:               
                                                                               
- A ROM                                                                        
- A RAM, which is nothing but a big stack (there's no heap).                   
- The usual general purpose registers (EBP, ESP, EIP, ERT)                     
                                                                               
Usage                                                                          
-----                                                                          
                                                                               
    make                                                                       
    cd build                                                                   
    ./compilo < demo.c  # compile C to assembly                                
    ./interpreteur < asm  # interpret assembly code                            
                                                                               
Sorry, all the code is in French ^^       
