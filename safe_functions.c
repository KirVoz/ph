/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:59:58 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/08 15:44:39 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("MALLOC ERROR!");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value spscified by mutex is invalid. ");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value spscified by attr is invalid. ");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the"
			"thread blocked waiting for mutex. ");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex. ");
	else if (ENOMEM == status)
		error_exit("The prosses cannot allocate enough memory to"
			" create another mutex. ");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("WRONG OPCODE FOR MUTEX");
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
