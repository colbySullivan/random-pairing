#include "screen.hpp"
#include <string> 

/**
 * Initialize global variables
 *
 * Includes variables for the height and width of the window
 *
 */
void screen::initVariables(){
    this->gameWidth = 960;
    this->gameHeight = 720;
    this->students = readCsv();
}

vector<vector<string>> screen::readCsv(){
    vector<vector<string>> content;

	fstream file (fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout<<"Could not open the file\n";
 
	return content;
}

/**
 * Creates a new window instance with the global size variables
 */
void screen::initWindow(){
	this->window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(gameWidth), static_cast<unsigned int>(gameHeight), 32), "Classroom Boogy", sf::Style::Default);
    this->window->setVerticalSyncEnabled(true);
    if(!this->backgroundTexture.loadFromFile("resources/classroom.png"))
        return exit(0);
    this->background = sf::Sprite(backgroundTexture);
}

/**
 * Font file can be found in the resource file
 * 
 * return True if file is found
 */
void screen::initFonts(){
    if (!this->font.loadFromFile("resources/tuffy.ttf"))
        return exit(0);
}

/**
 * Creates a global text variable that is meant to display
 * a simple message on the window.
 *
 */
void screen::initMessages(){
    this->defaultMessage.setFont(font);
    this->defaultMessage.setCharacterSize(40);
    this->defaultMessage.setPosition(170.f, 200.f);
    this->defaultMessage.setFillColor(sf::Color::White);
    // for(int i=0;i<students.size();i++)
	// {
	// 	for(int j=0;j<students[i].size();j++)
	// 	{
	// 		cout<<students[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }
    string test = students[0][0];
    this->defaultMessage.setString(test);
}

/**
 * return True if window is still opened
 */
const bool screen::running() const{
	return this->window->isOpen();
}

/**
 * Checks if any key has been pressed and runs an event accordingly
 */
void screen::pollEvents(){
    while (this->window->pollEvent(this->event)){
            // Window closed or escape key pressed: exit
            if ((this->event.type == sf::Event::Closed) ||
               ((this->event.type == sf::Event::KeyPressed) && (this->event.key.code == sf::Keyboard::Escape))){
                this->window->close();
                break;
            }
        }
}

/**
 * Main run file that polls and displays
 */
void screen::rungame(){
    // Handle events
    this->pollEvents();

    // Clear the window
    this->window->clear(sf::Color(0, 0, 0));

    //Display default message
    this->window->draw(defaultMessage);

    //Display classroom background
    //this->window->draw(background);

    // Display things on screen
    this->window->display();
}

/**
 * Default global variables for new game class instance
 *
 */
screen::screen(){
	this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initMessages();
}