#include "minirt.h"

static void	draw_text_line(t_rt *mini, int y, char *text, int color)
{
	mlx_string_put(mini->mlx_ptr, mini->win_ptr, 30, y, color, text);
}

void	draw_help_overlay(t_rt *mini)
{
	int	white;
	int	yellow;
	int	cyan;

	if (!mini->show_help)
		return ;
	white = 0xFFFFFF;
	yellow = 0xFFFF00;
	cyan = 0x00FFFF;
	draw_text_line(mini, 30, "===== MINIRT - CONTROLS =====", yellow);
	draw_text_line(mini, 60, "CAMERA MOVEMENT:", cyan);
	draw_text_line(mini, 80, "  W          - Move forward", white);
	draw_text_line(mini, 100, "  S          - Move backward", white);
	draw_text_line(mini, 120, "  A          - Strafe left (lateral)", white); 
	draw_text_line(mini, 140, "  D          - Strafe right (lateral)", white); 
	draw_text_line(mini, 170, "ARROW KEYS:", cyan);
	draw_text_line(mini, 190, "  Arrow UP   - Move up (vertical)", white);
	draw_text_line(mini, 210, "  Arrow DOWN - Move down (vertical)", white);
	draw_text_line(mini, 230, "  Arrow LEFT - Rotate camera left", white);
	draw_text_line(mini, 250, "  Arrow RIGHT- Rotate camera right", white);
	draw_text_line(mini, 280, "NUMPAD - PRESET CAMERAS:", cyan);
	draw_text_line(mini, 300, "  1          - Front view", white);
	draw_text_line(mini, 320, "  2          - Front-bottom view", white);
	draw_text_line(mini, 340, "  3          - Right side view", white);
	draw_text_line(mini, 360, "  4          - Left side view", white);
	draw_text_line(mini, 380, "  5          - Top view", white);
	draw_text_line(mini, 400, "  6          - Back view", white);
	draw_text_line(mini, 420, "  7          - Isometric view", white);
	draw_text_line(mini, 440, "  8          - Alt isometric view", white);
	draw_text_line(mini, 470, "OTHER FUNCTIONS:", cyan);
	draw_text_line(mini, 490, "  R          - Reset camera to initial position", white);
	draw_text_line(mini, 510, "  Q          - High quality render", white);
	draw_text_line(mini, 530, "  TAB        - Show/Hide this help", white);
	draw_text_line(mini, 550, "  ESC        - Exit program", white);
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
