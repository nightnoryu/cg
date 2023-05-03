bool PointIsOnTheLeft(vec2 p0, vec2 p1, vec2 p)
{
    vec2 p0p1 = p1 - p0;
    vec2 n = vec2(-p0p1.y, p0p1.x);
    
    return dot(p - p0, n) > 0.0;
}

bool PointIsInsideStar(
    vec2 p0, vec2 p1, vec2 p2,
    vec2 p3, vec2 p4, vec2 p5,
    vec2 p6, vec2 p7, vec2 p8,
    vec2 p9, vec2 p)
{
    return
        (PointIsOnTheLeft(p0, p1, p) &&
         PointIsOnTheLeft(p1, p9, p) &&
         PointIsOnTheLeft(p9, p0, p)) ||
        (PointIsOnTheLeft(p1, p2, p) &&
         PointIsOnTheLeft(p2, p3, p) &&
         PointIsOnTheLeft(p3, p1, p)) ||
        (PointIsOnTheLeft(p3, p4, p) &&
         PointIsOnTheLeft(p4, p5, p) &&
         PointIsOnTheLeft(p5, p3, p)) ||
        (PointIsOnTheLeft(p5, p6, p) &&
         PointIsOnTheLeft(p6, p7, p) &&
         PointIsOnTheLeft(p7, p5, p)) ||
        (PointIsOnTheLeft(p7, p8, p) &&
         PointIsOnTheLeft(p8, p9, p) &&
         PointIsOnTheLeft(p9, p7, p)) ||
        (PointIsOnTheLeft(p1, p3, p) &&
         PointIsOnTheLeft(p3, p5, p) &&
         PointIsOnTheLeft(p5, p7, p) &&
         PointIsOnTheLeft(p7, p9, p) &&
         PointIsOnTheLeft(p9, p1, p));
}

void main()
{
    vec2 pos = gl_TexCoord[0].xy;

    const vec2 p0 = vec2(0.75, 0.3);
    const vec2 p1 = vec2(2.0, 1.2);
    const vec2 p2 = vec2(3.25, 0.3);
    const vec2 p3 = vec2(2.75, 1.75);
    const vec2 p4 = vec2(4.0, 2.65);
    const vec2 p5 = vec2(2.45, 2.65);
    const vec2 p6 = vec2(2.0, 4.0);
    const vec2 p7 = vec2(1.55, 2.65);
    const vec2 p8 = vec2(0.0, 2.65);
    const vec2 p9 = vec2(1.25, 1.75);

    if (PointIsInsideStar(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, pos))
    {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else
    {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}
