/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:37:55 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/22 21:09:51 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include "libft/libft.h"

typedef struct	s_sig
{
	int		sigint;
	int		sigquit;
	pid_t	pid;
	int		ret;
	char	*cur_cmd;
}				t_sig;

typedef struct	s_shell
{
	char	**cmds;
	char	**pipes;
	char	**args;
	char	**paths;
	char	**exports;
	char	*filename;
	char	*cmd;
	char	**history;
	int		his_n;
}				t_shell;

t_sig			g_sig;

int				join_free(char **dest, char *s, int j);
int				join_sub(char **dest, char *s, int j);
char			*join_free_char(char *dest, char c, int j);
int				array_size(char **arr);
void			print_env_export(char **env, char **exports);
void			free_all(t_shell *shell, char **env, int code);
void			ft_exit(t_shell *shell, char **env);
int				ft_putchar(int c);
struct termios	init_termcap(void);
void			get_termcap(char *s);
int				shell_loop(char ***env, t_shell *shell);
void			free_shell(t_shell *shell);
void			quit_handler(int signum);
void			int_handler(int signum);
char			*find_redirections(char ***args, int *redir);
int				fd_error(char *filename);
char			*find_arg(char **args, int *i, char c);
int				cmd_begin(char *s1, char *s2);
void			handle_up(t_shell *shell, char *cmd, int *cmd_len, int *n);
void			handle_down(t_shell *shell, char *cmd, int *cmd_len, int *n);
void			handle_arrows(t_shell *shell, char *cmd, int *cmd_len, int *n);
void			handle_del(t_shell *shell, char *cmd, int *cmd_len, int *n);
void			handle_char(t_shell *shell, char *cmd, int *cmd_len, int *n);
char			*get_cmd(char **env, t_shell *shell);
char			**get_paths(char **env);
int				exec_prog(char **env, t_shell *shell);
int				find_prog(char **argv, char **env, char **paths,
				t_shell *shell);
void			free_half(t_shell *shell, char **env, char *cmd);
void			free_array(char **arr);
void			free_array_int(int **arr, int n);
void			free_array_n(char **arr, int n);
int				handle_pipes(char ***env, char *cmd, t_shell *shell);
int				handle_cmds(char ***env, char *cmd, t_shell *shell);
int				route_cmd(char ***env, t_shell *shell);
void			find_dollars(char ***args, char **env);
char			*dollar_found(char *arg, char **env, int *i);
int				ft_echo(char **args);
int				ft_pwd(char **args);
int				find_env(char **env, char *target);
void			update_pwd(char ***env, char *pwd);
int				ft_chdir(char *target, char ***env);
int				special_chdir(char ***env, char *target);
void			print_env(char **env);
void			add_env(char *key, char *value, char ***env);
void			remove_env(char ***env, int n);
void			dehash(char *line, char **key, char **value);
void			rehash(char ***env, int i, char *key, char *value);
int				index_of(char *s, char c);
void			ft_unsetenv(char **args, char ***env, t_shell *shell);
int				ft_export(t_shell *shell, char ***env);
int				ft_env(char **env, t_shell *shell);
int				env_loop(char ****en_cp_pt_cm, t_shell *shell, int **options,
				int *i);
void			env_end(int **options, char **env, char **copy, char **args);
void			print_unset(int *options, char **env);
void			print_args(char **args);
int				interpret_option(char **args, int *i, char ***env,
				int **options);
int				print_unrecog_option(char *s);
int				print_no_arg_chdir(void);
int				print_no_arg_unset(void);
void			restore_env(char ***env);
void			print_verbose(char **args, int *options, char **env);
void			print_cd_error(char *dir);
int				print_invalid_option(char *s);
void			empty_env(char ***env, int **options);
void			add_env_hashed(char *line, char ***env);
int				is_short_option(char c);
void			printf_env(char **env, int *options);
int				exec_options(int **options, char **args, int *i, char ***env);
int				exec_options2(int **options, char **args, int *i, char ***env);
int				print_env_version(void);
int				print_env_help(void);
int				find_dir(char **args, int *i, char ***env);
void			is_long_option(char *arg, int **options);
int				special_cmp(char *s1, char *s2);
char			**copy_array(char **array);
void			found_dir(char ***env, char *dir);
int				chdir_env(char **env, char *target);
int				unset(char **args, int *i, char ***env);
void			add_unset(char ***env, char *key);
char			**split_quoting_set(char const *s, char *set);
int				nb_of_splits_quoting(char const *s, char *set);
void			is_quote(char c, int *squote, int *dquote);
int				handle_quote(char ***args, char **env);
#endif
