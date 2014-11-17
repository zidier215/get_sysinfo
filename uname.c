/* ************************************************************************
 *       Filename:  uname.c
 *    Description:  
 *        Version:  1.0
 *        Created:  11/16/2014 07:43:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 *        Company:  
 * ************************************************************************/
//#ifdef __linux__
    #define _GNU_SOURCE
//#endif
#include <sys/utsname.h>
#include <stdio.h>
int main(int argc ,char * argv[])
{	
    struct utsname uts;
    uname(&uts);
    printf("Node name:   %s\n",uts.nodename);
    printf("System name :   %s\n",uts.sysname);
    printf("Release :   %s\n",uts.release);
    printf("Version :   %s\n",uts.version);
    printf("Machine :   %s\n",uts.machine);
#ifdef _GNU_SOURCE
    printf("Domain name : %s\n",uts.domainname);
#endif
    return 0;
}



