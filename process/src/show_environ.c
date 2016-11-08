/*
 * =====================================================================================
 *
 *       Filename:  show_environ.c
 *
 *    Description:  show 环境变量
 *
 *        Version:  1.0
 *        Created:  2016年10月20日 20时15分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Clay Zhang (伦), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdio.h>
#include	<stdlib.h>
#include    <unistd.h>
#include	<string.h>

extern char **environ;		// environ 是一个指针数组 ，每个指针都指一个环境变量，最后一个指针为NULL


	void
show_env ()
{
	int i = 0;
	char *env;
	while((env = environ[i])  != NULL){
		printf("%s\n",env);
		i++;
	}
}		/* -----  end of function show_env  ----- */


	int
main (void)
{
	show_env();
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */





