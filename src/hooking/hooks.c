#include "minirt.h"

int	key_hook(int keysym, t_rt *mini)
{
	if (keysym == XK_Escape)
		ft_err_handler(mini, -1);
	return (0);
}

int	close_hook(t_rt *mini)
{
	return (ft_err_handler(mini, -1));
}