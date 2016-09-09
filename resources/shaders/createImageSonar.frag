#version 130

in vec3 out_vertex;
out vec4 out_colors;

void main(){

    //out_colors = vec4(out_vertex.xy, 0, 1.0);
    out_colors = vec4(1,0,0,1);
}
