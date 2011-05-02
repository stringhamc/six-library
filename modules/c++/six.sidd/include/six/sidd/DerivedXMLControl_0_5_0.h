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
#ifndef __SIX_DERIVED_XML_CONTROL_0_5_0_H__
#define __SIX_DERIVED_XML_CONTROL_0_5_0_H__

#include "six/XMLControl.h"
#include "six/sidd/DerivedData.h"
#include "six/sidd/SFA.h"
#include <import/xml/lite.h>

namespace six
{
namespace sidd
{
/*!
 *  \class DerivedXMLControl_0_5_0
 *  \brief Turns an DerivedData object into XML and vice versa
 *
 *  Derived XMLControl object for reading and writing DerivedData*
 *  The XMLFactory should be used to create this object, and only
 *  if necessary.  A best practice is to use the six::toXMLCharArray
 *  and six::toXMLString functions to turn Data* objects into XML
 */
class DerivedXMLControl_0_5_0 : public XMLControl
{

public:

    DerivedXMLControl_0_5_0(logging::Logger* log = NULL, bool ownLog = false) :
        XMLControl(log, ownLog)
    {
    }

    virtual ~DerivedXMLControl_0_5_0()
    {
    }

    /*!
     *  Returns a new allocated DOM document, created from the DerivedData*
     */
    virtual xml::lite::Document* toXML(const Data* data);
    /*!
     *  Returns a new allocated DerivedData*, created from the DOM Document*
     *
     */
    virtual Data* fromXML(const xml::lite::Document* doc);

protected:
    typedef xml::lite::Element* XMLElem;

    static const char SI_COMMON_URI[];
    static const char SFA_URI[];

    //! Returns the default URI
    virtual std::string getDefaultURI() const;

    //! Returns the URI to use with SI Common types
    virtual std::string getSICommonURI() const;

    virtual std::string getSFAURI() const;

    virtual XMLElem createLUT(std::string name, const LUT *l, XMLElem parent =
            NULL);
    virtual XMLElem
            toXML(const ProductCreation* productCreation, XMLElem parent = NULL);
    virtual XMLElem toXML(const ProductProcessing* productProcessing, XMLElem parent =
            NULL);
    virtual void fromXML(const XMLElem elem, ProductProcessing* productProcessing);
    virtual XMLElem toXML(const ProcessingModule* procMod, XMLElem parent = NULL);
    virtual void fromXML(const XMLElem elem, ProcessingModule* procMod);
    virtual XMLElem toXML(const DownstreamReprocessing* d, XMLElem parent = NULL);
    virtual void fromXML(const XMLElem elem, DownstreamReprocessing* downstreamReproc);
    virtual XMLElem toXML(const Display* display, XMLElem parent = NULL);
    virtual XMLElem toXML(const GeographicAndTarget* g, XMLElem parent = NULL);
    virtual XMLElem toXML(const GeographicCoverage* g, XMLElem parent = NULL);
    virtual XMLElem toXML(const Measurement* measurement, XMLElem parent = NULL);
    virtual XMLElem
            toXML(const ExploitationFeatures* exFeatures, XMLElem parent = NULL);
    virtual XMLElem toXML(const Annotation *a, XMLElem parent = NULL);
    virtual void fromXML(const XMLElem productCreationXML,
            ProductCreation* productCreation);
    virtual void fromXML(const XMLElem displayXML, Display* display);
    virtual void fromXML(const XMLElem measurementXML, Measurement* measurement);
    virtual void fromXML(const XMLElem elem, GeographicAndTarget* geographicAndTarget);
    virtual void fromXML(const XMLElem elem, GeographicCoverage* geoCoverage);
    virtual void fromXML(const XMLElem elem, ExploitationFeatures* exFeatures);
    virtual void fromXML(const XMLElem annotationXML, Annotation *a);
    virtual void fromXML(const XMLElem elem, SFAGeometry *g);
    virtual XMLElem toXML(const SFAGeometry *g, std::string useName, XMLElem parent =
            NULL);
};

}
}
#endif
