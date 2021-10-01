# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 15:29:21 by lruncorn          #+#    #+#              #
#    Updated: 2021/08/15 20:04:48 by lruncorn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c	ft_isalpha.c	ft_isprint.c \
  	  ft_memcmp.c	ft_memset.c	ft_strlcat.c \
  	  ft_strncmp.c	ft_tolower.c ft_calloc.c\
	  ft_bzero.c	ft_isascii.c	ft_memccpy.c \
  	  ft_memcpy.c	ft_putchar_fd.c	ft_strlcpy.c \
  	  ft_strnstr.c	ft_toupper.c ft_isalnum.c \
  	  ft_isdigit.c	ft_memchr.c	ft_memmove.c \
	  ft_strchr.c	ft_strlen.c	ft_strrchr.c \
	  ft_strdup.c ft_putendl_fd.c ft_putstr_fd.c\
	  ft_itoa.c ft_putnbr_fd.c ft_substr.c\
	  ft_strjoin.c ft_strtrim.c ft_strmapi.c\
	  ft_split.c get_next_line.c ft_strnew.c

BNS = ft_lstnew.c ft_lstsize.c ft_lstadd_front.c \
	  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	  ft_lstclear.c ft_lstiter.c ft_lstmap.c

HDR = libft.h

BNSO = $(BNS:.c=.o)

OBJS = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -c

all: $(NAME)

$(NAME):	$(OBJS)	
	ar rc $(NAME) $(OBJS)

bonus:  $(OBJS) $(BNSO)
	ar rc $(NAME) $(OBJS) $(BNSO)

norm: 
	norminette $(SRC) $(HDR) $(BNS) 

clean:
	rm -rf *.o

fclean: clean
	rm -rf ${NAME}

re: fclean all

