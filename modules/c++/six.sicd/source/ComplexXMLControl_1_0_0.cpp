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
#include "six/sicd/ComplexXMLControl_1_0_0.h"
#include "six/sicd/ComplexData.h"
#include "six/Types.h"
#include "six/Utilities.h"
#include <import/str.h>
#include <iostream>

using namespace six;
using namespace six::sicd;

typedef xml::lite::Element* XMLElem;

const char ComplexXMLControl_1_0_0::SICD_URI_1_0_0[] = "urn:SICD:1.0.0";

std::string ComplexXMLControl_1_0_0::getDefaultURI() const
{
    return SICD_URI_1_0_0;
}

std::string ComplexXMLControl_1_0_0::getSICommonURI() const
{
    return SICD_URI_1_0_0;
}

Data* ComplexXMLControl_1_0_0::fromXML(const xml::lite::Document* doc)
{
    // for now, just change the version of the returned data
    ComplexData *sicd = (ComplexData*)ComplexXMLControl_1_0_0::fromXML(doc);
    sicd->mVersion = six::sicd::SICD_1_0_0;
    return sicd;
}
