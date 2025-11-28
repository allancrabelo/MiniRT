#ifndef COLORS_H
# define COLORS_H

									//CHANGE BINARY NAME WHEN PROJECT IS DONE!!!!
// Basic Colors
# define BLACK			"\033[0;30m"
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define MAGENTA		"\033[0;35m"
# define CYAN			"\033[0;36m"
# define WHITE			"\033[0;37m"

// Bright Colors
# define BBLACK			"\033[1;30m"
# define BRED			"\033[1;31m"
# define BGREEN			"\033[1;32m"
# define BYELLOW		"\033[1;33m"
# define BBLUE			"\033[1;34m"
# define BMAGENTA		"\033[1;35m"
# define BCYAN			"\033[1;36m"
# define BWHITE			"\033[1;37m"

// Background Colors
# define ON_BLACK		"\033[40m"
# define ON_RED			"\033[41m"
# define ON_GREEN		"\033[42m"
# define ON_YELLOW		"\033[43m"
# define ON_BLUE		"\033[44m"
# define ON_MAGENTA		"\033[45m"
# define ON_CYAN		"\033[46m"
# define ON_WHITE		"\033[47m"

// Bright Background Colors
# define ON_BBLACK		"\033[0;100m"
# define ON_BRED		"\033[0;101m"
# define ON_BGREEN		"\033[0;102m"
# define ON_BYELLOW		"\033[0;103m"
# define ON_BBLUE		"\033[0;104m"
# define ON_BMAGENTA	"\033[0;105m"
# define ON_BCYAN		"\033[0;106m"
# define ON_BWHITE		"\033[0;107m"

// Text Effects
# define RESET			"\033[0m"
# define BOLD			"\033[1m"
# define DIM			"\033[2m"
# define UNDERLINE		"\033[4m"
# define BLINK			"\033[5m"
# define INVERT			"\033[7m"
# define HIDDEN			"\033[8m"

#endif