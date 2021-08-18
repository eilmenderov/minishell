#include "head_minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*str;
	int		i;

	v_init_data(&data, env);
	i = 0;
	while (i < 1)
	{
		str = readline(SHELL_FW);
		add_history(str);
		if (!ft_parsing(&data, str))
			printf("|%s|\n", data.str_cmd);
		// 	ft_run_cmd(&data);
		// ft_free_cmd_str(&data, str);
		i++;
	}
//	v_print_data(&data);
	v_free_data(&data);
	// sleep (20);
	return (0);
}
