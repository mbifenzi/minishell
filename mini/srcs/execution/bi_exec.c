/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbifenzi <mbifenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 00:52:50 by mbifenzi          #+#    #+#             */
/*   Updated: 2021/11/18 22:21:03 by mbifenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void    middle_exec(int *fd, t_main *cmd)
// {
// 	if ()
// }


void	child_process1(t_main *cmd)
{
	int fd[2];
    int pid;
    if (pipe(fd) == -1)
        error();
    pid = fork();
    if(pid == -1)
        error();
    if (pid == 0)
    {
        close (fd[0]);
        dup2(fd[1], 1);
        middle_exec(fd, cmd);
    }
    else
    {
        close (fd[1]);
        dup2(fd[0], 0);
        close (fd[0]);
    }
    
}
void    bi_execute(t_main   *main)
{
    t_command	*cmdi;
    cmdi = main->cmd;
    while (cmdi)
    {
        child_process(cmdi);
        cmdi = cmdi->nextcmd;
    }
    	printf("main->line = %s\n", main->line);

}