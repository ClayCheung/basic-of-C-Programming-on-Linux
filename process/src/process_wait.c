/*
 * =====================================================================================
 *
 *       Filename:  process_wait.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年11月08日 20时21分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Clay Zhang (伦), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include	<unistd.h>
#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/wait.h>
#include	<sys/types.h>


void out_status(int status);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main (void)
{
	int status;
	pid_t pid;
	
	pid = fork();		//fork一个子进程，并正常退出子进程，并用wait()回收，记录并输出该子进程是以什么状态退出的
	
	if(pid < 0){
		perror("fork error");
		exit(1);
	}else if(pid == 0){	//子进程
		printf("pid: %d, ppid: %d\n",getpid(),getppid());
		exit(3);		//子进程正常退出，退出状态码是3
	}					//现在，子进程退出，却没有告知父进程，
						//	所以不能完全回收子进程的资源，子进程变为僵尸进程
	
	/*下面，父进程将调用wait()，父进程阻塞并查询是否有子进程终止，
	 * 直到有子进程终止，回收之，结束阻塞*/
	
	wait(&status);			//wait()回收终止的子进程的资源
							//把子进程终止时的状态存在status中，
	out_status(status);		//out_status() 翻译status的信息后输出
	printf("-----------------------------\n");

	
	pid = fork();		//再fork一个子进程，并异常终止子进程，并用wait()回收，记录并输出该子进程是以什么状态退出的
	
	if(pid < 0){
		perror("fork error");
		exit(1);
	}else if(pid == 0){	//子进程
		printf("pid: %d, ppid: %d\n",getpid(),getppid());
		
		int a = 8, b = 0;
		printf("a/b = %d\n",a/b);   // “除0”错误，子进程会异常终止，并放出异常信号
	}	
	//父进程wait回收，同上
	wait(&status);
	out_status(status);
	printf("-----------------------------\n");



	pid = fork();		//再fork一个子进程，使用pause()或者sleep循环 暂停子进程，
						//此时只有用waitpid()回收，并指定WUNTRACE 参数，
						//才能记录到子进程终止前暂停过，
						//并输出该子进程是以什么状态退出的（暂停状态被强制退出的）
	
	if(pid < 0){
		perror("fork error");
		exit(1);
	}else if(pid == 0){	//子进程
		printf("pid: %d, ppid: %d\n",getpid(),getppid());
		
		printf("提示：此时该子进程处于暂停状态用 kill -19 子进程pid ，就可以终止子进程，waitpid函数就可以回收并检测到子进程终止前处于暂停状态\n");

		//pause();
		int i = 0;
		while(++i >0) sleep(3);		//死循环，一直sleep(3)
	}	

	do{
		pid = waitpid(pid, &status, WNOHANG | WUNTRACED); //WNOHANG--非阻塞， 
														  //WUNTRACED--可以检测到子进程终止前处于暂停状态
														  //waitpid() 如果没有检测到子进程终止，返回0
														  //如果检测到子进程终止，成功回收，返回 子进程pid
		if(pid == 0) sleep(1);		//如果没检测到子进程终止，睡眠1秒
	}while(pid == 0);			//因为option参数写了WNOHANG，所以是非阻塞，所以需要循环，直到检测到子进程终止才结束循环

	out_status(status);



	return 0;
}				/* ----------  end of function main  ---------- */





/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  out_status
 *  Description:  
 * =====================================================================================
 */
	void
out_status(int status)
{
	if(WIFEXITED(status)){	//如果子进程正常退出，输出退出状态码
		printf("normal exit: %d\n",WEXITSTATUS(status));
	}else if(WIFSIGNALED(status)){	//如果子进程运行错误，异常终止，输出终止信号码
		printf("abnormal term: %d\n",WTERMSIG(status));
	}else if(WIFSTOPPED(status)){	//如果子进程终止之前被停止过，输出停止信号码
		printf("stopped sig； %d\n",WSTOPSIG(status));
	}else{
		printf("unknonw sig\n");
	}

}		/* -----  end of function out_status  ----- */
