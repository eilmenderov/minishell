#include "head_minishell.h"

typedef struct s_cmd
{
	char			*coomand;
	char			**args;
	struct s_cmd	*next;
}				t_cmd;

void	ft_run_cmd(char *str)
{
	t_cmd	*tmp;
	char	**split;
	int		i;

	split = ft_split(str, ' ');
	i = 0;
	while (split[i])
		printf("str[%d] : |%s|\n", i, split[i]), i++;
	// ft_porc_cmd();
}

int	main(void)
{
	char	*cmd;

	cmd = ft_strdup("< privet echo 1234sad | cat -e");
	ft_run_cmd(cmd);
}
