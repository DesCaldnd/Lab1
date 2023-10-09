//
// Created by ivanl on 09.10.2023.
//
#include "../functions.h"
#include <string.h>

enum flag_type
{D_F, I_F, S_F, A_F, UNDEFINED};

struct flag_id
{
	bool is_n;
	enum flag_type type;
};

void docs();
struct flag_id get_flag_id(char str[]);
void get_out_path(char in_path[], char out_path[]);
void execute_d_flag(FILE* in, FILE* out);
void execute_i_flag(FILE* in, FILE* out);
void execute_s_flag(FILE* in, FILE* out);
void execute_a_flag(FILE* in, FILE* out);

int main(int argc, char* argv[])
{
	if (argc < 3 || argc > 4)
	{
		incorrect_argc(&docs);
		return 0;
	}

	struct flag_id id = get_flag_id(argv[1]);
	char out_path[256];

	if (!id.is_n && argc != 4)
	{
		incorrect_argc(&docs);
		return 0;
	}
	if (id.is_n)
		get_out_path(argv[2], out_path);

	FILE *in = fopen(argv[2], "r"), *out = fopen(id.is_n ? out_path : argv[3], "w");

	if (in == NULL || out == NULL)
	{
		printf("One of files can`t be opened\n");
		return 0;
	}

	switch (id.type)
	{
		case D_F:
		{
			execute_d_flag(in, out);
			break;
		}
		case S_F:
		{
			execute_s_flag(in, out);
			break;
		}
		case I_F:
		{
			execute_i_flag(in, out);
			break;
		}
		case A_F:
		{
			execute_a_flag(in, out);
			break;
		}
		default:
		{
			printf("Incorrect flag\n");
			break;
		}
	}

	fclose(in);
	fclose(out);
}

void get_out_path(char in_path[], char out_path[])
{
	int len = strnlen_s(in_path, 256), index;

	for (int i = len - 1; i >= 0 ; --i)
	{
		if (in_path[i] == '/')
		{
			index = i;
			break;
		}
	}

	for (int i = 0; i <= index; ++i)
	{
		out_path[i] = in_path[i];
	}

	out_path[index + 1] = 'o';
	out_path[index + 2] = 'u';
	out_path[index + 3] = 't';
	out_path[index + 4] = '_';

	for (int i = index + 5; i < len + 4; ++i)
	{
		out_path[i] = in_path[i - 4];
	}
}

void execute_d_flag(FILE* in, FILE* out)
{
	char buf;

	while(!feof(in))
	{
		fscanf(in, "%c", &buf);
		if (!(buf >= '0' && buf <= '9'))
			fprintf(out, "%c", buf);
	}
}

void execute_i_flag(FILE* in, FILE* out)
{
	char buf;
	unsigned int alpha_counter = 0, sym_counter = 0;

	while(!feof(in))
	{
		fscanf(in, "%c", &buf);
		++sym_counter;
		if ((buf >= 'a' && buf <= 'z') || (buf >= 'A' && buf <= 'Z'))
			++alpha_counter;
		else if(buf == '\n')
		{
			fprintf(out, "%d\n", alpha_counter);
			alpha_counter = sym_counter = 0;
		}
	}

	if (sym_counter != 0)
	{
		fprintf(out, "%d\n", alpha_counter);
	}
}

void execute_s_flag(FILE* in, FILE* out)
{
	char buf;
	unsigned int alpha_counter = 0, sym_counter = 0;

	while(!feof(in))
	{
		fscanf(in, "%c", &buf);
		++sym_counter;
		if(buf == '\n')
		{
			fprintf(out, "%d\n", alpha_counter);
			alpha_counter = sym_counter = 0;
		} else if (!((buf >= 'a' && buf <= 'z') || (buf >= '0' && buf <= '9') || (buf >= 'A' && buf <= 'Z') || buf == ' '))
			++alpha_counter;
	}

	if (sym_counter != 0)
	{
		fprintf(out, "%d\n", alpha_counter);
	}
}

void execute_a_flag(FILE* in, FILE* out)
{
	char buf;
	char str[3];

	while(!feof(in))
	{
		fscanf(in, "%c", &buf);
		if (buf >= '0' && buf <= '9')
			fprintf(out, "%c", buf);
		else
		{
			integer_to_n_radix(buf, 16, str);
			fprintf(out, "%s", str);
		}
	}
}

struct flag_id get_flag_id(char str[])
{
	struct flag_id result;
	int index = 1;

	if (str[index] == 'n')
	{
		++index;
		result.is_n = true;
	} else
		result.is_n = false;

	if (!(str[0] == '-' && str[index + 1] == '\0'))
	{
		result.type = UNDEFINED;
		return result;
	}

	switch (str[index])
	{
		case 'd':{
			result.type = D_F;
			break;
		}
		case 'i':{
			result.type = I_F;
			break;
		}
		case 's':{
			result.type = S_F;
			break;
		}
		case 'a':{
			result.type = A_F;
			break;
		}
		default:{
			result.type = UNDEFINED;
			break;
		}
	}
	return result;
}

void docs()
{
	printf("You must enter one flag with one or two filepaths. If flag starts with 'n', output file will be generated "
		   "automatically, or you can enter output filepath by yourself.\nFlags:\n"
		   "\t-d - exclude arabic digits\n"
		   "\t-i - for each string write how much there are latin alphas\n"
		   "\t-s - for each string write how much there are symbols that are not latin alphas, arabic digits or spaces\n"
		   "\t-a - write all symbols that are not arabic digits as hexadecimal ASCII code\n");
}