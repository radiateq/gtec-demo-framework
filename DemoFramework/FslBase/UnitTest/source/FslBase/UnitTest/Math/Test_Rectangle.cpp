/****************************************************************************************************************************************************
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    * Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *
 *    * Neither the name of the NXP. nor the names of
 *      its contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************************************************************************************/

#include <FslBase/Math/Rectangle.hpp>
#include <FslBase/Exceptions.hpp>
#include <FslBase/Log/Math/LogRectangle.hpp>
#include <FslBase/UnitTest/Helper/Common.hpp>
#include <FslBase/UnitTest/Helper/TestFixtureFslBase.hpp>
#include <array>
#include <limits>
#include <vector>

using namespace Fsl;

namespace
{
  using TestMath_Rectangle = TestFixtureFslBase;
}


TEST(TestMath_Rectangle, Empty)
{
  Rectangle value;

  EXPECT_EQ(Rectangle(), Rectangle::Empty());
  EXPECT_EQ(0, value.Left());
  EXPECT_EQ(0, value.Top());
  EXPECT_EQ(0, value.Right());
  EXPECT_EQ(0, value.Bottom());
  EXPECT_EQ(0, value.Width());
  EXPECT_EQ(0, value.Height());
  EXPECT_EQ(Point2(), value.TopLeft());
  EXPECT_EQ(Point2(), value.TopRight());
  EXPECT_EQ(Point2(), value.BottomLeft());
  EXPECT_EQ(Point2(), value.BottomRight());
}


TEST(TestMath_Rectangle, Construct1)
{
  int32_t offsetX = 1;
  int32_t offsetY = 2;
  int32_t width = 10;
  int32_t height = 20;
  Rectangle value(offsetX, offsetY, width, height);

  EXPECT_EQ(offsetX, value.Left());
  EXPECT_EQ(offsetY, value.Top());
  EXPECT_EQ(offsetX + width, value.Right());
  EXPECT_EQ(offsetY + height, value.Bottom());
  EXPECT_EQ(width, value.Width());
  EXPECT_EQ(height, value.Height());
  EXPECT_EQ(Point2(offsetX, offsetY), value.TopLeft());
  EXPECT_EQ(Point2(offsetX + width, offsetY), value.TopRight());
  EXPECT_EQ(Point2(offsetX, offsetY + height), value.BottomLeft());
  EXPECT_EQ(Point2(offsetX + width, offsetY + height), value.BottomRight());
}

TEST(TestMath_Rectangle, Construct2)
{
  int32_t left = 1;
  int32_t top = 2;
  int32_t right = 10;
  int32_t bottom = 20;
  Rectangle value(left, top, right, bottom, true);

  EXPECT_EQ(left, value.Left());
  EXPECT_EQ(top, value.Top());
  EXPECT_EQ(right, value.Right());
  EXPECT_EQ(bottom, value.Bottom());
  EXPECT_EQ(right - left, value.Width());
  EXPECT_EQ(bottom - top, value.Height());
  EXPECT_EQ(Point2(left, top), value.TopLeft());
  EXPECT_EQ(Point2(right, top), value.TopRight());
  EXPECT_EQ(Point2(left, bottom), value.BottomLeft());
  EXPECT_EQ(Point2(right, bottom), value.BottomRight());
}


TEST(TestMath_Rectangle, SetWidth)
{
  const int32_t offsetX = 1;
  const int32_t offsetY = 2;
  const int32_t height = 4;
  Rectangle value(offsetX, offsetY, 3, height);

  const int32_t newWidth = 10;
  value.SetWidth(newWidth);
  EXPECT_EQ(offsetX, value.Left());
  EXPECT_EQ(offsetY, value.Top());
  EXPECT_EQ(offsetX + newWidth, value.Right());
  EXPECT_EQ(offsetY + height, value.Bottom());
  EXPECT_EQ(newWidth, value.Width());
  EXPECT_EQ(height, value.Height());
}


TEST(TestMath_Rectangle, SetHeight)
{
  const int32_t offsetX = 1;
  const int32_t offsetY = 2;
  const int32_t width = 3;
  Rectangle value(offsetX, offsetY, width, 4);

  const int32_t newHeight = 10;
  value.SetHeight(newHeight);
  EXPECT_EQ(offsetX, value.Left());
  EXPECT_EQ(offsetY, value.Top());
  EXPECT_EQ(offsetX + width, value.Right());
  EXPECT_EQ(offsetY + newHeight, value.Bottom());
  EXPECT_EQ(width, value.Width());
  EXPECT_EQ(newHeight, value.Height());
}


TEST(TestMath_Rectangle, SetWidth_Invalid)
{
  Rectangle value(0, 0, 10, 10);

  value.SetWidth(-10);
  EXPECT_EQ(0, value.Left());
  EXPECT_EQ(0, value.Top());
  EXPECT_EQ(0, value.Right());
  EXPECT_EQ(10, value.Bottom());
  EXPECT_EQ(0, value.Width());
  EXPECT_EQ(10, value.Height());
}


TEST(TestMath_Rectangle, SetHeight_Invalid)
{
  Rectangle value(0, 0, 10, 10);

  value.SetHeight(-10);
  EXPECT_EQ(0, value.Left());
  EXPECT_EQ(0, value.Top());
  EXPECT_EQ(10, value.Right());
  EXPECT_EQ(0, value.Bottom());
  EXPECT_EQ(10, value.Width());
  EXPECT_EQ(0, value.Height());
}
