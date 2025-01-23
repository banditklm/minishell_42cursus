NAME = minishell

CC = cc

FLAGS = -Wextra -Wall -Werror -I ~/.brew/opt/readline/include

LDFLAGS = -lreadline -L ~/.brew/opt/readline/lib

SRCS = sources/minishell.c lexer/lexer0.c lexer/lexer1.c lexer/lexer2.c lexer/lexer3.c lexer/lexer4.c lexer/lexer5.c \
		parser/parser.c parser/parser0.c parser/parser1.c parser/parser2.c parser/parser3.c  parser/parser4.c parser/parser5.c parser/parser6.c \
		tokenizer/tokenizer0.c tokenizer/tokenizer1.c tokenizer/tokenizer2.c \
		sources/utils1.c sources/utils2.c sources/utils3.c sources/utils4.c sources/utils5.c sources/utils6.c \
		sources/init.c sources/is_utils1.c sources/is_utils2.c execution/execution_utils2.c \
		sources/is_utils3.c execution/ft_getfullenv.c execution/ft_getenv.c execution/ft_setenv.c \
		sources/ft_itoa.c execution/ft_openhd.c execution/ft_execution.c sources/ft_split.c sources/init_data.c \
		execution/ft_openfd.c execution/ft_redirection.c execution/execution_utils.c \
		 builtins/env.c builtins/handel_builtin.c builtins/exit.c builtins/pwd.c\
		builtins/unset.c builtins/echo.c builtins/cd.c builtins/export.c builtins/builtins_utils.c builtins/export2.c\
		sources/fill_tok0.c sources/fill_tok1.c sources/signal.c sources/signal2.c builtins/export3.c builtins/builtins_utils2.c\
		execution/execution_utils3.c execution/execution_utils4.c execution/ft_openhd1.c 

HEADERS = sources/minishell.h

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(LDFLAGS) $^ -o $@
	@echo "\033[32mMaking Completed ✅😜"

$(OBJS) : %.o: %.c $(HEADERS) Makefile
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)
	@echo "\033[0;33mCleaning Completed 🧼✨"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[0;31mRemoving Completed 🗑 💔"

re : fclean all

.PHONY : clean	
