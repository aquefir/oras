/****************************************************************************\
 *                            Oracion  Assembler                            *
 *                                                                          *
 *                        Copyright (C) 2022 Aquefir                        *
 *                 Released under Artisan Software Licence.                 *
\****************************************************************************/

#ifndef INC__ORAS_MAIN_H
#define INC__ORAS_MAIN_H

#include <uni/types/int.h>

struct state
{
	u8 * text;
	u32 valid : 1;
	u32 helpwanted : 1;
	u32 assemble : 1;
	u8 * in;
	u8 * out;
};

struct state preamble( u8 ** );

#endif /* INC__ORAS_MAIN_H */
