# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 12:26:07 by ilouacha          #+#    #+#              #
#    Updated: 2023/12/22 20:52:53 by ilouacha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo_bonus

SRC=		main.c\
			init.c\
			routine.c\
			actions.c\
			destroy_free.c\
			utils.c\
			

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
			$(CC) $(OBJ) -o $(NAME)

clean:		
		$(RM) $(OBJ)
		$(RM) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
