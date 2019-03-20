
#include <nanvix/const.h>
#include <nanvix/pm.h>
#include <nanvix/hal.h>
#include <sys/sem.h>

/**
	* @brief Create a semaphore
	* 
	* @details Take the initial value of a semaphore and return the initializing semaphore. If the initial value is negative, return a dead semaphore
	*
**/
PUBLIC Semaphore create(int n){
	Semaphore sem;

	if(n<0){
		return destroy(sem);
	}

	sem.val = n; //assert n>0
	sem.waiting_queue = NULL;
	
	return sem;
}

/**
	* @brief Decrease the semaphore's value and return the new semaphore
	* 
	* @details If the value become negative, the current processus is put in sleep. This function is a critical section.
	*
**/
PUBLIC Semaphore down(Semaphore sem){
	disable_interrupts();
	sem.val--;
	if(sem.val<0){		
		sleep(sem.waiting_queue,PRIO_SEM);
	}
	enable_interrupts();
	return sem;
}

/**
	* @brief Increase the semaphore's value and return the new semaphore
	* 
	* @details If the value become positive, we wake up the first process in the waiting queue. This function is a critical section.
	*
**/
PUBLIC Semaphore up(Semaphore sem){
	disable_interrupts();
	sem.val++;
	if(sem.val>=0){
		wakeup(sem.waiting_queue);
	}
	enable_interrupts();
	return sem;
}

/**
	* @brief Destroy the semaphore and return the new semaphore
	* 
	* @details Set the semaphore's value at DEAD_SEM and flutch its waiting queue.
	*
**/
PUBLIC Semaphore destroy(Semaphore sem){
	sem.val= DEAD_SEM;
	sem.waiting_queue=NULL;
	return sem;
}