/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzena <yzena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:12:38 by ninakamkia        #+#    #+#             */
/*   Updated: 2021/03/18 22:08:21 by yzena            ###   ########.fr       */
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
		{
			printf("tuuuut\n");
			exec_realize(parse_str, 0, q);
		}
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
	{
		count_one(flags, parse_str);	
	}
	else
	{
		int tube[2], tube_o;
		pipe(tube);
		int *KidsPID = calloc(kproc + 2, sizeof(*KidsPID));
		int k = 0;
		pids_check(KidsPID, tube);
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
		close(tube[0]);
		dup2(tube[1], 1);
		close (tube[1]);
		exec_realize(parse_str, a, b);
	} 
	pid_error(pid, KidsPID);
	close(tube[1]);
	KidsPID[k] = pid;
	k++;
	tube_o = tube[0];
	// -------- part 2 ---------------------
	for (int j = 1; j < kproc - 1; j++)
	{
		fflush(stdout);
		a = i;
		while (i < parse_str->cnt_coms && strcmp(parse_str->str[i],"|"))
			i++;
		b = i;
		i++;
		pipe(tube);
		if (!(pid = fork()))
		{
			close(tube[0]);
			dup2(tube_o, 0);
			close(tube_o);
			dup2(tube[1],1);
			close(tube[1]);
			exec_realize(parse_str, a, b);
		}
		else if (pid == -1)
		{
			killall(KidsPID, k);
			while (wait(NULL) >= 0) {
				// .......... // 
			}
			_exit(1);
		}
		close(tube[1]);
		close(tube_o);
		KidsPID[k] = pid;
		k++;
		tube_o = tube[0];
	}
	// ----- part 3 ------------------
		if (!(pid = fork()))
		{
			b = parse_str->cnt_coms;
			if (flags & (O_WRTFILE| O_WRTFILE))
				b -= 2;
			dup2(tube_o, 0);
			close(tube_o);
			exec_realize(parse_str, i, b);
		}
		pid_error(pid, KidsPID);
		// else
		// {
		// 	KidsPID[k] = pid;
		// 	k++;
		// 	close(tube_o);
		// }
	}
		// int pid;
		while ((pid = wait(NULL)) != -1);
		exit(0);
}
