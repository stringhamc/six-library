/* =========================================================================
 * This file is part of six-c++ 
 * =========================================================================
 * 
 * (C) Copyright 2004 - 2009, General Dynamics - Advanced Information Systems
 *
 * six-c++ is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this program; If not, 
 * see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef __SIX_DERIVED_XML_CONTROL_1_0_0_H__
#define __SIX_DERIVED_XML_CONTROL_1_0_0_H__

#include "six/sidd/DerivedXMLControl_0_5_0.h"

namespace six
{
namespace sidd
{

class DerivedXMLControl_1_0_0 : public DerivedXMLControl_0_5_0
{

public:

    DerivedXMLControl_1_0_0(logging::Logger* log = NULL, bool ownLog = false) :
        DerivedXMLControl_0_5_0(log, ownLog)
    {
    }

    virtual ~DerivedXMLControl_1_0_0()
    {
    }

    virtual Data* fromXML(const xml::lite::Document* doc);

protected:

    //! Returns the default URI
    virtual std::string getDefaultURI() const;

};

}
}
#endif
