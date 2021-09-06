#include "head_minishell.h"

void	ft_multiple_cmd(t_cmd *cmd)
{
	// ft_create_pipes(cmd->data);
	// ft_close_pipes(cmd->data, 3);
	// exit(0);
	ft_wait_all_cmd(cmd->data);
	return ;
}
