/*****************************************************************************\
 *                             Oracion Assembler                             *
 *                                                                           *
 *                        Copyright (C) 2022 Aquefir.                        *
 *                  Released under Artisan Software Licence                  *
\*****************************************************************************/

#include "main.h"

#include <stdio.h>
#include <uni/err.h>
#include <uni/memory.h>
#include <uni/str.h>
#include <uni/types/int.h>

#define BUF_SZ 65536

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

int main( int ac, char * av[] )
{
	/* TODO: Preamble (popt, input, initial state) */
	const ptri argc  = ac <= 0 ? 0 : (ptri)ac;
	u8 ** const argv = ascii_check( av, argc );

	const struct preamble p = preamble( argv );

	if(!p.valid || p.helpwanted)
	{
		printf( "%s%s\n", help_text, help_text2 );

		return p.valid ? 0 : 127;
	}

	printf( "%s\n", p.text );

	/* TODO: Lexer (turn raw input into token stream) */

	/* TODO: Parser (turn token stream into AST) */

	/* TODO: Generator (turn AST into assembly) */

	printf( "\n" );

	return 0;
}

u8 ** ascii_check( char * av[], ptri ac )
{
	ptri i;
	u8 ** ret = uni_alloc( sizeof( u8 * ) * ( ac + 1 ) );
	ret[ac]   = NULL;

	for(i = 0; i < ac; ++i)
	{
		ptri j;

		for(j = 0; av[i][j] != '\0'; ++j)
		{
			const u8 c = (u8)av[i][j];

			if(c >= 0x80)
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

struct preamble preamble( u8 ** av )
{
	struct preamble ret;
	u8 * in = NULL;
	ptri i;

	uni_memset( &ret, 0, sizeof ret );

	for(i = 0; av[i] != NULL; ++i)
	{
		const char * a = (const char *)av[i];

		if(uni_strequ( a, "-h" ) || uni_strequ( a, "--help" ))
		{
			/* set it as invalid if we already asked for help or
			 * assembly */
			ret.valid = ret.helpwanted || ret.assemble ? 0 : 1;
			ret.helpwanted = 1;
		}
		else if(uni_strequ( a, "assemble" ))
		{
			if(i != 1)
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
			if(i == 2)
			{
				in = av[i];
			}
			else if(i == 3)
			{
				ret.outfname = av[i];
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

	return ret.valid ? preamble2( ret, in ) : ret;
}

struct preamble preamble2( struct preamble ret, u8 * in )
{
	FILE * const fd = in == NULL ? stdin : fopen( (const char *)in, "rb" );
	u8 buf[BUF_SZ];
	ptri text_sz = 0, text_cap = BUF_SZ;

	uni_memset( buf, 0, BUF_SZ );
	ret.text = uni_alloc( sizeof( u8 ) * BUF_SZ );

	if(in == NULL)
	{
		freopen( NULL, "rb", stdin );
	}

	for(;;)
	{
		const ptri count = (ptri)fread( buf, BUF_SZ, 1, fd );
		void * const o   = (void *)((ptri)ret.text + text_sz);

		if(text_sz + count > text_cap)
		{
			/* << 1 -> * 2 */
			u8 * const nu = uni_realloc( ret.text, text_cap << 1 );

			ret.text = nu;
			text_cap <<= 1; /* *= 2 */
		}

		uni_memcpy( o, (const void *)buf, count );
		text_sz += count;

		if(count < BUF_SZ)
		{
			if(ferror( fd ))
			{
				uni_perror( "Failure reading input stream" );

				if(in != NULL)
				{
					fclose( fd );
				}

				ret.valid = 0;

				return ret;
			}

			break;
		}
	}

	/* realloc so it's just big enough */
	ret.text = uni_realloc( ret.text, text_sz + 1 );
	/* place the NUL at the end now since we're done */
	ret.text[text_sz] = '\0';

	if(in != NULL)
	{
		fclose( fd );
	}

	return ret;
}
