/* =========================================================================
* This file is part of six.sicd-c++
* =========================================================================
*
* (C) Copyright 2004 - 2016, MDA Information Systems LLC
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

#include <fstream>
#include <import/six/sicd.h>
#include <io/TempFile.h>
#include <sys/File.h>

namespace
{
    void writeTestFile(const std::string& testFile, const std::string& sicd,
        const std::string& log, const six::Vector3& scp,
        const six::RowColInt& scpPixel, double altitude)
    {
        std::ofstream testStream(testFile.c_str());
        testStream << log << "\n" <<
            "vtsRead21ISDFile " << sicd << "\n" <<
            "makeModelListFromISD SICD_SENSOR_MODEL SIX\n" <<
            "constructModelFromISD SICD_SENSOR_MODEL\n" <<
            "groundToImage1 " <<
                    scp[0] << " " << scp[1] << " " << scp[2] << "\n" <<
            "imageToGround1 " << scpPixel.row << " " << scpPixel.col <<
                    " " << altitude << "\n" <<
            "Exit\n";
    }

    void runTest(const std::string& testFile,
            const std::string& outputPathname)
    {
        sys::OS os;
        const std::string currentFile = os.getCurrentExecutable();
        const std::string currentDirectory =
            sys::Path::splitPath(currentFile).first;
        std::string vts = sys::Path::joinPaths(currentDirectory, "vts");
        if (os.isFile(vts + ".exe"))
        {
            vts = vts + ".exe";
        }

        // The test does write to a log, but the output there is chaotic
        sys::Exec command(vts + " < " + testFile + " > " + outputPathname);
        command.run();
    }

    void parseLog(const std::string& outputPathname, six::Vector3& convertedScp,
            six::RowColInt& convertedScpPixel)
    {
        std::ifstream log(outputPathname);
        std::string line;
        while (std::getline(log, line))
        {
            str::trim(line);
            if (str::startsWith(line, "Output Results:"))
            {
                std::getline(log, line);  //Results on next line

                // This looks something like:
                // [Row] 0.0000 Pass [Col] 0.00000 Pass [Other stuff]
                const std::vector<std::string> values = str::split(line);
                if (values.size() == 9) // I think the final triple is precision?
                {                       // Anyway, we don't need it
                    convertedScpPixel.row = six::toType<int>(values[0]);
                    convertedScpPixel.col = six::toType<int>(values[3]);
                }
                // We are assuming things work correctly, and what I asked for is
                // exactly what's there
                else
                {
                    convertedScp[0] = six::toType<double>(values[0]);
                    convertedScp[1] = six::toType<double>(values[3]);
                    convertedScp[2] = six::toType<double>(values[6]);
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    try
    {
        if (argc < 2)
        {
            throw except::Exception(Ctxt(
                    "Usage: " + std::string(argv[0]) + " <SICD>"));
        }
        const std::string sicdPathname(argv[1]);
        const io::TempFile log;
        const io::TempFile testFile;
        const io::TempFile output;
        const std::vector<std::string> schemaPaths;
        const std::auto_ptr<six::sicd::ComplexData> data = 
                six::sicd::Utilities::getComplexData(
                        sicdPathname, schemaPaths);

        const six::Vector3 scp = data->geoData->scp.ecf;
        const six::RowColInt scpPixel = data->imageData->scpPixel;
        const double altitude = data->geoData->scp.llh.getAlt();

        writeTestFile(testFile.pathname(), sicdPathname, log.pathname(),
                scp, scpPixel, altitude);
        runTest(testFile.pathname(), output.pathname());

        six::Vector3 convertedScp;
        six::RowColInt convertedScpPixel;
        parseLog(output.pathname(), convertedScp, convertedScpPixel);

        bool valuesMatch = true;
        if (std::abs(scp[0] - convertedScp[0]) > .01 ||
            std::abs(scp[1] - convertedScp[1]) > .01  ||
            std::abs(scp[2] - convertedScp[2]) > .01)
        {
            std::cerr << std::setprecision(8) <<
                    "Scp does not match." << std::endl;
            std::cerr << "Actual SCP: [" 
                    << scp[0] << ", " << scp[1] << ", " << scp[2] << "]\n";
            std::cerr << "Calculated SCP: ["
                << convertedScp[0] << ", " << convertedScp[1] << ", " <<
                convertedScp[2] << "]\n";
            valuesMatch = false;
        }

        if (scpPixel != convertedScpPixel)
        {
            std::cerr << "ScpPixel does not match." << std::endl;
            std::cerr << "Actual scpPixel: ["
                << scpPixel.row << ", " << scpPixel.col << "]\n";
            std::cerr << "Calculated scpPixel: ["
                << convertedScpPixel.row << ", " <<
                convertedScpPixel.col << "]\n";
            valuesMatch = false;
        }

        if (valuesMatch)
        {
            return 0;
        }

        return 1;

    }
    catch (const except::Exception& e)
    {
        std::cerr << e.getMessage() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
}
