# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rubennijhuis <rubennijhuis@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/24 20:14:42 by rubennijhui   #+#    #+#                  #
#    Updated: 2022/08/02 12:34:09 by jobvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#=====================================#
#========= General variables =========#
#=====================================#

CC				:=	gcc
EXEC_NAME		:=	miniRT
ASSETS_DIR		:=	assets
BIN_DIR			:=	bin
INCLUDE_DIR		:=	include
LIBS_DIR		:=	libs
OBJS_DIR		:= 	objs
SRC_DIR			:=	src
TEST_DIR		:=	test
NAME			:=	$(BIN_DIR)/$(EXEC_NAME)

INPUT_FILE		:=	$(ASSETS_DIR)/mandatory/amogus.rt

BONUS			:=	1
DEBUG			:=	0
# amount of threads to use for multithread rendering when bonus is on.
# set to 0 for auto detection.
THREADS			:=	0

HEADERS			:=	$(INCLUDE_DIR)/bonus.h \
					$(INCLUDE_DIR)/colors.h \
					$(INCLUDE_DIR)/minirt.h \
					$(INCLUDE_DIR)/objects.h \
					$(INCLUDE_DIR)/parsing.h \
					$(INCLUDE_DIR)/ray.h \
					$(INCLUDE_DIR)/threading.h \


MLX_DIR			:=	$(LIBS_DIR)/MLX42
MLX_H 			:=	$(MLX_DIR)/include/MLX42/MLX42.h
MLX_A 			:=	$(MLX_DIR)/libmlx42.a

#=====================================#
#=============== Input ===============#
#=====================================#

LIBFT_DIR		=	$(LIBS_DIR)/LibFT
LIBFT_INC_DIR	=	$(LIBFT_DIR)/include
LIBFT_H			=	$(LIBFT_INC_DIR)/libft.h
LIBFT_A			=	$(LIBFT_DIR)/libft.a

#=====================================#
#============= ft_printf =============#

PF_DIR			=	$(LIBS_DIR)/ft_printf
PF_H			=	$(PF_DIR)/ft_printf.h $(PF_DIR)/pf_util.h $(LIBFT_H)
PF_A			=	$(PF_DIR)/libftprintf.a
PF_PDEPS		=	pf_parsing.c pf_print_hex.c pf_print_int.c \
					pf_print_pointer.c pf_print_str_char.c \
					pf_printing.c pf_printing_util.c ft_printf.c \
					pf_util.c ft_uitoa.c ft_itoa_hex.c
PF_DEPS			=	$(PF_PDEPS:%.c=$(PF_DIR)/%.c)
PF_OBJ_DIR		=	$(PF_DIR)/obj
PF_OBJ			=	$(PF_DEPS:$(PF_DIR)/%.c=$(PF_OBJ_DIR)/%.o)

#============= ft_printf =============#
#=====================================#

LIBS			:=	$(MLX_A) \
					$(PF_A) \
					$(LIBFT_A) \
					$(LIBS_DIR)/Lib-Vec/libvec.a \


LIBS_HEADERS	:=	-I $(INCLUDE_DIR) \
					-I $(PF_DIR) \
					-I $(LIBS_DIR)/MLX42/include/ \
					-I $(LIBFT_INC_DIR) \
					-I $(LIBS_DIR)/Lib-Vec/include/ \

PROJECT_HEADERS	:=	$(LIBS_DIR)/colors.h \
					$(LIBS_DIR)/minirt.h \
					$(LIBS_DIR)/objects.h \

INC				:=	$(LIBS_HEADERS)

SRCS 			:=	src/intersections/sphere.c \
					src/intersections/disc.c \
					src/intersections/intersection.c \
					src/intersections/plane.c \
					src/intersections/cylinder_normal.c \
					src/intersections/cylinder.c \
					src/intersections/cylinder_caps.c \
					src/gnl/get_next_line_utils.c \
					src/gnl/get_next_line.c \
					src/file_parse/utils.c \
					src/file_parse/get_file_content.c \
					src/file_parse/file_format_check/check_scene_objects.c \
					src/file_parse/file_format_check/check_elements.c \
					src/file_parse/file_format_check/is_file_correctly_formatted.c \
					src/file_parse/file_format_check/check_vectors.c \
					src/file_parse/file_format_check/check_utils.c \
					src/file_parse/file_format_check/number_format.c \
					src/file_parse/file_format_check/check_object_settings.c \
					src/file_parse/file_format_check/rt_objstrcmp.c \
					src/ray/ray.c \
					src/render/fov.c \
					src/render/thread_routines.c \
					src/render/render_block.c \
					src/render/render.c \
					src/render/threads.c \
					src/utils/exit_error.c \
					src/utils/ft_atof.c \
					src/utils/angles.c \
					src/utils/math.c \
					src/utils/print_scene/print_shapes.c \
					src/utils/print_scene/print_scene.c \
					src/color/get_ray_color.c \
					src/color/color.c \
					src/color/color_utils.c \
					src/color/light_calc.c \
					src/create_objects/get_vec_from_string.c \
					src/create_objects/create_obj_from_str.c \
					src/create_objects/create_utils.c \
					src/create_objects/setup_scene/setup_objects.c \
					src/create_objects/setup_scene/setup_scene.c \
					src/setup_rt.c \
					src/main.c \

