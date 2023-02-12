#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// FILL IN THE BODY OF THIS FUNCTION.
// Feel free to create any other functions you like; just include them in this file.
void print_hex(unsigned int repr){
    printf("%X hexadecimal with upper case letters.\n", repr);
}

int is_smaller_than_zero(unsigned int repr){
    return (repr & 0x80000000);
}


void repr_convert(char source_repr, char target_repr, unsigned int repr) {
    //print_hex(repr);
    switch (source_repr){
        case '1':
        { //print_hex(repr);
            switch (target_repr){
                case '1':
                    print_hex(repr);
                    break;
                case '2':
                    // printf("Hello, World!");
                    if (is_smaller_than_zero(repr) == 0){
                        // if smaller than zero is false i.e. bigger than 0
                        print_hex(repr);
                    }else if (repr == 0){
                        print_hex(0);
                    }else{printf("ffff\n");
                        print_hex(repr + (unsigned int)1);
                    }
                    break;
                case 'S':
                    if (is_smaller_than_zero(repr) == 0){
                        print_hex(repr);
                    }else if (repr == 0){
                        print_hex(0);
                    }else{
                        printf("ffff\n");
                        unsigned int temp;
                        temp = ~ repr;
                        temp = temp + 0x80000000;
                        print_hex(temp);
                    }
                    break;
                case 'D':
                    break;
                default:
                    break;
            }
        }

        break;
        case '2':
            break;
        case 'S':
            break;
        case 'D':
            break;
        default:
            break;
    }
}


// DO NOT CHANGE ANY CODE BELOW THIS LINE
int main(int argc, char *argv[]) {
    (void)argc; // Suppress compiler warning
    repr_convert(argv[1][0], argv[2][0], (int)strtol(argv[3], NULL, 16));
    return 0;
}
