#pragma once

#include "weapon.h"
#include "timer.h"

class Dvd_Logo : public Weapon {
public:
     Dvd_Logo();
     void draw() override;
     void update() override;
private:
    float projectile_speed = 1.5f;
    float fire_rate = 0.5f;
   
    sf::Vector2f velocity;

    sf::Shader* shader;

    util::Timer timer;
};