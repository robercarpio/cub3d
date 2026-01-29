NAME = cub3D

# ================= COLORS ================= #
DEF_COLOR =		\033[0;39m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BRIGHT_GREEN =	\033[1;92m

# ================= SOURCES ================= #
SRCS =		main.c \
			./src/play.c \
			./src/parse/parse.c \
			./src/parse/checker_chars.c \
			./src/parse/cub_file.c \
			./src/gnl/get_next_line.c \
			./src/gnl/get_next_line_utils.c \
			./src/inputs/inputs.c \
			./src/aux/map_dimmenssions.c \
			./src/aux/file_to_arr.c \
			./src/aux/allocate_map.c \
			./src/process_map/process_map.c \
			./src/process_map/init_map.c \
			./src/movement/minimap.c \
			./src/movement/player.c \
			./src/parse/expand_map.c \

INCLUD = ./inc/cube.h

# ================= COMPILER ================= #
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -MMD -I./inc -I./src/Libft -I./mlx

# ================= LIBRARIES ================= #
LIB = -L./mlx -lmlx -lXext -lX11 -lm -L./src/Libft -lft

# ================= OBJECTS ================= #
OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

# ================= RULES ================= #
.c.o:
	@${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

-include ${DEPS}

${NAME}: ${OBJS}
	@echo "\n${BRIGHT_GREEN}Compiling libft ✓${DEF_COLOR}"
	@make -C ./src/Libft --no-print-directory > /dev/null

	@echo "\n${BRIGHT_GREEN}Compiling MiniLibX ✓${DEF_COLOR}"
	@make -C ./mlx --no-print-directory > /dev/null 2>&1

	@${CC} ${OBJS} ${LIB} -o ${NAME} -no-pie
	@echo "\n${BRIGHT_GREEN}Created ${NAME} ✓${DEF_COLOR}\n"


clean:
	@make -C ./mlx clean --no-print-directory > /dev/null
	@make -C ./src/Libft clean --no-print-directory > /dev/null
	@${RM} ${OBJS} ${DEPS}
	@echo "\n${BRIGHT_GREEN}Objects cleaned ✓${DEF_COLOR}\n"

fclean: clean
	@make -C ./src/Libft fclean --no-print-directory > /dev/null
	@${RM} ${NAME}
	@echo "\n${BRIGHT_GREEN}Executable cleaned ✓${DEF_COLOR}\n"


re: fclean all

.PHONY: all clean fclean re
