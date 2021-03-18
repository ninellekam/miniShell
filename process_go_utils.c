/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_go_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzena <yzena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:08:30 by ninakamkia        #+#    #+#             */
/*   Updated: 2021/03/18 23:52:24 by yzena            ###   ########.fr       */
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
    parse_str->flags = O_NOFL;
    if (parse_str->cnt_coms < 2)
        return parse_str->flags;
    if (!strcmp(parse_str->str[1],"<"))
        parse_str->flags |= O_RDFL;
    if (!strcmp(parse_str->str[parse_str->cnt_coms - 1],";")) {
        parse_str->flags |= O_NEXT;
        parse_str->cnt_coms--;
    }
    if (parse_str->cnt_coms < 3)
        return parse_str->flags;
    if (!strcmp(parse_str->str[parse_str->cnt_coms - 2],">"))
        parse_str->flags |= O_WRTFILE;
    else if (!strcmp(parse_str->str[parse_str->cnt_coms - 2],">>"))
        parse_str->flags |= O_WRTENDFILE;
    return parse_str->flags;
}

int main() 
{
    struct parsed_string s;
    s.str = (char **)malloc(sizeof(char *) * 4);
    s.str[0] = malloc(sizeof(char) * 6);
    s.str[1] = malloc(sizeof(char) * 1);
    s.str[2] = malloc(sizeof(char) * 5);
    s.str[3] = malloc(sizeof(char) * 6);
    s.cnt_coms = 4;
    s.str[0] = "ls";
    s.str[1] = "|";
    s.str[2] = "sort";
    s.str[3] = "-r";
    conveyor_start(&s);
}