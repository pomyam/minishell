/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:23:03 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/16 20:25:23 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <locale.h>
# include <errno.h>
# include "../src/libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <editline/readline.h>
# include <signal.h>

# define PIPE '1'
# define OTHER '0'
# define DOUBLEQUOTE '2'
# define QUOTE '3'
# define RDOUT '4'
# define RDIN '5'
# define SPAC '6'
# define DOLLAR '7'
# define HEREDOC_IN '8'
# define HEREDOC_OUT '9'
# define WORD 'a'

# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

struct	s_exec;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}				t_redir;

typedef struct s_signal
{
	pid_t	pid;
}				t_signal;

typedef struct s_exec
{
	char			**args;
	char			*path;
	int				fd[2];
	int				fdin;
	int				fdout;
	int				type;
	struct s_exec	*next;
	struct s_exec	*prev;
	int				exit_status;
	int				pid;
	int				num;
	int				not_found;
	t_redir			*redir;
}				t_exec;

typedef struct s_command
{
	char		type;
	char		*content;
	int			num;
}				t_command;

typedef struct s_msh
{
	char		**env_copy;
	char		**dop;
	char		*line;
	char		*mask;
	char		**commands;
	size_t		word_count;
	t_command	*coms;
	int			tmp_fd[2];
	int			flag;
	int			exit_status;
	int			count;
	int			cost;
	t_signal	sig;
}				t_msh;

typedef struct s_quotes
{
	int		dq;
	int		oq;
	int		i;
	char	*result;
	char	*copy;
}			t_quotes;

typedef struct s_dollar
{
	char	*start;
	char	*part;
	int		len;
}				t_dollar;

t_msh	g_msh;

int		get_request(t_msh *msh);
int		cmp_env(char *tmp, char *env);
int		make_commands(t_msh *msh);
int		split_with_mask(t_msh *msh);
int		find_quotes(t_msh *msh);
int		ft_strcmp(const char *str1, const char *str2);
int		get_mask(char c);
int		start_exec(t_msh *msh);
int		is_valid_env(char c);
int		add_symbol_to_str(char **result, char *copy,
			int open_quotes, int double_quotes);
char	**add_to_array(char **table, char *str);
int		free_table(char **table);
void	give_answer(t_msh *msh);
int		handle_redirect(t_exec *now);
int		exec_simple_cmd(t_exec *head);
int		is_builtin(char *str);
int		only_spaces(char *s);
int		parse_line(t_msh *msh);
int		error_message(char *str);
t_exec	*new_exec(void);
t_redir	*new_redir(void);
void	push_back_red(t_redir **head, t_redir *new);
int		exec_pipeline(t_exec *head);
int		exec_pipe(t_exec *head);
void	get_fd(t_exec *head, int fd_in, int fd_out);
int		split_msh(t_msh *msh, char *line, char *mask, size_t n);
int		find_in_envp(char *str, t_msh *msh);
char	*extend_str(char **com);
int		parse_execs(t_msh *msh, t_exec **head);
int		add_to_redir(char **extend, int *i, t_exec *tmp);
int		is_redir(char *str);
int		find_bin(char *com, char **paths, t_exec *exec);
int		is_redir(char *str);
void	build_in(char **line);
int		do_heredoc(t_exec *now, t_redir *red);
int		message_errno(int err, char *str);
void	reinit_msh(t_msh *msh);
void	init_msh(t_msh *msh);
int		do_builtin(t_exec *head);
void	do_execve(t_exec *head);
int		do_parent(t_exec *head);
int		contains_slash(char *str);
void	init_quotes(t_quotes *q, char **com);
int		free_exec(t_exec *head);
int		handle_exit_status(int status, t_exec *head);
int		error_signal(int status);
void	free_redir(t_redir *redir);
int		prepare_exec(t_exec *head);
int		is_builtin(char *str);
int		do_builtin(t_exec *head);

// buildin
int		ft_echo(char **line, int length);
int		ft_cd(char **line);
int		ft_env(int i);
int		ft_export(char **line);
int		ft_unset(char **line);
void	ft_exit(char **line);
int		ft_errors(int l);
int		exit_error(char *line, int num);
int		find_in_dop(char *str, t_msh *msh);
int		get_dollar(char *copy, int *i, char **result);
int		exec_cmd(int fd_in, int fd_out, t_exec *head, pid_t pid);
int		ft_cmp(char *s1, char *s2);
char	*ft_first(char *line);
char	*ft_sec(char *line);
int		ft_print_error(char *str);
void	ft_work_in_env(char *asd, char *line);
void	set_expressions(char *line, int i);
int		set_variables(char **line, int j);
void	check_dop(char *line);
void	ft_print_export(t_msh msh);
void	ft_eq(int i);
void	ft_work_in_dop(char *line, char *asd);
void	move_dir(char **line, char *buf, int i);
void	strjoin_to_str(char *line, char *asd, int i);

char	*readline(const char *prompt);

// signals
void	ft_signal_in(int code);
void	ft_signal_out(int code);
void	rl_replace_line(const char *text, int clear_undo);

#endif
