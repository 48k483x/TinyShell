#include "../../minishell.h"

void disable_echo(void)
{
    // This function disables echo in the terminal. This is useful when we want
    // to read input from the user without displaying it on the screen.

    // The termios structure is used to store the terminal attributes. The
    // tcgetattr function gets the current terminal attributes and stores them in
    // the termios structure.

    // The c_lflag field of the termios structure contains local flags that control
    // various terminal settings. The ECHO flag controls whether input characters
    // are echoed to the terminal.

    // The &= ~ operator clears the ECHO flag, disabling echo.

    // The tcsetattr function sets the terminal attributes to the values stored in
    // the termios structure.
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void    int_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
    }
}

void quit_handler(int signum)
{
    if (signum == SIGQUIT)
    {
        return ;
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
    }
}

