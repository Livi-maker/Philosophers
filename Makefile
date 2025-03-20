# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 19:54:33 by ldei-sva          #+#    #+#              #
#    Updated: 2025/03/20 20:00:40 by ldei-sva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = death.c free.c ft_atoi.c initializer.c philo.c routine.c time.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Werror -Wall -Wextra

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
