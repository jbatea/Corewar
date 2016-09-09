/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_lld_lldi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 13:06:04 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/09/08 18:53:34 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_sti(t_args *args, t_vm *vm, t_process *process)
{
	int		values[2];
	int		addr;

	if ((args->types[0] != REG_CODE) ||
		(args->types[1] != DIR_CODE && args->types[1] != IND_CODE &&
									args->types[1] != REG_CODE) ||
		(args->types[2] != T_REG && args->types[2] != DIR_CODE))
	{
		return ;
	}
	if (ft_check_reg_exist(args))
	{
		values[0] = get_value_depending_on_type(1, args, process, vm);
		values[1] = get_value_depending_on_type(2, args, process, vm);
		addr = values[0] + values[1];
		write_byte(process->reg[args->values[0] - 1],
				vm, addr % IDX_MOD, process);
	}
}

void		ft_lld(t_args *args, t_vm *vm, t_process *process)
{
	int		value;

	value = 0;
	if ((args->types[0] != DIR_CODE && args->types[0] != IND_CODE) ||
		args->types[1] != REG_CODE)
	{
		process->carry = 0;
		return ;
	}
	if (args->types[0] == IND_CODE)
		value = vm->memory[ft_loop_memory(process->pc + args->values[0])];
	else if (args->types[0] == DIR_CODE)
		value = args->values[0];
	if (args->values[1] > 0 && args->values[1] <= REG_NUMBER)
	{
		process->reg[args->values[1] - 1] = value;
		if (value == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	else
		process->carry = 0;
}

void		ft_lldi(t_args *args, t_vm *vm, t_process *process)
{
	int		values[2];
	int		value;
	int		addr;

	if ((args->types[0] != DIR_CODE && args->types[0] != IND_CODE &&
		args->types[0] != REG_CODE) || (args->types[1] != DIR_CODE &&
		args->types[1] != REG_CODE) || args->types[2] != REG_CODE)
	{
		process->carry = 0;
	}
	else if (ft_check_reg_exist(args))
	{
		values[0] = get_value_depending_on_type(0, args, process, vm);
		values[1] = get_value_depending_on_type(1, args, process, vm);
		addr = values[0] + values[1];
		value = ft_get_value(&vm->memory[ft_loop_memory(process->pc + addr)],
														4);
		process->reg[args->values[2] - 1] = value;
		if (value == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	else
		process->carry = 0;
}
