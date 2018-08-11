# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/03 15:42:03 by tdiaz             #+#    #+#              #
#    Updated: 2018/08/03 15:46:34 by tdiaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CC = @gcc

FLAGS = -Wall -Wextra -Werror -o $(NAME)

SRC = main.c md5/md5_rounds.c md5/md5_prmtvs.c md5/md5_bitset.c md5/md5_phase.c \
		md5/md5_dispatch.c

OBJ = $(SRC:.c=.o)

PRINTDIR = printf

PRINT = $(PRINTDIR)/libftprintf.a 

$(NAME): $(OBJ) $(PRINT)
	$(CC) $(FLAGS) $(OBJ) $(PRINT)

$(PRINT):
	@cd $(PRINTDIR) && make

.PHONY: clean fclean all re debug

debug: $(OBJ) $(PRINT)
	$(CC) -o debugger -g $(SRC) $(PRINT)

clean:
	@rm -f $(OBJ)
	@cd	$(PRINTDIR) && make clean 

fclean: clean
	@rm -f $(NAME)
	@cd $(PRINTDIR) && make fclean

all: $(NAME)

re: fclean all