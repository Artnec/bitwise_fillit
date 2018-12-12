#include "fillit.h"

static void		initiate_tetros(t_coordinates *tetros, int tetros_count,
								t_tetreminos *t, int map_side_size)
{
	for (int i = 0; i < tetros_count; i++)
	{
		int minr = tetros[i].row[0];
		int minc = tetros[i].column[0];
		for (int j = 1; j < 4; j++)
		{
			if (tetros[i].row[j] < minr)
				minr = tetros[i].row[j];
			if (tetros[i].column[j] < minc)
				minc = tetros[i].column[j];
		}
		for (int j = 0; j < 4; j++)
		{
			tetros[i].row[j] -= minr;
			tetros[i].column[j] -= minc;
			if (tetros[i].column[j] > t[i].max_map_l)
				t[i].max_map_l = tetros[i].column[j];
		}
		t[i].max_map_h = map_side_size - tetros[i].row[3];
		t[i].max_map_l = map_side_size - t[i].max_map_l;
		t[i].tetro |= (1L << tetros[i].column[0]);
		t[i].tetro |= (1L << (tetros[i].column[1] + 16 * tetros[i].row[1]));
		t[i].tetro |= (1L << (tetros[i].column[2] + 16 * tetros[i].row[2]));
		t[i].tetro |= (1L << (tetros[i].column[3] + 16 * tetros[i].row[3]));
	}
}

static int		get_map_side_size(int tetros_count)
{
	int map_side_size = 2;
	while (map_side_size * map_side_size < tetros_count * 4)
		map_side_size++;
	return map_side_size;
}

static int		read_file(char *buf, char *file_name)
{
	int fd;
	int size;

	if ((fd = open(file_name, O_RDONLY)) == -1 || (size = read(fd, buf, 550)) < 0)
	{
		printf("error: bad file\n");
		return -1;
	}
	if (size < 19 || size > 546 || (size % 21 != 19 && size % 21 != 20))
	{
		printf("error: wrong file size\n");
		return -1;
	}
	buf[size++] = '\n';
	if (size % 21 == 20)
		buf[size++] = '\n';
	buf[size] = '\0';
	return size;
}

int			main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: %s file_name\n", argv[0]);
		return 1;
	}
	char buf[550];
	int size;
	if ((size = read_file(buf, argv[1])) == -1)
		return 2;

	int tetros_count = size / 21;
	int map_side_size = get_map_side_size(tetros_count);
	t_coordinates	tetros[tetros_count];
	t_tetreminos	t[tetros_count];
	memset(t, 0, sizeof(t));

	parse_and_validate(buf, size, tetros);
	initiate_tetros(tetros, tetros_count, t, map_side_size);
	fillit(t, tetros_count, map_side_size);
	return 0;
}
