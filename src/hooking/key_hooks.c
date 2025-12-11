#include "minirt.h"

/**
 * @brief Handles special function keys.
 * 
 * Processes keys for toggling help, changing quality, and resetting camera.
 * 
 * @param mini Pointer to main program structure.
 * @param keysym Key symbol code from X11.
 */
void	handle_special_keys(t_rt *mini, int keysym)
{
	if (keysym == XK_Tab)
		toggle_controls_help(mini);
	else if (keysym == 'q' || keysym == 'Q')
		update_and_render(mini, QUALITY_HIGH);
	else if (keysym == 'r' || keysym == 'R')
	{
		mini->camera = mini->initial_camera;
		update_and_render(mini, QUALITY_HIGH);
	}
}

/**
 * @brief Handles numpad key inputs for camera positioning.
 * 
 * Routes numpad key presses to camera positioning functions.
 * 
 * @param mini Pointer to main program structure.
 * @param keysym Key symbol code from X11 numpad.
 */
void	handle_numpad_keys(t_rt *mini, int keysym)
{
	if (keysym >= XK_KP_1 && keysym <= XK_KP_9)
		handle_numpad_camera(mini, keysym);
	else if (keysym == XK_KP_Home || keysym == XK_KP_Up
		|| keysym == XK_KP_Prior || keysym == XK_KP_Left
		|| keysym == XK_KP_Begin || keysym == XK_KP_Right
		|| keysym == XK_KP_End || keysym == XK_KP_Down
		|| keysym == XK_KP_Next)
		handle_numpad_camera(mini, keysym);
}

/**
 * @brief Updates rendering quality and re-renders the scene.
 * 
 * Sets the new rendering quality level and triggers a scene re-render.
 * 
 * @param mini Pointer to main program structure.
 * @param quality New rendering quality level to apply.
 */
void	update_and_render(t_rt *mini, int quality)
{
	mini->render_quality = quality;
	render_scene(mini);
}

/**
 * @brief Handles window close events.
 * 
 * Called when the window close button is clicked.
 * Triggers the program's error handler with exit code.
 * 
 * @param param Pointer to main program structure (t_rt*).
 * @return int Return value from error handler.
 */
int	close_hook(void *param)
{
	t_rt	*mini;

	mini = (t_rt *)param;
	return (ft_err_handler(mini, SUCCESS));
}

/**
 * @brief Handles keyboard input events.
 * 
 * Processes key presses for camera movement, rotation, and program control.
 * 
 * @param keysym Key symbol code from X11.
 * @param param Pointer to main program structure (t_rt*).
 * @return int Always returns SUCCESS.
 */
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
	else if (keysym == 'a' || keysym == 'A' || keysym == 'd'
		|| keysym == 'D')
		move_camera_strafe(mini, keysym);
	else if (keysym == 'w' || keysym == 'W' || keysym == 's'
		|| keysym == 'S')
		move_camera_forward_back(mini, keysym);
	else if ((keysym >= XK_KP_Home && keysym <= XK_KP_Begin)
		|| (keysym >= XK_KP_0 && keysym <= XK_KP_9))
		handle_numpad_keys(mini, keysym);
	else
		handle_special_keys(mini, keysym);
	return (EXIT_SUCCESS);
}
