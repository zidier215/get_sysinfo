/* ************************************************************************
 *       Filename:  user_process.c
 *    Description:  
 *        Version:  1.0
 *        Created:  11/16/2014 09:47:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <alloca.h>
int judge_name(char *name)
{

  int n =  atoi(name);
//  printf("n = %d\n",n);
  if(n==0)
      goto E;
R:
    return 0;
E:
    return 1;
}
//int judge_
int get_file_info(char *name)
{
    char name_buf[1024]="";
    struct stat statbuf;
    sprintf(name_buf,"/proc/%s/status",name);
    printf("dirname:%s\n",name_buf);
    int fd = open(name_buf,O_RDONLY);
    if(fd <=0 )
        goto RETVAL;
    char buf;   
    int ret = 0;
//    while(1)
    {
        char buf[1024]="";
        char *p = buf;
        char *q = buf;
        while(read(fd,p,1))
        {
            printf("%c",*p);
            if(*p!=0)
            {
                p++;
                printf("buf=%s\n",buf);
//                printf("xxxxxxxxxxxxxxxx\n");
                continue;
            }
            p = buf;
        }
    }
 
    printf("\n");

    close(fd);
    return 0;
RET:
    close(fd);
RETVAL:
    return -1;
    
}
int main(int argc ,char * argv[])
{	
    struct dirent *dirent = NULL; 
    DIR *dir = opendir("/proc");
    while((dirent = readdir(dir))!=NULL)
    {
        if(dirent->d_type == DT_DIR)
        {
            if(!judge_name(dirent->d_name))
            {
                char name_buf[1024]="";
                get_file_info(dirent->d_name);
//                printf("dirname:%s\n",dirent->d_name);
            }
                    
        }
    }
    return 0;
}



