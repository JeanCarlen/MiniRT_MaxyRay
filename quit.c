/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalizia <fmalizia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:35:23 by nnemeth           #+#    #+#             */
/*   Updated: 2023/03/21 11:41:03 by fmalizia         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	close_window(t_data *data)
{
	free_struc(data);
	free_light(data);
	if (data->mlx.mlx_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img);
	free(data);
	data = NULL;
	exit(0);
	return (0);
}

int	escape(int keycode, t_data *data)
{
	if (keycode == DOWN)
		data->camera.pos.y += 0.5;
	if (keycode == UP)
		data->camera.pos.y -= 0.5;
	if (keycode == RIGHT)
		data->camera.pos.x += 1;
	if (keycode == LEFT)
		data->camera.pos.x -= 1;
	if (keycode == J_KEY)
		data->camera.pos.z += 1;
	if (keycode == K_KEY)
		data->camera.pos.z -= 1;
	if (keycode == KEY_ESC)
		close_window(data);
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.mlx_ptr, W, H);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	load_scene(data);
	return (0);
}
