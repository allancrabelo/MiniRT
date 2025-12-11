#include "minirt.h"

/**
 * @brief Calculates viewport dimensions based on camera FOV.
 * 
 * @param mini Main program structure.
 * @return t_viewport Viewport dimensions.
 */
t_viewport	calculate_viewport(t_rt *mini)
{
	t_viewport	vp;

	vp.aspect_ratio = (float)WIN_W / (float)WIN_H;
	vp.fov_rad = mini->camera.fov * M_PI / 180.0;
	vp.height = 2.0 * tan(vp.fov_rad / 2.0);
	vp.width = vp.height * vp.aspect_ratio;
	return (vp);
}

/**
 * @brief Calculates 3D position of pixel in viewport space.
 * 
 * @param x Pixel x-coordinate.
 * @param y Pixel y-coordinate.
 * @param vp Viewport dimensions.
 * @return t_vector Pixel position in viewport coordinates.
 */
t_vector	calculate_pixel_pos(float x, float y, t_viewport vp)
{
	t_vector	pixel_pos;

	pixel_pos.x = (x / WIN_W - 0.5) * vp.width;
	pixel_pos.y = (0.5 - y / WIN_H) * vp.height;
	pixel_pos.z = 1.0;
	return (pixel_pos);
}

/**
 * @brief Calculates camera coordinate basis vectors.
 * 
 * @param camera_orientation Camera forward direction.
 * @return t_camera_basis Camera right, up, and forward vectors.
 */
t_camera_basis	calculate_camera_basis(t_vector camera_orientation)
{
	t_camera_basis	basis;

	basis.forward = camera_orientation;
	basis.right = vector_normalize(vector_cross(basis.forward,
				(t_vector){0, 1, 0}));
	basis.up = vector_normalize(vector_cross(basis.right, basis.forward));
	return (basis);
}
