/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:47:56 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/08 15:07:17 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready)) // будет ли работать без значения булл вэлью
		;
}
