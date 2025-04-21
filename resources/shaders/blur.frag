#version 120

uniform sampler2D texture;
uniform vec2 size;
uniform float blurDirections;
uniform float blurQuality;
uniform float blurSize;

void main()
{
    float Pi = 6.28318530718; // Pi*2
   
    vec2 Radius = blurSize/size;
    
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_TexCoord[0].xy;
    // Pixel color
    vec4 Color = texture2D(texture, uv);
    
    // Blur calculations
    for( float d=0.0; d<Pi; d+=Pi/blurDirections)
    {
        for(float i=1.0/blurQuality; i<=1.0; i+=1.0/blurQuality)
        {
            Color += texture2D(texture, uv+vec2(cos(d),sin(d))*Radius*i);		
        }
    }
    
    // Output to screen
    float divisor = max(blurQuality * blurDirections - 15.0, 1.0);
    Color /= divisor;
    gl_FragColor = Color * gl_Color;
}