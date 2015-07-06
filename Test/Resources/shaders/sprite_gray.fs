//
//  GameShaderFS
//  ys
//
//  Created by dalton on 13-5-28.
//
//

#ifdef GL_ES
precision lowp float;
#endif

// 转换矩阵
uniform mat4 u_colorMatrix;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
	vec4 tmp = texture2D(CC_Texture0, v_texCoord);
	float g = dot(tmp.rgb , vec3(0.299, 0.587, 0.114));
	gl_FragColor = vec4(g,g,g,tmp.a);
}