/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 17:49:35 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/11 20:46:37 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef				RTV_H
# define			RTV_H

# include			<math.h>
# include			<stdio.h>
# include			<mlx.h>
# include			<libft.h>

# define DIST_V	1.0
# define DIST_LEN 0.35
# define DIST_WIDTH 0.5

typedef struct		s_univers
{
	int		w;
	int		h;
	void	*mlx;
	void	*win_ray;
	void	*img;
	int		bpp;
	int		endian;
	int		s_line;
	char	*data;
}					t_univers;

void	error_command(char *s);

void	init_univers(t_univers *v);
void	init_windows(t_univers *v);

#endif
