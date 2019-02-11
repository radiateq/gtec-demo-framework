#version 310 es
/****************************************************************************************************************************************************
 *This is free and unencumbered software released into the public domain.
 *
 *Anyone is free to copy, modify, publish, use, compile, sell, or
 *distribute this software, either in source code form or as a compiled
 *binary, for any purpose, commercial or non-commercial, and by any
 *means.
 *
 *In jurisdictions that recognize copyright laws, the author or authors
 *of this software dedicate any and all copyright interest in the
 *software to the public domain. We make this dedication for the benefit
 *of the public at large and to the detriment of our heirs and
 *successors. We intend this dedication to be an overt act of
 *relinquishment in perpetuity of all present and future rights to this
 *software under copyright law.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *OTHER DEALINGS IN THE SOFTWARE.
 *
 *For more information, please refer to <http://unlicense.org>
 ****************************************************************************************************************************************************/

// ShaderCode based on the OpenGL Tutorial https://learnopengl.com/Advanced-Lighting/HDR

#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif

layout(location = 0) in vec3 v_FragPosition;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TexCoord;

layout(std140, binding = 1) uniform UBO
{
  vec3 LightPositions[4];
  vec3 LightColors[4];
  // Tonemapping
  uniform float Exposure;
}
g_ubo;


layout(binding = 2) uniform sampler2D g_diffuseTexture;

layout(location = 0) out vec4 FragColor;

void main()
{
  vec3 color = texture(g_diffuseTexture, v_TexCoord).rgb;
  vec3 normal = normalize(v_Normal);
  // ambient
  vec3 ambient = 0.0 * color;
  // lighting
  vec3 lighting = vec3(0.0);
  for (int i = 0; i < 4; i++)
  {
    // diffuse
    vec3 lightDir = normalize(g_ubo.LightPositions[i] - v_FragPosition);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = g_ubo.LightColors[i] * diff * color;
    vec3 result = diffuse;
    // attenuation (use quadratic as we have gamma correction)
    float distance = length(v_FragPosition - g_ubo.LightPositions[i]);
    result *= 1.0 / (distance * distance);
    lighting += result;
  }

  // Embedded tone mapping (HDR)
  {
    const float gamma = 2.2;
    vec3 hdrColor = ambient + lighting;
    // reinhard
    // vec3 result = hdrColor / (hdrColor + vec3(1.0));
    // g_ubo.Exposure
    vec3 result = vec3(1.0) - exp(-hdrColor * g_ubo.Exposure);
    // also gamma correct while we're at it
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
  }
}