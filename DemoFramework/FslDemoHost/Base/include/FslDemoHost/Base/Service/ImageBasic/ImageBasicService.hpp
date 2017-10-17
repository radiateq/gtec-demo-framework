#ifndef FSLDEMOHOST_BASE_SERVICE_IMAGEBASIC_IMAGEBASICSERVICE_HPP
#define FSLDEMOHOST_BASE_SERVICE_IMAGEBASIC_IMAGEBASICSERVICE_HPP
/****************************************************************************************************************************************************
* Copyright (c) 2016 Freescale Semiconductor, Inc.
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

#include <FslDemoApp/Base/Service/ImageBasic/IImageBasicService.hpp>
#include <FslService/Consumer/ServiceProvider.hpp>
#include <FslService/Impl/ServiceType/Local/ThreadLocalService.hpp>
#include <FslGraphics/ImageFormat.hpp>
#include <deque>
#include <memory>
#include <map>

namespace Fsl
{
  class IBitmapConverter;
  class IImageLibraryService;

  class ImageBasicService
    : public ThreadLocalService
    , public IImageBasicService
  {
    std::shared_ptr<IBitmapConverter> m_bitmapConverter;
    std::deque<std::shared_ptr<IImageLibraryService> > m_imageLibraryServices;
    std::map<ImageFormat, std::shared_ptr<IImageLibraryService> > m_formatToImageLibrary;
  public:
    ImageBasicService(const ServiceProvider& serviceProvider);
    ~ImageBasicService();

    // From ImageBasicService
    virtual void Read(Bitmap& rBitmap, const IO::Path& absolutePath, const PixelFormat desiredPixelFormat = PixelFormat::Undefined, const BitmapOrigin desiredOrigin = BitmapOrigin::Undefined, const PixelChannelOrder preferredChannelOrder = PixelChannelOrder::Undefined) const override;
    virtual void Read(Texture& rTexture, const IO::Path& absolutePath, const PixelFormat desiredPixelFormat = PixelFormat::Undefined, const BitmapOrigin desiredOrigin = BitmapOrigin::Undefined, const PixelChannelOrder preferredChannelOrder = PixelChannelOrder::Undefined) const override;
    virtual void Write(const IO::Path& absolutePath, const Bitmap& bitmap, const ImageFormat imageFormat = ImageFormat::Undefined, const PixelFormat desiredPixelFormat = PixelFormat::Undefined) override;
    virtual void WriteExactImage(const IO::Path& absolutePath, const Bitmap& bitmap, const ImageFormat imageFormat, const PixelFormat desiredPixelFormat = PixelFormat::Undefined) override;
    virtual bool TryRead(Bitmap& rBitmap, const IO::Path& absolutePath, const PixelFormat desiredPixelFormat = PixelFormat::Undefined, const BitmapOrigin desiredOrigin = BitmapOrigin::Undefined, const PixelChannelOrder preferredChannelOrder = PixelChannelOrder::Undefined) const override;
    virtual bool TryWrite(const IO::Path& absolutePath, const Bitmap& bitmap, const ImageFormat imageFormat = ImageFormat::Undefined, const PixelFormat desiredPixelFormat = PixelFormat::Undefined) override;
    virtual bool TryWriteExactImage(const IO::Path& absolutePath, const Bitmap& bitmap, const ImageFormat imageFormat, const PixelFormat desiredPixelFormat = PixelFormat::Undefined) override;
  private:
    void DoWrite(const IO::Path& absPath, const Bitmap& bitmap, const ImageFormat imageFormat);
    void DoWriteExactImage(const IO::Path& absPath, const Bitmap& bitmap, const ImageFormat imageFormat);
  };
}

#endif
