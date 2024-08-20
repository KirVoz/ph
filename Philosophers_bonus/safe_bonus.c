/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:17:29 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/18 06:57:12 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	handle_sem_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (EACCES == status)
		error_exit("The required permissions (for reading and/or writing "
            "are denied for the given flags");
	else if (EINVAL == status && (opcode == OPEN || opcode == CLOSE ||
		opcode == POST || opcode == WAIT))
		error_exit("sem is not a valid semaphore descriptor");
	else
		error_exit("sem troubleshoot needed...");
}

void	safe_sem_handle(sem_t *semaphore, t_opcode opcode)
{
	if (OPEN == opcode)
		handle_sem_error(sem_wait(semaphore), opcode);
	else if (CLOSE == opcode)
		handle_sem_error(sem_close(semaphore), opcode);
	else if (POST == opcode)
		handle_sem_error(sem_post(semaphore), opcode);
	else if (WAIT == opcode)
		handle_sem_error(sem_wait(semaphore), opcode);
	else
		error_exit("Wrong opcode for sem_handle:"
			" use <OPEN> <CLOSE> <POST> <WAIT>");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		error_exit("No resourses to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that "
			"specified by a given thread ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of "
			"thread specifies the calling thread.");
}

void	safe_thread_handle(pthread_t *thread, void *(foo)(void *), void *data,
		t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle:"
			" use <CREATE> <JOIN> <DETACH>");
}
