/*
Now we need a module to define our code representation. The author has been using "chunk"
to refer to sequences of bytecode, so let's make that the offical name for that module

In our bytecode format, each instruction has a one-byte operation code
(universally shortened to opcode). That number controls what kind of instruction
we're dealing with--add,subtract, look up variable, etc. We define those here:
*/

// Include the header file
#include "common.h"

/*
For now, we start with a single instruction, OP_RETURN. When we have a full-featured VM,
this instruction will mean "return from the current function". I admit this isn't 
exactly useful yet, but we have to start somewhere, and this is a particulary simple
instruction.
*/
typedef enum {
    OP_RETURN,      
} OpCode;

/*
A DYANMIC ARRAY OF INSTRUCTIONS:

Bytecode is a series of instructions. Eventually, we'll store some other data
along with the instructions, so let's go ahead and create a sturct to hold it all.

At the moment, this is simply a wrapper around an array of bytes. Since we don't know
how big the array needs to be before we start compiling a chunk, it must be dynamic.
Dynamic arrays are one of my favourite data structures. Dynamic arrays provide:

1. Cache-friendly, dense storage
2. Constant-time indexed element lookup
3. Constant-time appending to the end of the array


We keep two numbers: the number of elements in the array we have allocated (“capacity”)
and how many of those allocated entries are actually in use (“count”).

When we add an element, if the count is less than the capacity, then there is already available
space in the array. We store the new element right in there and bump the count.

If we have no spare capacity, then the process is a little more involved.

1. Allocate a new array with more capacity.
2. Copy the existing elements from the old array to the new one.
3. Store the new capacity.
4. Delete the old array.
5. Update code to point to the new array.
6. Store the element in the new array now that there is room.
7. Update the count.
*/
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
} Chunk;

// We have our struct ready, so implement the functions to work with it.
//C dosen't have constructors, so we clare a function to initalise a new chunk
void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);

// The dynamic array starts off completely empty. We don't even allocate a raw array yet.
// To append a byte to the end of the chunk, we use a new function.
void writeChunk(Chunk* chunk, uint8_t byte);

