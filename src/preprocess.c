/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:59:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 19:19:37 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	append_job(t_job **head, t_job *new)
{
	t_job		*tmp;

	tmp = *head;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*head = new;
}

static void	launcher(t_job *job)
{
	while (job && !job->launched)
	{
		launch_job(job, job->foreground);
		job = job->next;
	}
	do_job_notification();
}

static void	loader(t_lexer *lexer)
{
	t_token		*tokens;
	t_job		*job;

	tokens = lexer->head;
	job = create_job(&tokens);
	append_job(&g_shell->jobs, job);
	while (tokens)
		append_job(&g_shell->jobs, create_job(&tokens));
	if (lexer->flags & DEBUG_JOBS)
		job_debug(job);
	launcher(job);
}

void	preprocess(char *input, t_shell *shell)
{
	t_lexer		lexer;

	ft_bzero(lexer.data, ARG_MAX);
	lexer.flags = 0;
	lexer.count = 0;
	lexer.head = NULL;
	lexer.first = NULL;
	lexer.last = NULL;
	tokenize(&lexer, input);
	if (lexer.flags & DEBUG_LEXER)
		lexer_debug(lexer);
	else if (~shell->mode & INTERRUPT)
	{
		add_entry(lexer.data, shell);
		parser(&lexer, shell) == PARSER_OK ? loader(&lexer) : PASS;
	}
	lexer_del(&lexer);
}
