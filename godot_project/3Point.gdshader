// 3 point texture filtering.
// Original author: ArthurCarvalho
// GLSL implementation: twinaphex, mupen64plus-libretro project.
// Ported to Godot by Ed3800

shader_type spatial;
render_mode vertex_lighting, specular_disabled, ambient_light_disabled, shadows_disabled;

uniform sampler2D tex;
uniform vec2 texSize;

void fragment() {
	vec2 offset = fract(UV*texSize - vec2(0.5));
	offset -= step(1.0, offset.x + offset.y);
	vec4 c0 = texture(tex, UV - (offset)/texSize);
	vec2 c1off = vec2(offset.x - sign(offset.x), offset.y);
	vec4 c1 = texture(tex, UV - (c1off)/texSize);
	vec2 c2off = vec2(offset.x, offset.y - sign(offset.y));
	vec4 c2 = texture(tex, UV - (c2off)/texSize);

	ALBEDO = vec4(c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0)).rgb;
}
