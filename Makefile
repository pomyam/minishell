NAME = minishell

PATHLIB = src/libft

SRC = 	src/error_manage/errors.c src/exec/exec.c src/exec/start_exec.c src/signal.c\
		src/parser/extend_str.c src/parser/make_commands.c src/parser/parce_line.c src/builtin/utils.c \
		src/parser/parce_redir.c src/parser/parse_execs.c src/parser/split_mask.c src/builtin/ft_export_print.c\
		src/utils/add_to_array.c src/utils/env_utils.c src/utils/utils.c src/builtin/ft_export_utils.c\
		src/main.c src/builtin/builtin.c src/builtin/ft_cd.c src/builtin/ft_echo.c src/builtin/ft_export_sets.c\
		src/builtin/ft_env.c src/builtin/ft_exit.c src/builtin/ft_export.c src/builtin/ft_unset.c \
		src/utils/init.c src/exec/exec_cmd.c src/exec/handle_redirect.c \
		src/utils/free_func.c

LIBSRC = $(PATHLIB)/*.c

OBJS = $(SRC:.c=.o)

CC = gcc

MAKE = make
CFLAGS = -Wall -Werror -Wextra
READLINE_FLAGS = -lreadline -L/usr/include/ \
	-L/Users/lruncorn/.brew/Cellar/readline/8.1/lib/ -I/Users/lruncorn/.brew/Cellar/readline/8.1/include

HDR = includes/minishell.h src/libft/libft.h 


.c.o: $(HDR)
		$(CC) $(CFLAGS) -c -I$(INC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)	
	make bonus -C src/libft
	cp src/libft/libft.a libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(READLINE_FLAGS) $(OBJS) libft.a

debug:
	make bonus -C src/libft
	cp src/libft/libft.a libft.a
	$(CC) -o $(NAME) -g $(READLINE_FLAGS) $(SRC) libft.a
norm: 
	make norm -C src/libft
	norminette $(SRC) $(HDR) 

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(PATHLIB)
	

fclean: clean
	@rm -f ${NAME}
	@$(MAKE) fclean -C $(PATHLIB)
	@rm libft.a

re: fclean all

.PHONY: all clean fclean re 
