# External Functions for Pipex
Here is the referrence of external functions for pipex project.

## Prototype
```c
void	*malloc(size_t size);
void	free(void *ptr);
void	exit(int status);
void	perror(const char *s);
char	*strerror(int errnum);
int		open(const char *pathname, int flags);
int		open(const char *pathname, int flags, mode_t mode);
int		close(int fd);
ssize_t	read(int fd, void *buf, size_t count);
ssize_t	write(int fd, void *buf, size_t count);
int		pipe(int pipefd[2]);
pid_t	fork(void);
int		dup(int oldfd);
int		dup2(int oldfd, int newfd);
int		access(const cahr *pathname, int mode);
int		execve(const char *pathname, char *const argv[], char *const envp[]);
pid_t	wait(int *wstatus);
pid_t	waitpid(pid_t pid, int *wstatus, int options);
int		unlink(const char *pathname);
```

## wait, waitpid
```c
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);
```
The call wait(&wstatus) is equivalent to:

	int wstatus;
	waitpid(-1, &wstatus, 0);

#### Description
The  waitpid()  system call suspends execution of the calling thread until a child specified by pid argument has changed state.  By default, waitpid() waits only  for  terminated  children.
The value of pid can be:

< -1 : wait for any child process whose process group ID is equal to the abs value of pid.

= -1 : wait for any child process.

= 0 : wait for any child process whose process group ID is equal to that of the calling process at the time of the call to waitpid();

(waitpid() の呼び出し時点で呼び出し元プロセスのプロセスグループ ID と等しいプロセスグループ ID を持つ子プロセスを待機する。)

\> 0 : wait for any child process whose process group ID is equal to the value of pid.

If wstatus is not NULL, wait() and waitpid() store status information in the int to which it points.  This integer can be inspected with the several macros (which take the integer itself as an argument, not a pointer to it, as is done in wait() and waitpid()!):

#### Return Vaue
Success : the process ID of the child whose state has changed / 
Error : -1


## open
```c
#include <stdio.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```
#### Description
The open() system call opens the file specified by *pathname*.  If the specified file does not exist, it may optionally (if **O_CREAT** is specified in flags) be created by open().
The return value of open() is a file descriptor, a small, nonnegative integer that  is  used in  subsequent  system  calls  (read(2), write(2), lseek(2), fcntl(2), etc.) to refer to the open file.  The file descriptor returned by a successful call will  be  the  lowest-numbered file descriptor not currently open for the process.

The argument *flags* must include one of the following access modes:  O_RDONLY,  O_WRONLY, or O_RDWR.  These request opening the file read-only, write-only, or read/write, respectively.

#### Return Value
Success: new file descriptor / 
Error: -1

## access
```c
#include <unistd.h>

int access(const char *pathname, int mode);
```
#### Description
access() checks whether the calling process can access the file pathname. If pathname is a symbolic link, it is dereferenced.

The mode specifies the accessibility check(s) to be performed, and is either the value F_OK, or  a  mask consisting of the bitwise OR of one or more of R_OK, W_OK, and X_OK. F_OK tests for the existence of the file.  R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.

#### Return Value
Success : 0 / 
Error : -1


## pipe - create pipe
```c
#include <unistd.h>

int pipe(int pipefd[2]);
```
#### Description
pipe()  creates a pipe, a **unidirectional** data channel that can be used for interprocess communication.  The array *pipefd* is used to return two file  descriptors  referring  to the  ends of the pipe.  *pipefd[0]* refers to the read end of the pipe.  *pipefd[1]* refers to the write end of the pipe.  **Data written** to the write end of the pipe **is buffered** by the  kernel  **until  it is read** from the read end of the pipe.  For further details, see pipe(7).

#### Return Value
Success: 0 / 
Error: -1


## dup, dup2 - duplicate a file descriptor
```c
#include <unistd.h>

int dup(int oldfd);
int dup2(int oldfd, int newfd);
```
#### Description
The  dup()  system  call creates a copy of the file descriptor *oldfd*, using the lowest-numbered unused file descriptor for the new descriptor.

The dup2() system call performs the same task as dup(), but instead of using  the  lowest-numbered  unused  file  descriptor, it uses the file descriptor number specified in *newfd*. If the file descriptor *newfd* was previously open, it is silently closed before being reused.

Note the following points:

*  If *oldfd* is not a valid file descriptor, then the  call  fails,  and  *newfd*  is  not closed.

*  If  *oldfd*  is  a  valid file descriptor, and *newfd* has the same value as *oldfd*, then dup2() does nothing, and returns *newfd*.

#### Return Value
Success: new file descriptor \ 
Error: -1


## perror
```c
#include <stdio.h>

void perror(const char *s);
```
#### Description

#### Return Value




## perror
```c
#include <stdio.h>

void perror(const char *s);
```
#### Description

#### Return Value



## perror
```c
#include <stdio.h>

void perror(const char *s);
```
#### Description

#### Return Value


