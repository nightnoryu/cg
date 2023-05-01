float CalculateRadius(float x)
{
    return (1.0 + sin(x)) *
           (1.0 + 0.9 * cos(8.0*x)) *
           (1.0 + 0.1 * cos(24.0 * x)) *
           (0.5 + 0.05 * cos(140.0 * x));
}

void main()
{
    vec4 position = gl_Vertex;
    float x = position.x;
    float R = CalculateRadius(x);

    position.x = R * cos(x);
    position.y = R * sin(x);

    gl_Position = gl_ModelViewProjectionMatrix * position;
}
