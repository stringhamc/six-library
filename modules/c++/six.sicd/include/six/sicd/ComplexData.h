/* =========================================================================
 * This file is part of six.sicd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2014, MDA Information Systems LLC
 *
 * six.sicd-c++ is free software; you can redistribute it and/or modify
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
#ifndef __SIX_COMPLEX_DATA_H__
#define __SIX_COMPLEX_DATA_H__

#include <mem/ScopedCloneablePtr.h>
#include <mem/ScopedCopyablePtr.h>

#include "six/Data.h"
#include "six/ErrorStatistics.h"
#include "six/Radiometric.h"
#include "six/sicd/CollectionInformation.h"
#include "six/sicd/ImageCreation.h"
#include "six/sicd/ImageData.h"
#include "six/sicd/GeoData.h"
#include "six/sicd/Grid.h"
#include "six/sicd/Timeline.h"
#include "six/sicd/Position.h"
#include "six/sicd/RadarCollection.h"
#include "six/sicd/ImageFormation.h"
#include "six/sicd/SCPCOA.h"
#include "six/sicd/Antenna.h"
#include "six/sicd/PFA.h"
#include "six/sicd/RMA.h"
#include "six/sicd/RgAzComp.h"
#include "six/sicd/MatchInformation.h"

namespace six
{
namespace sicd
{
/*!
 *  \class ComplexData
 *  \brief SICD data component
 *
 *  This class extends the Data object providing the SICD
 *  layer and utilities for access.  In order to write a SICD,
 *  you must have a ComplexData object that is populated with
 *  the mandatory parameters, and you must add it to the Container
 *  object first.
 *
 *  This object contains pointers to all of the sub-blocks for SICD.
 *  SIDD profiles may require that SICD collections are propagated through
 *  so for SIDD products, source SICDs should be added to the appropriate
 *  places in the SIDD Container object.
 *
 *  The best way to initialize a ComplexData object is using the
 *  ComplexDataBuilder, although it can be initialized directly.
 *
 *
 */
class ComplexData: public Data
{
public:
    //!  CollectionInfo block.  Contains the general collection information
    mem::ScopedCloneablePtr<CollectionInformation> collectionInformation;

    //!  (Optional) Block contains general information about the image creation
    mem::ScopedCloneablePtr<ImageCreation> imageCreation;

    //!  Block describes the image pixel data
    mem::ScopedCloneablePtr<ImageData> imageData;

    //!  Describes the geographic coords of the region covered by the image
    mem::ScopedCloneablePtr<GeoData> geoData;

    //!  Block of parameters describes the image sample grid
    mem::ScopedCloneablePtr<Grid> grid;

    //!  This block describes the imaging collection timeline
    mem::ScopedCopyablePtr<Timeline> timeline;

    //!  Describes the platform and the ground ref positions vs. time
    mem::ScopedCopyablePtr<Position> position;

    //!  This block describes the radar collection info
    mem::ScopedCloneablePtr<RadarCollection> radarCollection;

    //!  This block describes the image formation process
    mem::ScopedCopyablePtr<ImageFormation> imageFormation;

    //!  Describes Center of Aperture (COA) params for Scene Center Point (SCP)
    mem::ScopedCopyablePtr<SCPCOA> scpcoa;

    //!  (Optional) Radiometric calibration params
    mem::ScopedCopyablePtr<Radiometric> radiometric;

    //!  (Optional) Params describe the antenna during collection.
    mem::ScopedCopyablePtr<Antenna> antenna;

    //!  (Optional) Params needed for computing error statistics
    mem::ScopedCopyablePtr<ErrorStatistics> errorStatistics;

    //!  (Optional) Params describing other related imaging collections
    mem::ScopedCopyablePtr<MatchInformation> matchInformation;

    //!  (Optional/Choice) Polar Format Algorithm params -- if this is set,
    //          rma should remain NULL.
    mem::ScopedCopyablePtr<PFA> pfa;

    //!  (Optional/Choice) Range Migration Algorithm params -- if this is
    //          set, pfa should remain NULL.
    mem::ScopedCopyablePtr<RMA> rma;

    //!  (Optional/Choice) Simple Range Doppler Compression params -- 
    //   if this is set, pfa & rma should remain NULL.
    mem::ScopedCopyablePtr<RgAzComp> rgAzComp;

    ComplexData();

    ~ComplexData(){}

    /*!
     *  Returns COMPLEX.  This is used by Read/Write to determine
     *  whether we have a ComplexData (SICD) object or a DerivedData (SIDD)
     *  product in the Container.
     */
    DataType getDataType() const
    {
        return DataType::COMPLEX;
    }

