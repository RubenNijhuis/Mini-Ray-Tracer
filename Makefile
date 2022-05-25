# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rubennijhuis <rubennijhuis@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/24 20:14:42 by rubennijhui   #+#    #+#                  #
#    Updated: 2022/05/25 15:37:40 by jobvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#=====================================#
#========= General variables =========#
#=====================================#

EXEC_NAME :=	minirt
ASSETS_DIR :=	assets
BIN_DIR :=		bin
INCLUDE_DIR :=	include
LIBS_DIR :=		libs
OBJS_DIR := 	objs
SRC_DIR :=		src
TEST_DIR :=		test
NAME := $(BIN_DIR)/$(EXEC_NAME)

# TODO: More header watching
HEADERS = $(LIBS_DIR)/Lib-Vec/include/libvec.h


MLX_A =			$(LIBS_DIR)/MLX42/libmlx42.a

#=====================================#
#=============== Input ===============#
#=====================================#

INPUT_FILE = 	$(ASSETS_DIR)/mandatory/sphere_test.rt

LIBS :=			$(MLX_A) \
				$(LIBS_DIR)/LibFT/libft.a \
				$(LIBS_DIR)/Lib-Vec/libvec.a \
				$(LIBS_DIR)/Get-Next-Line/get-next-line.a \

LIBS_HEADERS :=	-I $(INCLUDE_DIR) \
				-I $(LIBS_DIR)/MLX42/include/ \
				-I $(LIBS_DIR)/LibFT/include/ \
				-I $(LIBS_DIR)/Lib-Vec/include/ \
				-I $(LIBS_DIR)/Get-Next-Line/include/ \

PROJECT_HEADERS :=	$(LIBS_DIR)/colors.h \
					$(LIBS_DIR)/minirt.h \
					$(LIBS_DIR)/objects.h \

OBJS =			$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

INC :=			$(LIBS_HEADERS)

SRCS :=			main.c \
				misc.c \
				\
				file_parse/get_file_content.c \
				file_parse/is_file_correctly_formatted.c \
				\
				create_objects/setup_scene.c \
				create_objects/create_obj_from_str.c \
				create_objects/get_vec_from_string.c \
				create_objects/get_objs_from_string.c \
				create_objects/get_shape_type_string.c \
				\
				utils/ft_atof.c \
				utils/exit_error.c \
				utils/color_util.c \
				\
				utils/print_scene/print_scene.c \
				utils/print_scene/print_shapes.c \

OBJS =			$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CC = 			gcc
CFLAGS =		-Wall -Werror -Wextra -g -fsanitize=address

# TODO: CLEAN UP THIS MAKEFILE

# stolen from MLX42
# TODO: Add NO_DEAD_CODE for linux
UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX = -ldl -lglfw -lm
else ifeq ($(UNAME_S), Darwin)
	NO_DEAD_CODE :=	-O1 -Os -fdata-sections -ffunction-sections -Wl, -dead_strip
	MLX = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
else
	$(error OS is not supported(uname -s: $(UNAME_S))!)
endif

#=====================================#
#=============== Rules ===============#
#=====================================#

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INC) -o $@ $<
	@echo "🔨 Compiling: $<"
	
all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(NO_DEAD_CODE) $^ -o $@ $(MLX)
	@echo "✅ Built $(NAME)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "🧹 Cleaning $(NAME) objects"

fclean: clean
	@$(MAKE) fclean -C $(LIBS_DIR)/Get-Next-Line
	@$(MAKE) fclean -C $(LIBS_DIR)/Lib-Vec
	@$(MAKE) fclean -C $(LIBS_DIR)/LibFT
	@$(MAKE)  clean -C $(LIBS_DIR)/MLX42
	@$(MAKE) fclean -C $(TEST_DIR)
	@echo "Cleaning up $(NAME)"
	@rm -f $(NAME)
	@rm -f $(NAME).a
	@echo "🧹 Cleaning $(NAME) binary"

re: fclean all

#=====================================#
#=========== Special Rules ===========#
#=====================================#

submodules:
	@git submodule update --init --recursive
	@cd $(LIBS_DIR)/LibFt/ && git pull origin main
	@cd $(LIBS_DIR)/Get-Next-Line/ && git pull origin main
	@cd $(LIBS_DIR)/Lib-Vec/ && git pull origin main
	@cd $(LIBS_DIR)/MLX42/ && git pull origin master
	
run: $(NAME)
	@./$< $(INPUT_FILE)

test:
	@$(MAKE) run -C $(TEST_DIR)/

bonus:
	@$(MAKE) -C -D BONUS=1

$(NAME).a: $(NAME)
	@ar -cr $@ $(OBJS)
	@echo "✅ Built test binary $@ \n"

test_binary: $(NAME).a

norm:
	@echo "\033[92m========= $(NAME) norm ========\033[0m"
	@-norminette $(INCLUDE_DIR)
	@-norminette $(SRC_DIR)
	@echo "\033[92m========= $(NAME) norm ========\033[0m"
	
	@echo
	@$(MAKE) norm -C $(LIBS_DIR)/Get-Next-Line
	@echo
	@$(MAKE) norm -C $(LIBS_DIR)/Lib-Vec
	@echo
	@$(MAKE) norm -C $(LIBS_DIR)/LibFT

#=====================================#
#========== Lib compilation ==========#
#=====================================#

$(MLX_A):
	@$(MAKE) -C $(LIBS_DIR)/MLX42

$(LIBS_DIR)/LibFT/libft.a:
	@$(MAKE) -C $(LIBS_DIR)/LibFT

$(LIBS_DIR)/Get-Next-Line/get-next-line.a:
	@$(MAKE) -C $(LIBS_DIR)/Get-Next-Line

$(LIBS_DIR)/Lib-Vec/libvec.a: $(LIBS_DIR)/Lib-Vec/include/libvec.h
	@$(MAKE) -C $(LIBS_DIR)/Lib-Vec

#=====================================#
#================ Misc ===============#
#=====================================#

.PHONY: all re run clean fclean test test_binary submodules norm
