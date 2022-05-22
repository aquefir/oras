/****************************************************************************\
 *                            Oracion  Assembler                            *
 *                                                                          *
 *                        Copyright (C) 2022 Aquefir                        *
 *                 Released under Artisan Software Licence.                 *
\****************************************************************************/

#include "main.h"

#include <stdio.h>
#include <uni/err.h>
#include <uni/memory.h>
#include <uni/str.h>
#include <uni/types/int.h>

const char * const help_text =
	"\noras\nThe Oracion Assembler\n\nCreated by Alexander Nicholi\n"
	"Copyright (C) 2022 Aquefir.\nAll rights reserved.\n\nUsage:\n\n"
	"   $ oras --help\n   $ oras -h\n      Print this help text and "
	"exit.\n\n   $ oras assemble <arch> [input] [output]\n      Asse"
	"mble an already desymbolised file into machine code. Valid\n   "
	"   values for <arch> are: 8086 i186 i286 armv4t [input] is opti"
	"onal;\n      if absent, stdin is used. [output] is optional; if";
const char * const help_text2 =
	" absent, stdout\n      is used. If only one optional parameter "
	"is given, it is assumed\n      to be [input].\n";

u8 ** ascii_check( char * av[], ptri ac )
{
	ptri i;
	u8 ** ret = uni_alloc( sizeof( u8 * ) * ( ac + 1 ) );
	ret[ac]   = NULL;

	for( i = 0; i < ac; ++i )
	{
		ptri j;

		for( j = 0; av[i][j] != '\0'; ++j )
		{
			const u8 c = (u8)av[i][j];

			if( c & 0x80 )
			{
				uni_perror(
					"Invalid character in argv[%lu] at position %lu: 0x%02X\n",
					i,
					j,
					c );
				uni_die( );
			}
		}

		ret[i] = uni_alloc( sizeof( u8 ) * ( j + 1 ) );
		uni_memcpy( ret[i], (const void *)av[i], j );
		ret[i][j] = '\0';
	}

	return ret;
}

int main( int ac, char * av[] )
{
	/* TODO: Preamble (popt, input, initial state) */
	const ptri argc  = ac <= 0 ? 0 : (ptri)ac;
	u8 ** const argv = ascii_check( av, argc );
	struct state s   = preamble( argv );

	if( !s.valid || s.helpwanted )
	{
		printf( "%s%s\n", help_text, help_text2 );

		return s.valid ? 0 : 127;
	}

	/* TODO: Lexer (turn raw input into token stream) */

	/* TODO: Parser (turn token stream into AST) */

	/* TODO: Generator (turn AST into assembly) */

	return 0;
}

struct state preamble( u8 ** av )
{
	struct state ret;
	ptri i;

	uni_memset( &ret, 0, sizeof ret );

	for( i = 0; av[i] != NULL; ++i )
	{
		const char * a = (const char *)av[i];

		if( uni_strequ( a, "-h" ) || uni_strequ( a, "--help" ) )
		{
			/* set it as invalid if we already asked for help or
			 * assembly */
			ret.valid = ret.helpwanted || ret.assemble ? 0 : 1;
			ret.helpwanted = 1;
		}
		else if( uni_strequ( a, "assemble" ) )
		{
			if( i != 1 )
			{
				ret.valid = 0;
			}
			else
			{
				ret.valid    = 1;
				ret.assemble = 1;
			}
		}
		else if( ret.assemble )
		{
			if( i == 2 )
			{
				ret.in = av[i];
			}
			else if( i == 3 )
			{
				ret.out = av[i];
			}
			else
			{
				ret.valid = 0;
			}
		}
		else
		{
			ret.valid = 0;
		}
	}

	return ret;
}
