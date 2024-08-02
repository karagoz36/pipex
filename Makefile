# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 11:39:57 by tkaragoz          #+#    #+#              #
#    Updated: 2024/06/28 16:24:54 by tkaragoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = libft
LIBFT_TARGET = ${LIBFT}/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I${LIBFT} -g
LDFLAGS = -L${LIBFT} -lft

SRC_FILES = pipex.c utils.c utils2.c
BNS_SRC_FILES = utils.c utils2.c pipex_bonus.c here_doc_bonus.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS = $(SRC_FILES)
BNS_SRCS = $(BNS_SRC_FILES)

OBJS = $(SRCS:.c=.o)
BNS_OBJS = $(BNS_SRCS:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_TARGET)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

all: $(NAME)

$(LIBFT_TARGET):
	make -C $(LIBFT)

bonus: $(BNS_OBJS) $(LIBFT_TARGET)
	$(CC) $(CFLAGS) $(BNS_OBJS) $(LDFLAGS) -o $(NAME)
clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS) $(BNS_OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re