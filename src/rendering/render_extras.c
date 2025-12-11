#include "minirt.h"

/**
 * @brief Creates a ray from camera through viewport pixel.
 * 
 * @param mini Main program structure.
 * @param x Pixel x-coordinate.
 * @param y Pixel y-coordinate.
 * @return t_ray Camera ray for this pixel.
 */
static t_ray	create_camera_ray(t_rt *mini, float x, float y)
{
	t_ray			ray;
	t_viewport		vp;
	t_vector		pixel_pos;
	t_camera_basis	basis;
	t_vector		ray_direction;

	vp = calculate_viewport(mini);
	pixel_pos = calculate_pixel_pos(x, y, vp);
	basis = calculate_camera_basis(mini->camera.orientation);
	ray_direction = vector_add(vector_mult(basis.forward, pixel_pos.z),
			vector_add(vector_mult(basis.right, pixel_pos.x),
				vector_mult(basis.up, pixel_pos.y)));
	ray.origin = mini->camera.coordinates;
	ray.direction = vector_normalize(ray_direction);
	return (ray);
}

/**
 * @brief Calculates final pixel color for a ray.
 * 
 * @param mini Main program structure.
 * @param ray Ray to trace.
 * @return int Packed 32-bit color value.
 */
static int	calculate_pixel_color(t_rt *mini, t_ray ray)
{
	t_color	color;
	int		pixel_color;

	color = ray_color(mini, ray);
	pixel_color = create_trgb(0,
			(int)(fmin(fmax(color.r, 0.0), 1.0) * 255),
			(int)(fmin(fmax(color.g, 0.0), 1.0) * 255),
			(int)(fmin(fmax(color.b, 0.0), 1.0) * 255));
	return (pixel_color);
}

/**
 * @brief Renders a block of pixels with same color.
 * 
 * @param img Image buffer.
 * @param block Block parameters (position, color, step size).
 */
static void	render_pixel_block(t_img *img, t_pixel_block block)
{
	int	i;
	int	j;

	i = 0;
	while (i < block.step && block.y + i < WIN_H)
	{
		j = 0;
		while (j < block.step && block.x + j < WIN_W)
		{
			img_pix_put(img, block.x + j, block.y + i, block.color);
			j++;
		}
		i++;
	}
}

/**
 * @brief Renders scene with adaptive quality (skipping pixels).
 * 
 * @param mini Main program structure.
 * @param step Pixel step size (1=full quality, 2=half resolution, etc).
 */
static void	render_quality_rows(t_rt *mini, int step)
{
	int				x;
	int				y;
	t_ray			ray;
	int				pixel_color;
	t_pixel_block	block;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = create_camera_ray(mini, x, y);
			pixel_color = calculate_pixel_color(mini, ray);
			block = (t_pixel_block){x, y, pixel_color, step};
			render_pixel_block(&mini->img, block);
			x += step;
		}
		y += step;
	}
}

/**
 * @brief Main rendering function with quality control.
 * 
 * @param mini Main program structure.
 * @param quality Rendering quality level (1=high, 2=medium, etc).
 */
void	render_scene_quality(t_rt *mini, int quality)
{
	render_quality_rows(mini, quality);
	mlx_put_image_to_window(mini->mlx_ptr,
		mini->win_ptr, mini->img.mlx_img, 0, 0);
	draw_help_overlay(mini);
}
