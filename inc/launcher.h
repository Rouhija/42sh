/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:14:31 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/22 13:27:34 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_H
# define LAUNCHER_H

/*
** List of built-in shell commands.
*/

# define BUILTIN_ARR	"exit", "jobs", "fc", "cd", "echo", "type", "alias", "unalias", "set", "export", "unset", "fg", "bg"
# define BUILTIN_SLOTS	13
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
int			bg_builtin(char **argv);
int			cd_builtin(char **argv);
int			echo_builtin(char **argv);
void		exit_builtin();
int			export_builtin(char **argv);
int			fg_builtin(char **argv);
int			hash_builtin(char **argv);
int			jobs_builtin(char **argv);
int			set_builtin(char **argv);
int			test_builtin(char **argv);
int         type_builtin(char **args);
int			unalias_builtin(char **argv);
int			unset_builtin(char **argv);

/*
** Builtin command utils
*/

char	current(t_job *job);
char	*state(t_job *job);

#endif
