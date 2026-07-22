#include "cub3d.h"

/*
** init_ray — set ray direction and map cell from player state and column x.
** camera_x maps column x to the range [-1, 1] across the view plane.
*/
static void	init_ray(t_ray *ray, t_game *game, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	if (ray->dir_x == 0.0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0.0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->dir_y);
}

/*
** init_ray_step — set step direction and initial side distances.
*/
static void	init_ray_step(t_ray *ray, t_game *game)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_y;
	}
}

/*
** perform_dda — step through the grid until a wall ('1') is hit.
** side == 0 means an X-boundary was crossed; side == 1 means Y-boundary.
*/
static void	perform_dda(t_ray *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->map_grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

/*
** calc_wall_hit — compute projected wall height, draw range, texture
** coordinates and which wall face (NO/SO/WE/EA) was hit.
*/
static void	calc_wall_hit(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wall_dist = ray->side_x - ray->delta_x;
	else
		ray->wall_dist = ray->side_y - ray->delta_y;
	if (ray->wall_dist < 0.0001)
		ray->wall_dist = 0.0001;
	ray->line_h = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_start = WIN_HEIGHT / 2 - ray->line_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = WIN_HEIGHT / 2 + ray->line_h / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0 && ray->step_x > 0)
		ray->tex_idx = TEX_EA;
	else if (ray->side == 0)
		ray->tex_idx = TEX_WE;
	else if (ray->step_y > 0)
		ray->tex_idx = TEX_SO;
	else
		ray->tex_idx = TEX_NO;
}

/*
** cast_rays — iterate over every screen column, run DDA and draw.
*/
void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, game, x);
		init_ray_step(&ray, game);
		perform_dda(&ray, game);
		calc_wall_hit(&ray, game);
		draw_tex_column(game, &ray, x);
		x++;
	}
}
