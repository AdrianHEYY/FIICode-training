#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "window.h"; 
#include "game.h"

#include <Windows.h>

#include "random.h"

enum room_types {
	// -1-2-3-
	// 4-5-6-7
	// -8-9-A-
	// B-C-D-E
	// -F-G-H-
	// I-J-K-L
	// -M-N-O-
	// A = 10, B = 11, C = 12 ... O = 24 (nerd emoji sa nu stricam cum arata)

	fight_1_small,
	// -1-
	// 4-5
	// -8-
	fight_1_medium,
	// -1-2-
	// 4---6
	// -8-9-
	fight_1_large,
	// -1-2-3-
	// 4-----7
	// B-----E
	// I-----L
	// -M-N-O-
	fight_1_reverse_L_shape,
	//-1-2-3
	//4-----7
	//-8-9---
	//   -D-E
	//   --H-
	starter,
	// -1-
	// 4-5
	// -8-
	finisher
	// -1-
	// 4-5
	// -8-
};

struct room {
	room(int max_doors, int possible_door_placements) {
		this->max_doors = max_doors;
		this->possible_door_placements = possible_door_placements;
	}
	int max_doors;
	int possible_door_placements;
};
const std::map<room_types, room> room_configurations = { 
	// bitul 1 (1 << 0) este in dreapta de tot
	// bitul 2 (1 << 1) este in dreapta de tot - 1
	// bitul 32 (1 << 31) este primul dupa 0b
	//                                     ONMLKJIHGFEDCBA987654321
	{fight_1_small, room({4, int(0b00000000000000000000000000000000)})},
};

class Room {
public:
	Room() {

	}
	inline int getRoomID() { return id; };
	inline room_types getRoomType() { return room_type; };
	inline sf::Vector2f getRoomDimensions() { return sf::Vector2f(float(width), float(height)); };
	inline int getDoors() { return doors; };
private:
	room_types room_type;

	int width;
	int height;
	
	int doors; 
	int id;
};

class Map {
public:
	Map(unsigned int seed = rand())
	: generator(seed){
	  
	}
private:
	Procedural generator;

	int layout[20][20] = { {} };
	std::map<int, std::unique_ptr<Room>> id_room;
};

int main() {
	srand(time(NULL));

	std::chrono::high_resolution_clock::time_point last_frame = std::chrono::high_resolution_clock::now();

	Game game;

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

		game.run_one();

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
		}
		else {
			delta_time = time_took / milliseconds_frame;
		}
		last_frame = current_frame;
	}

	return 0;
}