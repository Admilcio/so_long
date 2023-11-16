#include <stdio.h>

int iter(char *str, char c, int len)
{
    int i = 0;

    while(str[i] && (i < len || len == -1))
        if(str[i] == c)
            return (1);
}

char *rev(char *str)
{
    int i = 0;
    int j = 0;
    char tmp;

    while(str[i])
        i++;
    i--;
    while(j < i)
    {
        tmp = str[j];
        str[j] = str[i];
        str[i] = tmp;
        i--;
        j++;
    }
    return(str);
}

int main (int ac, char ** av)
{
    char str[] = "Everything";

    printf("%s\n", rev(str));
    /* 
    int i = 0;
    char *s1 = av[1];
    char *s2 = av[2];

    if (ac == 3)
    {
        while(s1[i])
        {
            if(!iter(s1, s1[i], i) && iter(s2, s1[i], -1))
                write(1, &s1[i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    */
}