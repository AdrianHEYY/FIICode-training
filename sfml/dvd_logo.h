#pragma once

#include "weapon.h"
#include "timer.h"
#include "weapons_enum.h"

extern class Player;

class Dvd_Logo : public Weapon {
public:
     Dvd_Logo(Player* owner, sf::Vector2f original_position);
     void draw() override;
     void update() override;
     const weapon_name name = DVD_LOGO;
     const weapon_type type = PASSSIVE;
     ~Dvd_Logo();
private:
    Player* owner;

    float projectile_speed = 1.5f;
    float fire_rate = 0.5f;
    
    int bounces_left = 1;

    sf::Vector2f velocity;

    sf::Shader* shader; // modifica culoarea

    util::Timer timer;
};