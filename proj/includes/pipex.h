/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:59 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/03 21:33:02 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include "../libft/includes/libft_bonus.h"
# include "../libft/includes/ft_printf.h"

# include <stdlib.h>

# define SUCCESS 0
# define FAILURE 1

typedef enum s_bool
{
	error = -1,
	success,
	failure
}	t_bool;

typedef struct s_pipex
{
	int		i_fd;
	int		o_fd;
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

int	pipex(char *av, char *ev);

#endif
