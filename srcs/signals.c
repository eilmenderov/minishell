#include "head_minishell.h"

/*
**	@brief	for ctrl+C in main state	
*/
static void	ft_signal_cltr_c(int sig)
{
	/* problem with newline after cltr_c + cltr_d // for work!!! */
	(void)sig;
	if (g_stat == 0)
		write(2, "\n", 1);
	// printf("rl_repl_line = %d g_stat = %d\t", rl_replace_line("", 0), g_stat);
	// printf("rl_onne_line = %d g_stat = %d\n", rl_on_new_line(), g_stat);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_stat = 100;
}

/*
**	@brief	signal handlers in main state	
*/
void	ft_signal(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, SIG_IGN);
}
