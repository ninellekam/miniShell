/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_go_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzena <yzena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:08:30 by ninakamkia        #+#    #+#             */
/*   Updated: 2021/03/18 22:13:40 by yzena            ###   ########.fr       */
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

void exec_realize(struct parsed_string *parse_str, int a, int b)
{
    char *argv[20];
    write(1, "lala", 4);
    for (int j = 0; j < (b - a); j++) {
        argv[j] = parse_str->str[a + j];
    }
    argv[b - a] = NULL;
    execvp(argv[0], argv);
}

int count_processes (struct parsed_string *parse_str)
{
    int cnt_coms = 0;
    for (int i = 0; i < parse_str->cnt_coms; i++) {
       cnt_coms += (strcmp(parse_str->str[i], "|") == 0);
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

int main() 
{
    struct parsed_string s;
    s.str[0] = malloc(sizeof(char) * 12);
    s.cnt_coms = 1;
    s.str[0] = "pwd";
 //   s.str[1] = "..";
    conveyor_start(&s);
}