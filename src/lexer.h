/****************************************************************************\
 *                            Oracion  Assembler                            *
 *                                                                          *
 *                        Copyright (C) 2022 Aquefir                        *
 *                 Released under Artisan Software Licence.                 *
\****************************************************************************/

#ifndef INC__ORAS_LEXER_H
#define INC__ORAS_LEXER_H

#include <uni/types/int.h>

enum
{
	LEXEME_EOF,
	LEXEME_LCOMMENT,
	LEXEME_DCOMMENT,
	LEXEME_LABEL,
	LEXEME_DIREC_IF,
	LEXEME_DIREC_IFDEF,
	LEXEME_DIREC_IFNDEF,
	LEXEME_DIREC_ELIF,
	LEXEME_DIREC_ELIFDEF,
	LEXEME_DIREC_ELIFNDEF,
	LEXEME_DIREC_ELSE,
	LEXEME_DIREC_ENDIF,
	LEXEME_DIREC_SET,
	LEXEME_DIREC_GLOBL,
	LEXEME_DIREC_1BYTE,
	LEXEME_DIREC_2BYTE,
	LEXEME_DIREC_4BYTE,
	LEXEME_DIREC_8BYTE,
	LEXEME_DIREC_16BYTE,
	LEXEME_DIREC_1BYTER,
	LEXEME_DIREC_2BYTER,
	LEXEME_DIREC_4BYTER,
	LEXEME_DIREC_8BYTER,
	LEXEME_DIREC_16BYTER,
	LEXEME_OP_MNEMONIC,
	LEXEME_OP_PARAM,
	MAX_LEXEME
};

enum
{
	EXPR_LPAREN,
	EXPR_RPAREN,
	EXPR_PLUS,
	EXPR_MINUS,
	EXPR_MUL,
	EXPR_DIV,
	EXPR_MOD,
	EXPR_RSHIF,
	EXPR_LSHIF,
	EXPR_OR,
	EXPR_AND,
	EXPR_OROR,
	EXPR_ANDAND,
	EXPR_NOT,
	EXPR_BITNOT,
	EXPR_XOR,
	EXPR_EQ,
	EXPR_NE,
	EXPR_GT,
	EXPR_GE,
	EXPR_LE,
	EXPR_LT,
	EXPR_QMARK,
	EXPR_COLON,
	MAX_EXPR
};

struct bigint
{
	ptri bitcount;
	u8 * data;
};

struct lexeme_lcomment
{
	u8 * data;
	ptri sz;
};

struct lexeme_dcomment
{
	u8 * data;
	ptri sz;
};

struct lexeme_exprtok
{
	union
	{
		struct bigint n;
		u32 sym;
	};
};

struct lexeme_expr
{
	ptri count;
	struct lexeme_exprtok * toks;
};

struct lexeme
{
	ptri offset;
	u32 len;
	u8 type;
};

#endif /* INC__ORAS_LEXER_H */
