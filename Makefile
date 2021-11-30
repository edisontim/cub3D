# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedison <timothyedison@hotmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 14:15:12 by tedison           #+#    #+#              #
#    Updated: 2021/11/30 17:44:25 by tedison          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_BASE		=ft_atoi.c ft_bzero.c ft_isprint.c map_parser.c gnl/get_next_line_utils_bonus.c \
				gnl/get_next_line_bonus.c utils.c ft_strncmp.c \
				raycasting_utils.c texture.c sprite.c ceiling_floor_swaps.c \
				raycasting.c sprite_init.c game_init.c to_bmp.c parsing_utils.c \
				pars_store_v.c pars_store_more_v.c pars_store_more2.c utils_more.c
SRCS 			= $(addprefix srcs/,$(SRCS_BASE))
OBJS			= $(SRCS:.c=.o)

MANDATORY_BASE	= cub3d.c move.c server.c client.c
MANDATORY		= $(addprefix srcs/,$(MANDATORY_BASE))
MANDATORY_OBJS	= $(MANDATORY:.c=.o)

BONUS_BASE		= server.c client.c cub3d_bonus.c move_bonus.c move_bonus_sounds.c
BONUS			= $(addprefix srcs/,$(BONUS_BASE))
BONUS_OBJS		= $(BONUS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I. 
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				= libmlx.dylib

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS) $(MANDATORY_OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${MANDATORY_OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS) $(MANDATORY_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

bonus:			$(BONUS_OBJS) $(OBJS)
					gcc ${CFLAGS} -o ${NAME} ${OBJS} ${BONUS_OBJS} ${LIBS}
.PHONY:			all clean fclean re
