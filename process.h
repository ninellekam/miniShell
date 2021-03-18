/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzena <yzena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:08:56 by ninakamkia        #+#    #+#             */
/*   Updated: 2021/03/18 23:43:20 by yzena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
#define PROCESS_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>

struct parsed_string
{
    char **str;
    int cnt_coms;
    int *KidsPID;
    int tube[2];
    int tube_o;
    int flags;
    int kproc;
    int a;
    int b;
};

enum { O_NOFL = 0, O_WRTFILE = 1, O_WRTENDFILE = 2, O_RDFL = 4, O_NEXT = 8 };

int				count_processes(struct parsed_string *parse_str);
void			exec_realize(struct parsed_string *parse_str, int a, int b);
void			killall(pid_t *KidsPID, int k);
unsigned char	get_type (struct parsed_string *parse_str);
int		conveyor_start(struct parsed_string *parse_str);

#endif