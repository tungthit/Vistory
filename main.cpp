#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdint>

const uint8_t frames[][8] = {
	// Frame 1: Smiley
	{
		0b00111100,
		0b01000010,
		0b10100101,
		0b10000001,
		0b10100101,
		0b10011001,
		0b01000010,
		0b00111100
	},
	// Frame 2: Smiley Blink
	{
		0b00111100,
		0b01000010,
		0b10111101,
		0b10000001,
		0b10100101,
		0b10011001,
		0b01000010,
		0b00111100
	}
};
const int FRAME_COUNT = sizeof(frames) / sizeof(frames[0]);

class Rect {
	sf::RectangleShape rect;

public:
	Rect() {}

	Rect(float x, float y, float w, float h) {
		rect.setSize({ w, h });
		rect.setPosition({ x, y });
		rect.setFillColor(sf::Color::Black);
	}

	void setOn(bool isOn) {
		rect.setFillColor(isOn ? sf::Color::White : sf::Color::Black);
	}

	void draw(sf::RenderWindow& window) {
		window.draw(rect);
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Kappa");
	window.setFramerateLimit(60);

	Rect blocks[8][8];
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			blocks[y][x] = Rect(x * 10, y * 10, 10, 10);
		}
	}

	sf::Clock clock;
	int currentFrame = 0;
	const float frameDuration = 0.5f; // seconds per frame

	while (window.isOpen())
	{
		// Update animation frame
		if (clock.getElapsedTime().asSeconds() >= frameDuration) {
			currentFrame = (currentFrame + 1) % FRAME_COUNT;
			clock.restart();
		}

		// Update blocks based on current frame bits
		for (int y = 0; y < 8; ++y) {
			uint8_t row = frames[currentFrame][y];
			for (int x = 0; x < 8; ++x) {
				bool bitOn = row & (1 << (7 - x));
				blocks[y][x].setOn(bitOn);
			}
		}

		window.clear();
		for (int y = 0; y < 8; ++y)
			for (int x = 0; x < 8; ++x)
				blocks[y][x].draw(window);
		window.display();
	}

	return 0;
}
