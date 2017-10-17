#ifndef GLES3_PARTICLESYSTEM_PARTICLESYSTEMBASICSCENE_HPP
#define GLES3_PARTICLESYSTEM_PARTICLESYSTEMBASICSCENE_HPP
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

#include <FslBase/Math/Matrix.hpp>
#include <FslDemoApp/OpenGLES3/DemoAppGLES3.hpp>
#include <FslGraphics3D/BasicScene/Camera/ArcballCamera.hpp>
#include <FslUtil/OpenGLES3/GLProgram.hpp>
#include <FslUtil/OpenGLES3/GLTexture.hpp>
#include <FslUtil/OpenGLES3/GLVertexBuffer.hpp>
#include "AScene.hpp"
#include "PS/ParticleDrawContext.hpp"

namespace Fsl
{
  class BoxEmitter;
  class IGraphicsService;
  class IParticleSystem;
  class ParticleSystemGLES3;
  class ParticleSystemSnow;

  namespace UI
  {
    class CheckBox;
    class Label;
    class Slider;
    class SliderAndValueLabel;
    class ValueLabel;
    class WindowContext;
  }

  class ParticleSystemBasicScene
    : public AScene
  {
    enum class ParticleSystemType
    {
      Points,
      Instancing,
      GeometryShader
    };


    std::shared_ptr<IGraphicsService> m_graphics;
    bool m_allowAdvancedTechniques;

    Graphics3D::ArcballCamera m_camera;
    GLES3::GLProgram m_program;
    GLES3::GLVertexBuffer m_vbCube;
    GLES3::GLVertexAttribLink m_cubeAttribLink[3];
    GLES3::GLTexture m_texParticle;
    GLES3::GLTexture m_texParticleSnow;
    GLES3::GLTexture m_texCube;
    std::shared_ptr<BoxEmitter> m_boxEmitter;
    std::shared_ptr<IParticleSystem> m_particleSystem;
    std::shared_ptr<ParticleSystemGLES3> m_particleSystemGpu;
    std::shared_ptr<ParticleSystemSnow> m_particleSystemGpu2;

    GLint m_locWorldViewMatrix;
    GLint m_locProjMatrix;
    ParticleDrawContext m_particleDrawContext;
    Vector3 m_rotation;
    Vector3 m_rotationSpeed;
    bool m_rotate;

    ParticleSystemType m_particleSystemType;

  public:
    ParticleSystemBasicScene(const DemoAppConfig& config, const std::shared_ptr<UIDemoAppExtension>& uiExtension);
    ~ParticleSystemBasicScene();

    virtual void OnMouseButtonEvent(const MouseButtonEvent& event);
    virtual void OnMouseMoveEvent(const MouseMoveEvent& event);
    virtual void OnMouseWheelEvent(const MouseWheelEvent& event);
    virtual void Update(const DemoTime& demoTime);
    virtual void Draw();
  private:
    void DrawCube();
    void DrawParticles();
    void SetParticleSystem(const ParticleSystemType type, const bool force);
  };
}

#endif
