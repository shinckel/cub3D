# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinckel <shinckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 13:20:29 by shinckel          #+#    #+#              #
#    Updated: 2024/09/01 17:20:47 by shinckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=					cub3D

MSG =						make.msg

CC :=						gcc

INC_DIR :=			./header

CFLAGS :=				-Wall -Wextra -Werror -I$(INC_DIR) -g

CFLAGS +=				-I/opt/X11/include

# CFLAGS +=				-fsanitize=address

MLXFLAGS =			-L ./minilibx-linux -lm -Ilmlx -lXext -lX11

MLXFLAGS +=			-L/usr/X11/lib -L/opt/X11/lib

SRC_DIR :=			./src

SRC_DIR2 :=			./src/raycasting

OBJ_DIR :=			./obj

GNL_DIR :=			./get_next_line

LIBFT_DIR :=		./libft

MINILIBX_DIR :=	./minilibx-linux

SRC :=					$(wildcard $(SRC_DIR)/*.c)

OBJ :=					$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GNL :=					$(GNL_DIR)/get_next_line.a

LIBFT :=				$(LIBFT_DIR)/libft.a

MINILIBX :=			$(MINILIBX_DIR)/libmlx_Linux.a

RED :=					\033[1;30;41m

YELLOW :=				\033[1;30;103m

GREEN :=				\033[1;30;42m

RESET :=				\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(GNL_DIR)
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@$(MAKE) -C $(MINILIBX_DIR)
	@echo "$(YELLOW) MiniLibX compiled $(RESET)"
	@$(CC) $(OBJ) $(GNL) $(LIBFT) $(MINILIBX) $(CFLAGS) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN) Ready to CUB3D!!! $(RESET)"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(MLXFLAGS) -c $< -o $@

# Norminette check
norm:
	norminette -R CheckForbiddenSourceHeader $(SRC)
	norminette -R CheckDefine $(INC_DIR)/cub3d.h

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean
	@echo "$(RED) Remove objects $(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean
	@echo "$(RED) Remove objects & $(NAME) $(RESET)"

info:
	@make -f $(MSG) msgcub --no-print-directory

re: fclean all info

.PHONY: all clean fclean re norm