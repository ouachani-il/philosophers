# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 12:26:07 by ilouacha          #+#    #+#              #
#    Updated: 2024/02/02 22:45:06 by ilouacha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

SRC=		main.c\
			init.c\
			routine.c\
			actions.c\
			utils.c\
			utils2.c\
			

CC= cc -g3

OBJ_DIR= obj

CFLAGS= -Wall -Werror -Wextra

OBJ=	$(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

RM=	rm -rf

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -fsanitize=thread $(OBJ) -o $(NAME) #TSAN_OPTIONS=second_deadlock_stack=1
#			$(CC) $(OBJ) -o $(NAME)

clean:		
		$(RM) $(OBJ)
		$(RM) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
