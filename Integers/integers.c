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
                    if (is_smaller_than_zero(repr) == 0){
                        // if smaller than zero is false i.e. bigger than 0
                        print_hex(repr);
                    }else if (repr == 0){
                        print_hex(0);
                    }else{
                        print_hex(repr + (unsigned int)1);
                    }
                    break;
                case 'S':
                    if (is_smaller_than_zero(repr) == 0){
                        print_hex(repr);
                    }else if (repr == 0){
                        print_hex(0);
                    }else{
                        unsigned int temp;
                        temp = ~ repr;
                        temp = temp + 0x80000000;
                        print_hex(temp);
                    }
                    break;
                case 'D':
                    {
                        unsigned int result = 0;
                        if (repr == 0) {
                            print_hex(repr);
                        }else if (is_smaller_than_zero (repr) == 0){
                            int temp_one_D_Positive = repr;
                            for (int i = 0; i< 6 ; i++){
                                unsigned int five_digits = temp_one_D_Positive % 10;
                                five_digits = five_digits << (i*5);
                                result = result | five_digits;
                                temp_one_D_Positive = temp_one_D_Positive / 10;
                            }
                            print_hex(result);
                        }else{
                            int temp_one_D_Negative = repr;
                            temp_one_D_Negative = ~ (temp_one_D_Negative);
                            for (int i = 0; i < 6 ; i++){
                                unsigned int five_digits = temp_one_D_Negative % 10;
                                five_digits = five_digits << (i*5);
                                result = result | five_digits;
                                temp_one_D_Negative = temp_one_D_Negative / 10;
                            }
                            result = (result | 0xc0000000);
                            print_hex(result);
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        break;
        case '2':
            {switch (target_repr){
                case '1':{
                    if(repr == 0x80000000){
                        printf("undefined");
                    }
                    else if (repr == 0) {
                        // if smaller than zero is false i.e. bigger than 0
                        print_hex(0);
                    }else if (is_smaller_than_zero(repr) == 0){
                        print_hex(repr);
                    }else{
                        print_hex(repr - (unsigned int)1);
                    }
                    break;
                    }
                case '2':{
                    print_hex(repr);
                    break;
                }
                case 'S':{
                    if (repr == 0){
                        print_hex(0);
                    }else if (is_smaller_than_zero(repr) == 0){
                        print_hex(repr);
                    }else{
                        unsigned int temp;
                        temp = (~ repr) - 1;
                        temp = temp + 0x80000000;
                        print_hex(temp);
                    }
                    break;
                }
                case 'D':{
                        unsigned int result = 0;
                        if (repr == 0) {
                            print_hex(repr);
                        }else if (is_smaller_than_zero (repr) == 0){
                            int temp_two_D_Positive = repr;
                            for (int i = 0; i< 6 ; i++){
                                unsigned int five_digits = temp_two_D_Positive % 10;
                                five_digits = five_digits << (i*5);
                                result = result | five_digits;
                                temp_two_D_Positive = temp_two_D_Positive / 10;
                            }
                            print_hex(result);
                        }else{
                            int temp_two_D_Negative = repr;
                            temp_two_D_Negative = (~ (temp_two_D_Negative))-1;
                            for (int i = 0; i < 6 ; i++){
                                unsigned int five_digits = temp_two_D_Negative % 10;
                                five_digits = five_digits << (i*5);
                                result = result | five_digits;
                                temp_two_D_Negative = temp_two_D_Negative / 10;
                            }
                            result = (result | 0xc0000000);
                            print_hex(result);
                        }
                    }
            }
                
                
            }
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
