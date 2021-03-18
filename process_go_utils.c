/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_go_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninakamkia <ninakamkia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:08:30 by ninakamkia        #+#    #+#             */
/*   Updated: 2021/03/18 10:55:15 by ninakamkia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void killall(pid_t *KidsPID, int k)
{
    for (int i = 0 ; i < k; i++) {
        kill(KidsPID[i],SIGKILL);
    }
    free(KidsPID);
}

void exec_realize(struct parsed_string parse_str, int a, int b)
{
    char *argv[20];
    for (int j = 0; j < (b - a); j ++) {
        argv[j] = parse_str.str[a + j];
    }
    argv[b - a] = NULL;
    execvp(argv[0], argv);
}

int count_processes (struct parsed_string parse_str)
{
    int cnt_coms = 0;
    for (int i = 0; i < parse_str.cnt_coms; i++) {
        cnt_coms += (strcmp(parse_str.str[i], "|") == 0);
    }
    return cnt_coms + 1;
}

unsigned char get_type (struct parsed_string *parse_str)
{
    unsigned char flags = O_NOFL;
    if (parse_str->cnt_coms < 2)
        return flags;
    if (!strcmp(parse_str->str[1],"<"))
        flags |= O_RDFL;
    if (!strcmp(parse_str->str[parse_str->cnt_coms - 1],";")) {
        flags |= O_NEXT;
        parse_str->cnt_coms--;
    }
    if (parse_str->cnt_coms < 3)
        return flags;
    if (!strcmp(parse_str->str[parse_str->cnt_coms - 2],">"))
        flags |= O_WRTFILE;
    else if (!strcmp(parse_str->str[parse_str->cnt_coms - 2],">>"))
        flags |= O_WRTENDFILE;
    return flags;
}