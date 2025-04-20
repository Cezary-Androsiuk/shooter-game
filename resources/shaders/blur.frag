#version 120

uniform sampler2D texture;
uniform vec2 iResolution;

void main()
{
    float Pi = 6.28318530718; // Pi*2
    
    // GAUSSIAN BLUR SETTINGS
    float Directions = 16.0; // BLUR DIRECTIONS
    float Quality = 5.0; // BLUR QUALITY
    float Size = 16.0; // BLUR SIZE (Radius)
   
    vec2 Radius = Size/iResolution;
    
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_TexCoord[0].xy;
    // Pixel colour
    vec4 Color = texture2D(texture, uv);
    
    // Blur calculations
    for( float d=0.0; d<Pi; d+=Pi/Directions)
    {
        for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
            Color += texture2D(texture, uv+vec2(cos(d),sin(d))*Radius*i);		
        }
    }
    
    // Output to screen
    Color /= Quality * Directions - 15.0;
    gl_FragColor = Color * gl_Color;
}