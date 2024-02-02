#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <windows.h>

#include "player.h";
#include "window.h"; 

int main() {
	srand(time(NULL));

	Player player;
	
	std::chrono::high_resolution_clock::time_point last_frame = std::chrono::high_resolution_clock::now();

	while (win.isOpen()) {
		sf::Event ev;
		while (win.pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::Resized:
			{
				sf::FloatRect* view = new sf::FloatRect(0, 0, ev.size.width, ev.size.height);
				win.setSize({ ev.size.width, ev.size.height });
				win.setView(sf::View(*view));
			}
				break;
			default:

				break;
			}
		}
		win.clear(sf::Color::White);

		player.update();
		player.draw();

		win.display();

        std::chrono::high_resolution_clock::time_point current_frame = std::chrono::high_resolution_clock::now();
		double time_took = std::chrono::duration_cast<std::chrono::milliseconds>(current_frame - last_frame).count();
		if (time_took < milliseconds_frame) {
			while (time_took < milliseconds_frame) {
				Sleep(3);
				current_frame = std::chrono::high_resolution_clock::now();
				time_took = std::chrono::duration_cast<std::chrono::milliseconds>(current_frame - last_frame).count();
			}
			delta_time = 1.0f;
		}else{
			delta_time = time_took / milliseconds_frame;
		}
		last_frame = current_frame;
	}

	return 0;
}