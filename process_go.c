/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzena <yzena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:12:38 by ninakamkia        #+#    #+#             */
/*   Updated: 2021/03/18 23:52:12 by yzena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	count_one(int flags, struct parsed_string *parse_str)
{
		pid_t pid;
		int q = parse_str->cnt_coms;
		int b; 
		int i;
		if (flags & (O_WRTENDFILE | O_WRTFILE))
				q -= 2;
		if (flags & O_RDFL)
				q -= 2;
		if (!(pid = fork()))
			exec_realize(parse_str, 0, q);
		else if (pid == -1)
				exit(1);
		else
		{
				wait(NULL);
				exit(0);
		}
}

void	pids_check(int *KidsPID, int *tube)
{
	if (!KidsPID) {
		close(tube[0]);
		close(tube[1]);
		_exit(1);
	}
	return ;
}

void	pid_error(pid_t pid, int *KidsPID)
{
	if (pid == -1)
	{
		free(KidsPID);
		exit(1);
	}
}

void	part_three(pid_t pid, int flags, int i, struct parsed_string *parse_str)
{
	int b;
	if (!(pid = fork()))
		{
			b = parse_str->cnt_coms;
			if (flags & (O_WRTFILE| O_WRTFILE))
				b -= 2;
			dup2(parse_str->tube_o, 0);
			close(parse_str->tube_o);
			exec_realize(parse_str, i, b);
		}
		pid_error(pid, parse_str->KidsPID);
}

int	part_one(struct parsed_string *parse_str, pid_t pid, int *i)
{
	pipe(parse_str->tube);
	parse_str->KidsPID = calloc(parse_str->kproc + 2, sizeof(int));
	int k = 0;
	pids_check(parse_str->KidsPID, parse_str->tube);
	while (*i < parse_str->cnt_coms && strcmp(parse_str->str[*i],"|"))
		(*i)++;
	parse_str->b = *i;
	(*i)++;
	if (!(pid = fork()))
	{
		if (parse_str->flags & O_RDFL)
			parse_str->b -= 2;
		close(parse_str->tube[0]);
		dup2(parse_str->tube[1], 1);
		close (parse_str->tube[1]);
		exec_realize(parse_str, parse_str->a, parse_str->b);
	} 
	pid_error(pid, parse_str->KidsPID);
	close(parse_str->tube[1]);
	parse_str->KidsPID[k] = pid;
	k++;
	parse_str->tube_o = parse_str->tube[0];
	return (k);
}

int		conveyor_start(struct parsed_string *parse_str)
{
	pid_t	pid;
	int		i;
	int		k;

	i = 0;
	parse_str->a = i;
	parse_str->kproc = count_processes(parse_str);
	parse_str->flags = get_type(parse_str);
	if (parse_str->kproc == 0)
		exit(0);
	else if (parse_str->kproc == 1)
		count_one(parse_str->flags, parse_str);
	else
	{
		k = part_one(parse_str, pid, &i);
		for (int j = 1; j < parse_str->kproc - 1; j++)
		{
			fflush(stdout);
			parse_str->a = i;
			while (i < parse_str->cnt_coms && strcmp(parse_str->str[i],"|"))
				i++;
			parse_str->b = i;
			i++;
			pipe(parse_str->tube);
			if (!(pid = fork()))
			{
				close(parse_str->tube[0]);
				dup2(parse_str->tube_o, 0);
				close(parse_str->tube_o);
				dup2(parse_str->tube[1],1);
				close(parse_str->tube[1]);
				exec_realize(parse_str, parse_str->a, parse_str->b);
			}
			else if (pid == -1)
			{
				killall(parse_str->KidsPID, k);
				while (wait(NULL) >= 0) {
					// .......... // 
				}
				_exit(1);
			}
			close(parse_str->tube[1]);
			close(parse_str->tube_o);
			parse_str->KidsPID[k] = pid;
			k++;
			parse_str->tube_o = parse_str->tube[0];
		}
		part_three(pid, parse_str->flags, i, parse_str);
			while ((pid = wait(NULL)) != -1);
			exit(0);
	}
return 1;
}