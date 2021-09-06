#include "head_minishell.h"

void	ft_multiple_cmd(t_cmd *cmd)
{
	ft_wait_all_cmd(cmd->data);
	return ;
}
