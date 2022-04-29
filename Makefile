# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rubennijhuis <rubennijhuis@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/24 20:14:42 by rubennijhui   #+#    #+#                  #
#    Updated: 2022/04/29 11:42:15 by rnijhuis      ########   odam.nl          #
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
TEST_DIR := test
ASSETS_DIR := assets

#=====================================#
#=============== Input ===============#
#=====================================#

INPUT_FILE = $(ASSETS_DIR)/testcopy.rt

LIBS := $(LIBS_DIR)/LibFT/libft.a \
		$(LIBS_DIR)/Get-Next-Line/get-next-line.a \
		$(LIBS_DIR)/Lib-Vec/libvec.a \
		$(LIBS_DIR)/mlx/libmlx.a \

LIBS_HEADERS := -I $(INCLUDE_DIR) \
				-I $(LIBS_DIR)/LibFT/include/ \
				-I $(LIBS_DIR)/Get-Next-Line/include/ \
				-I $(LIBS_DIR)/Lib-Vec/include/ \
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
	@cd $(LIBS_DIR)/Lib-Vec/ && git pull

run: $(NAME)
	@./$(NAME) $(INPUT_FILE)

test:
	@make run -C $(TEST_DIR)/

norm:
	norminette $(SRC_DIR)
	norminette $(INCLUDE_DIR)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C $(LIBS_DIR)/Get-Next-Line
	@make fclean -C $(LIBS_DIR)/Lib-Vec
	@make fclean -C $(LIBS_DIR)/LibFT
	@make  clean -C $(LIBS_DIR)/mlx
	@rm -f $(NAME)

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

$(LIBS_DIR)/Lib-Vec/lib-vec.a:
	@make -C $(LIBS_DIR)/Get-Next-Line

#=====================================#
#================ Misc ===============#
#=====================================#

.PHONY: all re run clean fclean