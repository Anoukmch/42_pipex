# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 15:11:48 by amechain          #+#    #+#              #
#    Updated: 2022/10/10 17:37:37 by amechain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME =  pipex

BONUS = pipex_bonus

M_SRC = pipex.c \
        free_error.c \
        get_command.c \
        initialize.c \
        processes.c \
		utils.c

B_SRC = pipex_bonus.c \
		free_error_bonus.c \
		get_command_bonus.c \
		initialize_bonus.c \
		processes_bonus.c \
		utils_bonus.c

M_SRCS = $(addprefix ./m_pipex/, $(M_SRC))

B_SRCS = $(addprefix ./b_pipex/, $(B_SRC))

M_OBJS = $(M_SRCS:.c=.o)

B_OBJS = $(B_SRCS:.c=.o)

LIBS_DIR = ./includes/libs

LIBS_NAME = libs.a

all: $(NAME)

bonus : $(BONUS)

$(NAME): $(M_OBJS) $(LIBS_DIR)/$(LIBS_NAME)
	$(CC) $(CFLAGS) $^ -o $@

$(BONUS): $(B_OBJS) $(LIBS_DIR)/$(LIBS_NAME)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBS_DIR)/$(LIBS_NAME):
	make -sC $(LIBS_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBS_DIR)
	@rm -f $(M_OBJS) $(B_OBJS)

fclean: clean
	make fclean -C $(LIBS_DIR)
	@rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re
