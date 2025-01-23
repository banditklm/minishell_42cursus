/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:14:17 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/04 14:17:36 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>

typedef enum e_type
{
	PIPE,
	S_QUOTE,
	D_QUOTE,
	TEXT,
	EXP,
	BLANK,
	IN,
	OUT,
	APPEND,
	HERDOC,
	Q_DEL,
	DEL,
	SET,
	GET,
	CARD,
}	t_type;

typedef struct s_command	t_cmd;

typedef struct s_tokens
{
	t_cmd			*cmd;
	char			*token;
	t_type			type;
	bool			boole;
	char			*ambg;
	bool			ign;
	int				t_idx;
	int				fd;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_garbage
{
	void				*node;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_minishell	t_minishell;

typedef struct s_command
{
	t_tokens			*tokens;
	t_minishell			*msh;
	int					input;
	int					output;
	int					c_idx;
	int					fd[2];
	bool				fd_fail;
	char				**av;
	struct s_command	*next;
}	t_cmd;

typedef struct s_minishell
{
	t_tokens	*tokens;
	t_cmd		*cmd;
	t_garbage	*global;
	t_garbage	*local;
	char		**env;
	int			pipes;
	bool		env_checker;
	int			stdin_org;
	int			sflag;
}	t_minishell;

char		*ft_strjoin(t_minishell *msh, char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*sdup(t_minishell *msh, t_garbage **garbage, const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(t_minishell *minishell, int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strtrim(t_minishell *msh, char *s1, char *set, bool flag);
char		**ft_split0(t_minishell *msh, char *str, char *charset);
char		*_sub(t_minishell *msh, char const *s, unsigned int st, size_t len);
char		**ft_getfullenv(t_minishell *minishell, char **env);
char		**ft_setenv(t_minishell *minishell);
char		*ft_getenv(char *var, t_minishell *minishell);
int			ft_openhd_se(t_minishell *minishell, char *line, int *i, int *flag);
int			ft_isalnum(int c);
int			ft_isblank(char c);
int			ft_isstring(char c);
int			ft_issnglqs(char c);
int			ft_isdblqs(char c);
int			ft_isoperator(char c);
int			ft_isexpand(char c);
int			ft_iswdcard(char c);
int			ft_ispipe(char c);
int			ft_isin(char c);
int			ft_isout(char c);
bool		sd_handler(t_minishell *msh, char *line);
void		rm_exp(t_minishell *minishell);
void		rm_blank(t_minishell *minishell);
t_tokens	*ft_lstnew(t_minishell *minishell, void *content, t_type type);
t_garbage	*ft_garnew(t_minishell *m, void *node);
t_cmd		*ft_newcmd(t_minishell *minishell, void *content);
void		*ft_malloc(t_minishell *msh, t_garbage **garbage, size_t size);
void		ft_free(t_garbage **garbage, int boole);
void		ft_lstadd_back(t_tokens **lst, t_tokens *new);
void		ft_garadd_back(t_garbage **lst, t_garbage *new);
void		ft_addcmd_back(t_cmd **lst, t_cmd *new);
void		ft_garclear(t_garbage **lst);
int			getlen_string(char *line, int index);
int			getlen_sq(char *line, int index);
int			getlen_dq(char *line, int index);
int			getlen_blank(char *line, int index);
int			getlen_op(char *line, int index);
int			getlen_pipe(char *line, int index);
int			getlen_in(char *line, int index);
int			getlen_out(char *line, int index);
char		*get_string(t_minishell *minishell, char *line, int *index);
char		*get_sq(t_minishell *minishell, char *line, int *index);
char		*get_dq(t_minishell *minishell, char *line, int *index);
char		*get_blank(t_minishell *minishell, char *line, int *index);
char		*get_op(t_minishell *minishell, char *line, int *index);
char		*get_exp(t_minishell *minishell, int *index);
char		*get_wdcard(t_minishell *minishell, char *line, int *index);
char		*get_pipe(t_minishell *minishell, char *line, int *index);
char		*get_in(t_minishell *minishell, char *line, int *index);
char		*get_out(t_minishell *minishell, char *line, int *index);
char		*get_herdoc(t_minishell *minishell, char *line, int *index);
char		*get_append(t_minishell *minishell, char *line, int *index);
void		get_del(t_minishell *msh);
bool		handle_op(t_minishell *minishell, char *line, int *index);
bool		handle_pipe(t_minishell *minishell, char *line, int index);
bool		handle_in(t_minishell *minishell, char *line, int *index);
bool		handle_out(t_minishell *minishell, char *line, int *index);
bool		handle_herdoc(t_minishell *minishell, char *line, int index);
bool		handle_append(t_minishell *minishell, char *line, int index);
bool		ft_tokenizer(t_minishell *minishell, char *line);
bool		syntax_errorb(t_minishell *minishell, char *line, int index);
void		open_heredocs(t_minishell *minishell, char *line, int n);
void		token_handler(t_minishell *minishell);
void		qexp_handler(t_minishell *msh);
void		expainding(t_minishell *minishell);
void		stick_tok(t_minishell *m);
void		fill_cmd(t_minishell *minishell);
void		token_cmd(t_minishell *minishell);
void		token_index(t_minishell *minishell);
char		*get_key(t_minishell *msh, char *str);
char		*get_rest(t_minishell *msh, char *str);
void		exp_blank(t_minishell *minishell);
void		q_to_text(t_minishell *minishell);
void		card_to_text(t_minishell *msh);
bool		parser(t_minishell *minishell, char *line);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		sig_handler(int sig);
void		sig_handler0(int sig);
void		sig_handler1(int sig);
void		sig_handler11(int sig);
void		sig_handler2(int sig);
int			set_flag(int state, bool set);
void		wildcard(t_minishell *msh);
char		*handle_exit(t_minishell *msh, char *token);
bool		if_exp(char *str);
int			lnx(char *token, int index);
int			is_exit(char *herdoc);
int			lnx1(char *token, int index);
char		*handle_exit_s(t_minishell *msh, char *herdoc);
void		card_to_text(t_minishell *msh);
void		init_data(t_minishell *minishell, char **env, int ac, char **av);
void		init_data2(t_minishell *minishell);
void		free_fd_local(t_minishell *msh, char *line);
int			all_spaces(char *s);
void		check_line1(t_minishell *minishell, char *line);
// soufiix
void		execution(t_minishell *ms);
char		**ft_split(t_minishell *msh, char const *s, char c);
int			ft_openhd(t_minishell *msh);
int			ft_creatfd_forhd(t_minishell *msh, char **input);
char		*ft_getfile_name(t_minishell *msh);
int			ft_countline(char **environ);
int			ft_lstsize(t_cmd *lst);
void		args_maker(t_minishell *msh);
void		ft_onepipe(t_cmd	*cmd);
int			getavlen(t_cmd *cmd);
int			isbuiltin(char *av);
void		execute_onecmd(t_cmd *cmd);
int			ft_openfd(t_cmd *cmd);
int			ft_in(t_minishell *msh, t_tokens *token);
int			ft_out(t_minishell *msh, t_tokens *token);
int			ft_append(t_minishell *msh, t_tokens *token);
char		*getlinepath(char *path, char *commande, t_cmd *cmd);
void		put_stderr(char *s);
void		ft_multi_pipes(t_minishell *msh);
void		execute_childe(t_cmd *cmd);
void		ft_redirection(t_cmd *cmd);
void		handel_builtins(t_minishell *msh, t_cmd *cmd, bool flag);
void		ft_env(t_minishell *msh, t_cmd *cmd);
void		ft_exit(t_minishell *msh, t_cmd *cmd, bool fork);
void		ft_pwd(t_minishell *msh, t_cmd *cmd, bool fork);
void		ft_unset(t_minishell *msh, t_cmd *cmd, bool fork);
void		sort_env(char **env, int size);
int			check_invalid_id(char *str);
void		ft_echo(t_minishell *msh, t_cmd *cmd, bool fork);
void		print_echo(t_minishell *msh, int fd, char **av, int i);
int			ft_isdigit(char c);
int			isvalid_flag(char **av);
void		ft_cd(t_minishell *msh, t_cmd *cmd, bool fork);
void		cd_no_arg(t_minishell *msh, bool fork);
char		**set_oldpwd(t_minishell *msh, char *old_pwd);
char		*get_to_dir(t_minishell *msh, t_cmd *cmd, bool get, bool fork);
char		*herexp(t_minishell *minishell, char *herdoc);
void		ft_export(t_minishell *msh, t_cmd *cmd, bool fork);
void		print_export(t_minishell *msh, t_cmd *cmd);
int			check_invalid_id_export(char *str);
char		*ft_substr(t_minishell *msh, char *s,
				unsigned int start, size_t len);
bool		ft_ispluseq(char *str);
char		*get_var(t_minishell *msh, char *str, bool plus);
char		*strjoin_env(t_minishell *minishell,
				char const *s1, char const *s2);
char		**set_variable(t_minishell *msh, char *var, bool plus);
char		*get_v(t_minishell *msh, char *str);
int			find_eq(char *str, char c);
void		handel_exit_sig(int exit_status);
int			ft_exit_status(int status, t_type call);
char		*ft_getvariable(t_minishell *msh, char *str);
void		export_var(t_minishell *msh, char *var, bool plus);
void		ft_openhd_norm(t_minishell *msh, t_tokens *token, int *flag);
int			ft_lstsize(t_cmd *lst);
void		put_stderr(char *s);
int			ft_putstr_fd(char *str, int fd);
int			ft_putchar_fd(char c, int fd);
void		ft_waitpid_multicmd(t_minishell *msh, int *pid_store);
void		ft_waitpid_onecmd(t_minishell *msh, int pid);
char		**set_pwd(t_minishell *msh, char *pwd);
void		ft_child(t_minishell *msh, t_cmd *commande);
void		set_e_s_builtin(t_minishell *msh, bool fork, bool error);
char		*handel_cmd(t_cmd *cmd);
char		*handle_exit(t_minishell *msh, char *token);
void		ft_exit_prog(t_minishell *msh, int status);
void		print_export_fork(t_cmd *cmd);
char		*cd_no_arg_norm(t_minishell *msh,
				char *old_pwd, bool fork, char *pwd);
void		getlinepath_norm(t_minishell *msh, char *comm);
void		signal_norm(t_minishell *msh, int flag);
void		is_a_dir_norm(t_minishell *msh, t_cmd *commande);
char		*ft_error(t_cmd *cmd, char *av);
int			ft_fork_process(t_minishell *msh, t_cmd *commande,
				int *pid_store, int i);
void		ft_setup_pipes(t_cmd *commande, t_cmd *tmp);
void		process_heredoc(t_minishell *msh, t_tokens *token, int *flag);
int			handle_line(t_minishell *msh, t_tokens *token,
				char **store, int *flag);
void		print_export_env(t_minishell *msh, t_cmd *cmd);
void		print_export_value(char *env_var, int fd);
char		*export_plus_eq(t_minishell *msh, char *env, char *value);
char		*add_spaces(t_minishell *msh, char *str, size_t i[2], size_t len);
void		free_fd_local(t_minishell *msh, char *line);

#endif