OBJS			:=	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CFLAGS			:=	-Wall -Werror -Wextra

ifeq ($(DEBUG), 1)
	CFLAGS += -g -fsanitize=address
else
	CFLAGS += -Ofast -march=native -mtune=native 
endif

# Credits -> https://github.com/codam-coding-college/MLX42
# TODO: Add NO_DEAD_CODE for linux
UNAME_S			:=	$(shell uname -s)
ifeq ($(UNAME_S), Linux)
	# -pthread is only required for the bonus, however, since we can't check
	# wether the bonus is active or not, always use it here.
	LDFLAGS += -lm
	ifeq ($(BONUS), 1)
		LDFLAGS += -pthread
	endif

	ifeq ($(THREADS), 0)
		THREADS = $(shell nproc --all)
	endif
	MLX = -ldl -lglfw
else ifeq ($(UNAME_S), Darwin)
	# TODO: change to ifdef RUBEN_LAPTOP or something like that
	ifdef CODAM
		MLX = -lglfw3
	else
		LDFLAGS += -L /usr/local/Cellar/glfw/3.3.7/lib
		MLX = -lglfw
	endif
	NO_DEAD_CODE :=	-fdata-sections -ffunction-sections -Wl, -dead_strip
	MLX += -framework Cocoa -framework OpenGL -framework IOKit

	ifeq ($(THREADS), 0)
		THREADS = $(shell sysctl -n hw.logicalcpu)
	endif
else
	$(error OS is not supported(uname -s: $(UNAME_S))!)
endif

SWITCHES		:=	-D BONUS=$(BONUS) -D DEBUG=$(DEBUG) -D N_THREADS=$(THREADS)

#=====================================#
#=============== Rules ===============#
#=====================================#

$(OBJS_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INC) $(SWITCHES) -o $@ $<
	@echo "🔨 Compiling: $<"
	
$(NAME): $(OBJS) $(LIBS) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(NO_DEAD_CODE) $^ -o $@ $(LDFLAGS) $(MLX)
	@echo "✅ Built $(NAME)"

# ft_printf stuff
$(PF_A): $(PF_OBJ)
	@ar rcs $@ $^
	@echo "✅ Built ft_printf"

$(PF_OBJ_DIR)/%.o: $(PF_DIR)/%.c $(PF_H) | $(PF_OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(PF_DIR) -I$(LIBFT_INC_DIR) -c -o $@ $<
	@echo "🔨 Compiling: $<"

$(BIN_DIR):
	@mkdir $@

$(PF_OBJ_DIR):
	@mkdir $@

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "🧹 Cleaning $(NAME) objects"

fclean: clean
	@rm -rf $(PF_OBJ_DIR)
	@rm -f $(PF_A)
	@$(MAKE) fclean -C $(LIBS_DIR)/Lib-Vec
	@$(MAKE) fclean -C $(LIBS_DIR)/LibFT
	@$(MAKE) fclean -C $(LIBS_DIR)/MLX42
	
	@$(MAKE) fclean -C $(TEST_DIR)

	@echo "Cleaning up $(NAME)"
	@rm -f $(NAME)
	@rm -f $(NAME).a
	@echo "🧹 Cleaning $(NAME) binary"

re: fclean all

#=====================================#
#=========== Special Rules ===========#
#=====================================#

# Command to get a formatted list of all the .c files
# find src | grep "\.c$" | sed -E 's/$/ \\/'

submodules:
	@git submodule update --init --recursive --remote
	
run: $(NAME)
	@./$< $(INPUT_FILE)

test: $(NAME)
	@$(MAKE) run -C $(TEST_DIR)/

bonus:
	@$(MAKE) -C -D BONUS=1

$(NAME).a: $(NAME)
	@mkdir -p $(dir $@)
	@ar -cr $@ $(OBJS)
	@echo "✅ Built test binary $@ \n"

test_binary: $(NAME).a

norm:
	@echo "\033[92m========= $(NAME) norm ========\033[0m"
	@-norminette $(INCLUDE_DIR)
	@-norminette $(SRC_DIR)
	@echo "\033[92m========= $(NAME) norm ========\033[0m"

	@echo "\033[92m========= ft_printf norm ========\033[0m"
	@norminette      $(LIBS_DIR)/ft_printf
	@echo "\033[92m========= ft_printf norm ========\033[0m"

	@echo
	@$(MAKE) norm -C $(LIBS_DIR)/Lib-Vec
	@echo
	@$(MAKE) norm -C $(LIBS_DIR)/LibFT

#=====================================#
#========== Lib compilation ==========#
#=====================================#

$(MLX_A): $(MLX_H)
	@$(MAKE) -C $(LIBS_DIR)/MLX42

$(LIBFT_A): $(LIBFT_H)
	@$(MAKE) -C $(LIBS_DIR)/LibFT

$(LIBS_DIR)/Lib-Vec/libvec.a: $(LIBS_DIR)/Lib-Vec/include/libvec.h
	@$(MAKE) -C $(LIBS_DIR)/Lib-Vec

#=====================================#
#================ Misc ===============#
#=====================================#

.PHONY: all re run clean fclean test test_binary submodules norm
