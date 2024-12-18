/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:58:47 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 13:01:30 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_old_pwd(t_env *env)
{
	while (env->next && ft_strcmp(env->value, "OLDPWD") != 0)
		env = env->next;
	return (env->content);
}

void	ft_pwd(t_shell *sh)
{
	char	*path;

	(void)sh;
	path = getcwd(NULL, 0);
	if (!path)
		write(2, "getcwd failed !\n", 16);
	else
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
	g_exit_status = 0;
}
