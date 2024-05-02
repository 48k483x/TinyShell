/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbidayat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:26:25 by asfaihi           #+#    #+#             */
/*   Updated: 2024/05/02 10:22:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	allocate_args(char *s, t_cmd *cmd, t_list *env_lst)
{
	int		ret;
	int		i;

	ret = get_size(s);
	if (ft_strchr(s, '$'))
		ret += count_extra_args(s, 0, 0, env_lst);
	cmd->args = malloc(sizeof(char *) * (ret + 1));
	i = 0;
	while (i <= ret)
		cmd->args[i++] = NULL;
}
void	initialize_cmd_node(t_cmd *new, char *s, t_list *env_lst)
{
	int		i;

	i = 0;
	new->cmd = NULL;
	new->args = NULL;
	new->redir = NULL;
	allocate_args(s, new, env_lst);
}

void	initialize_redir_node(t_redir *new)
{
	new->file = NULL;
	new->type = '\0';
}

void	initialize_env_node(t_env *new)
{
	new->key = NULL;
	new->value = NULL;
}

void	initialize_prs_node(t_prs *prs)
{
	prs->i = 0;
	prs->arg_num = 0;
	prs->ambigous = 0;
	prs->ret_value = 0;
	prs->outside_quote = 0;
	prs->extra_args = NULL;
}
