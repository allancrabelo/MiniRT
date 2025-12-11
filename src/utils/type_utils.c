#include "minirt.h"

/**
 * @brief Checks if string contains only digits (unsigned long).
 * 
 * @param str String to validate.
 * @return int FAILURE if all characters are digits, SUCCESS otherwise.
 */
int	is_ulong(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

/**
 * @brief Checks if string is a valid floating point number.
 * 
 * Allows digits, minus sign, and decimal point.
 * 
 * @param str String to validate.
 * @return int FAILURE if valid float format, SUCCESS otherwise.
 */
int	is_float(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) != 1 && str[i] != '-' && str[i] != '.')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

/**
 * @brief Parses and validates a float from string.
 * 
 * @param str String containing float value.
 * @param num Pointer to store parsed value.
 * @return int SUCCESS if valid float parsed, FAILURE otherwise.
 */
int	float_parser(char *str, float *num)
{
	if (!is_float(str))
		return (EXIT_FAILURE);
	*num = ft_atof(str);
	return (EXIT_SUCCESS);
}

/**
 * @brief Parses and validates an unsigned long from string.
 * 
 * @param str String containing unsigned integer.
 * @param num Pointer to store parsed value.
 * @return int SUCCESS if valid ulong parsed, FAILURE otherwise.
 */
int	ulong_parser(char *str, size_t *num)
{
	if (!is_ulong(str))
		return (EXIT_FAILURE);
	*num = (size_t)ft_atoi(str);
	return (EXIT_SUCCESS);
}
