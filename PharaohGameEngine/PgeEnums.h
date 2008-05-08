
/*! $Id$
 *  @file   PgeEnums.h
 *  @author Chad M. Draper
 *  @date   May 7, 2008
 *  @brief  Common enumerated values used by the Pharaoh Game Engine.
 *
 */

#ifndef PGEENUMS_H_INCLUDED
#define PGEENUMS_H_INCLUDED

#include "PgeTypes.h"

namespace PGE
{
    /** @enum MatrixOrder
        Order for multiplying matrices
    */
    enum MatrixOrder
    {
        MatrixOrderPrepend,
        MatrixOrderAppend
    };

} // namespace PGE

#endif // PGEENUMS_H_INCLUDED