    /*!
     *  Deep copy of this, including all initialized sub-params
     *
     */
    Data* clone() const;

    /*!
     *  Utility function for getting the pixel type.  
     *  This is stored in the SICD along with the width  
     *
     *  Maps to: /SICD/ImageData/PixelType,
     *  /SIDD/Display/PixelType
     */
    virtual PixelType getPixelType() const
    {
        return imageData->pixelType;
    }
    virtual void setPixelType(PixelType pixelType)
    {
        imageData->pixelType = pixelType;
    }

    /*!
     *  Maps to: /SICD/ImageData/NumRows,
     *  /SIDD/Measurement/PixelFootprint/Row
     */
    virtual size_t getNumRows() const
    {
        return imageData->numRows;
    }
    /*!
     *  This accessor not only sets rows, it also sets
     *  the full image rows, and the scene center rows
     *
     */
    virtual void setNumRows(size_t numRows)
    {
        imageData->numRows = numRows;
        imageData->fullImage.row = numRows;
        imageData->scpPixel.row = numRows / 2;
    }

    /*!
     *  Maps to: /SICD/ImageData/NumCols,
     *  /SIDD/Measurement/PixelFootprint/Col
     */
    virtual size_t getNumCols() const
    {
        return imageData->numCols;
    }
    /*!
     *  This accessor not only sets columns, it also sets
     *  the full image columns, and the scene center column
     *
     */
    virtual void setNumCols(size_t numCols)
    {
        imageData->numCols = numCols;
        imageData->fullImage.col = numCols;
        imageData->scpPixel.col = numCols / 2;
    }

    /*!
     *  Maps to: /SICD/GeoData/ImageCorners,
     *  /SIDD/GeographicAndTarget/GeographicCoverage/Footprint
     */
    virtual LatLonCorners getImageCorners() const
    {
        return geoData->imageCorners;
    }
    virtual void setImageCorners(const LatLonCorners& imageCorners)
    {
        geoData->imageCorners = imageCorners;
    }

    /*!
     *  Maps to: /SICD/CollectionInfo/CoreName,
     *  /SIDD/ProductCreation/ProductName
     */
    virtual std::string getName() const
    {
        return collectionInformation->coreName;
    }
    virtual void setName(std::string name)
    {
        collectionInformation->coreName = name;
    }

    /*!
     *  Maps to: /SICD/CollectionInfo/CollectorName,
     */
    virtual std::string getSource() const
    {
        return collectionInformation->collectorName;
    }

    /*!
     *  Maps to: /SICD/CollectionInfo/CollectorName,
     */
    virtual void setSource(std::string name)
    {
        collectionInformation->collectorName = name;
    }

    /*!
     *  Maps to: /SICD/ImageCreation/DateTime
     */
    virtual DateTime getCreationTime() const
    {
        if (!imageCreation.get())
            throw except::Exception(Ctxt("Must add an imageCreation member first"));
        return imageCreation->dateTime;
    }

    /*!
     *  Maps to: /SICD/ImageCreation/DateTime
     */
    virtual void setCreationTime(DateTime creationTime)
    {
        if (!imageCreation.get())
            imageCreation.reset(new ImageCreation());
        imageCreation->dateTime = creationTime;
    }

    /*!
     *  Maps to: /SICD/Timeline/CollectStart
     */
    virtual DateTime getCollectionStartDateTime() const;

    /*!
     *  Classification info is needed by the NITFReadControl/NITFWriteControl
     *  to populate the nitf::FileSecurity.  This method is defined
     *  differently for SICD than SIDD.  Any profile parameters for 
     *  FileSecurity that do not conform to Classification transfer must
     *  be initialized directly.
     *  Maps to SICD/CollectionInfo/Classification
     */
    virtual const Classification& getClassification() const
    {
        return collectionInformation->classification;
    }

    virtual Classification& getClassification()
    {
        return collectionInformation->classification;
    }

    // Okay, little bit of a hack for now
    virtual LUT* getDisplayLUT()
    {
        throw except::Exception(Ctxt("Display LUT operation not supported"));
    }

    virtual std::string getVendorID() const
    {
        return std::string(VENDOR_ID);
    }

    virtual std::string getVersion() const
    {
        return mVersion;
    }

    virtual void setVersion(const std::string& version)
    {
        mVersion = version;
    }

private:
    static const char VENDOR_ID[];

    std::string mVersion;
};

}
}
#endif

