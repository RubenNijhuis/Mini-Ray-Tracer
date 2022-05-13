# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rubennijhuis <rubennijhuis@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/25 22:41:11 by rubennijhui   #+#    #+#                  #
#    Updated: 2022/05/13 17:38:47 by jobvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#=====================================#
#========== Setup variables ==========#
#=====================================#

ifdef CODAM
	CRITERION_DIR = -L /Users/$(USER)/.brew/Cellar/criterion/2.4.0_1/lib/
	CRITERION_INC = -I /Users/$(USER)/.brew/Cellar/criterion/2.4.0_1/include 
else
	CRITERION_DIR = -L /usr/local/Cellar/criterion/2.4.0_1/lib/
	CRITERION_INC = -I /usr/local/Cellar/criterion/2.4.0_1/include
endif

#=====================================#
#========= General variables =========#
#=====================================#

NAME := bin/tester
SRC_DIR := src
OBJS_DIR := objs

#=====================================#
#============ Input files ============#
#=====================================#

LIBS :=	../bin/minirt.a \
		../libs/LibFT/libft.a \
		../libs/Get-Next-Line/get-next-line.a \
		../libs/Lib-Vec/libvec.a \
		../libs/mlx/libmlx.a \

LIBS_HEADERS :=	-I ../libs/LibFT/include/ \
				-I ../libs/Get-Next-Line/include/ \
				-I ../libs/Lib-Vec/include/ \
				-I ../libs/mlx/ \
				$(CRITERION_INC)

INC := -I ../include/ $(LIBS_HEADERS)

SRCS :=	make_objects.c \
		misc.c \
		vector_utils.c \

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CC = gcc
CFLAGS = -Wall -Werror -Wextra $(INC)
LDFLAGS = $(CRITERION_DIR) -lcriterion

#=====================================#
#=============== Rules ===============#
#=====================================#

objs/%.o:src/*%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "🔨 Compiling: $^"
	
all: $(NAME)

$(NAME):$(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "✅ Built $(NAME)"

run: $(NAME) $(LIBS)
	@./$(NAME)

../bin/minirt.a:
	@make test_binary -C ../

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all run

.PHONY: all re run clean fclean