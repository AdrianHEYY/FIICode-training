#include "util.h"

namespace util {
	bool collision(const sf::Vector2f& pos_1, const sf::Vector2f& size_1, const sf::Vector2f& pos_2, const sf::Vector2f& size_2) {
		sf::Vector2f st_sus = pos_1;
		sf::Vector2f st_jos = pos_1 + sf::Vector2f(0.0f, size_1.y);
		sf::Vector2f dr_sus = pos_1 + sf::Vector2f(size_1.x, 0.0f);
		sf::Vector2f dr_jos = pos_1 + size_1;

		if (st_sus.x >= pos_2.x && st_sus.x <= pos_2.x + size_2.x &&
			st_sus.y >= pos_2.y && st_sus.y <= pos_2.y + size_2.y) {
			return 1;
		}
		if (st_jos.x >= pos_2.x && st_jos.x <= pos_2.x + size_2.x &&
			st_jos.y >= pos_2.y && st_jos.y <= pos_2.y + size_2.y) {
			return 1;
		}
		if (dr_sus.x >= pos_2.x && dr_sus.x <= pos_2.x + size_2.x &&
			dr_sus.y >= pos_2.y && dr_sus.y <= pos_2.y + size_2.y) {
			return 1;
		}
		if (dr_jos.x >= pos_2.x && dr_jos.x <= pos_2.x + size_2.x &&
			dr_jos.y >= pos_2.y && dr_jos.y <= pos_2.y + size_2.y) {
			return 1;
		}

		return 0;
	}
}