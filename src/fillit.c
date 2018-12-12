#include "fillit.h"

static void		print_result_map(int map_side_size, t_tetreminos *t, int tetros_count)
{
	char	map[map_side_size][map_side_size + 1];
	for (int j, i = 0; i < map_side_size; i++)
	{
		for (j = 0; j < map_side_size; j++)
			map[i][j] = '.';
		map[i][j] = '\n';
	}
	for (int n = 0; n < tetros_count; n++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (*((uint16_t *)(&t[n].tetro) + i) & (1L << j))
					map[t[n].h + i][t[n].l + j] = n + 'A';
			}
		}
	}
	write(1, map, map_side_size * (map_side_size + 1));
}

static int		place_tetro(t_tetreminos *t, uint16_t *map)
{
	while (t->h < t->max_map_h)
	{
		while (t->l < t->max_map_l)
		{
			if ((*(uint64_t *)(map + t->h) & (t->tetro << t->l)) == 0)
			{
				*(uint64_t *)(map + t->h) |= (t->tetro << t->l);
				return 1;
			}
			t->l++;
		}
		t->l = 0;
		t->h++;
	}
	t->h = 0;
	return 0;
}

void		fillit(t_tetreminos *t, int tetros_count, int map_side_size)
{
	uint16_t	map[16] = {0};
	for (int i = 0; i < tetros_count; i++)
	{
		if (place_tetro(&t[i], map) == 0)
		{
			if (--i >= 0)
			{
				*(uint64_t *)(map + t[i].h) ^= (t[i].tetro << t[i].l++);
				i--;
			}
			else
			{
				if (++map_side_size > 16)
				{
					write(2, "error\n", 6);
					exit(1);
				}
				for (int n = 0; n < tetros_count; n++)
				{
					t[n].max_map_l++;
					t[n].max_map_h++;
				}
			}
		}
	}
	print_result_map(map_side_size, t, tetros_count);
}
