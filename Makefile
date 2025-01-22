# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 13:59:42 by vperez-f          #+#    #+#              #
#    Updated: 2025/01/22 21:36:18 by vperez-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CFILES = src/error_management/error_management.c \
		src/window_management/key_identifiers/extra_keys.c \
		src/window_management/key_identifiers/settings_keys.c \
		src/window_management/key_identifiers/transformation_keys.c \
		src/window_management/window_management.c \
		src/parser/scene/ambient/ambient_parser.c \
		src/parser/scene/camera/camera_parser.c \
		src/parser/scene/objects/figures/box_parser.c \
		src/parser/scene/objects/figures/cone_parser.c \
		src/parser/scene/objects/figures/cylinder_parser.c \
		src/parser/scene/objects/figures/disk_parser.c \
		src/parser/scene/objects/figures/p_light_parser.c \
		src/parser/scene/objects/figures/plane_parser.c \
		src/parser/scene/objects/figures/quad_parser.c \
		src/parser/scene/objects/figures/sphere_parser.c \
		src/parser/scene/objects/material/material_parser.c \
		src/parser/scene/objects/objects_parser.c \
		src/parser/scene/objects/texture/texture_parser.c \
		src/parser/scene/scene_parser.c \
		src/parser/scene/settings/settings_parser.c \
		src/parser/utils/lexical_utils.c \
		src/parser/utils/numerical_utils.c \
		src/parser/map_file/parse_map_path.c \
		src/parser/parser.c \
		src/selection_menu/custom_writer/bresenham_font.c \
		src/selection_menu/custom_writer/writer.c \
		src/selection_menu/file_selector.c \
		src/selection_menu/buttons/buttons.c \
		src/selection_menu/draw/draw_menu.c \
		src/selection_menu/utils/selector_utils.c \
		src/path_tracer/memory_management/memory_management.c \
		src/path_tracer/thread_management/mutex_utils.c \
		src/path_tracer/thread_management/thread_management.c \
		src/path_tracer/scene/camera/utils/camera_utils.c \
		src/path_tracer/scene/camera/hooks/settings/camera_settings.c \
		src/path_tracer/scene/camera/hooks/camera_hooks.c \
		src/path_tracer/scene/camera/camera.c \
		src/path_tracer/scene/objects/figures/box/getters/getters.c \
		src/path_tracer/scene/objects/figures/box/hit/hit.c \
		src/path_tracer/scene/objects/figures/box/transformations/transformations.c \
		src/path_tracer/scene/objects/figures/box/utils/utils.c \
		src/path_tracer/scene/objects/figures/box/box.c \
		src/path_tracer/scene/objects/figures/cone/getters/getters.c \
		src/path_tracer/scene/objects/figures/cone/hit/hit.c \
		src/path_tracer/scene/objects/figures/cone/textures/texture.c \
		src/path_tracer/scene/objects/figures/cone/transformations/transformations.c \
		src/path_tracer/scene/objects/figures/cone/utils/utils.c \
		src/path_tracer/scene/objects/figures/cone/cone.c \
		src/path_tracer/scene/objects/figures/cylinder/getters/getters.c \
		src/path_tracer/scene/objects/figures/cylinder/hit/hit.c \
		src/path_tracer/scene/objects/figures/cylinder/textures/texture.c \
		src/path_tracer/scene/objects/figures/cylinder/transformations/transformations.c \
		src/path_tracer/scene/objects/figures/cylinder/utils/utils.c \
		src/path_tracer/scene/objects/figures/cylinder/cylinder.c \
		src/path_tracer/scene/objects/figures/disk/getters/getters.c \
		src/path_tracer/scene/objects/figures/disk/hit/hit.c \
		src/path_tracer/scene/objects/figures/disk/textures/texture.c \
		src/path_tracer/scene/objects/figures/disk/transformations/transformations.c \
		src/path_tracer/scene/objects/figures/disk/base/base.c \
		src/path_tracer/scene/objects/figures/disk/disk.c \
		src/path_tracer/scene/objects/figures/p_light/getters/getters.c \
		src/path_tracer/scene/objects/figures/p_light/hit/hit.c \
		src/path_tracer/scene/objects/figures/p_light/transformations/transformations.c \
		src/path_tracer/scene/objects/figures/p_light/p_light.c \
		src/path_tracer/scene/objects/figures/plane/getters/getters.c \
		src/path_tracer/scene/objects/figures/plane/hit/hit.c \
		src/path_tracer/scene/objects/figures/plane/textures/texture.c \
		src/path_tracer/scene/objects/figures/plane/transformations/transformations.c \
		src/path_tracer/scene/objects/figures/plane/plane.c \
		src/path_tracer/scene/objects/figures/quad/getters/getters.c \
		src/path_tracer/scene/objects/figures/quad/hit/hit.c \
		src/path_tracer/scene/objects/figures/quad/textures/texture.c \
		src/path_tracer/scene/objects/figures/quad/transformations/transformations.c \
		src/path_tracer/scene/objects/figures/quad/quad.c \
		src/path_tracer/scene/objects/figures/sphere/getters/getters.c \
		src/path_tracer/scene/objects/figures/sphere/hit/hit.c \
		src/path_tracer/scene/objects/figures/sphere/textures/texture.c \
		src/path_tracer/scene/objects/figures/sphere/transformations/transformations.c \
		src/path_tracer/scene/objects/figures/sphere/utils/utils.c \
		src/path_tracer/scene/objects/figures/sphere/sphere.c \
		src/path_tracer/scene/objects/figures/shared.c \
		src/path_tracer/scene/objects/material/scatters/dielectric_scatter.c \
		src/path_tracer/scene/objects/material/scatters/lambertian_scatter.c \
		src/path_tracer/scene/objects/material/scatters/metallic_scatter.c \
		src/path_tracer/scene/objects/material/modifiers/decrements.c \
		src/path_tracer/scene/objects/material/modifiers/increments.c \
		src/path_tracer/scene/objects/material/modifiers/type.c \
		src/path_tracer/scene/objects/material/material.c \
		src/path_tracer/scene/objects/texture/texture_objects.c \
		src/path_tracer/scene/objects/hooks/transformations/aspect/object_aspect.c \
		src/path_tracer/scene/objects/hooks/transformations/resize/object_resize.c \
		src/path_tracer/scene/objects/hooks/transformations/rotations/object_rotations.c \
		src/path_tracer/scene/objects/hooks/transformations/translations/object_translations.c \
		src/path_tracer/scene/objects/hooks/transformations/object_transformations.c \
		src/path_tracer/scene/objects/hooks/management/copy/object_copy.c \
		src/path_tracer/scene/objects/hooks/management/add/object_add.c \
		src/path_tracer/scene/objects/hooks/management/delete/object_delete.c \
		src/path_tracer/scene/objects/hooks/management/object_management.c \
		src/path_tracer/scene/objects/objects.c \
		src/path_tracer/scene/ray/ray.c \
		src/path_tracer/scene/ray/hit/ray_hit.c \
		src/path_tracer/scene/ray/scatter/ray_scatter.c \
		src/path_tracer/scene/ray/utils/ray_utils.c \
		src/path_tracer/scene/sampling/light_sampling.c \
		src/path_tracer/scene/export/export.c \
		src/path_tracer/scene/background_color/background_color.c \
		src/path_tracer/scene/scene.c \
		src/path_tracer/modes/edit_mode/edit_mode.c \
		src/path_tracer/modes/render_mode/render_mode.c \
		src/path_tracer/utils/math/math_utils.c \
		src/path_tracer/utils/print/print_utils.c \
		src/path_tracer/utils/color/int_color/int_color_utils.c \
		src/path_tracer/utils/color/vect_color/vect_color_utils.c \
		src/path_tracer/utils/rotations/rotations.c \
		src/path_tracer/utils/vectors/functions/vect_functions.c \
		src/path_tracer/utils/vectors/operations/scalar/scalar_operations.c \
		src/path_tracer/utils/vectors/operations/vector/vector_operations.c \
		src/path_tracer/utils/vectors/vectors.c \
		src/path_tracer/path_tracer.c \
		src/mlx/mlx_utils.c \
		src/miniRT.c

