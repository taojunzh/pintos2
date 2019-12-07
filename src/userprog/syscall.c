#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);
static void exit (int);
static pid_t exec (const char *);
static int wait (pid_t);
static bool create (const char*, unsigned);
static bool remove (const char *);
static int open (const char *);
static int filesize (int);
static int read (int, void *, unsigned);
static int write (int, const void *, unsigned);
static void seek (int, unsigned);
static unsigned tell (int);
static void close (int);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	check(f->esp);
	int * sp = f->esp;
	switch(*sp) 
  {
    /* Projects 2 and later. */
    case SYS_HALT:                   /* Halt the operating system. */
	shutdown_power_off();
	break;
    case SYS_EXIT:                   /* Terminate this process. */
	check(p+1);
	exit(*(p+1));
	break;
    case SYS_EXEC:                   /* Start another process. */
    case SYS_WAIT:                   /* Wait for a child process to die. */
    case SYS_CREATE:                 /* Create a file. */
    case SYS_REMOVE:                 /* Delete a file. */
    case SYS_OPEN:                   /* Open a file. */
    case SYS_FILESIZE:               /* Obtain a file's size. */
    case SYS_READ:                   /* Read from a file. */
    case SYS_WRITE:                  /* Write to a file. */
    case SYS_SEEK:                   /* Change position in a file. */
    case SYS_TELL:                   /* Report current position in a file. */
    case SYS_CLOSE:                  /* Close a file. */
}
  printf ("system call!\n");
  thread_exit ();
}

bool
check(const void *ptr){
	if(!is_user_vaddr (ptr) || pagedir_get_page (thread_current()->pagedir, *ptr)==NULL ){
		exit(-1);
		return false;
}			
	return true; 																				
}
void
exit(int status){
	
}

pid_t
exec(const char *cmd_line);

int 
wait(pid_t pid);
}
