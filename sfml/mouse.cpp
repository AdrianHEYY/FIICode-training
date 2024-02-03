#include "mouse.h"

#include <SFML/Graphics.hpp>

namespace util {
	bool mouse_is_clicked = 0;
	bool mouse_just_clicked = 0;
	bool mouseJustClicked() {
		return mouse_just_clicked;
	}
	bool mouseIsPressed() {
		return mouse_is_clicked;
	}
	void updateMouse() {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (mouse_is_clicked == 1) {
				mouse_just_clicked = 0;
			}
			else {
				mouse_is_clicked = 1;
				mouse_just_clicked = 1;
			}
		}
		else {
			mouse_is_clicked = 0;
			mouse_just_clicked = 0;
		}
	}
}