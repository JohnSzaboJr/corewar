# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 22:06:52 by yabdulha          #+#    #+#              #
#    Updated: 2018/08/17 16:23:28 by jszabo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra
FILES = ft_putchar ft_putstr ft_strcmp ft_strlen ft_strdup ft_strcpy ft_strcat \
		ft_strncat ft_strlcat ft_strstr ft_strncmp ft_atoi ft_toupper \
		ft_tolower ft_putnbr ft_isalpha ft_isdigit ft_isprint ft_itoa \
		ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove ft_memchr \
		ft_memcmp ft_strncpy ft_strchr ft_strrchr ft_strnstr ft_isalnum \
		ft_isascii ft_memalloc ft_memdel ft_strnew ft_strdel ft_strclr \
		ft_striter ft_striteri ft_strmap ft_strmapi ft_strequ ft_strnequ \
		ft_strsub ft_strjoin ft_strtrim ft_strsplit ft_putendl ft_putchar_fd \
		ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_lstnew ft_lstdelone \
		ft_lstdel ft_lstadd ft_lstiter ft_lstmap ft_strndup ft_strndup_len \
		ft_strrev ft_absolute ft_print_array ft_sqrt ft_power ft_isspace \
		ft_atoi_l ft_isnumber
FT_C =	$(patsubst %,%.c,$(FILES))
OBJ  =	$(patsubst %,%.o,$(FILES))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ):
	$(CC) $(FLAGS) -c $(FT_C)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
