/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:14:12 by dde-sott          #+#    #+#             */
/*   Updated: 2024/09/01 19:19:40 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_pixel(t_image *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_ceiling(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&game->img, x, y, game->colors.ceiling);
		y++;
	}
}

void	draw_floor(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_end;
	while (y < WIN_H)
	{
		my_mlx_pixel_put(&game->img, x, y, game->colors.floor);
		y++;
	}
}

void	draw_vertical_stripe(t_game *game, t_ray *ray, int x)
{
	int	y;
	int	tex_y;
	int	color;

	draw_ceiling(game, ray, x);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos & (ray->texture->h - 1);
		ray->tex_pos += ray->step;
		color = get_texture_pixel(ray->texture, ray->tex_x, tex_y);
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
	draw_floor(game, ray, x);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->config.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_texture_coordinates(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wall_x = game->p.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->p.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)(ray->texture->w));
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = ray->texture->w - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = ray->texture->w - ray->tex_x - 1;
	ray->step = 1.0 * ray->texture->h / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_H
			/ 2 + ray->line_height / 2) * ray->step;
}

void	determine_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->dir_y > 0)
			ray->texture = &game->walls.so_textu;
		else
			ray->texture = &game->walls.no_textu;
	}
	else
	{
		if (ray->dir_x > 0)
			ray->texture = &game->walls.ea_textu;
		else
			ray->texture = &game->walls.we_textu;
	}
}

void	calculate_distance(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->p.pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->p.pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
	determine_texture(game, ray);
	calculate_texture_coordinates(ray, game);
}

void	initialize_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->p.pos_x
				- ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0
				- game->p.pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->p.pos_y
				- ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0
				- game->p.pos_y) * ray->delta_dist_y;
	}
}

void	initialize_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_W - 1;
	ray->dir_x = game->p.dir_x + game->p.plane_x * ray->camera_x;
	ray->dir_y = game->p.dir_y + game->p.plane_y * ray->camera_x;
	ray->map_x = (int)game->p.pos_x;
	ray->map_y = (int)game->p.pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	initialize_step_and_side_dist(game, ray);
}

void	cast_single_ray(t_game *game, int x)
{
	t_ray	ray;

	initialize_ray(game, &ray, x);
	perform_dda(game, &ray);
	calculate_distance(&ray, game);
	draw_vertical_stripe(game, &ray, x);
}

void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		cast_single_ray(game, x);
		x++;
	}
}

void	init_player_position(t_game *game)
{
	int		y;
	int		x;
	char	**map;

	y = 0;
	map = game->config.map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSWE", map[y][x]))
			{
				game->p.pos_x = x + 0.5;
				game->p.pos_y = y + 0.5;
				game->p.dir_x = (map[y][x] == 'E') - (map[y][x] == 'W');
				game->p.dir_y = (map[y][x] == 'S') - (map[y][x] == 'N');
				game->p.plane_x = -game->p.dir_y * tan(30 * M_PI / 180);
				game->p.plane_y = game->p.dir_x * tan(30 * M_PI / 180);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x + game->p.dir_x
		* game->p.move_speed;
	new_y = game->p.pos_y + game->p.dir_y
		* game->p.move_speed;
	if (game->config.map[(int)new_y][(int)new_x] == '0'
		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x - game->p.dir_x
		* game->p.move_speed;
	new_y = game->p.pos_y - game->p.dir_y
		* game->p.move_speed;
	if (game->config.map[(int)new_y][(int)new_x] == '0'
		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x - game->p.plane_x
		* game->p.move_speed;
	new_y = game->p.pos_y - game->p.plane_y
		* game->p.move_speed;
	if (game->config.map[(int)new_y][(int)new_x] == '0'
		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x + game->p.plane_x
		* game->p.move_speed;
	new_y = game->p.pos_y + game->p.plane_y
		* game->p.move_speed;
	if (game->config.map[(int)new_y][(int)new_x] == '0'
		|| ft_strchr("NSWE", game->config.map[(int)new_y][(int)new_x]))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->p.dir_x;
	old_plane_x = game->p.plane_x;
	game->p.dir_x = game->p.dir_x * cos(game->p.rot_speed)
		- game->p.dir_y * sin(game->p.rot_speed);
	game->p.dir_y = old_dir_x * sin(game->p.rot_speed)
		+ game->p.dir_y * cos(game->p.rot_speed);
	game->p.plane_x = game->p.plane_x * cos(game->p.rot_speed)
		- game->p.plane_y * sin(game->p.rot_speed);
	game->p.plane_y = old_plane_x * sin(game->p.rot_speed)
		+ game->p.plane_y * cos(game->p.rot_speed);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->p.dir_x;
	old_plane_x = game->p.plane_x;
	game->p.dir_x = game->p.dir_x * cos(-game->p.rot_speed)
		- game->p.dir_y * sin(-game->p.rot_speed);
	game->p.dir_y = old_dir_x * sin(-game->p.rot_speed)
		+ game->p.dir_y * cos(-game->p.rot_speed);
	game->p.plane_x = game->p.plane_x * cos(-game->p.rot_speed)
		- game->p.plane_y * sin(-game->p.rot_speed);
	game->p.plane_y = old_plane_x * sin(-game->p.rot_speed)
		+ game->p.plane_y * cos(-game->p.rot_speed);
}

void	draw_tile(t_game *game, int x, int y, unsigned int color)
{
	int	k;
	int	l;

	k = 0;
	while (k < game->config.mt_size)
	{
		l = 0;
		while (l < game->config.mt_size)
		{
			my_mlx_pixel_put(&game->img, x + l, y + k, color);
			l++;
		}
		k++;
	}
}

void	draw_texture(t_game *game, t_image *texture, int x, int y)
{
	unsigned int	tex_color;
	int				k;
	int				l;

	if (texture->img_ptr)
	{
		k = 0;
		while (k < game->config.mt_size)
		{
			l = 0;
			while (l < game->config.mt_size)
			{
				tex_color = *(unsigned int *)(texture->addr
						+ (((k * texture->h) / game->config.mt_size)
							* texture->line_len + ((l * texture->w)
								/ game->config.mt_size) *(texture->bpp / 8)));
				my_mlx_pixel_put(&game->img, x + l, y + k, tex_color);
				l++;
			}
			k++;
		}
	}
}

void	draw_player(t_image *img, t_game *game, int x, int y)
{
	int	player_size;
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	player_size = 4;
	center_x = x + game->config.mt_size / 2;
	center_y = y + game->config.mt_size / 2;
	i = -player_size;
	while (i <= player_size)
	{
		j = -player_size;
		while (j <= player_size)
		{
			if (center_x + i >= 0 && center_x + i
				< WIN_W && center_y + j >= 0 && center_y + j < WIN_H)
			{
				my_mlx_pixel_put(img, center_x + i, center_y + j, 0x00FF0000);
			}
			j++;
		}
		i++;
	}
}

void	draw_player_on_map(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = game->p.pos_x * game->config.mt_size;
	player_y = game->p.pos_y * game->config.mt_size;
	draw_player(&game->img, game, player_x, player_y);
}

void	get_texture(t_game *game, int i, int j)
{
	t_image	*player_texture;

	player_texture = NULL;
	if (game->config.map[i][j] == '0')
		player_texture = &game->walls.so_textu;
	if (game->config.map[i][j] == 'N')
		player_texture = &game->walls.no_textu;
	else if (game->config.map[i][j] == 'S')
		player_texture = &game->walls.so_textu;
	else if (game->config.map[i][j] == 'E')
		player_texture = &game->walls.ea_textu;
	else if (game->config.map[i][j] == 'W')
		player_texture = &game->walls.we_textu;
	if (player_texture)
		draw_texture(game, player_texture, j
			* game->config.mt_size, i * game->config.mt_size);
	draw_player_on_map(game);
}

// SOFIAAAAA
void	free_texture_paths(t_game *game)
{
	if (game->walls.no_path)
	{
		free(game->walls.no_path);
		game->walls.no_path = NULL;
	}
	if (game->walls.so_path)
	{
		free(game->walls.so_path);
		game->walls.so_path = NULL;
	}
	if (game->walls.ea_path)
	{
		free(game->walls.ea_path);
		game->walls.ea_path = NULL;
	}
	if (game->walls.we_path)
	{
		free(game->walls.we_path);
		game->walls.we_path = NULL;
	}
}
// SOFIAAAA

void	destroy_texture_images(t_game *game)
{
	if (game->win.mlx_ptr == NULL)
		return ;
	if (game->walls.no_textu.img_ptr)
	{
		mlx_destroy_image(game->win.mlx_ptr, game->walls.no_textu.img_ptr);
		game->walls.no_textu.img_ptr = NULL;
	}
	if (game->walls.so_textu.img_ptr)
	{
		mlx_destroy_image(game->win.mlx_ptr, game->walls.so_textu.img_ptr);
		game->walls.so_textu.img_ptr = NULL;
	}
	if (game->walls.ea_textu.img_ptr)
	{
		mlx_destroy_image(game->win.mlx_ptr, game->walls.ea_textu.img_ptr);
		game->walls.ea_textu.img_ptr = NULL;
	}
	if (game->walls.we_textu.img_ptr)
	{
		mlx_destroy_image(game->win.mlx_ptr, game->walls.we_textu.img_ptr);
		game->walls.we_textu.img_ptr = NULL;
	}
}

void	free_textures(t_game *game)
{
	if (game == NULL)
		return ;
	free_texture_paths(game);
	destroy_texture_images(game);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	cleanup(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	if (game->config.map)
		free_matrix(game->config.map);
	if (game->config.map_norm)
	 	free_matrix(game->config.map_norm);
	if (game->img.img_ptr)
		mlx_destroy_image(game->win.mlx_ptr, game->img.img_ptr);
	if (game->win.win_ptr)
		mlx_destroy_window(game->win.mlx_ptr, game->win.win_ptr);
	if (game->win.mlx_ptr)
	{
		mlx_destroy_display(game->win.mlx_ptr);
		free(game->win.mlx_ptr);
	}
}

int	exit_game(t_game *game)
{
	cleanup(game);
	exit(EXIT_SUCCESS);
}

void	update_game(t_game *game)
{
	ft_memset(game->img.addr, 0, WIN_H * game->img.line_len);
	cast_rays(game);
	mlx_put_image_to_window(game->win.mlx_ptr, game->win.win_ptr,
		game->img.img_ptr, 0, 0);
}

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		rotate_left(game);
	else if (keycode == KEY_RIGHT)
		rotate_right(game);
	update_game(game);
	return (0);
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nThere is an error opening file");
		printf("%s\n", filename);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	my_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*trim_end_whitespace(char *str)
{
	char	*end;

	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && my_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}

void	load_texture(t_game *game, t_image *texture, char *path)
{
	texture->img_ptr = mlx_xpm_file_to_image(game->win.mlx_ptr,
			path, &texture->w, &texture->h);
	if (!texture->img_ptr)
	{
		printf("Error\nTexture not found! %s\n", path);
		cleanup(game);
		exit (EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img_ptr,
			&texture->bpp, &texture->line_len, &texture->endian);
}

void	load_all_textures(t_game *game)
{
	load_texture(game, &game->walls.no_textu, game->walls.no_path);
	load_texture(game, &game->walls.so_textu, game->walls.so_path);
	load_texture(game, &game->walls.ea_textu, game->walls.ea_path);
	load_texture(game, &game->walls.we_textu, game->walls.we_path);
}

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
}

// Função para encontrar o maior comprimento de uma linha do mapa
int find_max_width(char **map)
{
    int max_width = 0;
    int i = 0;
    while (map[i])
    {
		trim_end_whitespace(map[i]);
        int width = strlen(map[i]);
        if (width > max_width)
            max_width = width;
        i++;
    }
    return max_width;
}

void	check_empty_line_validation(char **map, t_game *game)
{
    int height = 0;
	int i = 0;
	int j;
	int map_start;
	int not_empty = -1;

	map_start = 0;
    while (map[i])
	{
		j = 0;
		if (!not_empty)
			break ;
		not_empty = 0;
		while (map[i][j])
		{
			if (ft_isalnum(map[i][j]) && !map_start)
			{
				map_start = i;
				not_empty = 1;
				height++;
				break ;
			}
			else if(ft_isalnum(map[i][j]))
			{
				not_empty = 1;
				height++;
				break ;
			}
			else if (!map_start)
				not_empty = 1;
			j++;
		}
		i++;
	}
	i = map_start + height - 1;
	if (map[i])
	{
		while (map[i])
		{
			j = 0;
			while (map[i][j])
			{
				if (ft_isalnum(map[i][j]))
				{
					printf("Error\nMap in the wrong format!");
					cleanup(game);
					exit(EXIT_FAILURE);
				}
				j++;
			}
			i++;
		}
	} 
}

// Função para encontrar a altura do mapa
int find_height(char **map, t_game *game)
{
    int height = 0;
	check_empty_line_validation(map, game);
    while (map[height])
	{
		trim_end_whitespace(map[height]);
		height++;
	}
    return height;
}

// Função para imprimir o mapa (ou mockup)
void print_map(char **map)
{
    int i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
}

void	init_game(t_game *game)
{
	game->p.move_speed = 0.4;
	game->p.rot_speed = 0.4;
	game->config.width = 0;
	game->config.height = 0;
	game->win.mlx_ptr = mlx_init();
	load_all_textures(game);
	game->config.mt_size = ((TILE_SIZE + MAP_SCALE - 1) / MAP_SCALE);
	game->win.win_ptr = mlx_new_window(game->win.mlx_ptr,
			WIN_W, WIN_H, "Cub3D");
	game->img.img_ptr = mlx_new_image(game->win.mlx_ptr,
			WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
}

int	check_name(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5 || name[len - 4] != '.' || name[len - 3] != 'c'
		|| name[len - 2] != 'u' || name[len - 1] != 'b')
	{
		printf("Error\nMap name needs to end with \".cub\"\n");
		return (1);
	}
	return (0);
}

void	finish_game(char* msg, t_game *game)
{
	printf("Error\n%s\n", msg);
	cleanup(game);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		printf("Error\nThe filename is missing!\n");
		return (EXIT_FAILURE);
	}
	if (check_name(argv[1]))
		return (1);
	game.config.map = read_map(argv[1], &game); //map related content
	counting_map(&game, game.config.map); // map size and direction / where to normalize?
	game.config.map_norm = normalize_map(game.config.map, &game);
	print_map(game.config.map_norm);
	check_map_char(game.config.map_norm, &game); // check-validate map
	check_enclosed_map(game.config.map_norm, &game); // flood-fill
	check_single_player(game.config.map_norm, &game);
	init_game(&game);
	init_player_position(&game);
	cast_rays(&game);
	mlx_put_image_to_window(game.win.mlx_ptr, game.win.win_ptr,
		game.img.img_ptr, 0, 0);
	mlx_hook(game.win.win_ptr, 2, 1L << 0, handle_key_press, &game);
	mlx_hook(game.win.win_ptr, 17, 1L << 17, exit_game, &game);
	mlx_loop(game.win.mlx_ptr);
	cleanup(&game);
	return (EXIT_SUCCESS);
}
