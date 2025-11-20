// Group members: Simar  Anand and Joseph Pele


// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

unsigned randomVertex(unsigned vertexNum, unsigned currentVert) {
	unsigned randomVertex;

	if (vertexNum != 3) {
		do {
			randomVertex = rand() % vertexNum;
		} while (randomVertex == currentVert);

		return randomVertex;
	}

	return rand() % vertexNum;
}

int main()
{
	// Create a video mode object
	srand(time(0));
	size_t const POINTS_SIZE = 10000;
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;


	unsigned vert{ UINT_MAX }, numberOfVertices;
	bool end{};


	do {
		cout << "Choose between 3 and 5 vertices to create the outline for your shape: " << endl;
		cin >> numberOfVertices;
	} while (numberOfVertices < 3 || numberOfVertices > 5);

	Font font;
	Text text;
	if (!font.loadFromFile("calibri.ttf")) {
		cerr << "Calibri failed to load." << endl;
		return 1;
	}

	text.setFont(font);
	text.setString("Click anywhere on the screen to create the vertices for your shape");
	text.setCharacterSize(26);
	text.setFillColor(Color::Red);
	text.setStyle(Text::Italic | Text::Underlined | Text::Bold);


	
	while (window.isOpen())
	{
	
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (vertices.size() < numberOfVertices)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						
						if (vertices.size() == numberOfVertices) {

							text.setString("Now select any point within the shape you've made");
						}
					}
					else if (points.size() == 0)
					{
						///fourth click
						///push back to points vector
						text.setString("Congrats! Watch your shape get made");
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						
					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() < POINTS_SIZE && points.size() > 0)
		{
			///generate more point(s)
			///select random vertex
			vert = randomVertex(numberOfVertices, vert);
			///calculate midpoint between random vertex and the last point in the 
			///push back the newly generated coord
			const float MAGIC_NUMBER = (numberOfVertices == 3 || numberOfVertices == 4) ? .5f : .618f;
			float newX = points.back().x + (vertices.at(vert).x - points.back().x) * MAGIC_NUMBER;
			float newY = points.back().y + (vertices.at(vert).y - points.back().y) * MAGIC_NUMBER;

			points.push_back(Vector2f(newX, newY));

			if (points.size() == POINTS_SIZE) {
				cout << "Points total: " << points.size() << endl;
			}

		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}

		///TODO:  Draw points
		for (size_t i = 0; i < points.size(); i ++) {
			RectangleShape rect(Vector2f(2.5f, 2.5));
			rect.setPosition(points[i]);
			rect.setFillColor(Color::White);
			window.draw(rect);
		}


		window.draw(text);
		window.display();


	}


}
