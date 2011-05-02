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
#ifndef __SIX_COMPLEX_XML_CONTROL_1_0_0_H__
#define __SIX_COMPLEX_XML_CONTROL_1_0_0_H__

#include "six/sicd/ComplexXMLControl_0_4_1.h"

namespace six
{
namespace sicd
{
/*!
 *  \class ComplexXMLControl_1_0_0
 *  \brief Turn a ComplexData object into XML or vice-versa
 *
 *  This class covers version 1.0.0. Other classes can derive this one as
 *  updates are made to the specification.
 */
class ComplexXMLControl_1_0_0 : public ComplexXMLControl_0_4_1
{

public:
    //!  Constructor
    ComplexXMLControl_1_0_0(logging::Logger* log = NULL) :
        ComplexXMLControl_0_4_1(log)
    {
    }

    //!  Destructor
    virtual ~ComplexXMLControl_1_0_0()
    {
    }

    virtual Data* fromXML(const xml::lite::Document* doc);

protected:

    typedef xml::lite::Element* XMLElem;

    //! Returns the default URI
    virtual std::string getDefaultURI() const;

    //! Returns the URI to use with SI Common types
    virtual std::string getSICommonURI() const;

};

}
}
#endif
