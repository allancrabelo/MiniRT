#include "minirt.h"

static void	move_camera(t_rt *mini, int direction)
{
	t_vector	move;
	t_vector	right;
	float		speed;

	speed = 2.0;
	move = (t_vector){0, 0, 0};
	
	if (direction == XK_Up)
		move = vector_mult(mini->camera.orientation, speed);
	else if (direction == XK_Down)
		move = vector_mult(mini->camera.orientation, -speed);
	else if (direction == XK_Left || direction == XK_Right)
	{
		right = vector_normalize(vector_cross(mini->camera.orientation, 
			(t_vector){0, 1, 0}));
		if (direction == XK_Left)
			move = vector_mult(right, -speed);
		else
			move = vector_mult(right, speed);
	}
	
	mini->camera.coordinates = vector_add(mini->camera.coordinates, move);
	mini->render_quality = 4;
	render_scene(mini);
}

int	key_hook(int keysym, void *param)
{
	t_rt	*mini;

	mini = (t_rt *)param;
	if (keysym == XK_Escape)
		ft_err_handler(mini, -1);
	else if (keysym == XK_Left || keysym == XK_Right || 
			keysym == XK_Up || keysym == XK_Down)
		move_camera(mini, keysym);
	else if (keysym == 'w' || keysym == 'W')
	{
		mini->camera.coordinates.y += 2.0;
		mini->render_quality = 4;
	}
	else if (keysym == 's' || keysym == 'S')
	{
		mini->camera.coordinates.y -= 2.0;
		mini->render_quality = 4;
	}
	else if (keysym == 'a' || keysym == 'A')
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
	else
		return (0);
	if (keysym == 'w' || keysym == 'W' || keysym == 's' || keysym == 'S' 
		|| keysym == 'r' || keysym == 'R')
		render_scene(mini);
	return (0);
}

int	close_hook(void *param)
{
	t_rt	*mini;

	mini = (t_rt *)param;
	return (ft_err_handler(mini, -1));
}