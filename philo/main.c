/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:20:03 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/25 15:50:57 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*thread_function(void *arg)
{
	int* num = (int*)arg;
	printf("Thread started with value: %d\n", *num);
	for (int i = 0; i < 5; i++)
	{
        printf("Thread working: %d\n", i);
        usleep(50000);  // Sleep for 0.5 seconds (simulate work)
    }

    printf("Thread finished\n");
    return NULL;
}

int	main(void)
{
	pthread_t thread1, thread2;   // Thread identifiers
    int arg1 = 1, arg2 = 2;

	if (pthread_create(&thread1, NULL, thread_function, &arg1) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }

    // Create thread 2
    if (pthread_create(&thread2, NULL, thread_function, &arg2) != 0) {
        perror("Failed to create thread 2");
        return 2;
    }
	printf("Main waiting for thread to finish...\n");
	if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join thread 1");
        return 3;
    }

    // Wait for thread 2 to finish
    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread 2");
        return 4;
    }
	printf("the thread is finish !\n");
	return (0);
}
