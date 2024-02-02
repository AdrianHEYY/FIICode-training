#include "dvd_logo.h"
#include "window.h"
#include <random>
#include <math.h>

Dvd_Logo::Dvd_Logo() 
	:timer(util::Timer(true))
{
	texture.loadFromFile("samples/dvd_logo.png");
	sprite.setTexture(&texture);
	sprite.setPosition({ 0.0f, 0.0f });
	sprite.setSize({ 200.0f, 100.0f });

	velocity = sf::Vector2f(3.2f,1.4f);

	std::string vertex =
		"" \
		"	void main()" \
		"	{" \
		"		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; " \
		"		gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;" \
		"		gl_FrontColor = gl_Color; " \
		"	}";
	std::string fragment =
		"	uniform sampler2D texture;" \
		"	uniform int time;" \
		"	void main()" \
		"	{" \
		"		vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
		"		if (pixel.a != 0.0) {" \
		"			 int a = time - (time / 255) * 255;" \
		"			 float normalizedA = float(a) / 255.0;" \
		"			 int parte = time / 255;" \
		"			 parte = parte - (parte / 3) * 3;" \
		"			 if (parte == 0) {" \
		"				pixel = vec4(1.0 - normalizedA, normalizedA, 0.0, 1.0);" \
		"			 }" \
		"			 else if (parte == 1) {" \
		"				pixel = vec4(0.0, 1.0 - normalizedA, normalizedA, 1.0);" \
		"			 }" \
		"			 else if (parte == 2) {" \
		"				pixel = vec4(normalizedA, 0.0, 1.0 - normalizedA, 1.0);" \
		"			 }" \
		"		}" \
		"		gl_FragColor = pixel;" \
		"	};";
	shader = new sf::Shader();
	shader->loadFromMemory(vertex, fragment);
	shader->setUniform("texture", texture);
}

void Dvd_Logo::draw() {
	win.draw(sprite, shader);
}

void Dvd_Logo::update() {
	shader->setUniform("time", int(timer.getElapsed()/10));

	sf::Vector2f position = sprite.getPosition();
	sf::Vector2f size = sprite.getSize();

	if ((velocity.x < 0 &&position.x - velocity.x < 0) || (velocity.x > 0 && position.x + size.x + velocity.x > win.getSize().x)) {
		velocity.x = -velocity.x;
	}
	if ((velocity.y<0&&position.y - velocity.y < 0)|| (velocity.y>0&&position.y + size.y + velocity.y > win.getSize().y)) {
		velocity.y = -velocity.y;
	}

	sprite.setPosition(sprite.getPosition() + velocity * projectile_speed);
}