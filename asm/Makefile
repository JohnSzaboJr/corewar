# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 19:09:41 by jszabo            #+#    #+#              #
#    Updated: 2018/07/28 14:33:29 by jszabo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

GCC_FLAGS = -Werror -Wextra -Wall

OBJS_DIR = objs
SRCS_DIR = srcs
SRCS_INCLUDES_DIR = includes

LIBFT_DIR = ../libft
LIBFT_FILE = $(LIBFT_DIR)/libft.a

SHARED_DIR = ../shared
SHARED_INCLUDES_DIR = $(SHARED_DIR)/includes

INCLUDE_DIRS = -I $(SRCS_INCLUDES_DIR) -I $(SHARED_INCLUDES_DIR)

INCLUDES_FILES = as_errors asm_prot asm_struct colors
HEADERS = $(addsuffix .h, $(patsubst %, $(SRCS_INCLUDES_DIR)/%, $(INCLUDES_FILES)))
HEADERS += $(SHARED_INCLUDES_DIR)/op.h
HEADERS += $(SHARED_INCLUDES_DIR)/libft.h

FILES = as_d_error as_d_param \
as_error_check as_error_check2 as_error_check3 \
as_error_print as_error_print2 as_error_print3 as_error_print4 as_error_print5 \
as_error_tracking as_error_tracking2 \
as_error as_error2 as_error3 as_error4\
as_free as_i_error as_i_param as_init \
as_output as_output2 as_output3 \
as_param \
as_parse as_parse2 as_parse3 \
as_r_error \
as_skip as_skip2 \
as_store as_store2 as_store3 \
as_utility as_utility2 \
asm op

OBJS_WITH_DIR = $(patsubst %, $(OBJS_DIR)/%.o, $(FILES))

GREEN_COLOR = "\033[0;32m"
DEFAULT_COLOR = "\033[0m"

all: $(NAME)

norm:
	@norminette $(SRCS_INCLUDES_DIR) $(SRCS_DIR)

$(LIBFT_FILE):
	@echo "Libft:" $(GREEN_COLOR) Compiling Libft $(DEFAULT_COLOR)
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_FILE) $(HEADERS) $(OBJS_DIR) $(OBJS_WITH_DIR)
	@echo "asm:" $(GREEN_COLOR) $(NAME) $(DEFAULT_COLOR)
	@cc $(GCC_FLAGS) $(OBJS_WITH_DIR) -o $(NAME) $(LIBFT_FILE) $(INCLUDE_DIRS)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "asm:" $(GREEN_COLOR) $< $(DEFAULT_COLOR)
	@cc $(GCC_FLAGS) -c $< -o $@ $(INCLUDE_DIRS)

clean:
	@make -C $(LIBFT_DIR)/ clean
	@rm -rf $(OBJS_DIR)

fclean:
	@make -C $(LIBFT_DIR)/ fclean
	@rm -rf $(OBJS_DIR) $(NAME)

re: fclean all

.PHONY: all norm clean fclean re