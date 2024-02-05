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

	//! -1-2-3-
	//! 4+5+6+7
	//! -8-9-A-
	//! B+C+D+E
	//! -F-G-H-
	//! I+J+K+L
	//! -M-N-O-
	//! A = 10, B = 11, C = 12 ... O = 24 (nerd emoji sa nu stricam cum arata)

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
const std::map<room_types, int> room_configurations = { 
	// bitul 1 (1 << 0) este in dreapta de tot
	// bitul 2 (1 << 1) este in dreapta de tot - 1
	// bitul 32 (1 << 31) este primul dupa 0b
	// !                                          O   LK   G    C  9  7 5 3 1 // nu le completa ca se fut space-uile
	{fight_1_small,            int(0b00000000000000000000000010011010)},
	{fight_1_medium,           int(0b00000000000000000000000110101011)},
	{fight_1_large,            int(0b00000000111100100010010001001111)},
	{fight_1_reverse_L_shape,  int(0b00000000000000010011000111001111)},
	{starter,                  int(0b00000000000000000000000010011001)},
	{finisher,                 int(0b00000000000000000000000010011001)}
};
const std::map<room_types, sf::Vector2i> room_sizes = {
	{fight_1_small,            sf::Vector2i(1, 1)},
	{fight_1_medium,           sf::Vector2i(2, 2)},
	{fight_1_large,            sf::Vector2i(3, 3)},
	{fight_1_reverse_L_shape,  sf::Vector2i(3, 2)},
	{starter,                  sf::Vector2i(1, 1)},
	{finisher,                 sf::Vector2i(1, 1)}
};
std::vector<sf::Vector2i> getDisplacements(room_types room_type, sf::Vector2i position, char direction) {
	switch (direction) {
	case 'N':
	{
		switch (room_type) {
		case fight_1_small:
		{
			return { {0, 0} };
			break;
		}
		case fight_1_medium:
		{
			return { {-1, -1}, {-1, 0} };
			break;
		}
		case fight_1_large:
		{
			return { {-2, -2}, {-2, -1}, {-2, 0} };
			break;
		}
		case fight_1_reverse_L_shape:
		{
			return { {-1, -2}, {0, -1}, {0, 0} };
			break;
		}
		}
		break;
	}
	case 'W':
	{
		switch (room_type) {
		case fight_1_small:
		{
			return { {0, 0} };
			break;
		}
		case fight_1_medium:
		{
			return { {-1, -1}, {0, -1} };
			break;
		}
		case fight_1_large:
		{
			return { {-2, -2}, {-1, -2}, {0, -2} };
			break;
		}
		case fight_1_reverse_L_shape:
		{
			return { {-1, -2}, {0, -2} };
			break;
		}
		}
		break;
	}
	case 'S':
	{
		switch (room_type) {
		case fight_1_small:
		{
			return { {0, 0} };
			break;
		}
		case fight_1_medium:
		{
			return { {0, 0}, {0, -1} };
			break;
		}
		case fight_1_large:
		{
			return { {0, 0}, {0, -1}, {0, -2} };
			break;
		}
		case fight_1_reverse_L_shape:
		{
			return { {0, 0}, {0, -1}, {0, -2} };
			break;
		}
		}
		break;
	}
	case 'E':
	{
		switch (room_type) {
		case fight_1_small:
		{
			return { {0, 0} };
			break;
		}
		case fight_1_medium:
		{
			return { {0, 0}, {-1, 0} };
			break;
		}
		case fight_1_large:
		{
			return { {0, 0}, {-1, 0}, {-2, 0} };
			break;
		}
		case fight_1_reverse_L_shape:
		{
			return { {0, 0}, {-1, -2} };
			break;
		}
		}
		break;
	}
	};
	return {};
}

class Room {
public:
	Room(room_types room_type, int id) :id(id),room_type(room_type) {
		width = room_sizes.find(room_type)->second.x;
		height = room_sizes.find(room_type)->second.y;
		doors = room_configurations.find(room_type)->second;
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
		: generator(seed) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				layout[i][j] = 0;
			}
		}
		int camera_start_x = generator.getRandomNumber() % 20, camera_start_y = generator.getRandomNumber() % 20;
		//camera_start_x = 19;
		//camera_start_y = 19;

		layout[camera_start_x][camera_start_y] = 1;
		id_room[1] = std::make_unique<Room>(starter, 1);

		//std::cout << "Camera start: " << camera_start_x << ' ' << camera_start_y << '\n';

		generateFurther(camera_start_x, camera_start_y, 'N');
	}
	void out_test() {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				std::cout << layout[i][j] << ' ';
			} std::cout << '\n';
		} std::cout << '\n';
	}
