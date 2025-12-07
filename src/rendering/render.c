#include "minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static t_ray	create_camera_ray(t_rt *mini, float x, float y)
{
	t_ray		ray;
	t_vector	pixel_pos;
	float		aspect_ratio;
	float		fov_rad;
	float		viewport_height;
	float		viewport_width;

	aspect_ratio = (float)WIN_W / (float)WIN_H;
	fov_rad = mini->camera.fov * M_PI / 180.0;
	viewport_height = 2.0 * tan(fov_rad / 2.0);
	viewport_width = viewport_height * aspect_ratio;

	pixel_pos.x = (x / WIN_W - 0.5) * viewport_width;
	pixel_pos.y = (0.5 - y / WIN_H) * viewport_height;
	pixel_pos.z = 1.0;

	ray.origin = mini->camera.coordinates;
	ray.direction = vector_normalize(vector_add(
		vector_mult(mini->camera.orientation, pixel_pos.z),
		vector_add(
			vector_mult(vector_normalize(vector_cross(
				mini->camera.orientation,
				(t_vector){0, 1, 0})), pixel_pos.x),
			vector_mult(vector_normalize(vector_cross(
				vector_normalize(vector_cross(
					mini->camera.orientation,
					(t_vector){0, 1, 0})),
				mini->camera.orientation)), pixel_pos.y)
		)
	));

	return (ray);
}

void	render_scene_quality(t_rt *mini, int quality)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	color;
	int		pixel_color;
	int		step;
	int		i;
	int		j;

	step = quality;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = create_camera_ray(mini, x, y);
			color = ray_color(mini, ray);
			pixel_color = create_trgb(0,
				(int)(color.r * 255),
				(int)(color.g * 255),
				(int)(color.b * 255));
			i = 0;
			while (i < step && y + i < WIN_H)
			{
				j = 0;
				while (j < step && x + j < WIN_W)
				{
					img_pix_put(&mini->img, x + j, y + i, pixel_color);
					j++;
				}
				i++;
			}
			x += step;
		}
		y += step;
	}
	mlx_put_image_to_window(mini->mlx_ptr, mini->win_ptr, mini->img.mlx_img, 0, 0);
	draw_help_overlay(mini);
}

void	render_scene(t_rt *mini)
{
	render_scene_quality(mini, mini->render_quality);
}
