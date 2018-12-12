#include "fillit.h"

static int	check_tetro(char *tetro_file, t_coordinates *tetro)
{
	int sharps = 0, connections = 0;
	for (int i = 0; i < 20; i++)
	{
		if (tetro_file[i] == '#' && i % 5 != 4 && ++sharps < 5)
		{
			if (tetro_file[i + 1] == '#')
				connections++;
			if (i > 0 && tetro_file[i - 1] == '#')
				connections++;
			if (i < 14 && tetro_file[i + 5] == '#')
				connections++;
			if (i >= 5 && tetro_file[i - 5] == '#')
				connections++;
			tetro->row[sharps - 1] = i / 5;
			tetro->column[sharps - 1] = i % 5;
		}
		else if ((i % 5 == 4 && tetro_file[i] == '.') || (i % 5 != 4 && tetro_file[i] == '\n'))
			return 0;
	}
	return sharps == 4 && tetro_file[20] == '\n' && (connections == 6 || connections == 8);
}

void		parse_and_validate(char *file_content, int size, t_coordinates *tetros)
{
	for (int i = 0; i < size; i += 21)
	{
		if (check_tetro(file_content + i, &tetros[i / 21]) == 0)
		{
			write(2, "error\n", 6);
			exit(1);
		}
	}
}
