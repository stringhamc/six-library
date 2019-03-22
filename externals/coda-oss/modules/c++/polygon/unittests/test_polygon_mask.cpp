/* =========================================================================
 * This file is part of polygon-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2019, MDA Information Systems LLC
 *
 * polygon-c++ is free software; you can redistribute it and/or modify
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
#include <limits>
#include <sstream>

#include "TestCase.h"

#include <mem/ScopedArray.h>

#include <polygon/DrawPolygon.h>
#include <polygon/PolygonMask.h>

namespace
{
TEST_CASE(testMarkAllTrue)
{
    const polygon::PolygonMask mask(polygon::PolygonMask::MARK_ALL_TRUE,
                                    types::RowCol<size_t>(100, 200));

    types::Range range = mask.getRange(50);
    TEST_ASSERT_EQ(range.mStartElement, 0);
    TEST_ASSERT_EQ(range.mNumElements, 200);
    TEST_ASSERT(mask.isInPolygon(50, 0));
    TEST_ASSERT(mask.isInPolygon(50, 199));
    TEST_ASSERT(!mask.isInPolygon(50, 200));

    range = mask.getRange(100);
    TEST_ASSERT_EQ(range.mStartElement, std::numeric_limits<size_t>::max());
    TEST_ASSERT_EQ(range.mNumElements, 0);
    TEST_ASSERT(!mask.isInPolygon(100, 0));
    TEST_ASSERT(!mask.isInPolygon(100, 199));
    TEST_ASSERT(!mask.isInPolygon(100, 200));
}

TEST_CASE(testMarkAllFalse)
{
    const polygon::PolygonMask mask(polygon::PolygonMask::MARK_ALL_FALSE,
                                    types::RowCol<size_t>(100, 200));

    types::Range range = mask.getRange(50);
    TEST_ASSERT_EQ(range.mStartElement, std::numeric_limits<size_t>::max());
    TEST_ASSERT_EQ(range.mNumElements, 0);
    TEST_ASSERT(!mask.isInPolygon(50, 0));
    TEST_ASSERT(!mask.isInPolygon(50, 199));
    TEST_ASSERT(!mask.isInPolygon(50, 200));

    range = mask.getRange(100);
    TEST_ASSERT_EQ(range.mStartElement, std::numeric_limits<size_t>::max());
    TEST_ASSERT_EQ(range.mNumElements, 0);
    TEST_ASSERT(!mask.isInPolygon(100, 0));
    TEST_ASSERT(!mask.isInPolygon(100, 199));
    TEST_ASSERT(!mask.isInPolygon(100, 200));
}

TEST_CASE(testWithPoints)
{
    std::vector<types::RowCol<double> > points;
    points.push_back(types::RowCol<double>(400, 100));
    points.push_back(types::RowCol<double>(100, 310));
    points.push_back(types::RowCol<double>(270, 590));
    points.push_back(types::RowCol<double>(445, 576));
    points.push_back(types::RowCol<double>(600, 350));
    const types::RowCol<sys::SSize_T> offset(50, 75);

    // Draw a mask
    const types::RowCol<size_t> dims(1000, 800);
    const mem::ScopedArray<bool> maskArray(new bool[dims.area()]);
    std::fill_n(maskArray.get(), dims.area(), false);
    polygon::drawPolygon(
            points, dims.row, dims.col, true, maskArray.get(), false, offset);

    // Infer a mask
    const polygon::PolygonMask mask(points, dims, offset);

    // Each point should match between the two masks
    for (size_t row = 0, idx = 0; row < dims.row; ++row)
    {
        std::ostringstream ostr;
        ostr << "row = " << row;

        for (size_t col = 0; col < dims.col; ++col, ++idx)
        {
            ostr << ", col = " << col;

            TEST_ASSERT_EQ_MSG(ostr.str(),
                               maskArray[idx], mask.isInPolygon(row, col));
        }
    }
}

TEST_CASE(testWithMask)
{
    std::vector<types::RowCol<double> > points;
    points.push_back(types::RowCol<double>(400, 100));
    points.push_back(types::RowCol<double>(100, 310));
    points.push_back(types::RowCol<double>(270, 590));
    points.push_back(types::RowCol<double>(445, 576));
    points.push_back(types::RowCol<double>(600, 350));
    const types::RowCol<sys::SSize_T> offset(50, 75);

    // Draw a mask
    const types::RowCol<size_t> dims(1000, 800);
    const mem::ScopedArray<bool> maskArray(new bool[dims.area()]);
    std::fill_n(maskArray.get(), dims.area(), false);
    polygon::drawPolygon(
            points, dims.row, dims.col, true, maskArray.get(), false, offset);

    // Infer a mask
    const polygon::PolygonMask mask(maskArray.get(), dims);

    // Each point should match between the two masks
    for (size_t row = 0, idx = 0; row < dims.row; ++row)
    {
        std::ostringstream ostr;
        ostr << "row = " << row;

        for (size_t col = 0; col < dims.col; ++col, ++idx)
        {
            ostr << ", col = " << col;

            TEST_ASSERT_EQ_MSG(ostr.str(),
                               maskArray[idx], mask.isInPolygon(row, col));
        }
    }
}

TEST_CASE(testWithAllFullRanges)
{
    std::vector<types::RowCol<double> > points;
    points.push_back(types::RowCol<double>(-100, -100));
    points.push_back(types::RowCol<double>(-100, 1100));
    points.push_back(types::RowCol<double>(1100, 1100));
    points.push_back(types::RowCol<double>(1100, -100));

    // Draw a mask
    const types::RowCol<size_t> dims(1000, 800);
    const polygon::PolygonMask mask(points, dims);

    TEST_ASSERT_EQ(mask.getMarkMode(), polygon::PolygonMask::MARK_ALL_TRUE);
}

TEST_CASE(testWithAllEmptyRanges)
{
    std::vector<types::RowCol<double> > points;
    points.push_back(types::RowCol<double>(2100, -100));
    points.push_back(types::RowCol<double>(2100, 1100));
    points.push_back(types::RowCol<double>(3100, 1100));
    points.push_back(types::RowCol<double>(3100, -100));

    // Draw a mask
    const types::RowCol<size_t> dims(1000, 800);
    const polygon::PolygonMask mask(points, dims);

    TEST_ASSERT_EQ(mask.getMarkMode(), polygon::PolygonMask::MARK_ALL_FALSE);
}
}

int main(int /*argc*/, char** /*argv*/)
{
    TEST_CHECK(testMarkAllTrue);
    TEST_CHECK(testMarkAllFalse);
    TEST_CHECK(testWithPoints);
    TEST_CHECK(testWithMask);
    TEST_CHECK(testWithAllFullRanges);
    TEST_CHECK(testWithAllEmptyRanges);
    return 0;
}
