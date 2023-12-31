#include "screen.hpp"
#include <string> 
#include <algorithm>
#include <random>

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

/**
 * Read from CSV and put into vector of vector strings
 * 
 * vector<vector<string>> allows for future track of 
 * partner pair if ever implemented
 *
 */
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
 * Creates global text variables that is meant to display
 * a simple message on the window.
 */
void screen::initMessages(){
    sf::Text defaultMessage[students.size()];
    for(int i=0;i<students.size();i++){
        this->defaultMessage[i].setFont(font);
        this->defaultMessage[i].setCharacterSize(18);
        this->defaultMessage[i].setFillColor(sf::Color::Black);
		// for(int j=0;j<students[i].size();j++){ // TODO For reading other columns
		// 	
		// }
    }
    randomize();
    for(int j=0;j<students.size();j++){
        string message = " "; //Absent student
        if(students[j][1] == "1")
            message = students[j][0];
        this->defaultMessage[j].setString(message);
    }
    this->initSeatPos();
}

// Very basic random function
void screen::randomize(){
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(students), std::end(students), rng);
}

// This is a mess and will only work for this lab
// There was very little thought into the future proof of this part
void screen::initSeatPos(){
    // Pixel spacing for first row[{80,70},{170,80}{400,80}, {490,80}]
    // int y = 70;
    // for(int j = 0; j < 4; j++){
    //     int x = 85;
    //     if (j == 2)
    //         y+=50;
    //     for(int i = 0; i < 6; i++){ //Rows
    //         if (i == 2 || i == 4) //Inbetween column table clusters
    //             x+=140;
    //         this->defaultMessage[(i + (j*6))].setPosition((x + (i*90)), (y + (j*80))); 
    //     }
    // }
    // y = 530;
    // int x = 400;
    // int spot = 24; //After instructor table
    // for(int l = 0; l <= 1; l++){
    //     x = 400;
    //     for(int z = 0; z < 4; z++){
    //         if(z == 2)
    //             x+= 140;
    //         this->defaultMessage[spot+z+(l*4)].setPosition((x + (z*90)), (y + (l*80)));
    //     }
    // }
    
    int posx;
    int posy;
    int index = 0;
    for (multimap<int,int>::iterator it= positions.begin(); it != positions.end(); ++it) {
        posx = it->first;
        posy = it->second;
        this->defaultMessage[index].setPosition(posx, posy); 
        index++;
        this->defaultMessage[index].setPosition(posx, posy+80);
        index++;

    }
}

void screen::intPosStorage(){
    this->positions.insert(std::pair<int, int>(85, 70)); // 85 70, 85 150
    this->positions.insert(std::pair<int, int>(85, 280)); // 85 280, 85 360

    this->positions.insert(std::pair<int, int>(175, 70)); // 175 70, 175 150
    this->positions.insert(std::pair<int, int>(175, 280)); //175 280, 175 360

    this->positions.insert(std::pair<int, int>(405, 70)); // 405 70, 405 150
    this->positions.insert(std::pair<int, int>(405, 280)); //405 280, 405 360
    this->positions.insert(std::pair<int, int>(405, 530)); //405 530, 405 610

    this->positions.insert(std::pair<int, int>(495, 70)); // 495 70, 495 150
    this->positions.insert(std::pair<int, int>(495, 280)); //495 280, 495 360
    this->positions.insert(std::pair<int, int>(495, 530)); //495 530, 495 610

    this->positions.insert(std::pair<int, int>(725, 70)); // 725 70, 725 150
    this->positions.insert(std::pair<int, int>(725, 280)); //725 280, 725 360
    this->positions.insert(std::pair<int, int>(725, 530)); //725 530, 725 610

    this->positions.insert(std::pair<int, int>(815, 70)); // 815 70, 815 150
    this->positions.insert(std::pair<int, int>(815, 280)); //815 280, 815 360
    this->positions.insert(std::pair<int, int>(815, 530)); //815 530, 815 610
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
            //Press space to reshuffle
            if ((this->event.type == sf::Event::KeyReleased) && (this->event.key.code == sf::Keyboard::Space))
                    this->initMessages();
        }
}

/**
 * Main run file that polls and displays
 */
void screen::rungame(){
    if(students.size() < 35){
    // Handle events
    this->pollEvents();

    // Clear the window
    this->window->clear(sf::Color(0, 0, 0));

    //Display classroom background
    this->window->draw(background);

    //Display student names
    for(int i = 0; i < 33; i++)
        this->window->draw(defaultMessage[i]);

    // Display things on screen
    this->window->display();
    }
}

/**
 * Default global variables for new game class instance
 *
 */
screen::screen(){
	this->initVariables();
    this->intPosStorage();
    this->initWindow();
    this->initFonts();
    this->initMessages();
}