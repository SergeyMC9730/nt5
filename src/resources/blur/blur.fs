#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

const float blurSize = 1.0/1000.0;

uniform float bokeh = 0.2;
uniform float samples = 50;
vec2 direction;

// uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

uniform float offset[5] = float[](0.0, 1.0, 2.0, 3.0, 4.0);
uniform float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216,
                                  0.0540540541, 0.0162162162);

void main() {
    // finalColor = texture2D(texture0, vec2(fragTexCoord) / 1024) * weight[0];

    // for (int i = 1; i < 2; i++) {
    //     finalColor += texture2D(texture0, (vec2(fragTexCoord) + vec2(0.0, offset[i])) / 1024.0) * weight[i];
    //     finalColor += texture2D(texture0, (vec2(fragTexCoord) - vec2(0.0, offset[i])) / 1024.0) * weight[i];
    //     finalColor += texture2D(texture0, (vec2(fragTexCoord) - vec2(0.0, offset[i])) / 1024.0) * weight[i];
    //     finalColor += texture2D(texture0, (vec2(fragTexCoord) - vec2(0.0, offset[i])) / 1024.0) * weight[i];
    // }
    vec4 texColor = vec4(0.0); // texture2D(u_texture, vTexCoord)
    texColor += texture2D(texture0, fragTexCoord - 4.0*blurSize) * 0.05;
    texColor += texture2D(texture0, fragTexCoord - 3.0*blurSize) * 0.09;
    texColor += texture2D(texture0, fragTexCoord - 2.0*blurSize) * 0.12;
    texColor += texture2D(texture0, fragTexCoord - blurSize) * 0.15;
    texColor += texture2D(texture0, fragTexCoord) * 0.1;
    texColor += texture2D(texture0, fragTexCoord + blurSize) * 0.15;
    texColor += texture2D(texture0, fragTexCoord + 2.0*blurSize) * 0.12;
    texColor += texture2D(texture0, fragTexCoord + 3.0*blurSize) * 0.09;
    texColor += texture2D(texture0, fragTexCoord + 4.0*blurSize) * 0.05;

    finalColor = vec4(texColor.rgb, texColor.a);;

    // direction.x = 0.866/1.333;
    // direction.y = 0.5;

    // vec4 sum = vec4(0.0);
    // vec4 msum = vec4(0.0);

    // float delta = 1.0/samples;
    // float di = 1.0/(samples-1.0);
    // for (float i=-0.5; i<0.501; i+=di) {
    //     vec4 color = texture2D(texture0, fragTexCoord + direction * i);
    //     sum += color * delta;
    //     msum = max(color, msum);
    // }

    // finalColor = mix(sum, msum, bokeh);
}