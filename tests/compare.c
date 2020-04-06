#include <ucontext.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <setjmp.h>
#include <assert.h>
#include <signal.h>

#define THREAD_STACK 65536
static ucontext_t uctx_main, uctx_func1, uctx_func2;
unsigned cycles_low, cycles_high;  //  1st cycles measurement
unsigned cycles_low1, cycles_high1; // 2nd cycles measurement
uint64_t sum = 0;
jmp_buf main_jb, func_jb;

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

void func3(void)
{
	if ( setjmp( func_jb) )
	{
		uint64_t start, end;
		asm volatile (  "RDTSCP\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				"CPUID\n\t"
				:"=r" (cycles_high1), "=r" (cycles_low1)
				:: "%rax", "%rbx", "%rcx", "%rdx");
		start = (((uint64_t) cycles_high << 32) | cycles_low);
		end = (((uint64_t) cycles_high1 << 32) | cycles_low1);
		//printf("%lu\n", (end - start));
		sum += end - start;
		longjmp( main_jb, 1 );
	}

	longjmp( main_jb, 1 );
}

void signalHandler( int signum )
{
	assert( signum == SIGUSR1 );
	if ( setjmp( func_jb) )
	{
		func3();
	}
	
	return;
}

static void func1(void)
{
	uint64_t start, end;
	asm volatile (  "RDTSCP\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			"CPUID\n\t"
			:"=r" (cycles_high1), "=r" (cycles_low1)
			:: "%rax", "%rbx", "%rcx", "%rdx");
	start = (((uint64_t) cycles_high << 32) | cycles_low);
	end = (((uint64_t) cycles_high1 << 32) | cycles_low1);
	//printf("%lu\n", (end - start));
	sum += end - start;
	//printf("func1: returning\n");
}


void* pthread_func(void *args)
{

	uint64_t start, end;
	asm volatile (  "RDTSCP\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			"CPUID\n\t"
			:"=r" (cycles_high1), "=r" (cycles_low1)
			:: "%rax", "%rbx", "%rcx", "%rdx");
	start = (((uint64_t) cycles_high << 32) | cycles_low);
	end = (((uint64_t) cycles_high1 << 32) | cycles_low1);
	//printf("%lu\n", (end - start));
	sum += (end-start);
}

int main(int argc, char *argv[])
{
	char func1_stack[16384];
	char func2_stack[16384];
	pthread_t tid;
	int i = 0;
	uint64_t prev_sum = 0;
	stack_t stack;
	struct sigaction sa;

	sum = 0;
	//func_call
	for(i=0; i< 10000; i++) {
		asm volatile (  "CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				:"=r" (cycles_high), "=r" (cycles_low)
				:: "%rax", "%rbx", "%rcx", "%rdx");
		func1();
	}
	printf("func call avg cycles:\t%f\n", ((float)sum)/10000.0);
	prev_sum = sum;

	sum = 0;
	/* Create the new stack */
	stack.ss_flags = 0;
	stack.ss_size = THREAD_STACK;
	stack.ss_sp = malloc( THREAD_STACK);
	if ( stack.ss_sp == 0 )
	{
		perror( "malloc: Could not allocate stack." );
		exit( 1 );
	}
	sigaltstack( &stack, 0 );

	/* Set up the custom signal handler */
	sa.sa_handler = &signalHandler;
	sa.sa_flags = SA_ONSTACK;
	sigemptyset( &sa.sa_mask );
	sigaction( SIGUSR1, &sa, 0 );

	/* Send the signal to call the function on the new stack */
	raise( SIGUSR1 );

	if ( setjmp( main_jb ) )
	{
		if ( setjmp( main_jb ) == 0 ) {
			//printf("b");
			longjmp( func_jb, 1 );
		}
	} else {
		//printf("a");
		longjmp( func_jb, 1 );
	}

	/* Execute the child context */
	for(i=0; i<10000; i++) {
		asm volatile (  "CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				:"=r" (cycles_high), "=r" (cycles_low)
				:: "%rax", "%rbx", "%rcx", "%rdx");
		if ( setjmp( main_jb ) ==0 ) {
			longjmp( func_jb, 1 );
		}
	}
	printf("longjmp avg cycles:\t%f\t(%f times slower than direct procedure calls)\n",
			((float)sum)/10000.0, ((float)sum)/prev_sum);
	prev_sum = sum;

	sum = 0;
	//func thread
	for(i=0; i< 10000; i++) {
		asm volatile (  "CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				:"=r" (cycles_high), "=r" (cycles_low)
				:: "%rax", "%rbx", "%rcx", "%rdx");

		if (getcontext(&uctx_func1) == -1)
			handle_error("getcontext");
		uctx_func1.uc_stack.ss_sp = func1_stack;
		uctx_func1.uc_stack.ss_size = sizeof(func1_stack);
		uctx_func1.uc_link = &uctx_main;
		makecontext(&uctx_func1, func1, 0);

		if (swapcontext(&uctx_main, &uctx_func1) == -1)
			handle_error("swapcontext");
	}
	printf("swapcontext avg cycles:\t%f\t(%f times slower than direct longjmp)\n",
			((float)sum)/10000.0, ((float)sum)/prev_sum);
	prev_sum = sum;

	sum = 0;
	//pthread
	for(i=0; i< 10000; i++) {
		asm volatile (  "CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				:"=r" (cycles_high), "=r" (cycles_low)
				:: "%rax", "%rbx", "%rcx", "%rdx");
		pthread_create(&tid , NULL, pthread_func, NULL);
		pthread_join(tid, NULL); // parent waits for the child to exit
	}
	printf("pthread avg cycles:\t%f\t(%f times slower than swapcontext)\n",
			((float)sum)/10000.0, ((float)sum)/prev_sum);

	exit(EXIT_SUCCESS);
}
