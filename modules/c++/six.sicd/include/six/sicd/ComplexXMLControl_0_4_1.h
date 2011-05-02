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
#ifndef __SIX_COMPLEX_XML_CONTROL_0_4_1_H__
#define __SIX_COMPLEX_XML_CONTROL_0_4_1_H__

#include "six/XMLControl.h"
#include "six/sicd/ComplexData.h"
#include <import/xml/lite.h>

namespace six
{
namespace sicd
{
/*!
 *  \class ComplexXMLControl_0_4_1
 *  \brief Turn a ComplexData object into XML or vice-versa
 *
 *  This class covers version 0.4.1. Other classes can derive this one as
 *  updates are made to the specification.
 *
 *  This class converts a ComplexData* object into a SICD XML
 *  Document Object Model (DOM).  The XMLControlFactory can be used
 *  to produce either SICD XML or SIDD XML for each Data* within a node.
 *
 *  Direct use of this class is discouraged, but publicly available.
 *  The best practice is to call six::toXMLCharArray() or six::toXMLString().
 *
 *  To use this class generally, consider using the 
 *  XMLControlFactory::newXMLControl() methods
 *  to create this object.
 */
class ComplexXMLControl_0_4_1 : public XMLControl
{

public:
    //!  Constructor
    ComplexXMLControl_0_4_1(logging::Logger* log = NULL) :
        XMLControl(log)
    {
    }

    //!  Destructor
    virtual ~ComplexXMLControl_0_4_1()
    {
    }

    /*!
     *  This function takes in a ComplexData object and converts
     *  it to a new-allocated XML DOM.
     *
     *  \param data Either a ComplexData or Deriv    XMLElem createEarthModelType(std::string name, const EarthModelType& value,
     XMLElem parent = NULL);
     XMLElem createSideOfTrackType(std::string name,
     const SideOfTrackType& value, XMLElem parent =
     NULL);edData object
     *  \return An XML DOM
     */
    virtual xml::lite::Document* toXML(const Data* data);

    /*!
     *  Function takes a DOM Document* node and creates a new-allocated
     *  ComplexData* populated by the DOM.  
     *
     *  
     */
    virtual Data* fromXML(const xml::lite::Document* doc);

protected:

    typedef xml::lite::Element* XMLElem;

    //! Returns the default URI
    virtual std::string getDefaultURI() const;

    //! Returns the URI to use with SI Common types
    virtual std::string getSICommonURI() const;

    virtual XMLElem toXML(const CollectionInformation *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const ImageCreation *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const ImageData *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const GeoData *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const GeoInfo *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const Grid *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const Timeline *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const Position *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const RadarCollection *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const ImageFormation *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const SCPCOA *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const Antenna *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(std::string name, AntennaParameters *ap, XMLElem parent =
            NULL);
    virtual XMLElem toXML(const MatchInformation *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const PFA *obj, XMLElem parent = NULL);
    virtual XMLElem toXML(const RMA *obj, XMLElem parent = NULL);

    virtual XMLElem areaLineDirectionParametersToXML(std::string name,
            const AreaDirectionParameters *obj,
            XMLElem parent = NULL);
    virtual XMLElem areaSampleDirectionParametersToXML(std::string name,
            const AreaDirectionParameters *obj,
            XMLElem parent = NULL);

    virtual void fromXML(const XMLElem collectionInfoXML, CollectionInformation *obj);
    virtual void fromXML(const XMLElem imageCreationXML, ImageCreation *obj);
    virtual void fromXML(const XMLElem imageDataXML, ImageData *obj);
    virtual void fromXML(const XMLElem geoDataXML, GeoData *obj);
    virtual void fromXML(const XMLElem geoInfoXML, GeoInfo *obj);
    virtual void fromXML(const XMLElem gridXML, Grid *obj);
    virtual void fromXML(const XMLElem timelineXML, Timeline *obj);
    virtual void fromXML(const XMLElem positionXML, Position *obj);
    virtual void fromXML(const XMLElem radarCollectionXML, RadarCollection *obj);
    virtual void fromXML(const XMLElem imageFormationXML, ImageFormation *obj);
    virtual void fromXML(const XMLElem scpcoaXML, SCPCOA *obj);
    virtual void fromXML(const XMLElem antennaXML, Antenna *obj);
    virtual void fromXML(const XMLElem antennaParamsXML, AntennaParameters* params);
    virtual void fromXML(const XMLElem matchInfoXML, MatchInformation *obj);
    virtual void fromXML(const XMLElem pfaXML, PFA *obj);
    virtual void fromXML(const XMLElem rmaXML, RMA *obj);

    virtual void parseEarthModelType(const XMLElem element, EarthModelType& value);
    virtual void parseSideOfTrackType(const XMLElem element, SideOfTrackType& value);

    virtual XMLElem createFFTSign(std::string name, six::FFTSign sign, XMLElem parent =
            NULL);
    virtual XMLElem createFootprint(std::string name, std::string cornerName,
                            const std::vector<LatLon>& corners,
                            XMLElem parent = NULL);
    virtual XMLElem createFootprint(std::string name, std::string cornerName,
                            const std::vector<LatLonAlt>& corners,
                            XMLElem parent = NULL);
    virtual XMLElem createEarthModelType(std::string name, const EarthModelType& value,
                                 XMLElem parent = NULL);
    virtual XMLElem createSideOfTrackType(std::string name,
                                  const SideOfTrackType& value, XMLElem parent =
                                          NULL);

    // Overridden methods from the base XMLControl, for adding attributes
    virtual XMLElem createString(std::string name, std::string uri, std::string p = "",
                         XMLElem parent = NULL);
    virtual XMLElem createInt(std::string name, std::string uri, int p = 0,
                      XMLElem parent = NULL);
    virtual XMLElem createDouble(std::string name, std::string uri, double p = 0,
                         XMLElem parent = NULL);
    virtual XMLElem createBooleanType(std::string name, std::string uri, BooleanType b,
                              XMLElem parent = NULL);
    virtual XMLElem createDateTime(std::string name, std::string uri, std::string s,
                           XMLElem parent = NULL);
    virtual XMLElem createDateTime(std::string name, std::string uri, DateTime p,
                           XMLElem parent = NULL);
    virtual XMLElem createDate(std::string name, std::string uri, DateTime p,
                       XMLElem parent = NULL);
    virtual XMLElem createString(std::string name, std::string p = "", XMLElem parent =
            NULL);
    virtual XMLElem createInt(std::string name, int p = 0, XMLElem parent = NULL);
    virtual XMLElem createDouble(std::string name, double p = 0, XMLElem parent = NULL);
    virtual XMLElem createBooleanType(std::string name, BooleanType b, XMLElem parent =
            NULL);
    virtual XMLElem createDateTime(std::string name, std::string s, XMLElem parent =
            NULL);
    virtual XMLElem createDateTime(std::string name, DateTime p, XMLElem parent = NULL);
    virtual XMLElem createDate(std::string name, DateTime p, XMLElem parent = NULL);

};

}
}
#endif
