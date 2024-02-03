uniform sampler2D texture;
uniform int time;
void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if (pixel.a != 0.0) {
		 int a = time - (time / 255) * 255;
		 float normalizedA = float(a) / 255.0;
		 int parte = time / 255;
		 parte = parte - (parte / 3) * 3;
		 if (parte == 0) {
			pixel = vec4(1.0 - normalizedA, normalizedA, 0.0, 1.0);
		 }
		 else if (parte == 1) {
			pixel = vec4(0.0, 1.0 - normalizedA, normalizedA, 1.0);
		 }
		 else if (parte == 2) {
			pixel = vec4(normalizedA, 0.0, 1.0 - normalizedA, 1.0);
		 }
	}
	gl_FragColor = pixel;
};
                                                                           