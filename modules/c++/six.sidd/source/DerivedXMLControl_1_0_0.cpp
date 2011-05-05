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
#include "six/Types.h"
#include "six/Utilities.h"
#include <import/str.h>

#include "six/sidd/DerivedXMLControl_1_0_0.h"
#include "six/sidd/DerivedData.h"

using namespace six;
using namespace six::sidd;

typedef xml::lite::Element* XMLElem;

std::string DerivedXMLControl_1_0_0::getDefaultURI() const
{
    return "urn:" + six::sidd::SIDD_ID_1_0_0.toString();
}

Data* DerivedXMLControl_1_0_0::fromXML(const xml::lite::Document* doc)
{
    // for now, just change the version of the returned data
    // we may want to override any/all of this depending on what the spec says
    DerivedData *data = (DerivedData*)DerivedXMLControl_0_5_0::fromXML(doc);
    data->setVersion(six::sidd::SIDD_1_0_0);
    return data;
}
