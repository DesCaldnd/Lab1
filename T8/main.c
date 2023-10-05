//
// Created by Des Caldnd on 10/1/2023.
//
#include "../functions.h"
#include <stdlib.h>
#include <ctype.h>

void docs();
char process_number(char sym, FILE* in, FILE* out);
char skip(FILE* in);
int char_to_int(char digit);
bool is_char_correct(char digit, int radix);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        incorrect_argc(&docs);
        return 0;
    }

    FILE *input;
    FILE *output;

    fopen_s(&input, argv[1], "r");

    if(input == NULL)
    {
        printf("Input file path is not correct");
        return 0;
    }

    fopen_s(&output, argv[2], "w");

    if (output == NULL)
    {
        printf("Output filepath is not correct or file is opened");
        fclose(input);
        return 0;
    }

    char sym;
    fscanf_s(input, "%c", &sym);

    while (!feof(input))
    {
        if(sym != ' ' && sym != '\n' && sym != '\t')
        {
            sym = process_number(sym, input, output);
        } else
            fscanf_s(input, "%c", &sym);
    }

    fclose(input);
    fclose(output);
}

char process_number(char sym, FILE* in, FILE* out)
{
    char string[64];

    int counter = 0;
    while (sym != ' ' && sym != '\n' && sym != '\t' && counter < 64 && !feof(in))
    {
        string[counter] = sym;
        ++counter;
        fscanf_s(in, "%c", &sym);
    }

    if (sym != ' ' && sym != '\n' && sym != '\t' && !feof(in))
    {
        return skip(in);
    }

    string[counter] = '\0';
    int max_digit = 0;

    for (int i = 0; i < counter; ++i)
    {
        if (string[i] != '-' && string[i] != '+')
        {
            int digit = char_to_int(string[i]);
            if (digit == -1)
                return sym;
            else if (digit > max_digit)
                max_digit = digit;
        }
    }

    int radix = max_digit + 1;
    enum error_type error_return;

    ll number = integer_from_n_radix(string, radix, &error_return, &char_to_int, &is_char_correct);
    if (error_return == CORRECT)
    {
        int offset = 0;
        bool need_move = false;
        for (int i = 0; i < counter; ++i)
        {
            if (string[i] == 0 && !need_move)
                offset++;
            else if (string[i] != '-' && string[i] != '+')
            {
                need_move = true;
                string[i - offset] = string[i];
            }

    	}
        fprintf(out, "%s %d %lld\n", string, radix, number);
    }
    return sym;
}

char skip(FILE* in)
{
    char c = ' ';
    if (!feof(in))
        fscanf_s(in, "%c", &c);
    while (c != ' ' && c != '\n' && c != '\t' && !feof(in))
    {
        fscanf_s(in, "%c", &c);
    }
    return c;
}

int char_to_int(char digit)
{
    if (digit >= '0' && digit <= '9')
    {
        return digit - '0';
    } else if (digit >= 'A' && digit <= 'Z')
    {
        return digit - 'A' + 10;
    } else if (digit >= 'a' && digit <= 'z')
    {
        return digit - 'a' + 10;
    } else
    {
        return -1;
    }
}

bool is_char_correct(char digit, int radix)
{
    int tmp = char_to_int(digit);
    return tmp >= 0 && tmp < radix;
}

void docs()
{
    printf("You must enter two arguments: filepath to read and filepath to write");
}