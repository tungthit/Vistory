#include "SFML/Graphics.hpp"

class Component
{
public:
	bool isExist = false;
};

class CTransformComponent : Component
{

};

class CShapeComponent : Component
{
public:
	sf::CircleShape shape;
	float radius = 0;
};