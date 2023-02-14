/**
 * Name: Yichen Li
 * SBU_ID: 112946979
 * CSE_220_R01
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// FILL IN THE BODY OF THIS FUNCTION.
// Feel free to create any other functions you like; just include them in this file.


/**
 * This is the helper method to print the hex value according to pre setted rule,
 * 0s will be added to the front of it if the 7th hex character is not 0. 
*/
void print_hex(unsigned int repr){
    printf("%08x\n", repr);
}


/**
 * Helper function to detect the one's or two's complement is negative or positive. 
*/
int is_smaller_than_zero(unsigned int repr){
    return (repr & 0x80000000);
}


/**
 * Helper function to detect if the input repr is out of the home_made range. 
*/
int is_home_made_out_of_range(unsigned int repr){
    if ((repr < 0xf4240) && (repr > 0xFFF0BDC0))
    {
        return 0;
    }
    else{
        return 1;
    }
}


/**
 * Helper function to detect if the input repr is out of the sign_magnitude range. 
*/
int is_sign_mag_out_of_range(unsigned int repr){
    if ((repr < 0x7fffffff) && (repr > 0xffffffff))
    {
        return 0;
    }
    else{
        return 1;
    }
}


/**
 * Main part of the hw. 
*/
void repr_convert(char source_repr, char target_repr, unsigned int repr) {
    switch (source_repr)
    {
        case '1': // if the one's complement is provided in target_repr
        { 
            switch (target_repr){
                case '1': // if target is one
                    print_hex(repr);
                    break;
                case '2': // if target is two 
                    if (is_smaller_than_zero(repr) == 0){
                        // if smaller than zero is false i.e. bigger than 0
                        print_hex(repr);
                    }else if (repr == 0){
                        print_hex(0);
                    }else{
                        print_hex(repr + (unsigned int)1);
                    }
                    break;
                case 'S':// if target is sign/magnitude
                case 's':
                    if((is_sign_mag_out_of_range (repr)) == 0){
                        printf("undefined \n");
                    }
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
                case 'D': //if target is home_made
                case 'd':
                    {
                        if(is_home_made_out_of_range(repr) == 0)
                        {
                            printf("undefined\n");
                            break;
                        }
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
                    printf("error \n");
                    break;
            }
        }

        break;
        case '2': //if input 2 
            {
                switch (target_repr){
                case '1':{
                    if(repr == 0x80000000){
                        printf("undefined\n");
                    }
                    else if (repr == 0) {
                        // if smaller than zero is false i.e. bigger than 0
                        print_hex(0);
                    }else if (is_smaller_than_zero(repr) == 0){
                        print_hex(repr);
                    }else{
                        //change 2 to 1 if negative 
                        print_hex(repr - (unsigned int)1);
                    }
                    break;
                    }
                case '2':{
                    print_hex(repr);
                    break;
                }
                case 'S':
                case 's':
                {
                    if(is_sign_mag_out_of_range (repr) == 0){
                        printf("undefined \n");
                    }
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
                case 'D':
                case 'd':
                {
                    if(is_home_made_out_of_range(repr) == 0)
                    {
                        printf("undefined\n");
                        break;
                    }
                        unsigned int result = 0;
                        if (repr == 0) {
                            print_hex(repr);
                        }else if (is_smaller_than_zero (repr) == 0){
                            int temp_two_D_Positive = repr;
                            for (int i = 0; i< 6 ; i++){
                                //move digits for finding the home_made expression 
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
                                //move digits for finding the home_made expression 
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
        case 'S': // if the input is sign/magnitude format number. 
        case 's':
            switch (target_repr){
                case '1':{
                    if (repr == 0x80000000){
                        print_hex(repr | 0xFFFFFFFF);
                    }else if (repr == 0x00000000){
                        print_hex(repr);
                    }else if (is_smaller_than_zero (repr) == 0) {
                        print_hex(repr);
                    }else{
                        unsigned int temp_S_1_negative = repr;
                        temp_S_1_negative = ( temp_S_1_negative & 0x7FFFFFFF );
                        repr = temp_S_1_negative;
                        print_hex(repr);
                    }
                    break;
                }
                case '2':
                {
                    if ((repr == 0x80000000) || (repr == 0x00000000)){
                        print_hex(0);
                    }else if(repr == 0x80000001){
                        //change due to the definition of two's complement. 
                        repr = 0xFFFFFFFF;
                        print_hex(repr);
                    }
                    else if(is_smaller_than_zero (repr) == 0){
                        print_hex(repr);
                    }else{
                        unsigned int temp_S_2_negative = (~repr);
                        temp_S_2_negative = (temp_S_2_negative + (unsigned int)1);
                        temp_S_2_negative = (temp_S_2_negative | 0x70000000);
                        repr = temp_S_2_negative;
                        print_hex(repr);
                    }
                    break;
                }
                case 'S':
                case 's':
                {
                    print_hex(repr);
                    break;
                }
                case 'D':
                case 'd':
                {
                    if(is_home_made_out_of_range(repr) == 0)
                        {
                            printf("undefined\n");
                            break;
                        }
                    unsigned int result = 0;
                    if (repr == 0) {
                        print_hex(repr);
                    }else if (((repr & 0xc0000000) == 0x80000000) ||((repr & 0xc0000000) == 0x40000000)){
                        printf("undefined\n");
                    }
                    else if (is_smaller_than_zero (repr) == 0){
                        // positive, change 30th and 31st digit to 00.  
                        int temp_S_D_Positive = repr;
                        for (int i = 0; i< 6 ; i++){
                            unsigned int five_digits = temp_S_D_Positive % 10;
                            five_digits = five_digits << (i*5);
                            result = result | five_digits;
                            temp_S_D_Positive = temp_S_D_Positive / 10;
                        }
                        result = (result | 0x30000000);
                        print_hex(result);
                    }else{ //negative
                        int temp_S_D_Negative = repr;
                        temp_S_D_Negative = (~ (temp_S_D_Negative))-1;
                        for (int i = 0; i < 6 ; i++){
                            unsigned int five_digits = temp_S_D_Negative % 10;
                            five_digits = five_digits << (i*5);
                            result = result | five_digits;
                            temp_S_D_Negative = temp_S_D_Negative / 10;
                        }
                        result = (result | 0xc0000000);
                        print_hex(result);
                    }
                    break;
                }
                default:
                    printf("error \n");
                    break;
            }
            break;
        case 'D': // if the input is home_made format. 
        case 'd':
        {
            if (((repr & 0xc0000000) == 0x80000000) || ((repr & 0xc0000000) == 0x40000000)){
                printf("error\n");
                break;
            }
            switch (target_repr){
                case '1':
                {
                    if (repr == 0){
                        // if zero
                        print_hex(0x00000000);
                    }
                    else if ((repr & 0xc0000000) == 0){
                        unsigned int temp_D_1_Positive = repr;
                        unsigned int result = 0;
                        for (int i = 0; i < 6 ; i++){
                            //reversed for loop to change home_made to other forms. 
                            unsigned int five_digits = (temp_D_1_Positive & 0x3E000000);
                            five_digits = five_digits >> 25;
                            result = (result*10 + five_digits);
                            temp_D_1_Positive = temp_D_1_Positive << 5;
                        }
                        repr = result;
                        print_hex(repr);
                    }
                    else if ((repr & 0xc0000000) == 0xc0000000){
                        unsigned int temp_D_1_Negative = repr;
                        unsigned int result = 0;
                        for (int i = 0; i < 6 ; i++){
                            //reversed for loop to change home_made to other forms.
                            unsigned int five_digits = (temp_D_1_Negative & 0x3E000000);
                            five_digits = five_digits >> 25;
                            result = (result*10 + five_digits);
                            temp_D_1_Negative = temp_D_1_Negative << 5;
                        }
                        result = (result | 0xc0000000);
                        repr = result;
                        print_hex(repr);
                    }
                    else{
                        //error message will shown if the input is out of the if/else statement. 
                        printf("error\n");
                    }
                    break;
                }
                case '2':
                {
                    if (repr == 0){
                        // if zero
                        print_hex(0x00000000);
                    }
                    else if ((repr & 0xc0000000) == 0){
                        unsigned int temp_D_2_Positive = repr;
                        unsigned int result = 0;
                        for (int i = 0; i < 6 ; i++){
                            //reversed for loop to change home_made to other forms.
                            unsigned int five_digits = (temp_D_2_Positive & 0x3E000000);
                            five_digits = five_digits >> 25;
                            result = (result*10 + five_digits);
                            temp_D_2_Positive = temp_D_2_Positive << 5;
                        }
                        repr = result;
                        print_hex(repr);
                    }
                    else if ((repr & 0xc0000000) == 0xc0000000){
                        unsigned int temp_D_2_Negative = repr;
                        unsigned int result = 0;
                        for (int i = 0; i < 6 ; i++){
                            //reversed for loop to change home_made to other forms.
                            unsigned int five_digits = (temp_D_2_Negative & 0x3E000000);
                            five_digits = five_digits >> 25;
                            result = (result*10 + five_digits);
                            temp_D_2_Negative = temp_D_2_Negative << 5;
                        }
                        result = (result | 0xc0000000);
                        result = result + 1; 
                        repr = result;
                        print_hex(repr);
                    }
                    break;
                }
                case 'S':
                case 's':
                {
                    if(is_sign_mag_out_of_range (repr) == 0){
                        // determine if out of sign_magnitude's range. 
                        printf("undefined \n");
                    }
                    if (repr == 0){
                        // if zero
                        print_hex(0x00000000);
                    }
                    else if((repr & 0xc0000000) == 0){
                        // if positive
                        unsigned int temp_D_S_Positive = repr;
                        unsigned int result = 0;
                        for (int i = 0; i < 6 ; i++){
                            //reversed for loop to change home_made to other forms.
                            unsigned int five_digits = (temp_D_S_Positive & 0x3E000000);
                            five_digits = five_digits >> 25;
                            result = (result*10 + five_digits);
                            temp_D_S_Positive = temp_D_S_Positive << 5;
                        }
                        repr = result;
                        print_hex(repr); 
                    }
                    else if ((repr & 0xc0000000) == 0xc0000000){
                        //if negative 
                        unsigned int temp_D_S_negative = repr;
                        unsigned int result = 0;
                        for (int i = 0; i < 6 ; i++){
                            //reversed for loop to change home_made to other forms.
                            unsigned int five_digits = (temp_D_S_negative & 0x3E000000);
                            five_digits = five_digits >> 25;
                            result = (result*10 + five_digits);
                            temp_D_S_negative = temp_D_S_negative << 5;
                        }
                        result = (result | 0x80000000); // change to show the sign bit
                        repr = result;
                        print_hex(repr); 
                    }else{
                        printf("error \n");
                    }
                    break;
                }
                case 'D':
                case 'd':
                {
                    //print itself. 
                    print_hex(repr);
                    break;
                }
                default:
                {
                    //error message will shown if the selection is out of the switch statement. 
                    printf("error \n");
                    break;
                }
            }
            break;
        }
        default:{
            //error message will shown if the selection is out of the switch statement. 
            printf("error\n");
            break;
        }
    }
}


// DO NOT CHANGE ANY CODE BELOW THIS LINE
int main(int argc, char *argv[]) {
    (void)argc; // Suppress compiler warning
    repr_convert(argv[1][0], argv[2][0], (int)strtol(argv[3], NULL, 16));
    return 0;
}
