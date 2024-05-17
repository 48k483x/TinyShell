#include "../../minishell.h"

void	disable_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	int_handler(int signum)
{
	int	status;

	(void)signum;
	if (g_sig.pid != 0)
	{
		waitpid(g_sig.pid, &status, 0);
		g_sig.exit_status = 130;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.exit_status = 1;
	}
	g_sig.sigint = 1;
}

void	quit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		return ;
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}
