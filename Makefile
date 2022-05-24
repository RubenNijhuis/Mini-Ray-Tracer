# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rubennijhuis <rubennijhuis@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/24 20:14:42 by rubennijhui   #+#    #+#                  #
#    Updated: 2022/05/24 15:36:18 by jobvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#=====================================#
#========= General variables =========#
#=====================================#

NAME :=			bin/minirt
ASSETS_DIR :=	assets
BIN_DIR :=		bin
INCLUDE_DIR :=	include
LIBS_DIR :=		libs
OBJS_DIR := 	objs
SRC_DIR :=		src
TEST_DIR :=		test

# TODO: HEADER watching


MLX_A =			$(LIBS_DIR)/MLX42/libmlx42.a

#=====================================#
#=============== Input ===============#
#=====================================#

INPUT_FILE = 	$(ASSETS_DIR)/mandatory/test.rt

MLX := 			-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

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
				\
				utils/print_scene/print_scene.c \
				utils/print_scene/print_shapes.c \

OBJS =			$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CC = 			gcc
CFLAGS =		-Wall -Werror -Wextra -g $(INC)
NO_DEAD_CODE :=	-O1 -Os -fdata-sections -ffunction-sections -Wl, -dead_strip

#=====================================#
#=============== Rules ===============#
#=====================================#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "🔨 Compiling: $^"
	
all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) $(MLX) $(NO_DEAD_CODE) -o $@
	@echo "✅ Built $(NAME)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "🧹 Cleaning $(NAME) objects"

fclean: clean
	@make fclean -C $(LIBS_DIR)/Get-Next-Line
	@make fclean -C $(LIBS_DIR)/Lib-Vec
	@make fclean -C $(LIBS_DIR)/LibFT
	@make  clean -C $(LIBS_DIR)/MLX42
	@make fclean -C $(TEST_DIR)
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
	@./$(NAME) $(INPUT_FILE)

test:
	@make run -C $(TEST_DIR)/

bonus:
	@make -C -D BONUS=1

test_binary: $(NAME)
	@ar -cr $(NAME).a $(OBJS)
	@echo "✅ Built test binary $(NAME) \n"

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

$(MLX_A):
	@make -C $(LIBS_DIR)/MLX42

$(LIBS_DIR)/LibFT/libft.a:
	@make -C $(LIBS_DIR)/LibFT

$(LIBS_DIR)/Get-Next-Line/get-next-line.a:
	@make -C $(LIBS_DIR)/Get-Next-Line

$(LIBS_DIR)/Lib-Vec/libvec.a: $(LIBS_DIR)/Lib-Vec/include/libvec.h
	@make -C $(LIBS_DIR)/Lib-Vec

#=====================================#
#================ Misc ===============#
#=====================================#

.PHONY: all re run clean fclean test
