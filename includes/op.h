/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2016/09/09 05:15:05 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define IS_REG					1
# define IS_DIR_VALUE			2
# define IS_DIR_LABEL			3
# define IS_IND_VALUE			4
# define IS_IND_LABEL			5

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define HEADER_SIZE			4 + PROG_NAME_LENGTH + 8 + COMMENT_LENGTH + 4

typedef struct					s_header
{
	unsigned int				magic;
	char						*tmp;
	int							isset_name;
	int							isset_comment;
	int							setting;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef struct					s_op
{
	char						*name;
	int							nb_args;
	int							type_arg[3];
	int							code;
	int							cycle;
	char						*desc;
	int							octet;
	int							unknown;
	int							label_size;
	t_bool						has_encoding;
}								t_op;

static t_op						g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4, FALSE},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 4, TRUE},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 0, TRUE},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 0, TRUE},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 0, TRUE},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 4, TRUE},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 4, TRUE},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 4, TRUE},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 2, FALSE},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 2, TRUE},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 2, TRUE},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 2, FALSE},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 4, TRUE},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2, TRUE},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 2, FALSE},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 2, TRUE},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0, 0}
};

#endif
