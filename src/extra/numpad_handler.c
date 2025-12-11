#include "minirt.h"

/**
 * @brief Handles numpad camera preset selection.
 * 
 * Maps numpad keys to specific camera preset positions.
 * 
 * @param mini Pointer to main program structure.
 * @param keysym Numpad key symbol for camera preset.
 */
void	handle_numpad_camera(t_rt *mini, int keysym)
{
	if (keysym == XK_KP_1 || keysym == XK_KP_End)
		set_camera_front(mini);
	else if (keysym == XK_KP_2 || keysym == XK_KP_Down)
		set_camera_front_bottom(mini);
	else if (keysym == XK_KP_3 || keysym == XK_KP_Next)
		set_camera_right(mini);
	else if (keysym == XK_KP_4 || keysym == XK_KP_Left)
		set_camera_left(mini);
	else if (keysym == XK_KP_5 || keysym == XK_KP_Begin)
		set_camera_top(mini);
	else if (keysym == XK_KP_6 || keysym == XK_KP_Right)
		set_camera_back(mini);
	else if (keysym == XK_KP_7 || keysym == XK_KP_Home)
		set_camera_isometric(mini);
	else if (keysym == XK_KP_8 || keysym == XK_KP_Up)
		set_camera_alt_isometric(mini);
	else if (keysym == XK_KP_9 || keysym == XK_KP_Prior)
		set_camera_another_view(mini);
}
