uniform vec2 iResolution;
uniform sampler2D iChannel0;
uniform vec2 direction;

vec4 blur(sampler2D image, vec2 coord, vec2 resolution, vec2 direction) {
	vec2 uv = vec2(coord / resolution);
	vec2 move = vec2(direction / resolution);
	vec4 color = texture2D(image, uv) * 0.4;
	color += texture2D(image, uv + move) * 0.2;
	color += texture2D(image, uv - move) * 0.2;
	color += texture2D(image, uv + 2 * move) * 0.1;
	color += texture2D(image, uv - 2 * move) * 0.1;
	return color; 
}

void main()
{
	gl_FragColor = blur(iChannel0, gl_FragCoord.xy, iResolution, direction);
}