# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 15:26:29 by wweerasi          #+#    #+#              #
#    Updated: 2025/01/21 20:03:43 by wweerasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

DIR_LIBFT 	= ./lib/libft
DIR_SRC		= ./src
DIR_SRC_BONUS	= ./src_bonus
DIR_OBJ		= $(DIR_SRC)/objects
DIR_OBJ_BONUS	= $(DIR_SRC_BONUS)/objects_bonus
DIR_INC		= ./includes
HEADERS		= $(DIR_INC)/pipex.h
HEADERS_BONUS	= $(DIR_INC)/pipex_bonus.h

SOURCES = pipex_main.c \
	  pipex.c \
	  pipex_init.c \
	  pipex_cmd.c \
	  pipex_exit.c \

SOURCES_BONUS = pipex_main_bonus.c \
		pipex_bonus.c \
	       	pipex_init_bonus.c \
		pipex_cmd_bonus.c \
		pipex_exit_bonus.c \

OBJECTS		= $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
OBJECTS_BONUS 	= $(addprefix $(DIR_OBJ_BONUS)/,$(SOURCES_BONUS:.c=.o))

LIBFT_FLAGS	= -L $(DIR_LIBFT) -lft

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -rf

all: libft $(NAME)
bonus: libft .bonus

libft:
	@make -C $(DIR_LIBFT)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT_FLAGS) -o $@

.bonus: $(OBJECTS_BONUS)
	$(CC) $(OBJECTS_BONUS) $(LIBFT_FLAGS) -o $(NAME)_bonus
	@touch .bonus

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS) | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ_BONUS)/%.o: $(DIR_SRC_BONUS)/%.c $(HEADERS_BONUS) | $(DIR_OBJ_BONUS)
	@$(CC) $(CFLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ_BONUS):
	@mkdir -p $(DIR_OBJ_BONUS)

clean:
	@$(RM) $(DIR_OBJ)
	@$(RM) $(DIR_OBJ_BONUS)
	@make -C $(DIR_LIBFT) clean

fclean: clean
	$(RM) .bonus
	@$(RM) $(NAME)
	@$(RM) $(NAME)_bonus
	@make -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all bonus libft clean fclean re
