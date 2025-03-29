#version 430 core

layout (location = 0) out vec4 color;

// uniform vec4 light_pos;

in vec4 pos;
in vec2 texCoord;
in vec4 colour;
in float tex_index;
in vec4 centerPos;
in float radius;

uniform sampler2D textures[32];

void main() {
    // float intensity = 30 / length(pos.xy - light_pos.xy);
    color = vec4(1.0, 1.0, 1.0, 1.0);

    switch (int(tex_index)) {
        case -1:
            if (radius > 0.0) {
                float value = length(centerPos.xy - gl_FragCoord.xy);
                if (value <= radius) {
                    color *= colour;
                } else color.a = 0.0;
            } else color *= colour;
            break;
        case 0: color *= texture(textures[0], texCoord) * colour; break;
        case 1: color *= texture(textures[1], texCoord) * colour; break;
        case 2: color *= texture(textures[2], texCoord) * colour; break;
        case 3: color *= texture(textures[3], texCoord) * colour; break;
        case 4: color *= texture(textures[4], texCoord) * colour; break;
        case 5: color *= texture(textures[5], texCoord) * colour; break;
        case 6: color *= texture(textures[6], texCoord) * colour; break;
        case 7: color *= texture(textures[7], texCoord) * colour; break;
        case 8: color *= texture(textures[8], texCoord) * colour; break;
        case 9: color *= texture(textures[9], texCoord) * colour; break;
        case 10: color *= texture(textures[10], texCoord) * colour; break;
        case 11: color *= texture(textures[11], texCoord) * colour; break;
        case 12: color *= texture(textures[12], texCoord) * colour; break;
        case 13: color *= texture(textures[13], texCoord) * colour; break;
        case 14: color *= texture(textures[14], texCoord) * colour; break;
        case 15: color *= texture(textures[15], texCoord) * colour; break;
        case 16: color *= texture(textures[16], texCoord) * colour; break;
        case 17: color *= texture(textures[17], texCoord) * colour; break;
        case 18: color *= texture(textures[18], texCoord) * colour; break;
        case 19: color *= texture(textures[19], texCoord) * colour; break;
        case 20: color *= texture(textures[20], texCoord) * colour; break;
        case 21: color *= texture(textures[21], texCoord) * colour; break;
        case 22: color *= texture(textures[22], texCoord) * colour; break;
        case 23: color *= texture(textures[23], texCoord) * colour; break;
        case 24: color *= texture(textures[24], texCoord) * colour; break;
        case 25: color *= texture(textures[25], texCoord) * colour; break;
        case 26: color *= texture(textures[26], texCoord) * colour; break;
        case 27: color *= texture(textures[27], texCoord) * colour; break;
        case 28: color *= texture(textures[28], texCoord) * colour; break;
        case 29: color *= texture(textures[29], texCoord) * colour; break;
        case 30: color *= texture(textures[30], texCoord) * colour; break;
        case 31: color *= texture(textures[31], texCoord) * colour; break;
    }

    // To make the texture transparent
    if (color.a < 0.1) discard;
}