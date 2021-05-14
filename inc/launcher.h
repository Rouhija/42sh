/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:14:31 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/14 17:14:50 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_H
# define LAUNCHER_H

/*
** List of built-in shell commands.
*/

# define BUILTIN_ARR	"exit", "jobs", "fc", "cd", "echo", "type", "alias", "unalias", "set"
# define BUILTIN_SLOTS	9
# define BUILTIN_LEN	8

# define EXEC_OK 1
# define EXEC_ERROR 0

int			isbuiltin(char *command);
void		launch_job(t_job *job, int foreground);
void		launch_process(t_process *process, t_job *job, pid_t pgid, int infile, int outfile, int errfile, int foreground);
int			run_builtin(char **argv);

/*
** Builtin command protoypes.
*/

int 		fc(char **argv);
int			alias_builtin(char **args);
int			cd_builtin(char **argv);
int			echo_builtin(char **argv);
void		exit_builtin();
int			jobs_builtin(char **argv);
int			set_builtin(char **argv);
int         type_builtin(char **args);
int			unalias_builtin(char **argv);

#endif
