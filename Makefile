.PHONY: all clean fclean re val norm
NAME = cub3D

LIBFT_DIR = libft
LIBFT_A = libft.a

MLX_DIR	= mlx_linux
MLX_A = mlx_Linux.a

INCLUDE_DIR = include
SRCS_DIR = srcs
OUT_DIR = out

RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

SRCS = \
$(addsuffix .c, \
	$(addprefix $(SRCS_DIR)/, \
		cast_rays_utils \
		cast_rays \
		dark_color \
		draw_background \
		draw_player_2d \
		draw_map_2d \
		draw_rays_2d \
		draw_wall \
		end \
		ft_circle_put_to_image \
		ft_pixel_put_to_image \
		ft_rectangle_put_to_image \
		ft_square_put_to_image \
		get_img_color \
		get_map \
		gettime \
		init \
		key_hook \
		loop_hook \
		main \
		player_rotate \
	) \
	$(addprefix $(SRCS_DIR)/parse/, \
		parse_config \
		parse_config_color \
		parse_config_direction \
		parse_config_utils \
		parse_config_validation \
		parse_file \
		parse_file_read \
		parse_file_utils \
		parse_finalize \
		parse_map \
		parse_map_utils \
		parse_map_validation \
		parse_utils \
	) \
) \

OBJS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))

NPD_FLAG = --no-print-directory

CFLAGS = -Wall -Werror -Wextra
IFLAGS = -I/usr/$(INCLUDE_DIR) -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/$(INCLUDE_DIR) -I$(MLX_DIR)
LFLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft
VFLAGS = \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-fds=yes \

all: $(NAME)

$(NAME): $(LIBFT_DIR)/$(LIBFT_A) $(MLX_DIR)/$(MLX_A) | $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

$(LIBFT_DIR)/$(LIBFT_A):
	@make $(NPD_FLAG) -C $(LIBFT_DIR) all

$(MLX_DIR)/$(MLX_A):
	@make $(NPD_FLAG) -C $(MLX_DIR) all

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@make $(NPD_FLAG) -C $(LIBFT_DIR) clean
	@make $(NPD_FLAG) -C $(MLX_DIR) clean
	@$(RM) -r $(OUT_DIR)

fclean: clean
	@$(RM) $(LIBFT_DIR)/$(LIBFT_A)
	@$(RM) $(NAME) $(VALGRIND_LOG)

re: fclean all

de:
	@clear
	@make $(NPD_FLAG) re
	@./$(NAME)

VALGRIND_LOG = valgrind.log

val:
	@clear
	@make $(NPD_FLAG) re
	@valgrind $(VFLAGS) ./$(NAME) 2> $(VALGRIND_LOG)

norm:
	@$(call check_norminette, $(LIBFT_DIR))
	@$(call check_norminette, $(SRCS_DIR))
	@$(call check_norminette, $(INCLUDE_DIR))

define ok
	echo $1"$(GREEN)OK$(RESET)"
endef

define check_norminette
	@if norminette $1 | grep -q Error; then \
		norminette $1 | grep Error; \
	else \
		$(call ok, $1": "); \
	fi
endef
