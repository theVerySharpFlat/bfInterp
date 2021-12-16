#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

struct CallStackNode {
    long loc;
    struct CallStackNode* pNext; 
};
struct CallStackNode* stack;
void pushLoc(long location);
void popLoc();
long lastLoc();

char* loadFileAsString(char* fileName, long* fileLength);

int main( int argc, char** argv) {
    if(argc != 2) {
        printf("please specify a brainf file!\n");
    }

    printf("loading \"%s\"\n", argv[1]);
    long len;
    char* program = loadFileAsString(argv[1], &len);
    printf("length is %ld bytes\n", len);

    //allocate data buffer
    char data[3000] = {0};
    char* dataPtr = data; 

    //set up instruction stack
    stack = NULL;

    //loop through program
    long currentInstruction = 0;
    while(currentInstruction < len) {
        /*printf("current instruction: \'%c\' at instruction %ld at register %d\n", 
        program[currentInstruction],
        currentInstruction,
        (int)(dataPtr - data)
        );*/
        switch (program[currentInstruction]) {
            case '+':
                //printf("dataptr before +: %d", *dataPtr);
                (*dataPtr)++;
                //printf("dataptr after +: %d", *dataPtr);
                break;

            case '-':
                //printf("dataptr before -: %d ", *dataPtr);
                (*dataPtr)--;
                //printf("dataptr after -: %d\n", *dataPtr);
                break;

            case '>':
                dataPtr++;
                break;
            
            case '<':
                dataPtr--;
                break;
            
            case ',':
                scanf(" %c", dataPtr);
                break;
            
            case '.':
                printf("%c", *dataPtr);
                break;
            
            case '[':
                if(!*dataPtr) {
                    while(program[currentInstruction] != ']') 
                        currentInstruction++;
                }else {
                    pushLoc(currentInstruction);
                }
                break;
            
            case ']':
            {
                if(*dataPtr){                
                    //long location = lastLoc();
                    currentInstruction = lastLoc();
                }
                break;
            }
            
        }
        
        currentInstruction++;
    }

    //free(data); //DON'T REMOVE. MEMORY LEEEEK
    return 0;
}

char* loadFileAsString(char* fileName, long* fileLength) {
    FILE* fp = fopen(fileName, "r");
    // find the length of file
    fseek(fp, 0, SEEK_END); //go to the end
        long length = ftell(fp); // get length
        *fileLength = length;
    fseek(fp, 0 , SEEK_SET); // go back to the beginning

    // create buffer
    char* buffer = (char*) malloc(length + 1);

    char c;
    int i = 0;
    while(1) {
        c = fgetc(fp);
        if(c == EOF)
            break;
        else
            buffer[i] = c;
        i++;
    }
    fclose(fp);
    buffer[length + 1] = 0x00;
    return buffer;
}

void pushLoc(long location) {
    struct CallStackNode* temp = (struct CallStackNode*) malloc(sizeof(struct CallStackNode));
    temp -> loc = location;
    temp -> pNext = stack;

    stack = temp;
}

void popLoc() {
    struct CallStackNode* temp = stack;
    stack = stack -> pNext;

    //DIE DIE DIE DIE DIE DIE DIE DIE DIE DIE DIE DIE DIE DIE DIE DIE
    free(temp);
}

long lastLoc() {
    if(stack == NULL) {
        printf("Stack pointer is null!\n");
        exit(-1);
    }
    return stack -> loc;
}