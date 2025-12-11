NAME		:= minirt
CC			:= cc
RM			:= rm -f

CFLAGS		:= -Wall -Wextra -Werror

HEADDIR		:= ./includes/
HEADLIST	:= minirt.h
HEADERS		:= $(addprefix ${HEADDIR}, ${HEADLIST})

VPATH		:=	src \
				src/camera \
				src/error \
				src/extra \
				src/garbage_collector \
				src/hooking \
				src/light \
				src/objects \
				src/parsing \
				src/rendering \
				src/utils \

SRCSLIST	:=	main \
				camera \
				error_handler \
				errors \
				garbage_collector \
				hooks \
				key_hooks \
				light \
				objects \
				element_parser \
				file_parser \
				parser \
				scene_parser \
				shapes_parser \
				vector_parser \
				render \
				intersect \
				intersect_cylinder \
				ray_trace \
				array_utils \
				color_utils \
				color_ops \
				conversion_utils \
				type_utils \
				vector_utils \
				vector_math \
				vector_math2 \
				controls_help \
				camera_presets \
				camera_presets_especials \
				numpad_handler \

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

download:
	@if [ ! -d "$(MLX_DIR)/.git" ]; then \
		git submodule update --init --recursive; \
		printf "${YELLOW}MLX submodule initialized ...${RESET}\n"; \
	fi


clean:
	@echo ""
	@echo "${RED}Deleting object files ...${RESET}"
	@${RM} -r ${OBJSDIR}
	@make -C ${LIBFTDIR} clean --no-print-directory --quiet
	@make -C ${MLX_DIR} clean --no-print-directory --quiet

fclean: clean
	@if [ -f ${NAME} ]; then \
		echo "${RED}Deleting ${NAME} ...${RESET}"; \
		${RM} ${NAME}; \
	fi
	@make -C ${LIBFTDIR} fclean --no-print-directory --quiet

re: fclean all

run: ${NAME}
	./${NAME}

.PHONY: all clean fclean re run download
