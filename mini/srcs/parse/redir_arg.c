/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:01:39 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/23 20:33:58 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		sizedoublp(char **a)
{
	int i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}
char	**arg_fill(t_redirect **red, char ***arg, int j)
{
	char **a;
	char *c;
	char *q;
	
	a = ft_split1((*red)->line + j, ' ');
	if ((*red)->type == 4)
	{	
		c = ignore_quotes(a[0], 1);
		//(*red)->file = ft_strdup(ignore_quotes(a[0], 1));
		(*red)->file = ft_strdup(c);
		free(c);
	}
	else
	{
		c = dollar_check(a[0], (*red)->env);
		q = ignore_quotes(c, 1);
		(*red)->file = ft_strdup(q);
		free(c);
		c = NULL;
		//free(q);
	}
	//	(*red)->file = ft_strdup(ignore_quotes(dollar_check(a[0], (*red)->env),  1));
//	free(a[0]);
	a[0] = NULL;
	*arg = a;
	a++;
	if (sizedoublp(a) > 0)
		return (a);
	return (NULL);
}

char	**getter(t_redirect **red, int i, char c, char ***arg)
{
	char **a;

	int j;
	
	j = 1;
	a = NULL;
	if ((*red)->line[1] == '>' || (*red)->line[1] == '<')
		j = 2;
	if (i == 0 && (c== '>' || c == '<'))
	{
		(*red)->flag = 1;
		return (arg_fill(red, arg, j));
	}
	else
	{
		if (((*red)->line[0] == '>' || (*red)->line[0] == '<'))
		{
			(*red)->flag = 0;
			return (arg_fill(red, arg, j));
		}
		else
		{
			(*red)->file = ft_strdup("");
			a = ft_split1((*red)->line, ' ');
			(*red)->flag = 0;
			return (a);
		}
	}
	return (0);
}

void	ft_fres1(char **b)
{
	int i;

	i = 0;
	while (b[i])
	{
		free(b[i]);
		b[i] = NULL;
		i++;
	}
	free(b);
	b = NULL;
}

int		get_argv(t_command *cmd, char **env)
{
	int i;
	char **b;
	t_redirect *l;

	i = 0;
	cmd->fcmd = NULL;
	cmd->argument = NULL;
	l = cmd->redirect;
	b = NULL;
	(void)env;
	while (i <= cmd->count)
	{
		if (cmd->cmd)
		{
			b = getter(&cmd->redirect, i, cmd->cmd[0], &cmd->fakearg);
			if (b)
				cmd->argument = ignore_quotes1(strdjoin(cmd->redirect->flag,cmd->argument, b), env);
			free(cmd->fakearg);
			cmd->fakearg = NULL;
			cmd->redirect = cmd->redirect->nextred;
			i++;
		}
	}
	if (cmd->argument)
		cmd->fcmd = cmd->argument[0];
	cmd->redirect = l;
	return (1);
}
