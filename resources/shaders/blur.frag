uniform sampler2D texture;
uniform vec2 textureSize;
uniform float blurRadius;

void main()
{
    vec2 texCoord = gl_TexCoord[0].xy;
    vec4 sum = vec4(0.0);
    
    // Gaussian blur weights
    float weights[5];
    weights[0] = 0.2270270270;
    weights[1] = 0.1945945946;
    weights[2] = 0.1216216216;
    weights[3] = 0.0540540541;
    weights[4] = 0.0162162162;
    
    // Horizontal blur
    for (int i = -4; i <= 4; i++)
    {
        float weight = weights[abs(i)];
        sum += texture2D(texture, texCoord + vec2(i * blurRadius / textureSize.x, 0.0)) * weight;
    }
    
    // Vertical blur
    for (int i = -4; i <= 4; i++)
    {
        float weight = weights[abs(i)];
        sum += texture2D(texture, texCoord + vec2(0.0, i * blurRadius / textureSize.y)) * weight;
    }
    
    // Average the horizontal and vertical results
    gl_FragColor = sum * 0.5;
}