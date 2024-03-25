#version 330 core
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to
//the screen for each pixel

out vec4 color;

uniform sampler2D mySampler;
uniform float TIME;

void main() {
	vec2 movedUV = fragmentUV + vec2(TIME, TIME);
	vec4 textureColor = texture(mySampler, movedUV);

	if (textureColor == vec4(1.0, 1.0, 1.0, 1.0)){

	}
	else{

	}

	//color = textureColor * fragmentColor;

	color = fragmentColor * textureColor;
}