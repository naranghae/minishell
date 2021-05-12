#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main()
{
    struct dirent *item;
    DIR *dp;

    dp = opendir("/goinfre/chanykim/minishell");
    if (dp != NULL)
    {
        while(1)
        {
            item = readdir(dp);
            if (item == NULL)
                break;
            printf("%s\n", item->d_name);
        }
        closedir(dp);
    }
}
