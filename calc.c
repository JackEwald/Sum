#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

unsigned short get_binary_op(char *bin) {

    unsigned short num, bit = 1;
    int i;

    for(i = strlen(bin) - 1; i >= 0; i--)
    {
        if(bin[i] == '1')
        {
            num += bit;
        }
        bit *= 2;
    }
    return num;
}

void convert_to_binary(short acc, char *bin) {

    unsigned short temp = acc;
    int i;

    printf("%d", temp);

    for(i = strlen(bin) - 1; i >= 0; i--)
    {
        if(i % 5 == 4)
        {
            bin[i] = ' ';
            continue;
        }
        if(temp % 2 == 0)
        {
            bin[i] = '0';
        }
        if(temp % 2 == 1)
        {
            bin[i] = '1';
        }
        temp /= 2;
        printf("%hd", temp);
    }
}

short get_operand(char mode) {

    short input;
    bin_str b;

    switch(mode) {
        case 'B':
        {
            printf("Enter binary value: ");
            scanf("%s", b);
            printf("%s\n", b);
            input = get_binary_op(b);
            break;
        }
        case 'D':
        {
            printf("Enter decimal value: ");
            scanf("%hd", &input);
            printf("%hd\n", input);
            break;
        }
        case 'O':
        {
            printf("Enter octal value: ");
            scanf("%ho", &input);
            printf("%ho\n", input);
            break;
        }
        case 'H':
        {
            printf("Enter hex value: ");
            scanf("%hX", &input);
            printf("%hX\n", input);
            break;
        }
    }
    return input;
}

void add(short *acc, char mode) {

    short int acc_1, acc_2;
    acc_1 = *acc;
    acc_2 = get_operand(mode);
    *acc = acc_1 + acc_2;

    if(acc_1 > 0 && acc_2 > 0 && *acc < 0)
    {
        printf("Positive Overflow\n\n");
    }
    if(acc_1 < 0 && acc_2 < 0 && *acc > 0)
    {
        printf("Negative Overflow\n\n");
    }
}

void subtract(short *acc, char mode) {

    short int acc_1, acc_2;
    acc_1 = *acc;
    acc_2 = get_operand(mode);
    *acc = acc_1 - acc_2;

    if(acc_1 > 0 && (-acc_2) > 0 && *acc < 0)
    {
        printf("Positive Overflow\n\n");
    }
    if(acc_1 < 0 && (-acc_2 < 0) && *acc > 0)
    {
        printf("Negative Overflow\n\n");
    }
}

void print_acc(short acc, char mode) {

    char input_mode[4];
    bin_str binary = "0000 0000 0000 0000"; 
    convert_to_binary(acc, binary);

    switch(mode) {
        case 'B':
        {
            strcpy(input_mode, "Bin");
            break;
        }
        case 'D':
        {
            strcpy(input_mode, "Dec");
            break;
        }
        case 'O':
        {
            strcpy(input_mode, "Oct");
            break;
        }
        case 'H':
        {
            strcpy(input_mode, "Hex");
            break;
        }
    }

    printf("****************************************\n");
    printf("* Accumulator:         Input Mode: %s *\n", input_mode);
    printf("*   Binary  :  %s     *\n", binary);
    printf("*   Hex     :  %04hX                    *\n", acc);
    printf("*   Octal   :  %06ho                  *\n", acc);
    printf("*   Decimal :  %-10d              *\n", acc);
    printf("****************************************\n\n");
}

char print_menu(void) {

    char option[10];
    char valid_options[] = "BOHDCSQ&|^~<>+-N";
    char input;

    int loop_var = 1;

    do {
        printf("Please select one of the following options:\n\n");
        printf("B  Binary Mode             &  AND with Accumulator           +  Add to Accumulator\n");
        printf("O  Octal Mode              |  OR  with Accumulator           -  Subtract from Accumulator\n");
        printf("H  Hexadecimal Mode        ^  XOR with Accumulator           N  Negate Accumulator\n");
        printf("D  Decimal Mode            ~  Complement Accumulator\n\n");
        printf("C  Clear Accumulator       <  Shift Accumulator Left\n");
        printf("S  Set Accumulator         >  Shift Accumulator Right\n\n");
        printf("Q  Quit\n\n");
        printf("Option: ");
        scanf("%s", option);
        printf("%s\n", option); 
        input = toupper(option[0]);
        if(strlen(option) > 1 || (!strchr(valid_options, input))) {
            printf("\n");
            printf("Invalid option: %s\n\n", option);
        }
        else {
            loop_var = 0;
        }
    }
    while(loop_var);
    return input;
}

int main(void)
{
    short acc = 0, acc_2 = 0; //Initial value of accumulator set to '0'
    int num_shift = 0;
    int loop = 1; //Used for main menu loop
    char mode = 'D'; //Initial mode of accumulator set to 'Decimal'

    print_acc(acc, mode);

   while(loop) {
        char option = print_menu();

        switch(option) {
            case 'B':
            {
                printf("Mode is Binary\n\n");
                mode = 'B';
                print_acc(acc, mode);
                break;
            }
            case '&':
            {
                acc_2 = get_operand(mode);
                acc = acc & acc_2;
                print_acc(acc, mode);
                break;
            }
            case '+':
            {
                add(&acc, mode);
                print_acc(acc, mode);
                break;
            }
            case 'O':
            {
                printf("Mode is Octal\n\n");
                mode = 'O';
                print_acc(acc, mode);
                break;
            }
            case '|':
            {
                acc_2 = get_operand(mode);
                acc = acc | acc_2;
                print_acc(acc, mode);
                break;
            }
            case '-':
            {
                subtract(&acc, mode);
                print_acc(acc, mode);
                break;
            }
            case 'H':
            {
                printf("Mode is Hexadecimal\n\n");
                mode = 'H';
                print_acc(acc, mode);
                break;
            }
            case '^':
            {
                acc_2 = get_operand(mode);
                acc = acc ^ acc_2;
                print_acc(acc, mode);
                break;
            }
            case 'N':
            {
                acc = -acc;
                print_acc(acc, mode);
                break;
            }
            case 'D':
            {
                printf("Mode is Decimal\n\n");
                mode = 'D';
                print_acc(acc, mode);
                break;
            }
            case '~':
            {
                acc = ~acc;
                print_acc(acc, mode);
                break;
            }
            case 'C':
            {
                printf("\n");
                acc = 0;
                print_acc(acc, mode);
                break;
            }
            case '<':
            {
                printf("Enter number of positions to left shift accumulator: ");
                scanf("%d", &num_shift);
                printf("%d\n\n", num_shift);
                acc = acc << num_shift;
                print_acc(acc, mode);
                break;
            }
            case 'S':
            {
                acc = get_operand(mode);
                print_acc(acc, mode);
                break;
            }
            case '>':
            {
                printf("Enter number of positions to right shift accumulator: ");
                scanf("%d", &num_shift);
                printf("%d\n\n", num_shift);
                acc = acc >> num_shift;
                print_acc(acc, mode);
                break;
            }
            case 'Q':
            {
                loop = 0;
                break;
            }
        }
    }
}