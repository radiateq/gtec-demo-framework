#ifndef FSLBASE_MATH_MATRIX3_HPP
#define FSLBASE_MATH_MATRIX3_HPP
/****************************************************************************************************************************************************
* Copyright (c) 2015 Freescale Semiconductor, Inc.
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
*    * Neither the name of the Freescale Semiconductor, Inc. nor the names of
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


#include <algorithm>
#include <FslBase/OptimizationFlag.hpp>
#include <FslBase/Math/Vector3.hpp>

namespace Fsl
{
  struct Matrix;

  // Designed for 3D graphics.
  // Format:
  //   m11, m12, m13,
  //   m21, m22, m23,
  //   m31, m32, m33,
  struct Matrix3
  {
  private:
    //const int _M11 = (3 * 0 + 0);
    //const int _M12 = (3 * 0 + 1);
    //const int _M13 = (3 * 0 + 2);
    //const int _M21 = (3 * 1 + 0);
    //const int _M22 = (3 * 1 + 1);
    //const int _M23 = (3 * 1 + 2);
    //const int _M31 = (3 * 2 + 0);
    //const int _M32 = (3 * 2 + 1);
    //const int _M33 = (3 * 2 + 2);
    float m[3 * 3];
  public:
    //! @brief Creates a empty matrix (all components are set to zero)
    Matrix3();
    Matrix3(const float m11, const float m12, const float m13,
            const float m21, const float m22, const float m23,
            const float m31, const float m32, const float m33);

    //! @brief A optimization constructor that doesn't initialize the matrix so when this is called the content of the matrix in undefined!!!
    // coverity[uninit_member]
    Matrix3(const OptimizationFlag flag) {};

    //! @brief Direct access to the matrix array
    const float* DirectAccess() const { return m; }

    //! @brief Direct access to the matrix array
    float* DirectAccess() { return m; }

    //! @brief Return a instance of the identity matrix
    static Matrix3 GetIdentity()
    {
      return Matrix3(1.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 1.0f);
    }

    //! @brief Fill the matrix with zero
    void Clear();

    //! @brief Set the matrix to the identity matrix
    void SetIdentity();

    float Determinant() const;

    static Matrix3 Transpose(const Matrix3& matrix);
    static Matrix3 Invert(const Matrix3& matrix);

    bool operator==(const Matrix3 &rhs) const;
    bool operator!=(const Matrix3 &rhs) const;
  };
}

#endif
