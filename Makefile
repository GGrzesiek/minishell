NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = \
	main.c \
	file_manager.c \
	mem_utils.c \
	executor.c \
	init.c \
	signals.c \
	utils.c

OBJS = $(SRCS:.c=.o)
OBJ_PATHS = $(addprefix $(OBJS_DIR)/, $(OBJS))
OBJS_DIR = ./objs

LIB_DIR = libft

all: compile $(NAME)

compile: mkdirs $(OBJS)

mkdirs:
	mkdir -p $(OBJS_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I./$(LIB_DIR) -c $< -o $(OBJS_DIR)/$@ 

$(NAME): lib_make
	$(CC) $(CFLAGS) $(OBJ_PATHS) $(LIB_DIR)/libft.a -o $(NAME) -lbsd -lreadline

test: 
	./$(NAME)

run: re test

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

lib_make:
	make bonus -C $(LIB_DIR) > /dev/null 2>&1

.PHONY: all clean fclean re test lib_make
