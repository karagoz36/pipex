/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:03:46 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/06/28 16:17:31 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

void	ft_free(char **str);
void	ft_error(char *err_msg);
void	execute(char *cmd_str, char **env);
char	*get_next_line(int fd);
void	here_doc(char *limiter);

#endif