#include "minirt.h"

static t_camera	create_preset_camera(t_vector pos, t_vector orientation)
{
	t_camera	cam;

	cam.coordinates = pos;
	cam.orientation = vector_normalize(orientation);
	cam.fov = 70;
	return (cam);
}

static void	set_camera_front(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){0, 0, -20};
	orientation = (t_vector){0, 0, 1};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

static void	set_camera_front_bottom(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){0, -10, -20};
	orientation = (t_vector){0, 0.5f, 1};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

static void	set_camera_right(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){20, 0, 0};
	orientation = (t_vector){-1, 0, 0};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

static void	set_camera_left(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){-20, 0, 0};
	orientation = (t_vector){1, 0, 0};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

static void	set_camera_top(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){0, 25, 0};
	orientation = (t_vector){0, -1, 0};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

static void	set_camera_back(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){0, 0, 20};
	orientation = (t_vector){0, 0, -1};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

static void	set_camera_isometric(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){-15, 15, -15};
	orientation = (t_vector){0.577f, -0.577f, 0.577f};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

static void	set_camera_alt_isometric(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){15, 15, -15};
	orientation = (t_vector){-0.577f, -0.577f, 0.577f};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

static void	set_camera_another_view(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){-15, -10, -15};
	orientation = (t_vector){0.577f, 0.577f, 0.577f};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

void	handle_numpad_camera(t_rt *mini, int keysym)
{
	if (keysym == XK_KP_1)
		set_camera_front(mini);
	else if (keysym == XK_KP_2)
		set_camera_front_bottom(mini);
	else if (keysym == XK_KP_3)
		set_camera_right(mini);
	else if (keysym == XK_KP_4)
		set_camera_left(mini);
	else if (keysym == XK_KP_5)
		set_camera_top(mini);
	else if (keysym == XK_KP_6)
		set_camera_back(mini);
	else if (keysym == XK_KP_7)
		set_camera_isometric(mini);
	else if (keysym == XK_KP_8)
		set_camera_alt_isometric(mini);
	else if (keysym == XK_KP_9)
		set_camera_another_view(mini);
	else if (keysym == XK_KP_End)
		set_camera_front(mini);
	else if (keysym == XK_KP_Down)
		set_camera_front_bottom(mini);
	else if (keysym == XK_KP_Next)
		set_camera_right(mini);
	else if (keysym == XK_KP_Left)
		set_camera_left(mini);
	else if (keysym == XK_KP_Begin)
		set_camera_top(mini);
	else if (keysym == XK_KP_Right)
		set_camera_back(mini);
	else if (keysym == XK_KP_Home)
		set_camera_isometric(mini);
	else if (keysym == XK_KP_Up)
		set_camera_alt_isometric(mini);
	else if (keysym == XK_KP_Prior)
		set_camera_another_view(mini);
}
