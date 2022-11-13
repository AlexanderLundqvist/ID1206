#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* -----------------------------------------------------------------------------
Part 1
The purpose of this part is to work with fork, exec, and wait to create new
processes and use pipe to communicate between parent/child processes. You
should implement a code to illustrate the following command: ls / | wc -l.
This command prints out the number of files in the root path: ls / shows the
files/directories in the root path, and its output will be piped through | to wc
-l, which counts the number of lines.

Hint1: Use fork to make a child process. Then, the child process executes ls
/, passing the result (i.e., the list files/directories) through a pipe to the parent
process. The parent executes wc -l to print out the number of lines for the list
passed by the child.

Hint2: You can use dup2 to redirect the output of the exec to the input descriptor
made by pipe.

Written by Max Dern and Alexander Lundqvist
2022-11-13
----------------------------------------------------------------------------- */

int main(int argc, char *argv[]) {
  /*
  pipeFileDescriptors
  = {stdin(feed data somewhere), stdout(display data somewhere), stderr()}
  default for UNIX based systems.
  */
	int pipeFileDescriptors[2];
  /*
  A successful call to pipe() returns two open file descriptors in the array
  filedes: one for the read end of the pipe (filedes[0]) and one for the
  write end (filedes[1]).
  */
	pipe(pipeFileDescriptors);

  /*
  Creates the child process that will be responsible for executing the
  ls / command and then piping it to the parent process.
  */
	switch(fork()) {
		case 0: // In the case of a child process
      /*
      close() closes a file descriptor, so that it no longer refers to any
      file and may be reused.
      */
			close(pipeFileDescriptors[0]);
      /*
      The dup() system call creates a copy of a file descriptor.
      The dup2() system call is similar to dup() but the basic difference
      between them is that instead of using the lowest-numbered unused file
      descriptor, it uses the descriptor number specified by the user.
      */
			dup2(pipeFileDescriptors[1], 1);
			close(pipeFileDescriptors[1]);
			/*
			Execute the ls command by specifying the file and the path as /
			*/
		  execlp("ls","ls","/", (char *) NULL);
		default: // The parent process
      close(pipeFileDescriptors[1]);
      dup2(pipeFileDescriptors[0], 0);
      close(pipeFileDescriptors[0]);
      execlp("wc", "wc", "-l", (char *) NULL);
	}

	close(pipeFileDescriptors[0]);
	close(pipeFileDescriptors[1]);
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
	return 0;
}
