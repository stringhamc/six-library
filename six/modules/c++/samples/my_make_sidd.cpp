/* =========================================================================
* This file is part of six-c++
* =========================================================================
*
* (C) Copyright 2004 - 2017, MDA Information Systems LLC
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
#include <iostream>

#include <import/six.h>
#include <import/six/sidd.h>
#include <import/six/sicd.h>
#include <import/sio/lite.h>
#include <import/io.h>
#include <import/cli.h>
#include <import/xml/lite.h>
#include "utils.h"

namespace
{
std::auto_ptr<six::sidd::DerivedData> buildDerivedData(
        const sio::lite::FileHeader& fileHeader,
        six::PixelType pixelType)
{
    six::sidd::DerivedDataBuilder builder;
    std::auto_ptr<six::sidd::DerivedData> data(builder.steal());

    builder.addDisplay(pixelType);
    builder.addGeographicAndTarget(six::RegionType::GEOGRAPHIC_INFO);
    builder.addMeasurement(six::ProjectionType::PLANE);
    builder.addExploitationFeatures(1);

    data->setNumRows(fileHeader.getNumLines());
    data->setNumCols(fileHeader.getNumElements());

    data->productCreation->productName = "ProductName";
    data->productCreation->productClass = "Classy";
    data->productCreation->classification.classification = "U";

    six::sidd::ProcessorInformation& processorInformation =
        *data->productCreation->processorInformation;

    processorInformation.application = "ProcessorName";
    processorInformation.profile = "Profile";
    processorInformation.site = "Ypsilanti, MI";

    data->display->pixelType = pixelType;
    data->display->decimationMethod = six::DecimationMethod::BRIGHTEST_PIXEL;
    data->display->magnificationMethod = six::MagnificationMethod::NEAREST_NEIGHBOR;

    data->setImageCorners(makeUpCornersFromDMS());

    six::sidd::PlaneProjection* planeProjection =
        (six::sidd::PlaneProjection*) data->measurement->projection.get();

    planeProjection->timeCOAPoly = six::Poly2D(0, 0);
    planeProjection->timeCOAPoly[0][0] = 1;
    data->measurement->arpPoly = six::PolyXYZ(0);
    data->measurement->arpPoly[0] = 0.0;
    planeProjection->productPlane.rowUnitVector = 0.0;
    planeProjection->productPlane.colUnitVector = 0.0;

    six::sidd::Collection* parent =
        data->exploitationFeatures->collections[0].get();

    parent->information->resolution.rg = 0;
    parent->information->resolution.az = 0;
    parent->information->collectionDuration = 0;
    parent->information->collectionDateTime = six::DateTime();
    parent->information->radarMode = six::RadarModeType::SPOTLIGHT;
    parent->information->sensorName = "the sensor";
    data->exploitationFeatures->product.resolution.row = 0;
    data->exploitationFeatures->product.resolution.col = 0;

    data->annotations.push_back(mem::ScopedCopyablePtr<
        six::sidd::Annotation>(new six::sidd::Annotation));
    six::sidd::Annotation *ann = (*data->annotations.rbegin()).get();
    ann->identifier = "1st Annotation";
    ann->objects.push_back(mem::ScopedCloneablePtr<
        six::sidd::SFAGeometry>(new six::sidd::SFAPoint));
    return data;
}
}

/*!
*  We want to create a SIDD NITF from something
*  else.  For this simple example, I will use
*  sio.lite to read in the image data.
*
*  SICD data is read in from the first argument.  To test multi-image
*  SIDD, the <N times> argument uses the target <input-file> over and
*  over as different images in the NITF.
*
*  The segmentation loophole can be exploitated by overriding the product
*  size (essentially bluffing the 10GB limit, and overriding ILOC_R=99999,
*  although you may not extend those limits -- they are NITF format maxes.
*/
int main(int argc, char** argv)
{
    try
    {
        cli::ArgumentParser parser;
        parser.setDescription("Create a SIDD from some SICD XML and SIOs containing"
            " image array.");
        parser.addArgument("--sicdXml", "SICD XML pathname", cli::STORE,
            "sicdXml", "sicdXml", 1, 1);
        parser.addArgument("--sio", "input sio file", cli::STORE,
            "sio", "sio", 1, 3, true);
        parser.addArgument("--lut", "look up table to use");
        parser.addArgument("--output", "pathname of output SIDD", cli::STORE,
            "output", "output", 1, 1, true);
        const std::auto_ptr<cli::Results> options(parser.parse(argc, argv));

        const std::string xmlPathname(options->get<std::string>("sicdXml"));

        const cli::Value& sios = *options->getValue("sio");
        std::vector<std::string> sioPathnames(sios.size());
        for (size_t ii = 0; ii < sioPathnames.size(); ++ii)
        {
            sioPathnames[ii] = sios.get<std::string>(ii);
        }

        const std::string outputPathname(options->get<std::string>("output"));
        const std::string lutPathname = options->hasValue("lut") ?
            options->get<std::string>("lut") : "";

        // Ensure Schema path
        try
        {
            sys::OS().getEnv(six::SCHEMA_PATH);
        }
        catch (const except::Exception&)
        {
            throw except::Exception(Ctxt(
                "Must specify SIDD schema path via " +
                std::string(six::SCHEMA_PATH) + " environment variable"));
        }

        six::NITFWriteControl writer;
        std::auto_ptr<six::sicd::ComplexData> complexData =
                six::sicd::Utilities::getComplexData(
                        xmlPathname, std::vector<std::string>());

        mem::SharedPtr<six::Container> container(new six::Container(
            six::DataType::DERIVED));

        // We have a source for each image
        std::vector<io::InputStream*> sources;

        sio::lite::FileReader sioReader(
                new io::FileInputStream(sioPathnames[0]));
        const sio::lite::FileHeader* fileHeader = sioReader.readHeader();
        const bool needsByteSwap = sys::isBigEndianSystem()
                && fileHeader->isDifferentByteOrdering();
        container->addData(buildDerivedData(*fileHeader,
                six::PixelType::MONO8LU));
        container->addData(complexData.get());
        writer.getOptions().setParameter(six::WriteControl::OPT_BYTE_SWAP,
            six::Parameter(static_cast<sys::Uint16_T>(needsByteSwap)));
        writer.initialize(container);
        writer.save(sources, outputPathname);
    }

    catch (const except::Exception& ex)
    {
        std::cerr << ex.toString() << std::endl;
        return 1;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "An unknown error occured\n";
        return 1;
    }

    return 0;
}
