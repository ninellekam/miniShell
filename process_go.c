/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzena <yzena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:12:38 by ninakamkia        #+#    #+#             */
/*   Updated: 2021/03/18 23:16:18 by yzena            ###   ########.fr       */
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

int		conveyor_start(struct parsed_string *parse_str)
{
	pid_t pid;
	int i = 0;
	int a = i;
	int b;
	int kproc = count_processes(parse_str);
	int flags = get_type(parse_str);
	if (kproc == 0)
		exit(0);
	else if (kproc == 1)
		count_one(flags, parse_str);	
	else
	{
		pipe(parse_str->tube);
		parse_str->KidsPID = calloc(kproc + 2, sizeof(int));
		int k = 0;
		pids_check(parse_str->KidsPID, parse_str->tube);
		while (i < parse_str->cnt_coms && strcmp(parse_str->str[i],"|")) {
			i++;
	}
	b = i;
	i++;
	// -------- part 1 ---------------------
	if (!(pid = fork()))
	{
		if (flags & O_RDFL)
			b -= 2;
		close(parse_str->tube[0]);
		dup2(parse_str->tube[1], 1);
		close (parse_str->tube[1]);
		exec_realize(parse_str, a, b);
	} 
	pid_error(pid, parse_str->KidsPID);
	close(parse_str->tube[1]);
	parse_str->KidsPID[k] = pid;
	k++;
	parse_str->tube_o = parse_str->tube[0];
	// -------- part 2 ---------------------
	for (int j = 1; j < kproc - 1; j++)
	{
		fflush(stdout);
		a = i;
		while (i < parse_str->cnt_coms && strcmp(parse_str->str[i],"|"))
			i++;
		b = i;
		i++;
		pipe(parse_str->tube);
		if (!(pid = fork()))
		{
			close(parse_str->tube[0]);
			dup2(parse_str->tube_o, 0);
			close(parse_str->tube_o);
			dup2(parse_str->tube[1],1);
			close(parse_str->tube[1]);
			exec_realize(parse_str, a, b);
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
	// ----- part 3 ------------------
	part_three(pid, flags, i, parse_str);
	}
		// int pid;
		while ((pid = wait(NULL)) != -1);
		exit(0);
}
