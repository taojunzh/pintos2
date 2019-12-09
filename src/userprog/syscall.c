#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "list.h"
#include "threads/vaddr.h"
#include "process.h"
#include "userprog/pagedir.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "devices/input.h"
#include "devices/shutdown.h"
#include "threads/synch.h"

typedef int pid_t;
struct lock file_lock;

static void syscall_handler (struct intr_frame *);
void check_addr(const void *ptr);
void halt (void);
void exit (int status);
pid_t exec (const char *cmd_line);
int wait (pid_t pid);
bool create (const char *file, unsigned initial_size);
bool remove (const char *file);
int open (const char *file);
int filesize (int fd);
int read (int fd, void *buffer, unsigned size);
int write (int fd, const void *buffer, unsigned size);
void seek (int fd, unsigned position);
unsigned tell (int fd);
void close (int fd);



void
syscall_init (void) 
{
	lock_init(&file_lock);
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	check_addr(f->esp);
	int *sp = f->esp;
	switch(*sp) 
  {
    /* Projects 2 and later. */
    case SYS_HALT:                   /* Halt the operating system. */
	halt();
	break;
    case SYS_EXIT:                   /* Terminate this process. */
	check_addr(sp+1);
	exit(*(sp+1));
	break;
    case SYS_EXEC:                   /* Start another process. */
	check_addr(sp+1);
	f->eax=exec((char*)*(sp+1));
	break;
    case SYS_WAIT:                   /* Wait for a child process to die. */
	check_addr(sp+1);
	f->eax=wait(*(sp+1));
	break;
    case SYS_CREATE:                 /* Create a file. */
	check_addr(sp+1);
	check_addr(sp+2);
	f->eax=create((char*)*(sp+1),*(sp+2));
        break;
    case SYS_REMOVE:                 /* Delete a file. */
	check_addr(sp+1);
	f->eax=remove((char*)*(sp+1));
	break;
    case SYS_OPEN:                   /* Open a file. */
	check_addr(sp+1);
	f->eax=open((char*)*(sp+1));
	break;
    case SYS_FILESIZE:               /* Obtain a file's size. */
	check_addr(sp+1);
	f->eax=filesize(*(sp+1));
	break;
    case SYS_READ:                   /* Read from a file. */
	check_addr(sp+1);
	check_addr(sp+2);
	check_addr(sp+3);
	f->eax=read(*(sp+1), (void*)*(sp+2), *(sp+3));
	break;
    case SYS_WRITE:                  /* Write to a file. */
	check_addr(sp+1);
	check_addr(sp+2);
	check_addr(sp+3);
	f->eax=write(*(sp+1), (void*)*(sp+2), *(sp+3));
	break;
    case SYS_SEEK:                   /* Change position in a file. */
	check_addr(sp+1);
	seek(*(sp+1),*(sp+2));
	break;
    case SYS_TELL:                   /* Report current position in a file. */
	check_addr(sp+1);
	f->eax=tell(*(sp+1));
	break;
    case SYS_CLOSE:                  /* Close a file. */
	check_addr(sp+1);
	close(*(sp+1));
	break;
}
  printf ("system call!\n");
//  thread_exit ();
}

void
check_addr(const void *ptr){
	if(ptr==NULL || !is_user_vaddr (ptr) || !pagedir_get_page (thread_current()->pagedir, ptr) ){
		exit(-1);
}			 																				
}

void halt(void){
	shutdown_power_off();
}
void
exit(int status){
	thread_current()->ret=status;
	thread_exit();
}

pid_t exec(const char *cmd_line){
	pid_t pid=-1;
	if(*cmd_line==NULL) return pid;
	struct thread *cur=thread_current();
	sema_down(&cur->child_sema);
	pid=process_execute(cmd_line);
	if(!cur->success){
	return -1;
}
	return pid;
}


int wait(pid_t pid){
	return process_wait(pid);
}
bool create (const char *file, unsigned initial_size){
	bool ret;
	lock_acquire(&file_lock);
	ret=filesys_create(file, initial_size);
	lock_release(&file_lock);
	return ret;
}
bool remove (const char *file){
	bool ret;
	lock_acquire(&file_lock);
	ret=filesys_remove(file);
	lock_release(&file_lock);
	return ret;
}
int open (const char *file){
	return -1;
}
int filesize (int fd){
	return -1;
}
int read (int fd, void *buffer, unsigned size){
	return -1;
}
int write (int fd, const void *buffer, unsigned size){
	int ret=-1;
	if(fd==1){
	putbuf(buffer, size);
	ret=size;
	}else{
	
	
}
	return ret;
}
void seek (int fd, unsigned position){
	return ;
}
unsigned tell (int fd){
	return -1;
}
void close (int fd){
	return;
}


