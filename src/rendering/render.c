#include "minirt.h"

/**
 * @brief Creates a 32-bit color value from components.
 * 
 * @param t Transparency (unused in this implementation).
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 * @return int Packed 32-bit color value.
 */
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * @brief Sets a pixel color in the image buffer.
 * 
 * Handles endianness differences in pixel storage.
 * 
 * @param img Image buffer structure.
 * @param x X-coordinate of pixel.
 * @param y Y-coordinate of pixel.
 * @param color Color to set (32-bit packed).
 */
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

/**
 * @brief Main scene rendering function.
 * 
 * Delegates to quality-based renderer using current quality setting.
 * 
 * @param mini Main program structure.
 */
void	render_scene(t_rt *mini)
{
	render_scene_quality(mini, mini->render_quality);
}