private:
	bool nu_iese(int x, int y) {
		if (x >= 0 && x < 20 && y >= 0 && y < 20) return 1;
		return 0;
	}
	bool incape(room_types room_type, sf::Vector2i st_sus) {
		bool debug = 0;
		if (debug == 1) {
			std::cout << "Incape ";
			switch (room_type) {
			case fight_1_small:
			{
				std::cout << "SMLALL\n";
				break;
			}
			case fight_1_medium:
			{
				std::cout << "MEDIUM\n";
				break;
			}
			case fight_1_large:
			{
				std::cout << "larghert\n";
				break;
			}
			case fight_1_reverse_L_shape:
			{
				std::cout << "Reverse L\n";
				break;
			}
			};
		}
		//std::cout << st_sus.x << ' ' << st_sus.y << '\n';

		std::string room_layout;
		switch (room_type) {
		case fight_1_small:
		{
			room_layout = "x";
			break;
		}
		case fight_1_medium:
		{
			room_layout = "xx/xx";
			break;
		}
		case fight_1_large:
		{
			room_layout = "xxx/xxx/xxx";
			break;
		}
		case fight_1_reverse_L_shape:
		{
			room_layout = "xxx/--x";
			break;
		}
		};

		int start_x = st_sus.x, start_y = st_sus.y;
		int width = room_sizes.find(room_type)->second.x;
		int height = room_sizes.find(room_type)->second.y;
		//std::cout << "width/height: " << width << ' ' << height << '\n';
		for (int i = start_x; i < start_x + height; i++) {
			for (int j = start_y; j < start_y + width; j++) {
				int poz_string = (i - start_x) * (width + 1) + (j - start_y);
				
				//std::cout << i << ' ' << j << room_layout[poz_string] << '\n';

				if (!nu_iese(i, j) && room_layout[poz_string] == 'x') {
					//std::cout << "iese" << i << ' ' << j << '\n';
					return 0;
				}
				//std::cout << i - start_x << ' ' << j - start_y << ' ' << poz_string << '\n';
				if (room_layout[poz_string] == 'x' && layout[i][j] != 0) {
					//std::cout << "lay != 0 " << i << ' ' << j << '\n';
					return 0;
					
				}
			}
		}
		return 1;
	}
	bool nu_iese(sf::Vector2i xy) {
		return nu_iese(xy.x, xy.y);
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x_curent"></param>
	/// <param name="y_curent"></param>
	/// <param name="door_position">E=East, W=West, S=South, N=North</param>
	void generateFurther(int x_curent, int y_curent, char direction) {
		sf::Vector2i next_space;
		switch (direction) {
		case 'E':
		{
			next_space = sf::Vector2i(1.0f, 0.0f);
			break;
		}
		case 'W':
		{
			next_space = sf::Vector2i(-1.0f, 0.0f);
			break;
		}
		case 'S':
		{
			next_space = sf::Vector2i(0.0f, 1.0f);
			break;
		}
		case 'N':
		{
			next_space = sf::Vector2i(0.0f, -1.0f);
			break;
		}
		}

		for (auto& i : placeable) {
			sf::Vector2i dir;
			switch (direction) {
			case 'E':
			{
				dir = sf::Vector2i(0.0f, 1.0f);
				break;
			}
			case 'W':
			{
				dir = sf::Vector2i(0.0f, -1.0f);
				break;
			}
			case 'S':
			{
				dir = sf::Vector2i(1.0f, 0.0f);
				break;
			}
			case 'N':
			{
				dir = sf::Vector2i(-1.0f, 0.0f);
				break;
			}
			}
			sf::Vector2i spatiu_nou = sf::Vector2i(x_curent, y_curent) + dir;
			//std::cout << "Spatiu nou: " << spatiu_nou.x << ' ' << spatiu_nou.y << '\n';
			std::vector<sf::Vector2i> displacements = getDisplacements(i, spatiu_nou, direction);
			for (auto& k : displacements) {
				//std::cout << "Inainte displacement: " << k.x << ' ' << k.y << '\n';
				if (incape(i, spatiu_nou + k)) {
					std::cout << "Incape ";
					switch (i) {
					case fight_1_small:
					{
						std::cout << "SMLALLn    ";
						break;
					}
					case fight_1_medium:
					{
						std::cout << "MEDIUM    ";
						break;
					}
					case fight_1_large:
					{
						std::cout << "LARGE    ";
						break;
					}
					case fight_1_reverse_L_shape:
					{
						std::cout << "Reverse L    ";
						break;
					}
					};
					std::cout << "Displacement: " << k.x << ' ' << k.y << '\n';
				}
			}
		}std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";

		//next_space = sf::Vector2i(x_curent, y_curent) + next_space;
		if (!nu_iese(sf::Vector2i(x_curent,y_curent)+next_space)) { // iese din grid
			return;
		}
		//!					room_type -> st_sus la room-ul respectiv
		std::vector<std::pair<room_types, sf::Vector2i>> can_be_placed;
		int j, k;
		for (auto& i : placeable) {
			switch (i)
			{
			case fight_1_small:
				j = 1;
				k = 1;
				break;
			case fight_1_medium:
				j = 2;
				k = 2;
				break;
			case fight_1_large:
				j = 3;
				k = 3;
				break;
			default:
				j = 2;
				k = 3;
				break;
			}
			j -= abs(next_space.y);
			k -= abs(next_space.x);
			std::cout<<k<<" "<<j<<"\n";
			if(i!=fight_1_reverse_L_shape)
			if (next_space.x == 0)
			{
				if (next_space.y < 0)
				{
					j *= -1;
				}
				else
				{
					j = 1;
				}
				k *= -1;
				for (j; j <= 0; j++) {
					std::cout << k << " " << j << "\n";
					if (nu_iese(x_curent+k,y_curent+j) && incape(i, sf::Vector2i(x_curent,y_curent)+sf::Vector2i(k, j))) {
						can_be_placed.push_back(std::pair(i,sf::Vector2i(x_curent,y_curent)+ sf::Vector2i(k, j)));
					}
				}
			}
			else
			{
				if (next_space.y < 0)
				{
					k *= -1;
				}
				else
				{
					k = 1;
				}
				j *= -1;
				for (k; k <= 0; k++) {
					std::cout << k << " " << j << "\n";
					if (nu_iese(x_curent+k,y_curent+j) && incape(i, sf::Vector2i(x_curent,y_curent)+sf::Vector2i(k, j))) {
						can_be_placed.push_back(std::pair(i,sf::Vector2i(x_curent,y_curent)+ sf::Vector2i(k, j)));
					}
				}
			}
			else
			{
			    switch(direction)
				{
					case 'N':
						for (int p = 2; p >= 1; p--)
							if (nu_iese(x_curent + (-p), y_curent + (-p) && incape(i, sf::Vector2i(x_curent + (-p), y_curent + (-p)))))
								can_be_placed.push_back(std::pair(i, sf::Vector2i(x_curent - p, y_curent - p)));
						if (nu_iese(x_curent, y_curent - 1) && incape(i, sf::Vector2i(x_curent, y_curent - 1)))
						can_be_placed.push_back(std::pair(i, sf::Vector2i(x_curent, y_curent - 1)));
						break;
					case 'E':
						if (nu_iese(x_curent-1, y_curent - 1) && incape(i, sf::Vector2i(x_curent-1, y_curent - 1)))
							can_be_placed.push_back(std::pair(i, sf::Vector2i(x_curent-1, y_curent - 1)));
						//if()
						break;

				}
			}
			for (auto i : can_be_placed) {
				std::cout << "Can place" << room_sizes.find(i.first)->second.x << ' ' << room_sizes.find(i.first)->second.y << ' ' << i.second.x << ' ' << i.second.y << '\n';
			}
			    

		}

		}
	
private:

	Procedural generator;

	int layout[20][20] = { {} };
	std::map<int, std::unique_ptr<Room>> id_room;
	std::vector<room_types> placeable = { fight_1_small, fight_1_medium, fight_1_large, fight_1_reverse_L_shape };
};

int main() {
	srand(time(NULL));

	std::chrono::high_resolution_clock::time_point last_frame = std::chrono::high_resolution_clock::now();

	//Game game;
	Map map;



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

		//game.run_one();

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