/******************************************************************************\
 * $Id: defs.h 501 2002-02-12 02:32:31Z blais $
 * $Date: 2002-02-11 21:32:31 -0500 (Mon, 11 Feb 2002) $
 *
 * Copyright (C) 1999-2001  Martin Blais <blais@iro.umontreal.ca>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 ******************************************************************************/

#ifndef INCL_XXDIFF_DEFS
#define INCL_XXDIFF_DEFS

/*==============================================================================
 * EXTERNAL DECLARATIONS
 *============================================================================*/

//
// Types and enumerations
//

typedef unsigned int 	uint;


// Note: disable the namespaces for now because the moc cannot deal with this.
// We could circumvent the problem by including moc-generated output but then we
// couldn't use the automoc script.
#undef XX_USE_NAMESPACE

#ifdef XX_USE_NAMESPACE

#define XX_NAMESPACE		        Xxdiff
#define XX_NAMESPACE_BEGIN		namespace XX_NAMESPACE {
#define XX_NAMESPACE_END		}
#define XX_NAMESPACE_USING		using namespace XX_NAMESPACE;
#define XX_NAMESPACE_PREFIX		XX_NAMESPACE ::

#else

#define XX_NAMESPACE_BEGIN
#define XX_NAMESPACE_END
#define XX_NAMESPACE_USING
#define XX_NAMESPACE_PREFIX

#endif


//
// Std differences.
//

#if defined COMPILER_MIPSPRO
#define XX_THROW_NOTHING  throw()

#elif defined COMPILER_GNU
#define XX_THROW_NOTHING  __STL_NOTHROW

#elif defined COMPILER_COMPAQCXX
#define XX_THROW_NOTHING  _RWSTD_THROW_SPEC_NULL

#else
#define XX_THROW_NOTHING

#endif


//
// Debugging stuff.
//

#ifdef XX_DEBUG

#ifndef INCL_STD_IOSTREAM
#include <iostream>
#define INCL_STD_IOSTREAM
#endif


#define XX_CHECK(x)	if ( !(x) ) \
  	{ throw XxInternalError( XX_EXC_PARAMS ); }

#define XX_TRACE(x)		std::cerr << "xx_trace " << x << std::endl;

#define XX_DEBUG_COMPILE(x)	x

#else

#define XX_CHECK(x)

#define XX_TRACE(x)

#define XX_DEBUG_COMPILE(x)

#endif

#define XX_ASSERT(x)	if ( !(x) ) \
  	{ throw XxInternalError( XX_EXC_PARAMS ); }

#define XX_ABORT()	\
  	{ throw XxInternalError( XX_EXC_PARAMS ); }


#ifndef INCL_XXDIFF_EXCEPTIONS
#include <exceptions.h>
#endif

#ifdef WINDOWS
#include <winfixes/winfixes.h>
#endif

#endif

