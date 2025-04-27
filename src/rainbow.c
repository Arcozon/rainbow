/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:01:04 by gaeudes           #+#    #+#             */
/*   Updated: 2025/04/09 06:09:17 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rainbow.h"

int	slash_in_exe(char *exe_name)
{
	for (int i = 0; exe_name[i]; ++i)
		if (exe_name[i] == '/')
			return (1);
	return (0);
}

char	*find_pathvar(char **env)
{
	while (*env)
	{
		if (!strncmp(*env, "PATH=", 5))
			break;
		++env;
	}
	return (*env);
}

char	*find_cat_path(char **env, char path_cat[P_C_SIZE], char *exe_name)
{
	char *path;
	int	len_exe_name = strlen(exe_name);
	int i_pcpy, i_exe;

	if (slash_in_exe(exe_name))
	{
		if (access(exe_name, X_OK) == 0)
			return (exe_name);
		return (0);
	}
	path = find_pathvar(env);
	if (!path)
		return (0);
	path += 5;
	while (*path)
	{
		for (i_pcpy = 0; path[i_pcpy] && path[i_pcpy] != ':' 
				&& i_pcpy < P_C_SIZE - len_exe_name - 1; ++i_pcpy)
			path_cat[i_pcpy] = path[i_pcpy];
		path_cat[i_pcpy] = '/';
		for (i_exe = 0; exe_name[i_exe]; ++i_exe)
			path_cat[i_pcpy + 1 + i_exe] = exe_name[i_exe];
		path_cat[i_pcpy + 1 + i_exe] = 0;
		if (access(path_cat, X_OK) == 0)
			return (path_cat);
		path += i_pcpy;
		if (path[0] == ':')
			++path;
	}
	return (0);
}

int	ac_neq_1(char **av, char **env)
{
	char	*exe_path;
	char	noslash_exe_path[P_C_SIZE];
	int	pipe[2];
	int cat_pid;
	exe_path = find_cat_path(env, noslash_exe_path, av[1]);
	if (exe_path)
	{
		if (pipe2(pipe, 0))
			return (1);
		cat_pid = fork();
		if (cat_pid == -1)
			return (2);
		if (cat_pid == 0)
		{
			close(pipe[0]);
			if (dup2(pipe[1], 1) < 0)
				return (close(pipe[1]), 3);
			close(pipe[1]);
			execve(exe_path, av + 1, env);
			exit(1);
		}
		close(pipe[1]);
		if (dup2(pipe[0], 0) < 0)
			return (3);
		close(pipe[0]);
		return (0);
	}
	return (1);
}

int main(int ac, char **av, char **env)
{
	if (ac > 1)
		if (ac_neq_1(av, env))
			return (1);
	rainbow();	
	return (0);
}
