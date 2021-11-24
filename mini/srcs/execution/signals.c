/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbifenzi <mbifenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 03:57:11 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/24 02:50:04 by mbifenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	__get_var(t_norm op, int value)
{
	static int		exit_status = 0;
	static int		pids = 0;

	if (op == GETEXIT)
		return (exit_status);
	if (op == SETEXIT)
		exit_status = value;
	if (op == SETPID)
		pids = value;
	if (op == GETPID)
		return (pids);
	return (0);
}

void	handle_sigint(int sigint)
{
	(void)sigint;
	if (__get_var(GETPID, 0) == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		__get_var(SETEXIT, 130);
	}
}
