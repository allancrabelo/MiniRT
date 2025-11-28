NAME		:= rt#CHANGE
CC			:= cc
RM			:= rm -f

CFLAGS		:= -Wall -Wextra -Werror
DEBUGFLAGS	:= -g

HEADDIR		:= ./includes/
HEADLIST	:= minirt.h
HEADERS		:= $(addprefix ${HEADDIR}, ${HEADLIST})

VPATH		:=	src \

SRCSLIST	:=	main \
				garbage_collector \
				error_handler \

SRCS		:= $(addsuffix .c, ${SRCSLIST})

OBJSDIR		:= ./obj/
OBJS		:= ${SRCS:%.c=${OBJSDIR}%.o}

LIBFTDIR	:= ./libft/
LIBFT		:= ${LIBFTDIR}libft.a
MLX_DIR		:= ./minilibx/
MLX_LIB		:= ${MLX_DIR}libmlx.a

YELLOW		:= \033[33m
RED			:= \033[91m
RESET		:= \033[0m

# ============================
# Default build
# ============================

all: download ${NAME}

${NAME}: ${OBJS} ${LIBFT} ${MLX_LIB}
	@echo ""
	@echo "${YELLOW}Linking ${NAME} ...${RESET}"
	${CC} ${CFLAGS} ${DEBUGFLAGS} ${OBJS} ${LIBFT} ${MLX_LIB} \
		-L${MLX_DIR} -L${LIBFTDIR} -I${HEADDIR} \
		-lXext -lX11 -lm -o ${NAME}
	@echo ""
	@echo "${YELLOW}${NAME} Ready to use${RESET}"

${OBJSDIR}%.o: %.c ${HEADERS}
	@echo "${YELLOW}Compiling $< ...${RESET}"
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -I${HEADDIR} ${DEBUGFLAGS} -c $< -o $@

${LIBFT}:
	@echo "${YELLOW}Compiling libft ...${RESET}"
	@make -C ${LIBFTDIR} --no-print-directory

${MLX_LIB}:
	@echo "${YELLOW}Compiling MiniLibX ...${RESET}"
	@make -C ${MLX_DIR} --no-print-directory

clean:
	@echo ""
	@if [ -d ${OBJSDIR} ]; then \
		echo "${RED}Deleting object files ...${RESET}"; \
		${RM} -r ${OBJSDIR}; \
	fi
	@make -C ${LIBFTDIR} clean --no-print-directory --quiet
	@make -C ${MLX_DIR} clean --no-print-directory --quiet

fclean: clean
	@echo ""
	@if [ -f ${NAME} ]; then \
		echo "${RED}Deleting ${NAME} ...${RESET}"; \
		${RM} ${NAME}; \
	fi
	@make -C ${LIBFTDIR} fclean --no-print-directory --quiet

re: fclean all

download:
	@if [ ! -d "$(MLX_DIR)/.git" ]; then \
		git submodule update --init --recursive; \
		printf "${YELLOW}MLX submodule initialized ...${RESET}\n"; \
	fi

# ============================
# Extra targets
# ============================

run: ${NAME}
	./${NAME}

.PHONY: all clean fclean re run download
