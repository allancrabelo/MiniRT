#include "minirt.h"

/**
 * @brief Sets camera to front view preset.
 * 
 * Positions camera in front of the scene looking forward.
 * 
 * @param mini Pointer to main program structure.
 */
void	set_camera_front(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){0, 0, -20};
	orientation = (t_vector){0, 0, 1};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

/**
 * @brief Creates a camera preset with specified position and orientation.
 * 
 * Normalizes the orientation vector and sets default field of view.
 * 
 * @param pos Camera position vector.
 * @param orientation Camera orientation vector (will be normalized).
 * @return t_camera Configured camera structure.
 */
t_camera	create_preset_camera(t_vector pos, t_vector orientation)
{
	t_camera	cam;

	cam.coordinates = pos;
	cam.orientation = vector_normalize(orientation);
	cam.fov = 70;
	return (cam);
}

/**
 * @brief Sets camera to another view preset.
 * 
 * Positions camera in an alternative diagonal view position.
 * 
 * @param mini Pointer to main program structure.
 */
void	set_camera_another_view(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){-15, -10, -15};
	orientation = (t_vector){0.577f, 0.577f, 0.577f};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

/**
 * @brief Sets camera to isometric view preset.
 * 
 * Positions camera in standard isometric (3/4) view.
 * 
 * @param mini Pointer to main program structure.
 */
void	set_camera_isometric(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){-15, 15, -15};
	orientation = (t_vector){0.577f, -0.577f, 0.577f};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}

/**
 * @brief Sets camera to alternate isometric view preset.
 * 
 * Positions camera in alternate diagonal position for 3/4 view.
 * 
 * @param mini Pointer to main program structure.
 */
void	set_camera_alt_isometric(t_rt *mini)
{
	t_vector	pos;
	t_vector	orientation;

	pos = (t_vector){15, 15, -15};
	orientation = (t_vector){-0.577f, -0.577f, 0.577f};
	mini->camera = create_preset_camera(pos, orientation);
	mini->render_quality = 1;
	render_scene(mini);
}
