uniform float time;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    float t = clamp(time / 6., 0., 1.);

    vec2 coords = gl_TexCoord[0].st;
    vec2 dir = coords - vec2(.5);
    
    float dist = distance(coords, vec2(.5));
    vec2 offset = dir * (sin(dist * 40. - time * 15.) + .5) / 30.;
    // TODO: коэффициент diffuse должен зависеть от радиуса и смещаться с течением времени

    vec2 texCoord = coords + offset;
    vec4 diffuse = texture2D(tex1, texCoord);

    vec4 mixin = texture2D(tex2, texCoord);

    gl_FragColor = mixin * t + diffuse * (1. - t);
}
