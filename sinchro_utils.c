/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:47:56 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/05 17:47:56 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready)); // будет ли работать без значения булл вэлью
		;
}