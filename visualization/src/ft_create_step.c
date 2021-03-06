/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_step.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 17:20:45 by rnovodra          #+#    #+#             */
/*   Updated: 2018/07/31 17:20:46 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visual.h"

int					ft_read_map_size(t_visual_data *d, char *line)
{
	uintmax_t	*ptr;
	char		*cp;

	ptr = (uintmax_t*)line;
	if (*ptr != 0x2075616574616c50)
		return (-2);
	cp = line;
	if (ft_getnbr(&cp, &d->info[MAP].h) < 0 ||
		ft_getnbr(&cp, &d->info[MAP].w) < 0 ||
		ft_getnbr(&cp, NULL) != 0 ||
		d->info[MAP].h <= 0 || d->info[MAP].w <= 0)
	{
		free(line);
		return (-2);
	}
	free(line);
	if (d->info[MAP].h >= 300 || d->info[MAP].w >= 500)
		return (-8);
	return (0);
}

static inline int	ft_write_map(t_visual_data *d, t_vis_map *step)
{
	char	*line;
	int		y;

	y = 1;
	while (y < d->info[MAP].h)
	{
		if (get_next_line(0, &line) < 0)
			return (-1);
		if ((int)ft_strlen(line) != 4 + d->info[MAP].w)
		{
			free(line);
			return (-2);
		}
		step->map[y++] = line;
	}
	return (0);
}

static inline int	ft_create_map(t_visual_data *d, t_vis_map *step)
{
	char	*line;
	int		ret;

	line = NULL;
	if (!(step->map = ft_arrnew(d->info[MAP].h)) ||
		get_next_line(0, &line) < 0)
		return (-1);
	free(line);
	if (get_next_line(0, &line) < 0)
		return (-1);
	step->map[0] = line;
	if ((ret = ft_write_map(d, step)) < 0)
		return (ret);
	return (0);
}

t_vis_map			*ft_create_step(t_visual_data *d, t_vis_map *prev)
{
	t_vis_map	*step;
	int			ret;
	static int	number = 0;

	if (!(step = (t_vis_map*)malloc(sizeof(t_vis_map))))
		ft_thread_error(d, -1);
	if ((ret = ft_create_map(d, step)) < 0)
	{
		ft_free_step(&step);
		ft_thread_error(d, ret);
	}
	++number;
	step->next = NULL;
	step->prev = prev;
	step->number = number;
	step->score_x = -1;
	step->score_o = -1;
	return (step);
}
