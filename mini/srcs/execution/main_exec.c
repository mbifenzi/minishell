/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbifenzi <mbifenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:39:02 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/24 02:28:22 by mbifenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_option(char **args)
{
	if (!ft_strncmp(args[1], "-n", 2))
		return (2);
	return (1);
}

int	echoo(char **args)
{
	int	i;
	int	e;
	int	sa;

	sa = ft_strdlen(args);
	if (sa == 1)
		write(1, "\n", 1);
	else if (sa >= 2)
	{
		i = check_option(args);
		e = i;
		while (args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			if (args[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		if (e == 1)
			write(1, "\n", 1);
	}
	return (1);
}

char	*find_path2(char *cmd, char **env)
{
	int		i;
	int		sa;
	int		scmd;
	char	*path;

	i = 0;
	sa = ft_strdlen(env);
	scmd = ft_strlen(cmd);
	while (!ft_strnstr(env[i], cmd, ft_strlen(cmd)) && i < sa)
		i++;
	if (i == sa)
		return (NULL);
	else if (ft_strchr(env[i], '='))
		path = ft_strdup(env[i] + scmd + 1);
	else
		path = ft_strdup(cmd);
	return (path);
}

char	*find_path3(char *cmd, char **env)
{
	int		i;
	int		sa;
	int		scmd;
	char	*path;

	i = 0;
	sa = ft_strdlen(env);
	scmd = ft_strlen(cmd);
	while (ft_strncmp(env[i], cmd, ft_strlen(cmd)) && i < sa)
		i++;
	if (i == sa)
		return (NULL);
	else if (ft_strchr(env[i], '='))
		path = ft_strdup(env[i] + scmd + 1);
	else
		path = ft_strdup(cmd);
	return (path);
}

int	execute(t_main *main)
{
	t_command	*cmd1;
	t_tools		*tools;
	int			i;
	int			in;
	int			out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	i = 0;
	tools = malloc(sizeof(t_tools));
	garbage(&g, tools);
	tools_init(main->count, tools);
	cmd1 = main->cmd;
	if (!cmd1->nextcmd && builtin(cmd1, &main->env))
		return (0);
	while (cmd1->nextcmd)
	{
		execute_pipe(tools, cmd1, &main->env);
		tools->i++;
		cmd1 = cmd1->nextcmd;
	}
	execute_lcmd(tools, cmd1, &main->env);
	tools->i++;
	while (i <= main->count)
	{
		waitpid(tools->pid[i], NULL, 0);
		i++;
	}
	dup2(in, 1);
	dup2(out, 0);
	close(in);
	close(out);
	ft_free_tools(tools);
	return (1);
}
