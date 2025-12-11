#include "minirt.h"

/**
 * @brief Sets camera to front-bottom view preset.
 * 
 * Positions camera low and in front of the scene looking
 * slightly upward.
 * 
 * @param mini Pointer to main program structure.
 */
void	set_camera_front_bottom(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){0, -10, -20};
	orientation = (t_vector){0, 0.5f, 1};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

/**
 * @brief Sets camera to right side view preset.
 * 
 * Positions camera to the right of the scene looking left.
 * 
 * @param mini Pointer to main program structure.
 */
void	set_camera_right(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){20, 0, 0};
	orientation = (t_vector){-1, 0, 0};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

/**
 * @brief Sets camera to left side view preset.
 * 
 * Positions camera to the left of the scene looking right.
 * 
 * @param mini Pointer to main program structure.
 */
void	set_camera_left(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){-20, 0, 0};
	orientation = (t_vector){1, 0, 0};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

/**
 * @brief Sets camera to top view preset.
 * 
 * Positions camera above the scene looking down.
 * 
 * @param mini Pointer to main program structure.
 */
void	set_camera_top(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){0, 25, 0};
	orientation = (t_vector){0, -1, 0};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

/**
 * @brief Sets camera to back view preset.
 * 
 * Positions camera behind the scene looking forward.
 * 
 * @param mini Pointer to main program structure.
 */
void	set_camera_back(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){0, 0, 20};
	orientation = (t_vector){0, 0, -1};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}
