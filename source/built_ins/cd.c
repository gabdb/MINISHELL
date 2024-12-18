/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:28:41 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 16:05:37 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_old_pwd(t_env *env)
{
	while (env && env->next && ft_strcmp(env->value, "OLDPWD") != 0)
		env = env->next;
	if (env && env->content)
		free(env->content);
	if (env)
		env->content = getcwd(NULL, 0);
}

void	update_pwd(t_env *env)
{
	while (env && env->next && ft_strcmp(env->value, "PWD") != 0)
		env = env->next;
	if (env && env->content)
		free(env->content);
	if (env)
		env->content = getcwd(NULL, 0);
}

void	my_write(int fd, char *str, int flag)
{
	write(fd, str, ft_strlen(str));
	if (flag == 1 || flag == 2)
		g_exit_status = 1;
}

void	write_plus_newline(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	ft_cd(t_cmd *node, t_env *env, char *path)
{
	g_exit_status = 0;
	if (!(node->arg[1]))
	{
		path = find_home(env);
		if (!path)
			return (my_write(2, "minishell: cd: HOME not set\n", 1));
	}
	else
		path = node->arg[1];
	if (path && ft_strcmp(path, "-") == 0)
	{
		path = find_old_pwd(env);
		write_plus_newline(1, path);
	}
	update_old_pwd(env);
	if (chdir(path) != 0)
	{
		my_write(2, "minishell: cd: ", 1);
		my_write(2, node->arg[1], 1);
		my_write(2, ": No such file or directory\n", 1);
	}
	update_pwd(env);
}
