#version 300 es

#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif

in vec2 v_TexCoord;

// Tonemapping
uniform float g_exposure;

uniform sampler2D g_hdrTexture;

out vec4 FragColor;

void main()
{
  vec3 hdrColor = texture(g_hdrTexture, v_TexCoord).rgb;

  // Exposure
  hdrColor *= g_exposure;

  // Linear framebuffer so we dont need gamma correction.
  // hdrColor = pow(hdrColor, vec3(1.0 / 2.2));

  FragColor = vec4(hdrColor, 1.0);
}
