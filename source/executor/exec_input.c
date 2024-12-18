/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:05:37 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 14:49:33 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input(t_redir *node, t_env **env, t_shell *sh)
{
	int	fd;

	fd = open(node->file, O_RDONLY);
	if (fd < 0 || !node->cmd)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (node->cmd)
		execute_ast(node->cmd, env, sh);
}
