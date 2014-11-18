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
#include <pwd.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
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
int get_file_info_fp(int *u_id,char *process_name,char *name)
{
    char name_buf[1024]="";
    char buf[1024]="";
    struct stat statbuf;
    sprintf(name_buf,"/proc/%s/status",name);
//    printf("dirname:%s\n",name_buf);
    FILE *fp= fopen(name_buf,"r");
    if(fp ==NULL)
        return -1;
    while(1)
    {
        char *p = fgets(buf,sizeof(buf),fp);
        if(buf[0]==0)
            break;
//        printf("buf=%s\n",buf);
        if((p = strstr(buf,"Uid"))!=NULL)
        {
//            printf("%s\n",p);
            sscanf(p,"Uid:%d\n",u_id);
        }
        if((p = strstr(buf,"Name"))!=NULL)
        {
//            printf("%s\n",p);
//            strcpy(process_name,p);
            sscanf(p,"Name:%s\n",process_name);
        }
        memset(buf,0,sizeof(buf));
    }
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
    if(argc <2)
    {
        printf("Usage:./user_process Username");
        return -1;
    }
    printf("argv[1]=%s\n",argv[1]);
    int uid = 1004;
//    int uid = 0;
    struct passwd * pw;
    pw = getpwnam(argv[1]);
    if(pw == NULL)
    {
        perror("getpwent");
        return -1;
    }
    
    printf("User %s's(id:%d) process:\n",argv[1],pw->pw_uid);
    while((dirent = readdir(dir))!=NULL)
    {
        if(dirent->d_type == DT_DIR)
        {
            if(!judge_name(dirent->d_name))
            {
                char name_buf[1024]="";
//                get_file_info(dirent->d_name);
                int u_id_get = 0; 
                char process_name[1024]="";
                get_file_info_fp(&u_id_get,process_name,dirent->d_name);
            if(pw->pw_uid == u_id_get)
            {
//                printf("Uid=%d\n",u_id_get);
                printf("\t%s\n",process_name);
            }
            }
                    
        }
    }
    return 0;
}



