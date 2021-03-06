# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/30 16:01:32 by rnovodra          #+#    #+#              #
#    Updated: 2018/07/30 16:01:36 by rnovodra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	visual

SRC				=	main.c \
					ft_visual_error.c \
					ft_thread_error.c \
					ft_visual_exit.c \
					ft_create_win.c \
					ft_visual.c \
					ft_key_window_events.c \
					ft_check_vm_header.c \
					ft_check_players.c \
					ft_read_game.c \
					ft_create_step.c \
					ft_skip_piece.c \
					ft_free_step.c \
					ft_music.c \
					ft_draw_game.c \
					ft_colors.c \
					ft_put_font.c \
					ft_put_bar.c \
					ft_put_winner.c \
				
OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC_DIR			=	./src/
OBJ_DIR			=	./obj/
INC_DIR			=	./inc/
LIB_DIR			=	./../lib/

LIBFT_DIR		=	$(LIB_DIR)libft/

LIBFT			=	$(LIBFT_DIR)libft.a

PRINTF_DIR		=	$(LIB_DIR)ft_printf/

LIBPRINTF		=	$(PRINTF_DIR)libftprintf.a

HEAD_PRINTF		=	$(PRINTF_DIR)$(INC_DIR)ft_printf.h
HEAD_LIBFT		=	$(LIBFT_DIR)$(INC_DIR)libft.h

HEAD_VISUAL		=	$(INC_DIR)filler_visual.h

HEAD_FLAGS		=	-I $(INC_DIR) -I $(PRINTF_DIR)$(INC_DIR) -I $(LIBFT_DIR)$(INC_DIR)

LIBS_FLAGS		=	-L $(PRINTF_DIR) -lft -L $(LIBFT_DIR) -lftprintf

THREAD_FLAGS	=	-lpthread

CC_FLAGS		=	-std=c11

SDL_LIB			=	-L ~/.brew/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image
SDL_HEADER		=	-I ~/.brew/include/ -D_THREAD_SAFE

CC				=	gcc

BG				=	"\033[32;1m"
BR				=	"\033[31;1m"
EOC				=	"\033[0m"

all: $(LIBFT) $(NAME)

$(LIBFT): $(LIBPRINTF)
	@make -C $(LIBFT_DIR)

$(LIBPRINTF):
	@make -C $(PRINTF_DIR)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(SDL_LIB) $(LIBS_FLAGS) $(THREAD_FLAGS)
	@echo ${BG}"visual is ready"${EOC}

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c $(HEAD_VISUAL)
	@$(CC) -c $< -o $@ $(CC_FLAGS) $(HEAD_FLAGS) $(SDL_HEADER)
	@echo ${BG}"[✓] $<"

clean:
	@rm -rf $(OBJ)
	@echo ${BR}"[✗] clean"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo ${BR}"[✗] $(NAME)"

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all fclean clean re 
