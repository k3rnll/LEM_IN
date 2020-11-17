# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clouise <clouise@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 00:34:02 by clouise           #+#    #+#              #
#    Updated: 2020/10/31 00:38:40 by clouise          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBR = -L$(LIB_DIR) -lft
INCL = -I$(HDR_DIR) -I$(LIB_HDR)

LIB = $(LIB_DIR)libft.a
LIB_DIR = ./libft/
LIB_HDR = $(LIB_DIR)

HDR_DIR = ./include/
HDR_LIST =	lem_in.h
HDR = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRC_DIR = ./src/
SRC_LIST = 	bfs.c\
		    flow_helper.c\
		    logic.c\
		    memory.c\
		    print.c\
		    reader.c\
		    routes.c\
		    smart_atoi.c\
			temp_func.c\

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY: all clean fclean re

all: $(NAME) $(NAME2)

$(NAME): $(LIB) $(OBJ_DIR) $(OBJ) $(OBJ_DIR)main.o
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(OBJ_DIR)main.o $(LIBR)
	@echo $@ Done

$(OBJ_DIR)main.o: $(SRC_DIR)main.c $(HDR)
	@$(CC) $(FLAGS) $(INCL) -o $@ -c $<
	@echo OBJECT: $@ updated

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo OBJECT_DIRECTORY is created

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDR)
	@$(CC) $(FLAGS) $(INCL) -o $@ -c $<
	@echo OBJECT: $@ updated

$(LIB):
	@$(MAKE) -C $(LIB_DIR)
	@echo libft Done

clean:
	@$(MAKE) -C $(LIB_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo clean Done

fclean: clean
	@rm -f $(LIB)
	@rm -f $(NAME) $(NAME2)
	@echo fclean Done

re:
	@$(MAKE) fclean
	@$(MAKE) all