/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec_helper1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbifenzi <mbifenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 02:20:46 by mbifenzi          #+#    #+#             */
/*   Updated: 2021/11/24 02:23:59 by mbifenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_lcmd(t_tools *tools, t_command *cmd, char ***env)
{
	tools->pid[tools->i] = fork();
	if (tools->pid[tools->i] == 0)
	{
		if (cmd->redirect)
			redirect_to(cmd, tools);
		if (builtin(cmd, env))
			exit(0);
		else
			non_builtin(cmd, *env);
	}
}

void	tools_init(int i, t_tools *tools)
{
	tools->i = 0;
	tools->in = -1;
	tools->out = -1;
	tools->pid = (int *)malloc((i + 1) * sizeof(int));
	garbage(&g, tools->pid);
}

void	ft_free_tools(t_tools *tools)
{
	free(tools->pid);
	tools->pid = NULL;
	free(tools);
	tools = NULL;
}