/*
 * =====================================================================================
 *
 *       Filename:  process_orphen.c
 *
 *    Description:  孤儿进程的父进程为1号init进程
 *
 *        Version:  1.0
 *        Created:  2016年11月07日 17时35分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Clay Zhang (伦), 
 *   Organization:  
 *
 * =====================================================================================
 */




#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main (void)
{
	pid_t pid;
	pid = fork();
	if(pid < 0){
		perror("fork error");
		exit(1);
	}else if(pid > 0){//parent_process
		printf("parent_process id:%d ,parent_process dead now\n",getpid());
		exit(0);
	}else{//child_process
		sleep(4);
		printf("child_process id:%d ,and now it's orphen process,ppid:%d\n",getpid(),getppid());
	}


	return 0;
}				/* ----------  end of function main  ---------- */
