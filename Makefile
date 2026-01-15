NAME = cub3D

DEF_COLOR =		\033[0;39m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BRIGHT_GREEN =	\033[1;92m

SRCS = ./src/main.c

INCLUD = ./inc/cube.h

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -MMD -I./inc -I./src/Libft
LIB = -L. -lmlx -lXext -lX11 -lm -L./src/Libft -lft

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

OBJS = ${SRCS:.c=.o}
DEPS = $(addsuffix .d, $(basename $(SRCS)))

all: ${NAME}

-include $(DEPS)
${NAME}: ${OBJS}
	@echo "\n${BRIGHT_GREEN}Compiling libft ✓$(DEF_COLOR)"
	@make -C ./src/Libft > /dev/null
	@echo "\n${BRIGHT_GREEN}Minilibx compilation ✓$(DEF_COLOR)\n"
	@make -C ./mlx all > /dev/null 2>&1
	@cp ./mlx/libmlx.a .
	@${CC} ${OBJS} $(LIB) -o $(NAME) -no-pie
	@echo "$(BRIGHT_GREEN)Created ${NAME} ✓$(DEF_COLOR)\n"


clean:
	@make -C ./mlx clean --no-print-directory > /dev/null
	@make -C ./src/Libft clean --no-print-directory > /dev/null
	@${RM} ${OBJS} ${DEPS}
	@echo "\n$(BRIGHT_GREEN)All objects cleaned successfully $(DEF_COLOR)\n"

fclean:
	@make -C ./mlx clean --no-print-directory > /dev/null
	@make -C ./src/Libft fclean --no-print-directory > /dev/null
	@${RM} ${OBJS} ${DEPS} ${NAME}  libmlx.a
	@echo "\n$(BRIGHT_GREEN)All objects and executable cleaned successfully $(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re