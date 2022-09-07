/*****************************************************************************\
 *                             Oracion Assembler                             *
 *                                                                           *
 *                        Copyright (C) 2022 Aquefir.                        *
 *                  Released under Artisan Software Licence                  *
\*****************************************************************************/

#ifndef INC__ORAS_MAIN_H
#define INC__ORAS_MAIN_H

#include <uni/types/int.h>

struct preamble
{
	u32 valid : 1;
	u32 helpwanted : 1;
	u32 assemble : 1;
	u8 * outfname;
	u8 * text;
};

u8 ** ascii_check( char *[], ptri );
struct preamble preamble( u8 ** );
struct preamble preamble2( struct preamble, u8 * );

#endif /* INC__ORAS_MAIN_H */
