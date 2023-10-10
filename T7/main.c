//
// Created by Des Caldnd on 10/10/2023.
//
#include "../functions.h"
#include <ctype.h>

enum flag_type
{R_F, A_F, UNDEFINED};

enum state_types
{READ_FIRST, READ_SECOND, FIRST_ENDED, SECOND_ENDED, FINISH};

enum flag_type get_flag_type(char* str);
void process_r_flag(char* in_1_path, char* in_2_path, char* out_path);
void process_a_flag(char* in_path, char* out_path);
void docs();

int main(int argc, char* argv[])
{
    if (argc != 4 && argc != 5)
    {
        incorrect_argc(&docs);
        return 0;
    }
    switch (get_flag_type(argv[1]))
    {
        case R_F:
        {
            if (argc != 5)
            {
                incorrect_argc(&docs);
                return 0;
            }
            process_r_flag(argv[2], argv[3], argv[4]);
            break;
        }
        case A_F:
        {
            if (argc != 4)
            {
                incorrect_argc(&docs);
                return 0;
            }
            process_a_flag(argv[2], argv[3]);
            break;
        }
        default:
        {
            printf("'%s' is not a flag\n\n", argv[1]);
            break;
        }
    }
}

void process_r_flag(char* in_1_path, char* in_2_path, char* out_path)
{
    FILE *in_1 = fopen(in_1_path, "r"), *in_2 = fopen(in_2_path, "r"), *out = fopen(out_path, "w");
    if (in_1 == NULL || in_2 == NULL || out == NULL)
    {
        printf("One of files cannot be opened\n\n");
        return;
    }

    char sym, next_1, next_2;
    enum state_types state = READ_FIRST;
    bool lex_started = false, need_change = false;

    sym = fgetc(in_1);
    next_1 = fgetc(in_1);
    next_2 = fgetc(in_2);

    while (state != FINISH)
    {
        if (!isspace(sym))
        {
            fwrite(&sym, sizeof(char), 1, out);
            lex_started = true;
        } else if(lex_started)
        {
            fprintf(out, " ");
            lex_started = false;
            need_change = true;
        }
        if (state == READ_FIRST && feof(in_1))
            state = FIRST_ENDED;
        else if(state == READ_SECOND && feof(in_2))
            state = SECOND_ENDED;
        if (isspace(sym) && state == READ_FIRST && need_change)
        {
            state = READ_SECOND;
            need_change = false;
        }
        else if(isspace(sym) && state == READ_SECOND && need_change)
        {
            state = READ_FIRST;
            need_change = false;
        }
        else if ((state == FIRST_ENDED && feof(in_2)) || (state == SECOND_ENDED && feof(in_1)))
            state = FINISH;


        if (state == READ_FIRST || state == SECOND_ENDED)
        {
            sym = next_1;
            next_1 = fgetc(in_1);
        } else if (state != FINISH)
        {
            sym = next_2;
            next_2 = fgetc(in_2);
        }
    }
    fclose(in_1);
    fclose(in_2);
    fclose(out);
}

void process_a_flag(char* in_path, char* out_path)
{
    FILE *in = fopen(in_path, "r"), *out = fopen(out_path, "w");
    if (in == NULL || out == NULL)
    {
        printf("One of files cannot be opened\n\n");
        return;
    }

    char sym;
    bool lex_started = false;
    ll lex_num = 1;
    sym = fgetc(in);
    while (!feof(in))
    {
        if (!isspace(sym))
        {
            lex_started = true;
            if (lex_num % 10 == 0)
            {
                char str[5];
                integer_to_n_radix(tolower(sym), 4, str);
                fprintf(out, "%s", str);
            } else if (lex_num % 2 == 0)
            {
                sym = tolower(sym);
                fwrite(&sym, sizeof(char), 1, out);
            } else if (lex_num % 5 == 0)
            {
                char str[4];
                integer_to_n_radix(sym, 8, str);
                fprintf(out, "%s", str);
            } else
            {
                fwrite(&sym, sizeof(char), 1, out);
            }
        } else if (lex_started)
        {
            lex_started = false;
            ++lex_num;
            fprintf(out, " ");
        }
        sym = fgetc(in);
    }
    fclose(in);
    fclose(out);
}

enum flag_type get_flag_type(char* str)
{
    if (!(str[0] == '-' && str[2] == '\0'))
    {
        return UNDEFINED;
    }
    switch (str[1])
    {
        case 'r':
        {
            return R_F;
        }
        case 'a':
        {
            return  A_F;
        }
        default:
        {
            return UNDEFINED;
        }
    }
}

void docs()
{
    printf("You must enter one of following flags:\n"
           "\t-r - (in_filepath, in_filepath, out_fdilepath) alternate write from two files\n"
           "\t-a - (in_filepath, out_filepath) process lexems");
}