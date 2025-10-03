/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:21:19 by namejojo          #+#    #+#             */
/*   Updated: 2025/09/27 01:02:33 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFF 10

char *ft_strstr(char *big, char *little)
{
    int indb;
    int indl;

    if (big == NULL || little == NULL)
        return (NULL);
    while (*big)
    {
        indb = 0;
        indl = 0;
        while (little[indl] == big[indb])
        {
            indb++;
            indl++;
            if (little[indl] == '\0')
                return (big);
        }
        big++;
    }
    return (NULL);
}

int ft_strlen(char *str)
{
    int ind;

    ind = 0;
    if (str == NULL)
        return (0);
    while (str[ind])
    {
        ind++;
        if (str[ind - 1] == '\n')
            return (ind);
    }
    return (ind);
}

char    *ft_strjoin(char *str1, char *str2)
{
    char    *ret;
    int     ind;
    int     ind2;

    ret = calloc(ft_strlen(str1) + ft_strlen(str2) + 1, 1);
    ind = 0;
    if (ret == NULL)
        return (free(str1), NULL);
    if (str1)
    {
        while (str1[ind])
        {
            ret[ind] = str1[ind];
            ind++;
        }
    }
    ind2 = 0;
    while (str2[ind2])
    {
        ret[ind] = str2[ind2];
        ind++;
        ind2++;
        if (str2[ind2 - 1] == '\n')
            break ;
    }
    free (str1);
    return (ret);
}

char *gnl(int fd)
{
    static char buffer[BUFF + 1];
    char        *ret;
    int         byt;
    char        *temp;

    ret = NULL;
    byt = 1;
    ret = ft_strjoin(ret, buffer);
    while (ft_strstr(ret, "\n") == NULL && byt > 0)
    {
        byt = read(fd, buffer, BUFF);
        if (byt >= 0)
        buffer[byt] = '\0';
        ret = ft_strjoin(ret, buffer);
    }
    if (ft_strstr(buffer, "\n"))
    {
        temp = ft_strstr(buffer, "\n");
        memmove(buffer, temp + 1, strlen(temp) + 1);
    }
    if (*ret == '\0')
        return (free(ret), NULL);
    return (ret);
}

int main(void)
{
    char *str;
    int fd = open("txt", 0644);

    str = gnl(fd);
    while (str)
    {
        printf("%s", str);
        free(str);    
        str = gnl(fd);
    }
}