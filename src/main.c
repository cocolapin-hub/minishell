/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:14:39 by claffut           #+#    #+#             */
/*   Updated: 2025/09/03 14:04:16 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(void)
{
	//t_command	*cmd = NULL;
    char *line;

    while (1)
    {
		line = readline("minishell$ ");
		if (!line)
			break;


		/*parsing*/
        // if (*line)
		// {
		//	   cmd = parsing(line);
        //     add_history(line);
		// }

		/*executable*/
		// if (strlen(line) != 0 && line != NULL)
		// 	exec(cmd);

		printf("You typed: %s\n", line);
        free(line);
    }
    return 0;
}





