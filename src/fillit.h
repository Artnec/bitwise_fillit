#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>


typedef struct	s_coordinates
{
	int			row[4];
	int			column[4];
}				t_coordinates;

typedef struct	s_tetreminos
{
	uint64_t	tetro;
	long		h;
	long		l;
	long		max_map_h;
	long		max_map_l;
}				t_tetreminos;


void			parse_and_validate(char *file_content, int size, t_coordinates *data);
void			fillit(t_tetreminos *t, int tetros_count, int map_side_size);

#endif
