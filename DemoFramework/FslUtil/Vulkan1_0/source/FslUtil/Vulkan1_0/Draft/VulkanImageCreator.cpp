/****************************************************************************************************************************************************
* Copyright 2017 NXP
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

#include <FslUtil/Vulkan1_0/Draft/VulkanImageCreator.hpp>
#include <FslBase/Log/Log.hpp>
#include <FslGraphics/Texture/Texture.hpp>
#include <FslUtil/Vulkan1_0/Draft/VulkanImageCreatorUtil.hpp>
#include <FslUtil/Vulkan1_0/Util/ConvertUtil.hpp>
#include <cassert>
#include <limits>
#include <utility>

using namespace RapidVulkan;

namespace Fsl
{
  namespace Vulkan
  {

    namespace
    {
      ImageView CreateImageView(const VkDevice device, const VkImage image, const VkFormat imageFormat, const TextureType textureType, const TextureInfo& textureInfo)
      {
        VkImageSubresourceRange imageSubresourceRange{};
        imageSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageSubresourceRange.baseMipLevel = 0;
        imageSubresourceRange.levelCount = textureInfo.Levels;
        imageSubresourceRange.baseArrayLayer = 0;
        imageSubresourceRange.layerCount = textureInfo.Faces * textureInfo.Layers;

        VkImageViewCreateInfo imageViewCreateInfo{};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.flags = 0;
        imageViewCreateInfo.image = image;
        imageViewCreateInfo.viewType = ConvertUtil::ToImageViewType(textureType);
        imageViewCreateInfo.format = imageFormat;
        imageViewCreateInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };
        imageViewCreateInfo.subresourceRange = imageSubresourceRange;

        return ImageView(device, imageViewCreateInfo);
      }
    }



    VulkanImageCreator::VulkanImageCreator(const VUDevice& device, const VkQueue queue, const uint32_t queueFamilyIndex)
      : m_physicalDevice(device.GetPhysicalDevice())
      , m_commandPool(device.Get(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, queueFamilyIndex)
      , m_commandBuffer()
      , m_queue(queue)
    {
      // Create command buffer for submitting image barriers and converting tilings
      VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
      commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
      commandBufferAllocateInfo.commandPool = m_commandPool.Get();
      commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
      commandBufferAllocateInfo.commandBufferCount = 1;

      m_commandBuffer.Reset(device.Get(), commandBufferAllocateInfo);
    }


    VulkanImageCreator::~VulkanImageCreator()
    {
    }


    VUImage VulkanImageCreator::CreateImage(const Bitmap& src, const std::string& name, const VkImageUsageFlags imageUsageFlags)
    {
      const VkAccessFlags accessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;

      ImageEx image;
      Memory memory;
      VulkanImageCreatorUtil::Create(image, memory, m_physicalDevice, m_commandBuffer.GetDevice(), m_queue, m_commandBuffer.Get(), src, accessMask, imageUsageFlags);

      const TextureInfo info(1, 1, 1);
      auto imageView = CreateImageView(m_commandBuffer.GetDevice(), image.Get(), image.GetFormat(), TextureType::Tex2D, info);

      return VUImage(std::move(image), std::move(memory), std::move(imageView), name);
    }


    VUImage VulkanImageCreator::CreateImage(const Texture& src, const std::string& name, const VkImageUsageFlags imageUsageFlags)
    {
      const VkAccessFlags accessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;

      ImageEx image;
      Memory memory;
      VulkanImageCreatorUtil::Create(image, memory, m_physicalDevice, m_commandBuffer.GetDevice(), m_queue, m_commandBuffer.Get(), src, accessMask, imageUsageFlags);

      auto imageView = CreateImageView(m_commandBuffer.GetDevice(), image.Get(), image.GetFormat(), src.GetTextureType(), src.GetTextureInfo());

      return VUImage(std::move(image), std::move(memory), std::move(imageView), name);
    }


    VUTexture VulkanImageCreator::CreateTexture(const Bitmap& src, const VkSamplerCreateInfo& samplerCreateInfo, const std::string& name, const VkImageUsageFlags imageUsageFlags)
    {
      Sampler sampler(m_commandBuffer.GetDevice(), samplerCreateInfo);
      return CreateTexture(src, std::move(sampler), name, imageUsageFlags);
    }


    VUTexture VulkanImageCreator::CreateTexture(const Texture& src, const VkSamplerCreateInfo& samplerCreateInfo, const std::string& name, const VkImageUsageFlags imageUsageFlags)
    {
      Sampler sampler(m_commandBuffer.GetDevice(), samplerCreateInfo);
      return CreateTexture(src, std::move(sampler), name, imageUsageFlags);
    }


    VUTexture VulkanImageCreator::CreateTexture(const Bitmap& src, Sampler&& sampler, const std::string& name, const VkImageUsageFlags imageUsageFlags)
    {
      auto image = CreateImage(src, name, imageUsageFlags);
      return VUTexture(std::move(image), std::move(sampler));
    }


    VUTexture VulkanImageCreator::CreateTexture(const Texture& src, Sampler&& sampler, const std::string& name, const VkImageUsageFlags imageUsageFlags)
    {
      auto image = CreateImage(src, name, imageUsageFlags);
      return VUTexture(std::move(image), std::move(sampler));
    }
  }
}
