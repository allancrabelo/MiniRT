#include "minirt.h"

#define xWHITE 0xFFFFFF
#define xYELLOW 0xFFFF00
#define xCYAN 0x00FFFF

static void	draw_text_line(t_rt *mini, int y, char *text, int color)
{
	mlx_string_put(mini->mlx_ptr, mini->win_ptr, 30, y, color, text);
}

static void	draw_camera_overlay(t_rt *mini)
{
	draw_text_line(mini, 280, "NUMPAD - PRESET CAMERAS:", xCYAN);
	draw_text_line(mini, 300, "  1          - Front view", xWHITE);
	draw_text_line(mini, 320, "  2          - Front-bottom view", xWHITE);
	draw_text_line(mini, 340, "  3          - Right side view", xWHITE);
	draw_text_line(mini, 360, "  4          - Left side view", xWHITE);
	draw_text_line(mini, 380, "  5          - Top view", xWHITE);
	draw_text_line(mini, 400, "  6          - Back view", xWHITE);
	draw_text_line(mini, 420, "  7          - Isometric view", xWHITE);
	draw_text_line(mini, 440, "  8          - Alt isometric view", xWHITE);
	draw_text_line(mini, 470, "OTHER FUNCTIONS:", xCYAN);
	draw_text_line(mini, 490, "  R          - Reset camera to initial position",
		xWHITE);
	draw_text_line(mini, 510, "  Q          - High quality render", xWHITE);
	draw_text_line(mini, 530, "  TAB        - Show/Hide this help", xWHITE);
	draw_text_line(mini, 550, "  ESC        - Exit program", xWHITE);
}

void	draw_help_overlay(t_rt *mini)
{
	if (!mini->show_help)
		return ;
	draw_text_line(mini, 30, "===== MINIRT - CONTROLS =====", xYELLOW);
	draw_text_line(mini, 60, "CAMERA MOVEMENT:", xCYAN);
	draw_text_line(mini, 80, "  W          - Move forward", xWHITE);
	draw_text_line(mini, 100, "  S          - Move backward", xWHITE);
	draw_text_line(mini, 120, "  A          - Strafe left (lateral)", xWHITE);
	draw_text_line(mini, 140, "  D          - Strafe right (lateral)", xWHITE);
	draw_text_line(mini, 170, "ARROW KEYS:", xCYAN);
	draw_text_line(mini, 190, "  Arrow UP   - Move up (vertical)", xWHITE);
	draw_text_line(mini, 210, "  Arrow DOWN - Move down (vertical)", xWHITE);
	draw_text_line(mini, 230, "  Arrow LEFT - Rotate camera left", xWHITE);
	draw_text_line(mini, 250, "  Arrow RIGHT- Rotate camera right", xWHITE);
	draw_camera_overlay(mini);
}

void	toggle_controls_help(t_rt *mini)
{
	mini->show_help = !mini->show_help;
	if (mini->show_help)
		draw_help_overlay(mini);
	else
	{
		mlx_put_image_to_window(mini->mlx_ptr, mini->win_ptr,
			mini->img.mlx_img, 0, 0);
	}
}
