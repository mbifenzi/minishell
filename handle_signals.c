/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbifenzi <mbifenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:06:00 by mbifenzi          #+#    #+#             */
/*   Updated: 2021/11/21 22:43:59 by mbifenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini/includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

// void    handle_sig()
// {
// 	printf("signal caught in here \n");
//     exit (0);
// }

// int main()
// {
//     int pid;
//     signal(SIGINT, handle_sig);
// 	signal(SIGMINE, handle_sig);
//     pid = fork();
//     if (pid == 0)
//     {
//         while (1)
//         {
//             printf("weeeeeeeee\n");

//         }
//     }
//     waitpid(pid , NULL, 0);
// }