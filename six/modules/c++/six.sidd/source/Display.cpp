/* =========================================================================
 * This file is part of six.sidd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2014, MDA Information Systems LLC
 *
 * six.sidd-c++ is free software; you can redistribute it and/or modify
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
#include "six/sidd/Display.h"

namespace six
{
namespace sidd
{
MonitorCompensationApplied::MonitorCompensationApplied() :
    gamma(six::Init::undefined<double>()),
    xMin(six::Init::undefined<double>())
{
}

DRAHistogramOverrides::DRAHistogramOverrides() :
    clipMin(six::Init::undefined<int>()),
    clipMax(six::Init::undefined<int>())
{
}

BandInformation::BandInformation() :
    displayFlag(six::Init::undefined<size_t>())
{
}

DynamicRangeAdjustment::DRAParameters::DRAParameters() :
    pMin(six::Init::undefined<double>()),
    pMax(six::Init::undefined<double>()),
    eMinModifier(six::Init::undefined<double>()),
    eMaxModifier(six::Init::undefined<double>())
{
}

DynamicRangeAdjustment::DRAOverrides::DRAOverrides() :
    subtractor(six::Init::undefined<double>()),
    multiplier(six::Init::undefined<double>())
{
}

bool MonochromeDisplayRemap::equalTo(const Remap& rhs) const
{
    const MonochromeDisplayRemap* remap = dynamic_cast<const MonochromeDisplayRemap*>(&rhs);
    if (remap != NULL)
    {
        return *this == *remap;
    }
    return false;
}

bool MonochromeDisplayRemap::operator==(const MonochromeDisplayRemap& rhs) const
{
    return (remapType == rhs.remapType &&
        remapParameters == rhs.remapParameters &&
        remapLUT == rhs.remapLUT);
}

bool ColorDisplayRemap::equalTo(const Remap& rhs) const
{
    ColorDisplayRemap const* remap = dynamic_cast<ColorDisplayRemap const*>(&rhs);
    if (remap != NULL)
    {
        return *this == *remap;
    }
    return false;
}

bool ColorDisplayRemap::operator==(const ColorDisplayRemap& rhs) const
{
    return remapLUT == rhs.remapLUT;
}

Display::Display() :
    pixelType(PixelType::NOT_SET),
    magnificationMethod(MagnificationMethod::NOT_SET),
    decimationMethod(DecimationMethod::NOT_SET),
    histogramOverrides(NULL),
    monitorCompensationApplied(NULL)
{
}
bool Display::operator==(const Display& rhs) const
{
    return (pixelType == rhs.pixelType &&
        remapInformation == rhs.remapInformation &&
        magnificationMethod == rhs.magnificationMethod &&
        decimationMethod == rhs.decimationMethod &&
        histogramOverrides == rhs.histogramOverrides &&
        monitorCompensationApplied == rhs.monitorCompensationApplied &&
        displayExtensions == rhs.displayExtensions);
}

}
}
