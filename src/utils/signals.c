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
void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
    }
}

void d_handler(int signum)
{
    if (signum == SIGQUIT)
    {
        //printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
    }
}

void sigchld_handler(int signum)
{
    // This function is a signal handler for the SIGCHLD signal. This signal is
    // sent to a process when one of its child processes terminates or stops.

    // The while loop continues as long as there are any child processes that
    // have terminated but not been waited for. This is determined by the waitpid
    // function, which waits for state changes in a child of the calling process.

    // The -1 argument to waitpid means wait for any child process. The function
    // will return the PID of the child process that has state changes, or -1 if
    // there are no child processes.

    // The NULL argument means that we're not interested in the exit status of
    // the child.

    // The WNOHANG argument means to return immediately if there are no child
    // processes that have terminated. If this option was not specified, waitpid
    // would block until a child process terminates.

    // So, in summary, this function cleans up all terminated child processes,
    // preventing them from becoming zombie processes.
    (void)signum;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}
