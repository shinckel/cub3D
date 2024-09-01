# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/16 17:13:54 by shinckel          #+#    #+#              #
#    Updated: 2024/06/16 17:33:46 by shinckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

BONUS = $(wildcard bonus/*.c)
BONUS_OBJ = $(BONUS:.c=.o)

CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -Iheader -g
#CFLAGS += -fsanitize=address

# Define colors
RED := \033[1;30;41m
GREEN := \033[1;30;42m
RESET := \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "$(GREEN) GNL compiled $(RESET)"

bonus: $(OBJ) $(BONUS_OBJ)
	@ar rc $(NAME) $(OBJ) $(BONUS_OBJ)
	@echo "$(GREEN) GNL & bonus compiled $(RESET)"

clean:

fclean: clean
	@$(RM) $(OBJ) $(BONUS_OBJ) $(NAME)
	@echo "$(RED) Remove objects & $(NAME) $(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
