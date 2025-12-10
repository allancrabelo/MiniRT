#include "minirt.h"

static t_vector	rotate_vector_y(t_vector v, float angle)
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

static void	rotate_camera(t_rt *mini, int direction)
{
	float	angle;

	angle = 0.1;
	if (direction == XK_Right)
		angle = -angle;
	mini->camera.orientation = vector_normalize(
			rotate_vector_y(mini->camera.orientation, angle));
	mini->render_quality = 4;
	render_scene(mini);
}

static void	move_camera_forward_back(t_rt *mini, int direction)
{
	t_vector	move;
	float		speed;

	speed = 2.0;
	if (direction == 'w' || direction == 'W')
		move = vector_mult(mini->camera.orientation, speed);
	else
		move = vector_mult(mini->camera.orientation, -speed);
	mini->camera.coordinates = vector_add(mini->camera.coordinates, move);
	mini->render_quality = 4;
	render_scene(mini);
}

static void	move_camera_strafe(t_rt *mini, int direction)
{
	t_vector	move;
	t_vector	right;
	float		speed;

	speed = 2.0;
	right = vector_normalize(vector_cross(mini->camera.orientation,
				(t_vector){0, 1, 0}));
	if (direction == 'a' || direction == 'A')
		move = vector_mult(right, -speed);
	else
		move = vector_mult(right, speed);
	mini->camera.coordinates = vector_add(mini->camera.coordinates, move);
	mini->render_quality = 4;
	render_scene(mini);
}

static void	move_camera_vertical(t_rt *mini, int direction)
{
	float	speed;

	speed = 2.0;
	if (direction == XK_Up)
		mini->camera.coordinates.y += speed;
	else
		mini->camera.coordinates.y -= speed;
	mini->render_quality = 4;
	render_scene(mini);
}

int	key_hook(int keysym, void *param)
{
	t_rt	*mini;

	mini = (t_rt *)param;
	if (keysym == XK_Escape)
		ft_err_handler(mini, -1);
	else if (keysym == XK_Up || keysym == XK_Down)
		move_camera_vertical(mini, keysym);
	else if (keysym == XK_Left || keysym == XK_Right)
		rotate_camera(mini, keysym);
	else if (keysym == 'a' || keysym == 'A' || keysym == 'd' || keysym == 'D')
		move_camera_strafe(mini, keysym);
	else if (keysym == 'w' || keysym == 'W' || keysym == 's' || keysym == 'S')
		move_camera_forward_back(mini, keysym);
	else if (keysym == XK_Tab || keysym == 0xff09)
	{
		toggle_controls_help(mini);
		return (0);
	}
	else if (keysym == 'q' || keysym == 'Q')
	{
		mini->render_quality = 1;
		render_scene(mini);
		return (0);
	}
	else if (keysym == 'r' || keysym == 'R')
	{
		mini->camera = mini->initial_camera;
		mini->render_quality = 1;
	}
	// Numpad with Num Lock ON (numeric keysyms: 0xffb1-0xffb9)
	else if (keysym >= XK_KP_1 && keysym <= XK_KP_9)
	{
		handle_numpad_camera(mini, keysym);
		return (0);
	}
	// Numpad with Num Lock OFF (navigation keysyms)
	else if (keysym == XK_KP_Home || keysym == XK_KP_Up || keysym == XK_KP_Prior ||
			keysym == XK_KP_Left || keysym == XK_KP_Begin || keysym == XK_KP_Right ||
			keysym == XK_KP_End || keysym == XK_KP_Down || keysym == XK_KP_Next)
	{
		handle_numpad_camera(mini, keysym);
		return (0);
	}
	else
		return (0);
	if (keysym == 'r' || keysym == 'R')
		render_scene(mini);
	return (0);
}

int	close_hook(void *param)
{
	t_rt	*mini;

	mini = (t_rt *)param;
	return (ft_err_handler(mini, -1));
}
