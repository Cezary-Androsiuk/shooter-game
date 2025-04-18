uniform sampler2D texture;   // tekstura źródłowa
uniform vec2 direction;      // kierunek rozmycia: (1.0, 0.0) dla poziomego, (0.0, 1.0) dla pionowego
uniform float radius;        // promień rozmycia (np. 5.0)
uniform vec2 texSize;        // rozmiar tekstury (potrzebne do przeliczeń UV)

const float pi = 3.14159265359;

float gaussian(float x, float sigma) {
    return exp(-(x * x) / (2.0 * sigma * sigma)) / (sqrt(2.0 * pi) * sigma);
}

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 color = vec4(0.0);
    float sigma = radius / 2.0;
    float weightSum = 0.0;

    for (float i = -radius; i <= radius; i++) {
        float weight = gaussian(i, sigma);
        vec2 offset = direction * i / texSize;
        color += texture2D(texture, uv + offset) * weight;
        weightSum += weight;
    }

    gl_FragColor = color / weightSum;

}
