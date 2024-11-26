/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:14:51 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/21 17:35:26 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Vérifie si c'est une commande ou un argument
int	is_command(int type)
{
	if (type == CMD || type == ARG)
		return (0);
	return (1);
}

//Vérifie si les redirections sont possiblement faisables
int	verif_redirect(t_token *current_t)
{
	if (current_t->next == NULL || is_command(current_t->next->t_type) == 1)
		return (ft_error("ERROR PIPE\n", 0, 0));
	return (0);
}

//Vérifie le type et l'existence des tokens
int	verif_token(t_shell *sh)
{
	int		verif;
	t_token	*temp;

	verif = 0;
	temp = sh->token;
	if (temp->t_type == PIPE && temp->next == NULL)
		return (ft_error(SYNTAX_ERROR, '|', 1));
	while (temp != NULL)
	{
		if (temp->t_type == TRUNC || temp->t_type == INPUT
			|| temp->t_type == APPEND || temp->t_type == HEREDOC)
			verif = verif_redirect(temp);
		temp = temp->next;
		if (verif != 0)
			return (verif);
	}
	return (verif);
}

// Helper function to print spaces
void	print_spaces(int spaces)
{
	for (int i = 0; i < spaces; i++)
		printf(" ");
}

// Function to recursively print the AST in a tree-like format
void	print_ast_tree(t_ast *node, int depth)
{
	if (!node)
		return;

	// Calculate spacing for proper alignment
	int spacing = 16 - depth * 2;

	// Print the current node
	print_spaces(spacing);
	printf("%s", node->value ? node->value[0] : "(null)");

	// Check if node has children
	if (node->left || node->right)
	{
		printf("\n");
		print_spaces(spacing - 2);
		printf("/               \\\n");

		// Recursively print left and right children
		if (node->left)
			print_ast_tree(node->left, depth + 1);
		else
		{
			print_spaces(spacing * 2 / 3);
			printf("(null)\n");
		}

		if (node->right)
			print_ast_tree(node->right, depth + 1);
		else
		{
			print_spaces(spacing * 2 / 3);
			printf("(null)\n");
		}
	}
	else
	{
		printf("\n");
	}
}

// Wrapper function to start printing the AST
void	print_ast(t_ast *root)
{
	if (!root)
	{
		printf("AST is empty\n");
		return;
	}
	printf("=== Abstract Syntax Tree ===\n\n");
	print_ast_tree(root, 0);
	printf("\n============================\n");
}

//Gère le déroulement général du parsing
int	parsing(t_shell *sh)
{
	if (verif_token(sh) > 0)
		return (1);
	sh->ast = make_ast(sh->token);
	if (!sh->ast)
		return (1);
	print_ast(sh->ast);
	return (0);
}
 