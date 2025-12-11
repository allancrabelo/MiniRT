#include "minirt.h"

/**
 * @brief Rotates a vector around the Y-axis.
 * 
 * Applies rotation matrix for Y-axis rotation to the input vector.
 * 
 * @param v Vector to rotate.
 * @param angle Rotation angle in radians.
 * @return t_vector Rotated vector.
 */
t_vector	rotate_vector_y(t_vector v, float angle)
{
	t_vector	result;
	float		cos_a;
	float		sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	result.x = v.x * cos_a + v.z * sin_a;
	result.y = v.y;
	result.z = -v.x * sin_a + v.z * cos_a;
	return (result);
}

/**
 * @brief Rotates the camera left or right.
 * 
 * Rotates camera orientation around Y-axis based on arrow key input.
 * 
 * @param mini Pointer to main program structure.
 * @param direction Rotation direction (XK_Left or XK_Right).
 */
void	rotate_camera(t_rt *mini, int direction)
{
	float	angle;

	angle = ROTATE_ANGLE;
	if (direction == XK_Right)
		angle = -angle;
	mini->camera.orientation = vector_normalize(
			rotate_vector_y(mini->camera.orientation, angle));
	update_and_render(mini, QUALITY_FAST);
}

/**
 * @brief Moves the camera forward or backward.
 * 
 * Moves camera along its orientation vector based on WASD input.
 * 
 * @param mini Pointer to main program structure.
 * @param direction Movement direction ('w' for forward, 's' for backward).
 */
void	move_camera_forward_back(t_rt *mini, int direction)
{
	t_vector	move;

	if (direction == 'w' || direction == 'W')
		move = vector_mult(mini->camera.orientation, CAMERA_SPEED);
	else
		move = vector_mult(mini->camera.orientation, -CAMERA_SPEED);
	mini->camera.coordinates = vector_add(mini->camera.coordinates, move);
	update_and_render(mini, QUALITY_FAST);
}

/**
 * @brief Moves the camera sideways (strafing).
 * 
 * Calculates right vector from camera orientation and moves camera left/right.
 * 
 * @param mini Pointer to main program structure.
 * @param direction Strafe direction ('a' for left, 'd' for right).
 */
void	move_camera_strafe(t_rt *mini, int direction)
{
	t_vector	move;
	t_vector	right;

	right = vector_normalize(vector_cross(mini->camera.orientation,
				(t_vector){0, 1, 0}));
	if (direction == 'a' || direction == 'A')
		move = vector_mult(right, -CAMERA_SPEED);
	else
		move = vector_mult(right, CAMERA_SPEED);
	mini->camera.coordinates = vector_add(mini->camera.coordinates, move);
	update_and_render(mini, QUALITY_FAST);
}

/**
 * @brief Moves the camera vertically.
 * 
 * Adjusts camera's Y-coordinate based on arrow key input.
 * 
 * @param mini Pointer to main program structure.
 * @param direction Direction key (XK_Up or XK_Down).
 */
void	move_camera_vertical(t_rt *mini, int direction)
{
	if (direction == XK_Up)
		mini->camera.coordinates.y += CAMERA_SPEED;
	else
		mini->camera.coordinates.y -= CAMERA_SPEED;
	update_and_render(mini, QUALITY_FAST);
}
