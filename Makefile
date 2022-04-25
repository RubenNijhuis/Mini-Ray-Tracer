# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rubennijhuis <rubennijhuis@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/24 20:14:42 by rubennijhui   #+#    #+#                  #
#    Updated: 2022/04/24 20:14:43 by rubennijhui   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#=====================================#
#========= General variables =========#
#=====================================#

NAME := bin/minirt
INCLUDE_DIR := include
SRC_DIR := src
LIBS_DIR := libs
OBJS_DIR := objs
BIN_DIR := bin
PROGRAM_LOCATION := $(BIN_DIR)/$(NAME)

#=====================================#
#=============== Input ===============#
#=====================================#

INPUT_FILE = assets/test.rt

LIBS := $(LIBS_DIR)/LibFT/libft.a \
		$(LIBS_DIR)/Get-Next-Line/get-next-line.a \
		$(LIBS_DIR)/mlx/libmlx.a \

LIBS_HEADERS := -I $(INCLUDE_DIR) \
				-I $(LIBS_DIR)/LibFT/include/ \
				-I $(LIBS_DIR)/Get-Next-Line/include/ \
				-I $(LIBS_DIR)/mlx/ \

MLX := -framework OpenGL -framework AppKit

INC := $(LIBS_HEADERS)

SRCS := main.c \
		\
		file_parse/get_objs_from_file.c \

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g $(INC)

#=====================================#
#=============== Rules ===============#
#=====================================#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "🔨 Compiling: $^"
	
all: $(NAME)

$(NAME):$(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) $(MLX) -o $(NAME)
	@echo "✅ Built $(NAME)"

submodules:
	@git submodule update --init --recursive
	@cd $(LIBS_DIR)/LibFt/ && git pull
	@cd $(LIBS_DIR)/Get-Next-Line/ && git pull

run: $(NAME)
	@./$(NAME) $(INPUT_FILE)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C $(LIBS_DIR)/Get-Next-Line
	@make fclean -C $(LIBS_DIR)/LibFT
	@make clean -C $(LIBS_DIR)/mlx
	@rm -f $(PROGRAM_LOCATION)

re: fclean all

#=====================================#
#========== Lib compilation ==========#
#=====================================#

$(LIBS_DIR)/mlx/libmlx.a:
	@make -C $(LIBS_DIR)/mlx

$(LIBS_DIR)/LibFT/libft.a:
	@make -C $(LIBS_DIR)/LibFT

$(LIBS_DIR)/Get-Next-Line/get-next-line.a:
	@make -C $(LIBS_DIR)/Get-Next-Line

#=====================================#
#================ Misc ===============#
#=====================================#

.PHONY: all re run clean fclean
