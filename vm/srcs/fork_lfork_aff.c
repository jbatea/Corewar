/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 13:02:51 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/09/02 13:04:37 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_fork(t_args *args, t_vm *vm, t_process *process)
{
	t_process	*new;
	int			i;

	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_exit_error("Error : malloc process", NULL);
	new->live = process->live;
	new->carry = process->carry;
	new->cycle_to_wait = 0;
	new->waiting_op = 0;
	new->pc = ft_loop_memory((process->pc + (args->values[0] % IDX_MOD)));
	new->prev = NULL;
	process->is_waiting = 0;
	i = 0;
	while (i < REG_NUMBER)
	{
		new->reg[i] = process->reg[i];
		i++;
	}
	vm->process->prev = new;
	new->next = vm->process;
	vm->process = new;
	vm->nb_process++;
}

void		ft_lfork(t_args *args, t_vm *vm, t_process *process)
{
	t_process	*new;
	int			i;

	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_exit_error("Error : malloc process", NULL);
	new->live = process->live;
	new->carry = process->carry;
	new->waiting_op = 0;
	new->cycle_to_wait = 0;
	new->pc = ft_loop_memory(process->pc + args->values[0]);
	new->prev = NULL;
	i = 0;
	while (i < REG_NUMBER)
	{
		new->reg[i] = process->reg[i];
		i++;
	}
	vm->process->prev = new;
	new->next = vm->process;
	vm->process = new;
	vm->nb_process++;
}

void		ft_aff(t_args *args, t_vm *vm, t_process *process)
{
	if (args->values[0] > 0 && args->values[0] <= REG_NUMBER)
		ft_putchar((unsigned char)process->reg[args->values[0]]);
	(void)args;
	(void)vm;
}
