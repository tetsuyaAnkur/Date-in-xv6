# Date-in-xv6


# Files Changed

I have added a system call named as date, which returns today’s date.
It is a simple system call, but for implementing it a lot of files
needed to be modified.

I started with syscall.h file where a number is assigned to every
system call in the xv6 system. There are 21 system calls already
defined in this file.

So I added the following line to reserve a system call number for
my own system call -
              
              #define SYS_date 22
              
Now I had to make some changes in syscall.c file related to the line I
added in the header file above. So, I opened the C file. There was an
array of function pointers inside the file with the function prototype

        static int (*syscalls[ ])(void).
        
It uses the numbers of system calls defined above as indexes for a pointer
to each system call function defined elsewhere. At the end of this function
pointer array, I added the following line -
                
                [SYS_getyear] sys_date,
                
This means, when a system call occurred with the system call number 22, the
function pointed by the function pointer sys_date will be called.

So, I had to implement this function. However, this file was not the one to 
implement it. I just put the function prototype here inside this file, using
the line below -
                
                extern int sys_date(void);
                
Now, I had to implement this actual system call function. There are two files
inside xv6 system where system calls are defined.
        
        sysproc.c and sysfile.c are those two places.

On checking, I found out that many system calls related to file system are located in
sysfile.c while the rest are in sysproc.c. So, to implement my system call, I used the
file sysproc.c. I added the following function implementation at the end of the file -

        int sys_date(void)
        {
          struct rtcdate *r;
          if(argptr(0, (void*)&r, sizeof(r)) < 0)
           return -1;
          cmostime(r);
          return 0;
         }
         
Now just two little files needed to be edited and these files would contain the interface
for the user program to access the system call. First of these files is called usys.S. 
I added the line given below at the end of the file -

          SYSCALL(date)
          
Then, I modified user.h by adding the following line -
            
            int date(struct rtcdate *);
            
This is the function that the user program will be calling. There is no such function
implemented in the system. Instead, a call to the below function from a user program
will be simply mapped to the system call number 22 which is defined as SYS_date
preprocessor directive. The system knows what exactly is this system call and how to
handle it.

After all the above steps my xv6 operating system now contains a new system call. Now
I wrote a user program which would try to make that new system call to see whether
the xv6 kernel responds to it.
