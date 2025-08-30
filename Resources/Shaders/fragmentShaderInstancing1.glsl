#version 430

out vec4 color;

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float tf;   //time factor for animation and placement

in vec4 varyingColor;

void main(void)
{
  color = varyingColor;
}