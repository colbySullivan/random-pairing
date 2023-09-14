#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

//Needed for CSV
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
 *	Class that acts as the game engine.
 *	Wrapper class.
*/

class screen{
private:
    // Variables
    float gameWidth;
    float gameHeight;

    // Window setup
    sf::RenderWindow* window;

    // Classroom image
    sf::Sprite background;
    sf::Texture backgroundTexture;

    // Set font
    sf::Font font;

    // Create text
    sf::Text defaultMessage;

    //Running events
    sf::Event event;

    //CSV contents
    string fname = "students.csv";
    vector<vector<string>> students;
	vector<string> row;
	string line, word;
    

    void initVariables();
    void initWindow();
    void initFonts();
	void initMessages();
public:
	//Constructors / Destructors
	screen();

	//Accessors
	const bool running() const;

    //Functions
    void pollEvents();
    void rungame();
    vector<vector<string>> readCsv();
};