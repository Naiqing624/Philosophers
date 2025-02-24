NAME = philo

CC = cc
FLAG = -Wall -Wextra -Werror -lpthread -g

SRC_DIR = src/
OBJ_DIR = obj/

FILES = main utils00 utils01 initia monitor thread_routine 

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

$(OBJ_DIR) :
		@mkdir -p $(OBJ_DIR)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(FLAG) $(OBJS) -o $(NAME)
		@echo "\033[32mPhilo Compiled\033[32m"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(FLAG) -c $< -o $@

clean :
		@rm -rf $(OBJ_DIR)
		@rm -rf $(OBJF)
		@echo "\033[32mObjects cleaned!\033[0m"

fclean : clean
		@rm -rf $(NAME)
		@echo "\033[32mAll is Cleaned!\033[0m"

re : fclean all
		@echo "\033[32mCleaned and rebuilt!\033[0m"

.PHONY : all clean fclean re