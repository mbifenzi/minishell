/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbifenzi <mbifenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 00:52:50 by mbifenzi          #+#    #+#             */
/*   Updated: 2021/11/21 23:41:32 by mbifenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
char	*find_path1(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	**paths;
	char	*tmp;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	path = ft_strdup(env[i] + 5);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}
void	execute_exe(t_command *cmd, char **env)
{
	// char	**splited;
	char	*file_path;

	// splited = ft_split(cmd, ' ');
	file_path = find_path1(cmd->argument[0], env);
	if (execve(file_path, cmd->argument, env) == -1)
		error();
}

void	child_process1(t_command *cmd, char **env)
{
	int fd[2];
    int pid;
    if (pipe(fd) == -1)
        error();
    int in;
    int out;

    in = dup(0);
    out = dup(1);
    pid = fork();
    if(pid == -1)
        error();
    if (pid == 0)
    {
        close (fd[0]);
         dup2(fd[1], 1);
        close(fd[1]);
        execute_exe(cmd, env);
    }
    else
    {
        close (fd[1]);
        dup2(fd[0], 0);
        close (fd[0]);
    }
    dup2(in, 0);
    dup2(out, 1);
    close(in);
    close(out);
   // waitpid(pid, NULL, 0);
    // dup2(1, fd[1]);
    // dup2(0, fd[0]);
}

int    bi_execute(t_main   *main, char **env)
{
    t_command	*cmdi;
    cmdi = main->cmd;
    while (cmdi->nextcmd)
    {
        child_process1(cmdi, env);
        cmdi =  cmdi->nextcmd;
       // return (-1);
    }
    int pid;
    pid = fork();
    if (pid == 0)
        execute_exe(cmdi, env);
    waitpid(pid, NULL, 0);
    //else
    //{
      //  printf("waa 3ok3ook\n");
        //return (1);
    //}

    // exit(0);
    // printf("main->line = %s\n", main->line);
    return(1);

}