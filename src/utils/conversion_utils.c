#include "minirt.h"

/**
 * @brief Converts string to clamped color value (0-255).
 * 
 * @param str String containing integer value.
 * @return int Clamped color value between 0 and 255.
 */
int	ft_atoc(char *str)
{
	int	c;

	c = ft_atoi(str);
	if (c < 0)
		return (0);
	if (c > 255)
		return (255);
	return (c);
}

/**
 * @brief Converts string to floating point number.
 * 
 * Supports negative numbers and decimal points.
 * 
 * @param str String to convert (e.g., "3.14", "-2.5").
 * @return float Converted floating point value.
 */
float	ft_atof(char *str)
{
	float	sum;
	float	prec;
	float	div;
	float	sign;

	prec = 0.0;
	div = 1.0;
	sign = 1.0;
	if (str && str[0] == '-')
		sign *= -1.0;
	sum = (float)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str++ == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			div *= 10.0;
			prec += (*str - '0') / div;
			str++;
		}
		sum += prec * sign;
	}
	return (sum);
}
