# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 08:47:29 by dnakano           #+#    #+#              #
#    Updated: 2021/06/06 08:55:25 by dnakano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
LDFLAGS			=	-L$(LIBFTDIR) $(patsubst lib%,-l%,$(basename $(LIBFT)))
SRCNAME			=	main.c \
					ppx_fdhandler.c \
					ppx_readfromfile.c \
					ppx_writetofile.c \
					ppx_execcmd.c \
					ppx_wait_children.c \
					ppx_utils.c
SRCDIR			=	.
SRCS			=	$(addprefix $(SRCDIR)/,$(SRCNAME))
OBJS			=	$(SRCS:%.c=%.o)
HEADERNAME		=	pipex.h libft/libft.h
HEADERDIR		=	.
HEADERS			=	$(addprefix $(HEADERDIR)/,$(HEADERNAME))
LIBFT			=	libft.a
LIBFTDIR		=	libft
NAME			=	pipex
OUTPUTDIR		=	.
OUTPUT			=	$(OUTPUTDIR)/$(NAME)

.SUFFIXES:		.o .c

.PHONY:			all
all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJS) $(HEADERS)
				$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(OUTPUT)

$(LIBFT):
				make $(LIBFT) -C $(LIBFTDIR)

%.o:%.c
				$(CC) $(CFLAGS) -c $< -o $@

.PHONY:			test
test:		$(NAME)
			cd test && ./test.sh

.PHONY:			clean
clean:
				make fclean -C $(LIBFTDIR)
				rm -f $(OBJS)

.PHONY:			fclean
fclean:			clean
				make clean -C $(LIBFTDIR)
				rm -f $(OUTPUT)

.PHONY:			re
re:				fclean all
