#include "player_animation.h"

Player_Animation::Player_Animation(sf::RectangleShape& sprite) {
	up.loadFromFile("samples/8_way_up.png");
	down.loadFromFile("samples/8_way_down.png");
	left.loadFromFile("samples/8_way_left.png");
	right.loadFromFile("samples/8_way_right.png");
	up_left.loadFromFile("samples/8_way_up_left.png");
	up_right.loadFromFile("samples/8_way_up_right.png");
	down_left.loadFromFile("samples/8_way_down_left.png");
	down_right.loadFromFile("samples/8_way_down_right.png");

	no_frames = up.getSize().x / up.getSize().y;
	current_frame = 0;
	time_since_start = std::chrono::high_resolution_clock::now();

	height = up.getSize().y;
	width = up.getSize().x;
	unit_width = height;
}


void Player_Animation::update(sf::Vector2f velocity, sf::RectangleShape& sprite) {
	std::string new_direction = "--";
	if (velocity.x < 0) new_direction[0] = 'L';
	else if (velocity.x > 0) new_direction[0] = 'R';
	if (velocity.y < 0) new_direction[1] = 'U';
	else if (velocity.y > 0) new_direction[1] = 'D';

	if (new_direction == "--") {
		if (current_texture == nullptr) {
			current_texture = &down;
			sprite.setTexture(current_texture);
		}
		sprite.setTextureRect(sf::IntRect(0, 0, unit_width, height));
		last_direction = new_direction;
		return;
	}

	if (new_direction != last_direction) {
		last_direction = new_direction;
		time_since_start = std::chrono::high_resolution_clock::now();
		current_frame = 0;

		if (new_direction == "L-") {
			if (current_texture != &left) {
				current_texture = &left;
				sprite.setTexture(current_texture);
			}
		}
		else if (new_direction == "R-") {
			if (current_texture != &right) {
				current_texture = &right;
				sprite.setTexture(current_texture);
			}
		}
		else if (new_direction == "-U") {
			if (current_texture != &up) {
				current_texture = &up;
				sprite.setTexture(current_texture);
			}
		}
		else if (new_direction == "-D") {
			if (current_texture != &down) {
				current_texture = &down;
				sprite.setTexture(current_texture);
			}
		}
		else if (new_direction == "LD") {
			if (current_texture != &down_left) {
				current_texture = &down_left;
				sprite.setTexture(current_texture);
			}
		}
		else if (new_direction == "RD") {
			if (current_texture != &down_right) {
				current_texture = &down_right;
				sprite.setTexture(current_texture);
			}
		}
		else if (new_direction == "LU") {
			if (current_texture != &up_left) {
				current_texture = &up_left;
				sprite.setTexture(current_texture);
			}
		}
		else if (new_direction == "RU") {
			if (current_texture != &up_right) {
				current_texture = &up_right;
				sprite.setTexture(current_texture);
			}
		}
	}
	else { // acceasi directie
		long long timp_trecut = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - time_since_start).count();
		int new_current_frame = (timp_trecut / milliseconds_frame) % no_frames;
		//std::cout << "new frame: " << new_current_frame << '\n';
		if (new_current_frame != current_frame) {
			current_frame = new_current_frame;
			sprite.setTextureRect(sf::IntRect(new_current_frame * unit_width, 0, unit_width, height));
			//std::cout << "new rect: " << new_current_frame * unit_width << ' ' << 0 << ' ' << unit_width << ' ' << height << '\n';
		}
	}
}