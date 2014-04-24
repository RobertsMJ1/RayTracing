#version 150

in vec4 vs_position;

void main() { 
	//gl_Position is built-in
    gl_Position = vs_position;
}