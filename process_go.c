/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninakamkia <ninakamkia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:12:38 by ninakamkia        #+#    #+#             */
/*   Updated: 2021/03/18 10:55:41 by ninakamkia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	count_one(int flags, struct parsed_string parse_str)
{
		pid_t pid;
		int q = parse_str.cnt_coms;
		if (flags & (O_WRTENDFILE | O_WRTFILE))
				q -= 2;
		if (flags & O_RDFL)
				q -= 2;
		if (!(pid = fork()))
				exec_realize(parse_str, 0, q);
		else if (pid == -1)
				exit(1);
		else {
				wait(NULL);
				exit(0);
		}
}


// int conveyor (struct parsed_string parse_str)
// {
// 		int kproc = count_processes(parse_str);
// 		int flags = get_type(&parse_str);
// 		if (kproc == 0)
// 				exit(0);
// 	else if (kproc == 1)
// 			 count_one(flags, parse_str);
// 	else {
// 				int tube[2], tube_o;
// 				if (pipe(tube) == -1) {
// 						_exit(1);
// 				}
// 				int *KidsPID = calloc(kproc + 2, sizeof(*KidsPID));
// 				int k = 0;
// 				if (!KidsPID) {
// 						close(tube[0]);
// 						close(tube[1]);
// 						_exit(1);
// 				}
// 				pid_t pid;
// 				int i = 0, a = i, b;
// 				while (i < parse_str.cnt_coms && strcmp(parse_str.str[i],"|")) {
// 						i++;
// 				}
// 				b = i;
// 				i++;
// 				if (!(pid = fork())) {
// 						if (flags & O_RDFL) {
// 								b -= 2;
// 						}
// 						if (close(tube[0]) == -1) {
// 								close(tube[1]);
// 								free(KidsPID);
// 								_exit(1);
// 						} else if ((dup2(tube[1], 1) == -1)) {
// 								close(tube[1]);
// 								free(KidsPID);
// 								_exit(1);
// 						} else if (close (tube[1])) {
// 								free(KidsPID);
// 								_exit(1);
// 						} else {
// 								exec_realize(parse_str, a, b);
// 						}
// 				} else if (pid == -1) {
// 						free(KidsPID);
// 						exit(1);
// 				}
// 				if (close(tube[1]) == -1) {
// 						free(KidsPID);
// 						kill(pid,SIGKILL);
// 						wait(NULL);
// 						exit(1);
// 				} else {
// 						KidsPID[k] = pid;
// 						k++;
// 				}
// 				tube_o = tube[0];
// 				for (int j = 1; j < kproc - 1; j++) {
// 						fflush(stdout);
// 						a = i;
// 						while (i < parse_str.cnt_coms && strcmp(parse_str.str[i],"|")) {
// 								i++;
// 						}
// 						b = i;
// 						i++;
// 						if (pipe(tube) == -1) {
// 								killall(KidsPID,k);
// 								while (wait(NULL) >= 0) {
// 										//
// 								}
// 								_exit(1);
// 						}
// 						if (!(pid = fork())) {
// 								if ((close(tube[0]) == -1) || (dup2(tube_o,0) == -1) || (close(tube_o) == -1)) {
// 										killall(KidsPID,k);
// 										_exit(1);
// 								}
// 								if ((dup2(tube[1],1) == -1) || (close(tube[1]) == -1)) {
// 										killall(KidsPID,k);
// 										_exit(1);
// 								}
// 								exec_realize(parse_str, a, b);
// 						} else if (pid == -1) {
// 								killall(KidsPID, k);
// 								while (wait(NULL) >= 0) {
// 										//
// 								}
// 								_exit(1);
// 						}
// 						if ((close(tube[1]) == -1) || (close(tube_o) == -1)) {
// 								killall(KidsPID,k);
// 								_exit(1);
// 						}
// 						KidsPID[k] = pid;
// 						k++;
// 						tube_o = tube[0];
// 				}
// 				if (!(pid = fork())) {
// 						b = parse_str.cnt_coms;
// 						if (flags & (O_WRTFILE| O_WRTFILE)) {
// 								b -= 2;
// 						}
// 						if ((dup2(tube_o,0) == -1) || (close(tube_o) == -1)) {
// 								free(KidsPID);
// 								_exit(1);
// 						}
// 						exec_realize(parse_str, i, b);
// 				} else if (pid == -1) {
// 						killall(KidsPID,k);
// 						while (wait(NULL) >= 0);
// 						exit(1);
// 				} else {
// 						KidsPID[k] = pid;
// 						k++;
// 						if (close(tube_o) == -1) {
// 								killall(KidsPID,k);
// 								while (wait(NULL) >= 0);
// 								exit(1);
// 						}
// 				}
// 		}
// 		int pid;
// 		while ((pid = wait(NULL)) != -1);
// 		exit(0);
// }
