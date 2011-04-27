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
#ifndef __SIX_UTILS_H__
#define __SIX_UTILS_H__

#include <import/six.h>
#include <import/six/sicd.h>
#include <import/six/sidd.h>


/*!
 *  This function converts DMS corners into decimal degrees using NITRO,
 *  and then puts them into a lat-lon
 */
std::vector<six::LatLon> makeUpCornersFromDMS()
{
    int latTopDMS[3] = { 42, 17, 50 };
    int latBottomDMS[3] = { 42, 15, 14 };
    int lonEastDMS[3] = { -83, 42, 12 };
    int lonWestDMS[3] = { -83, 45, 44 };

    double latTopDecimal = nitf::Utils::geographicToDecimal(latTopDMS[0],
                                                            latTopDMS[1],
                                                            latTopDMS[2]);

    double latBottomDecimal = nitf::Utils::geographicToDecimal(latBottomDMS[0],
                                                               latBottomDMS[1],
                                                               latBottomDMS[2]);

    double lonEastDecimal = nitf::Utils::geographicToDecimal(lonEastDMS[0],
                                                             lonEastDMS[1],
                                                             lonEastDMS[2]);

    double lonWestDecimal = nitf::Utils::geographicToDecimal(lonWestDMS[0],
                                                             lonWestDMS[1],
                                                             lonWestDMS[2]);

    std::vector<six::LatLon> c(4);
    c[six::CornerIndex::FIRST_ROW_FIRST_COL] = six::LatLon(latTopDecimal,
                                                           lonWestDecimal);
    c[six::CornerIndex::FIRST_ROW_LAST_COL] = six::LatLon(latTopDecimal,
                                                          lonEastDecimal);
    c[six::CornerIndex::LAST_ROW_LAST_COL] = six::LatLon(latBottomDecimal,
                                                         lonEastDecimal);
    c[six::CornerIndex::LAST_ROW_FIRST_COL] = six::LatLon(latBottomDecimal,
                                                          lonWestDecimal);
    return c;
}

/**
 * Creates a new XMLControlRegistry. The caller is responsible for deleting
 * this when finished.
 */
six::XMLControlRegistry* newXMLControlRegistry()
{
    six::XMLControlRegistry *xmlRegistry = new six::XMLControlRegistry;

    xmlRegistry->addCreator(six::sicd::SICD_0_4_1, new six::XMLControlCreatorT<
            six::sicd::ComplexXMLControl_0_4_1>());
    xmlRegistry->addCreator(six::sicd::SICD_1_0_0, new six::XMLControlCreatorT<
            six::sicd::ComplexXMLControl_1_0_0>());
    xmlRegistry->addCreator(six::sidd::SIDD_0_5_0, new six::XMLControlCreatorT<
            six::sidd::DerivedXMLControl>());
    return xmlRegistry;
}

#endif
