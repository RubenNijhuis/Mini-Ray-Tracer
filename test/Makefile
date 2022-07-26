# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rubennijhuis <rubennijhuis@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/25 22:41:11 by rubennijhui   #+#    #+#                  #
#    Updated: 2022/07/26 16:09:09 by rnijhuis      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#=====================================#
#========== Setup variables ==========#
#=====================================#

ifdef CODAM
	CRITERION_DIR = -L /Users/$(USER)/.brew/Cellar/criterion/2.4.1/lib
	CRITERION_INC = -I /Users/$(USER)/.brew/Cellar/criterion/2.4.1/include 
else
	CRITERION_DIR = -L /usr/local/Cellar/criterion/2.4.0_1/lib/
	CRITERION_INC = -I /usr/local/Cellar/criterion/2.4.0_1/include
endif

#=====================================#
#========= General variables =========#
#=====================================#

NAME :=			bin/tester
SRC_DIR :=		src
OBJS_DIR :=		objs

#=====================================#
#============ Input files ============#
#=====================================#

LIBS :=			../bin/minirt.a \
				../libs/LibFT/libft.a \
				../libs/Get-Next-Line/get-next-line.a \
				../libs/Lib-Vec/libvec.a \
				../libs/MLX42/libmlx42.a \

LIBS_HEADERS :=	-I ../libs/LibFT/include/ \
				-I ../libs/Get-Next-Line/include/ \
				-I ../libs/Lib-Vec/include/ \
				-I ../libs/MLX42/include/ \
				$(CRITERION_INC)

INC :=			-I ../include/ $(LIBS_HEADERS)

SRCS :=			$(shell find $(SRC_DIR) -type f -name "*.c")


OBJS =			$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CC =			gcc
CFLAGS =		-Wall -Wextra $(INC) -fsanitize=address -g
LDFLAGS =		$(CRITERION_DIR) -lcriterion -lm
# -fsanitize=address -g

#=====================================#
#=============== Rules ===============#
#=====================================#

$(OBJS_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "🔨 Compiling: $^"
	
all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "✅ Built $(NAME)"

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all run

#=====================================#
#=========== Special Rules ===========#
#=====================================#

../bin/minirt.a:
	@make test_binary -C ../

run: $(NAME) $(LIBS)
	@./$(NAME)

.PHONY: all re run clean fclean