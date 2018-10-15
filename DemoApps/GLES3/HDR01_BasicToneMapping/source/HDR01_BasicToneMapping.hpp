#ifndef GLES3_HDR01_BASICTONEMAPPING_HDR01_BASICTONEMAPPING_HPP
#define GLES3_HDR01_BASICTONEMAPPING_HDR01_BASICTONEMAPPING_HPP
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

#include <FslBase/Transition/TransitionCache.hpp>
#include <FslBase/Transition/TransitionValue.hpp>
#include <FslDemoApp/OpenGLES3/DemoAppGLES3.hpp>
#include <FslDemoApp/Base/Service/Keyboard/IKeyboard.hpp>
#include <FslDemoApp/Base/Service/Mouse/IMouse.hpp>
#include <FslGraphics3D/Camera/FirstPersonCamera.hpp>
#include <FslSimpleUI/App/UIDemoAppExtension.hpp>
#include <FslSimpleUI/Base/Control/CheckBox.hpp>
#include <FslSimpleUI/Base/Control/FloatSliderAndValueLabel.hpp>
#include <FslSimpleUI/Base/Control/Label.hpp>
#include <FslSimpleUI/Base/Layout/CanvasLayout.hpp>
#include <FslUtil/OpenGLES3/GLProgram.hpp>
#include <FslUtil/OpenGLES3/GLTexture.hpp>
#include <FslUtil/OpenGLES3/GLValues.hpp>
#include <FslUtil/OpenGLES3/GLVertexBuffer.hpp>
#include <FslUtil/OpenGLES3/GLVertexArray.hpp>
#include <Shared/OpenGLES3/HDR/BasicScene/BasicProgramLocations.hpp>
#include <Shared/OpenGLES3/HDR/BasicScene/MenuUI.hpp>
#include <Shared/OpenGLES3/HDR/BasicScene/OptionParser.hpp>
#include <Shared/OpenGLES3/HDR/BasicScene/SimpleMesh.hpp>
#include <vector>
#include <utility>

namespace Fsl
{
  class HDR01_BasicToneMapping
    : public DemoAppGLES3
    , public UI::EventListener
  {
    struct ProgramLocations : BasicProgramLocations
    {
      GLint Exposure;
      ProgramLocations()
        : Exposure(GLES3::GLValues::INVALID_LOCATION)
      {
      }
    };

    struct ProgramInfo
    {
      GLES3::GLProgram Program;
      ProgramLocations Location;
    };

    MenuUI m_menuUI;

    std::shared_ptr<IKeyboard> m_keyboard;
    std::shared_ptr<IMouse> m_mouse;
    std::shared_ptr<IDemoAppControl> m_demoAppControl;
    bool m_mouseCaptureEnabled;
    Graphics3D::FirstPersonCamera m_camera;
    Matrix m_matrixModel;
    Matrix m_matrixView;
    Matrix m_matrixProjection;

    GLES3::GLTexture m_texSRGB;

    ProgramInfo m_programHDR;
    ProgramInfo m_programLDR;

    SimpleMesh m_meshTunnel;

    std::vector<Vector3> m_lightPositions;
    std::vector<Vector3> m_lightColors;

  public:
    HDR01_BasicToneMapping(const DemoAppConfig& config);
    ~HDR01_BasicToneMapping() override;

  protected:
    void OnKeyEvent(const KeyEvent& event) override;
    void OnMouseButtonEvent(const MouseButtonEvent& event) override;
    void Update(const DemoTime& demoTime) override;
    void Draw(const DemoTime& demoTime) override;

  private:
    void UpdateInput(const DemoTime& demoTime);
    void UpdateCameraControlInput(const DemoTime& demoTime, const KeyboardState& keyboardState);

    void DrawScene(const ProgramInfo& programInfo);
    void PrepareLights();
    void CreateTextures(const std::shared_ptr<IContentManager>& contentManager);
    ProgramInfo CreateShader(const std::shared_ptr<IContentManager>& contentManager, const bool useHDR);
  };
}

#endif