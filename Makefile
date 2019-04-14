# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 15:07:58 by ymekraou          #+#    #+#              #
#    Updated: 2019/04/14 19:13:11 by ymekraou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
INC_PATHSDL = ./SDL2_utils/include/SDL2
INC_PATH = .

SRCS = srcs/

SRCS_BASENAME = main.c \
	  sdl_functions.c \
	  maths_functions.c \
	  parsing_error_functions.c \
	  light.c \
	  phong.c \
	  light_component.c \
	  shading.c \
	  camera.c \
	  sphere.c \
	  plan.c \
	  cone.c \
	  cylender.c \
	  ray_tracing.c \
	  hit_point.c \
	  file_parsing.c \
	  custom_atoi.c \
	  normal.c \
	  camera_movement.c \
	  update_scene.c \
	  update_objects.c \
	  hit_sphere.c \
	  hit_cone.c \
	  hit_plan.c \
	  hit_cylender.c \
	
INC = includes/rtv1.h

OBJS_DIR = objs/
OBJS_ALL = $(addprefix $(OBJS_DIR), $(SRCS_BASENAME:.c=.o))

LIBFT_DIR = libft/

SDL_UTILS = ./SDL2_utils
SDL_PATH = ./SDL2-2.0.9
SDL_BUILD_PATH = $(SDL_PATH)/build

SDL_LIBPATH = $(SDL_UTILS)/lib
SDL = $(SDL_LIBPATH)/libSDL2.a

CC = gcc

CFLAGS =  -Wall -Wextra -Werror -D_THREAD_SAFE

LDFLAGS = -lSDL2 -lm -lft

.PHONY: libft clean fclean re

all: create_obj_dir libft $(SDL) $(NAME)

create_obj_dir:
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS_ALL) $(LIBFT_DIR)libft.a
	$(CC) -o $@ $^ -L $(SDL_LIBPATH) -L $(LIBFT_DIR) $(LDFLAGS)
	
$(OBJS_DIR)%.o: $(SRCS)%.c $(INC)
	$(CC) $(CFLAGS) -c $< -I $(INC) -I $(INC_PATHSDL) -I $(LIBFT_DIR)includes/ -o $@

libft:
	make -C $(LIBFT_DIR)

$(SDL):
	unzip SDL2-2.0.9.zip
	mkdir -p $(SDL_UTILS)
	mkdir -p $(SDL_BUILD_PATH) 
	cd $(SDL_BUILD_PATH) && CC=./build-scripts/gcc-fat.sh && ../configure --prefix $(abspath $(SDL_UTILS))
	make -C $(SDL_BUILD_PATH)
	make install -C $(SDL_BUILD_PATH)

SDLclean:
	rm -rf SDL2_utils
	rm -rf SDL2-2.0.9

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean SDLclean
	rm -f $(LIBFT_DIR)libft.a
	rm -f $(NAME)

re: fclean all
