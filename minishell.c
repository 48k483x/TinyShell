#include "minishell.h"

void _fork(t_tini *tiny)
{
    tiny->pid = fork();
    if (tiny->pid < 0)
        printsdr("fork");
    if (tiny->pid == 0)
        execve_error(tiny);
    else
        waitpid(tiny->pid, NULL, 0);
}

// int main()
// {
//     t_tini tiny;

//     while (1)
//     {
//         signal(SIGINT, sig_handler);
//         signal(SIGCHLD, sigchld_handler);
//         tiny.line = readline(initialise_prompt(&tiny));
//         if (!tiny.line || _strlen(tiny.line) == 0)
//             continue;
//         if (tiny.line && !check_syntax(tiny.line))
//         {
//             path_checker(&tiny);
//             add_history(tiny.line);
//             _fork(&tiny);
//         }
//     }
//     _free(&tiny);
// }


int main(int ac, char **av, char **env)
{
    t_tiny tiny;
    
    (void)ac;
    (void)av;
    tiny.in = dup(0);
    tiny.out = dup(1);
    tiny.exit = 0;
    tiny.ret = 0;
    tiny.no_exec = 0;
    reset_fds(&tiny);
    init_env(&tiny, env);
    private_init_env(&tiny,env);
    set_shell_level(tiny.env);
    // while (1)
    // {
    //     tiny.line = readline(initialise_prompt(&tiny));
    //     if (!tiny.line || _strlen(tiny.line) == 0)
    //         continue;
    //     if (tiny.line && !check_syntax(tiny.line))
    //     {
    //         add_history(tiny.line);
    //     }
    // }
    free_all(&tiny);
}