OFILES = $(CFILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ = $(OFILES)

DEPS = $(OBJ:%.o=%.d)

INCLUDES = -Iincludes/ -Isrc/ -Ilibraries/

HEADERS = includes/

SRC_DIR = src/

OBJ_DIR = obj/

DIR_LIBFT = libraries/libft/ 

PATH_LFT = libraries/libft/libft.a

DIR_PTF = libraries/printf/

PATH_PTF = libraries/printf/libftprintf.a

MLX_VERSION = 2.4.1

MLX_URL = https://github.com/codam-coding-college/MLX42/archive/refs/tags/v2.4.1.tar.gz

DIR_MLX	 = libraries/mlx/

BUILD_DIR_MLX = libraries/mlx/MLX42/build/

PATH_MLX = $(BUILD_DIR_MLX)libmlx42.a

CFLAGS = -Wall -Wextra -Werror -Ofast -g -fsanitize=address -fsanitize=leak #-fsanitize=thread

MLXFLAGS = -L -lmlx42 -lXext -lX11 -lm -lglfw

CC = cc

ARLIB = ar rc

RM = rm -f

all: $(NAME)

$(NAME): extra_make $(OBJ) $(PATH_LFT) $(PATH_PTF) $(PATH_MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(PATH_LFT) $(PATH_PTF) $(PATH_MLX) $(MLXFLAGS) -o $(NAME)
	@printf "\n$(NAME) COMPILED!\n"

extra_make: $(PATH_MLX)
	@printf "LIBFT: COMPILING...\n"
	@$(MAKE) -C $(DIR_LIBFT) --no-print-directory
	@printf "PRINTF: COMPILING...\n"
	@$(MAKE) -C $(DIR_PTF) --no-print-directory
	@printf "MINILIBX: COMPILING...\n"
	@$(MAKE) -C $(BUILD_DIR_MLX) --no-print-directory

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(DIR_MLX)MLX42:
	@printf "Downloading MLX...\n"
	@curl -sOL $(MLX_URL) || { echo "Failed to download MLX"; exit 1; }
	@tar -xpf v$(MLX_VERSION).tar.gz
	@rm -rf v$(MLX_VERSION).tar.gz
	@mkdir -p $(DIR_MLX)
	@mv -f MLX42-$(MLX_VERSION) MLX42
	@mv -f MLX42 $(DIR_MLX)
	@echo "MLX downloaded successfully\n"

$(PATH_MLX): $(DIR_MLX)MLX42
	@echo "Creating MLX"
	@cd $(DIR_MLX)MLX42 && cmake -B build && cmake --build build --parallel --config Release

clean:
	@$(MAKE) -C $(DIR_LIBFT) clean  --no-print-directory
	@$(MAKE) -C $(DIR_PTF) clean --no-print-directory
	@$(RM) $(OBJ)
	@printf "MiniRT: Object files removal successful!\n"

fclean:
	@$(MAKE) -C $(DIR_LIBFT) fclean --no-print-directory
	@$(MAKE) -C $(DIR_PTF) fclean --no-print-directory
	@$(RM) $(OBJ)
	@$(RM) $(NAME)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BUILD_DIR_MLX)
	@printf "MiniRT: Exe && MLX build removal successful!\n"

cleanMLX:
	@rm -rf $(DIR_MLX)
	@printf "MiniRT: MLX complete removal successful!\n"

cleanALL: fclean cleanMLX
	@printf "MiniRT: Total clean successful!\n"

re:	fclean all

.PHONY: all clean fclean re

-include $(DEPS)
-include $(MDEPS)
-include $(BDEPS)