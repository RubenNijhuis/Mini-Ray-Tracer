# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rubennijhuis <rubennijhuis@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/24 20:14:42 by rubennijhui   #+#    #+#                  #
#    Updated: 2022/05/01 23:13:30 by rubennijhui   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#=====================================#
#========= General variables =========#
#=====================================#

NAME := bin/minirt
ASSETS_DIR := assets
BIN_DIR := bin
INCLUDE_DIR := include
LIBS_DIR := libs
OBJS_DIR := objs
SRC_DIR := src
TEST_DIR := test

#=====================================#
#=============== Input ===============#
#=====================================#

INPUT_FILE = $(ASSETS_DIR)/test.rt

MLX := -framework OpenGL -framework AppKit

LIBS := $(LIBS_DIR)/LibFT/libft.a \
		$(LIBS_DIR)/Get-Next-Line/get-next-line.a \
		$(LIBS_DIR)/Lib-Vec/libvec.a \
		$(LIBS_DIR)/mlx/libmlx.a \

LIBS_HEADERS := -I $(INCLUDE_DIR) \
				-I $(LIBS_DIR)/LibFT/include/ \
				-I $(LIBS_DIR)/Get-Next-Line/include/ \
				-I $(LIBS_DIR)/Lib-Vec/include/ \
				-I $(LIBS_DIR)/mlx/ \

INC := $(LIBS_HEADERS)

SRCS := main.c \
		\
		file_parse/get_objs_from_file.c \
		file_parse/create_obj_from_str.c \
		file_parse/is_correctly_formatted.c \
		file_parse/setup_scene.c \
		\
		utils/ft_atof.c \
		utils/print_scene.c \
		utils/exit_error.c \
		utils/get_file_contents.c \
		utils/get_shape_type_string.c \

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g $(INC)
NO_DEAD_CODE := -O1 -Os -fdata-sections -ffunction-sections -Wl, -dead_strip

#=====================================#
#=============== Rules ===============#
#=====================================#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "🔨 Compiling: $^"
	
all: $(NAME)

$(NAME):$(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) $(MLX) $(NO_DEAD_CODE) -o $(NAME)
	@echo "✅ Built $(NAME)"

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
#=========== Special Rules ===========#
#=====================================#

submodules:
	@git submodule update --init --recursive
	@cd $(LIBS_DIR)/LibFt/ && git pull origin main
	@cd $(LIBS_DIR)/Get-Next-Line/ && git pull origin main
	@cd $(LIBS_DIR)/Lib-Vec/ && git pull origin main
	
run: $(NAME)
	@./$(NAME) $(INPUT_FILE)

test:
	@make run -C $(TEST_DIR)/

norm:
	@echo "\033[92m========= $(NAME) norm ========\033[0m"
	@-norminette $(INCLUDE_DIR)
	@-norminette $(SRC_DIR)
	@echo "\033[92m========= $(NAME) norm ========\033[0m"
	
	@echo
	@make norm -C $(LIBS_DIR)/Get-Next-Line
	@echo
	@make norm -C $(LIBS_DIR)/Lib-Vec
	@echo
	@make norm -C $(LIBS_DIR)/LibFT

#=====================================#
#========== Lib compilation ==========#
#=====================================#

$(LIBS_DIR)/mlx/libmlx.a:
	@make -C $(LIBS_DIR)/mlx

$(LIBS_DIR)/LibFT/libft.a:
	@make -C $(LIBS_DIR)/LibFT

$(LIBS_DIR)/Get-Next-Line/get-next-line.a:
	@make -C $(LIBS_DIR)/Get-Next-Line

$(LIBS_DIR)/Lib-Vec/libvec.a:
	@make -C $(LIBS_DIR)/Lib-Vec

#=====================================#
#================ Misc ===============#
#=====================================#

.PHONY: all re run clean fclean test
