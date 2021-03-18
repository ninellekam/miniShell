/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninakamkia <ninakamkia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:08:56 by ninakamkia        #+#    #+#             */
/*   Updated: 2021/03/18 10:55:30 by ninakamkia       ###   ########.fr       */
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
};

enum { O_NOFL = 0, O_WRTFILE = 1, O_WRTENDFILE = 2, O_RDFL = 4, O_NEXT = 8 };

int				count_processes(struct parsed_string x);
void			exec_realize(struct parsed_string x, int a, int b);
void			killall(pid_t *KidsPID, int k);
unsigned char	get_type (struct parsed_string *x);

#endif