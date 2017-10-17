/****************************************************************************************************************************************************
* Copyright (c) 2014 Freescale Semiconductor, Inc.
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

#include <FslBase/Exceptions.hpp>
#include <FslDemoPlatform/Setup/DemoHostAppSetupBuilder.hpp>
#include <FslDemoApp/Base/Host/DemoAppHostConfigEGL.hpp>
#include <FslDemoApp/Base/Host/DemoAppHostConfigVulkan.hpp>
#include <FslDemoApp/Base/Host/DemoAppHostConfigWindow.hpp>


namespace Fsl
{
  DemoHostAppSetupBuilder::DemoHostAppSetupBuilder()
    : m_records()
  {
  }


  void DemoHostAppSetupBuilder::Register(const DemoAppSetup& demoAppSetup, const DemoHostFeature& demoHostFeature)
  {
    // Force limit for now
    if (m_records.size() != 0)
      throw UsageErrorException("One and only one demo app can be registered!");

    const std::shared_ptr<DemoAppHostConfig> appHostConfig;
    const auto demoHostFeatureDeque = std::make_shared<DemoHostAppSetup::DemoHostFeatureDeque>();
    demoHostFeatureDeque->push_back(demoHostFeature);
    m_records.push_back(DemoHostAppSetup(demoAppSetup, demoHostFeatureDeque, appHostConfig));
  }


  void DemoHostAppSetupBuilder::Register(const DemoAppSetup& demoAppSetup, const std::deque<DemoHostFeature>& demoHostFeatures)
  {
    // Force limit for now
    if (m_records.size() != 0)
      throw UsageErrorException("One and only one demo app can be registered!");

    const std::shared_ptr<DemoAppHostConfig> appHostConfig;
    const auto demoHostFeatureDeque = std::make_shared<DemoHostAppSetup::DemoHostFeatureDeque>(demoHostFeatures);
    m_records.push_back(DemoHostAppSetup(demoAppSetup, demoHostFeatureDeque, appHostConfig));
  }


  void DemoHostAppSetupBuilder::Register(const DemoAppSetup& demoAppSetup, const DemoHostFeature& demoHostFeature, const DemoAppHostConfigEGL& demoHostConfig)
  {
    // Force limit for now
    if (m_records.size() != 0)
      throw UsageErrorException("One and only one demo app can be registered!");

    const auto appHostConfig = std::make_shared<DemoAppHostConfigEGL>(demoHostConfig);
    const auto demoHostFeatureDeque = std::make_shared<DemoHostAppSetup::DemoHostFeatureDeque>();
    demoHostFeatureDeque->push_back(demoHostFeature);
    m_records.push_back(DemoHostAppSetup(demoAppSetup, demoHostFeatureDeque, appHostConfig));
  }

  void DemoHostAppSetupBuilder::Register(const DemoAppSetup& demoAppSetup, const std::deque<DemoHostFeature>& demoHostFeatures, const DemoAppHostConfigEGL& demoHostConfig)
  {
    // Force limit for now
    if (m_records.size() != 0)
      throw UsageErrorException("One and only one demo app can be registered!");

    const auto appHostConfig = std::make_shared<DemoAppHostConfigEGL>(demoHostConfig);
    const auto demoHostFeatureDeque = std::make_shared<DemoHostAppSetup::DemoHostFeatureDeque>(demoHostFeatures);
    m_records.push_back(DemoHostAppSetup(demoAppSetup, demoHostFeatureDeque, appHostConfig));
  }


  void DemoHostAppSetupBuilder::Register(const DemoAppSetup& demoAppSetup, const DemoHostFeature& demoHostFeature, const DemoAppHostConfigVulkan& demoHostConfig)
  {
    // Force limit for now
    if (m_records.size() != 0)
      throw UsageErrorException("One and only one demo app can be registered!");

    const auto appHostConfig = std::make_shared<DemoAppHostConfigVulkan>(demoHostConfig);
    const auto demoHostFeatureDeque = std::make_shared<DemoHostAppSetup::DemoHostFeatureDeque>();
    demoHostFeatureDeque->push_back(demoHostFeature);
    m_records.push_back(DemoHostAppSetup(demoAppSetup, demoHostFeatureDeque, appHostConfig));
  }


  void DemoHostAppSetupBuilder::Register(const DemoAppSetup& demoAppSetup, const std::deque<DemoHostFeature>& demoHostFeatures, const DemoAppHostConfigVulkan& demoHostConfig)
  {
    // Force limit for now
    if (m_records.size() != 0)
      throw UsageErrorException("One and only one demo app can be registered!");

    const auto appHostConfig = std::make_shared<DemoAppHostConfigVulkan>(demoHostConfig);
    const auto demoHostFeatureDeque = std::make_shared<DemoHostAppSetup::DemoHostFeatureDeque>(demoHostFeatures);
    m_records.push_back(DemoHostAppSetup(demoAppSetup, demoHostFeatureDeque, appHostConfig));
  }


  void DemoHostAppSetupBuilder::Register(const DemoAppSetup& demoAppSetup, const DemoHostFeature& demoHostFeature, const DemoAppHostConfigWindow& demoHostConfig)
  {
    // Force limit for now
    if (m_records.size() != 0)
      throw UsageErrorException("One and only one demo app can be registered!");

    const auto appHostConfig = std::make_shared<DemoAppHostConfigWindow>(demoHostConfig);
    const auto demoHostFeatureDeque = std::make_shared<DemoHostAppSetup::DemoHostFeatureDeque>();
    demoHostFeatureDeque->push_back(demoHostFeature);
    m_records.push_back(DemoHostAppSetup(demoAppSetup, demoHostFeatureDeque, appHostConfig));
  }


  void DemoHostAppSetupBuilder::Register(const DemoAppSetup& demoAppSetup, const std::deque<DemoHostFeature>& demoHostFeatures, const DemoAppHostConfigWindow& demoHostConfig)
  {
    // Force limit for now
    if (m_records.size() != 0)
      throw UsageErrorException("One and only one demo app can be registered!");

    const auto appHostConfig = std::make_shared<DemoAppHostConfigWindow>(demoHostConfig);
    const auto demoHostFeatureDeque = std::make_shared<DemoHostAppSetup::DemoHostFeatureDeque>(demoHostFeatures);
    m_records.push_back(DemoHostAppSetup(demoAppSetup, demoHostFeatureDeque, appHostConfig));
  }

  DemoHostAppSetup DemoHostAppSetupBuilder::GetSetup() const
  {
    // Force limit for now
    if (m_records.size() != 1)
      throw UsageErrorException("One and only one demo app can be registered!");
    return m_records.front();
  }
}
