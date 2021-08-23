#include "head_minishell.h"

static void	v_check_cmd(t_data *data)
{
	char	**split;
	int		i;

	if (ft_strlen_m(data->str_cmd, '|'))
	{
		split = ft_split(data->str_cmd, '|');
		i = 0;
		while (split[i])
			v_pool_cmd(data, split[i]), free(split[i]), i++;
		if (split)
			free(split);
	}
	else
		v_pool_cmd(data, data->str_cmd);
	i = 0;
	while (split[i])
		printf("str[%d] : |%s|\n", i, split[i]), i++;
}

int	main(void)
{
	char	*cmd;
	t_data	data;

	data.str_cmd = ft_strdup("ls -la > outfile");
	v_check_cmd(&data);
}

// gcc v_cmd.c ../libft/libft.a  && ./a.out