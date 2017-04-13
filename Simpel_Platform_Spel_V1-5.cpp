/// g++ Programmanaam.cpp -std=c++11 -o "%e" "%f" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
// -DNDEBUG vor release

// Benodigde libraries
#include <iostream>
#include <string> 
#include <cmath> 
#include <chrono> 
#include <thread>
#include <vector>
#include <cassert>
#include <SFML/Graphics.hpp> 

// Een uitgebreidere sprite klasse met de naam Blox.
class Blox
{
	
	// Coordinaten al van tevoren gedefinieerd.
	double x_coord = 0, y_coord = 0;
	
	// Afmetingen al van tevoren gedefinieerd.
	double x_size = 64, y_size = 64;
	
	// Verplaatsingssnelheden van tevoren gedefinieerd.
	double x_step = 1, y_step = 1;
	
	// assert(x_coord == 0 && y_coord == 0 && x_size == 64 && y_size == 64 && x_step == 1 && y_step == 1);
	
	// Bestandsnaam.
	std::string blox_img;
	
	// Textuur
	sf::Texture blox_tex;
	
	// Sprite
	sf::Sprite blox_sprite;
	
	// Kleur naar ondoorzichtig wit.
	sf::Color blox_color = {255, 255, 255, 255};
	
	// Kader
	sf::FloatRect blox_bounds;
	
	// Wat je via parameterfuncties kunt instellen.
	public:
		
		// assert(x_coord == 0 && y_coord == 0 && x_size == 64 && y_size == 64 && x_step == 1 && y_step == 1);
	
		// Coordinaten instellen
		void set_coords (double, double);
		
		// Afmetingen instellen
		void set_sizes (double, double);
		
		// Verplaatsingssnelheden instellen
		void set_steps (double, double);
						
		// Plaatje inladen en klaarmaken.
		void set_image (std::string);
		
		// Kleur veranderen
		void set_color (int, int, int, int);
		
		// Kleur veranderen
		void set_color (int, int, int);
		
		// Naar coordinaten bewegen
		void move_to_coords (double, double);
		
		double show_x_coord()
		{
			
			return x_coord;
			
		}
		
		double show_y_coord()
		{
			
			return y_coord;
			
		}
		
		double show_x_size()
		{
			
			return x_size;
			
		}
		
		double show_y_size()
		{
			
			return y_size;
			
		}
		
		// Om het plaatje te kunnen laten zien.
		sf::Sprite show_image()
		{
			
			return blox_sprite;
			
		}
		
		// Kader vaststellen
		void bounding()
		{
			
			blox_bounds = blox_sprite.getGlobalBounds();
			
		}
		
		sf::FloatRect show_bounds()
		{
			
			return blox_bounds;
			
		}
		
		// Stapje naar rechts doen.
		void x_step_up() 
		{
			
			x_coord = x_coord + x_step;
			
			blox_sprite.setPosition(sf::Vector2f(x_coord, y_coord));			
			
		}
		
		// Stapje naar links doen.
		void x_step_down() 
		{
			
			x_coord = x_coord - x_step;
			
			blox_sprite.setPosition(sf::Vector2f(x_coord, y_coord));	
			
		}
		
		// Stapje naar beneden doen.
		void y_step_up() 
		{
			
			y_coord = y_coord - y_step;
			
			blox_sprite.setPosition(sf::Vector2f(x_coord, y_coord));	
			
		}
		
		// Stapje naar boven doen.
		void y_step_down() 
		{
			
			y_coord = y_coord + y_step;
			
			blox_sprite.setPosition(sf::Vector2f(x_coord, y_coord));	
			
		}
	
};


// Coordinaten instellen
void Blox::set_coords (double x_cord, double y_cord)
{
	
	x_coord = x_cord;
	y_coord = y_cord;
	
}


// Afmetingen instellen
void Blox::set_sizes (double x_siz, double y_siz)
{
	
	x_size = x_siz;
	y_size = y_siz;
	
}


// Verplaatsingssnelheden instellen
void Blox::set_steps (double x_sep, double y_sep)
{
	
	x_step = x_sep;
	y_step = y_sep;
	
}

// Naar coordinaten bewegen
void Blox::move_to_coords (double x_cord, double y_cord)
{
	
	x_coord = x_cord;
	y_coord = y_cord;
	
	blox_sprite.setPosition(sf::Vector2f(x_coord, y_coord));
		
}

// Plaatje inladen en klaarmaken.
void Blox::set_image (std::string box_img)
{
	
	blox_img = box_img;
	
	//Plaatje laden
	if (!blox_tex.loadFromFile(blox_img))
	{
			
		std::cout << blox_img << " not found!\n";
		
			
	}
	
	// Patroon instellen
	blox_sprite.setTexture(blox_tex);
	
	// Positie van het ankerpunt instellen
	blox_sprite.setOrigin(sf::Vector2f(x_size/2, y_size/2));
	
	// Positie instellen
	blox_sprite.setPosition(sf::Vector2f(x_coord, y_coord));
	
	// Kleur instellen
	blox_sprite.setColor(blox_color);
	
	// Kader vaststellen
	blox_bounds = blox_sprite.getGlobalBounds();
	
}

void Blox::set_color (int red, int green, int blue, int opac)
{
	
	blox_color.r = red;
	blox_color.g = green;
	blox_color.b = blue;
	blox_color.a = opac;
	
	blox_sprite.setColor(blox_color);
	
}

void Blox::set_color (int red, int green, int blue)
{
	
	blox_color.r = red;
	blox_color.g = green;
	blox_color.b = blue;
	
	blox_sprite.setColor(blox_color);
	
}



// Start van het programma
int main()
{
	
	// char langolier;
	
	// De verversingstijd voor het programma in milliseconden.
	// Het aantal Hertz is 1000 gedeeld door de verversingstijd.
	const int wachttijt = 20;
	
	const double PI = 4*atan(1);
	
	const double period = 3000;
	double tau = 0;
	
	assert(wachttijt > 0);
	
	// Overzetten van gehele getallen naar de daadwerkelijke tijdseenheden.
	const std::chrono::milliseconds wachttijd(wachttijt);	
	
	
	// Stel de grootte van de helf tvan de window voor horizontaal (x) en vertikaal (y) in.
	const int halve_window_x = 352, halve_window_y = 352;
	
	assert(halve_window_x > 0 && halve_window_y > 0);
		
	// Nu de daadwerkelijke afmetingen van je window
	const int volle_window_x = 2*halve_window_x, volle_window_y = 2*halve_window_y;
	
	
	// Naam van het programma voor op de window, zodat iedereen die het gebruikt het weet.
	const std::string programmanaam = "Simpel Platform Spel V1.5";
	
	assert(programmanaam != "");
	
	// Beginwaarden voor veranderende regenboogkleuren.
	int regenboog_rood = 192, regenboog_groen = 64, regenboog_blauw = 64;
	
	// Grenswaarden voor maximum en minimum en stapwaarde.
	const int regenboog_max = 192, regenboog_min = 64, regenboog_stap = 1;
	
	assert((regenboog_rood > 0) && (regenboog_rood < 256) &&
			(regenboog_groen > 0) && (regenboog_groen < 256) &&
			(regenboog_blauw > 0) && (regenboog_blauw < 256) &&
			(regenboog_max > 0) && (regenboog_max < 256) &&
			(regenboog_min > 0) && (regenboog_min < regenboog_max) &&
			(regenboog_stap > 0) && (regenboog_stap < 256));
	
	// Spritegrootte
	const int x_img = 64, y_img = 64;
	
	const int finish_x_pix = 128, finish_y_pix = 128;
	
	const int char_x_pix = 32, char_y_pix = 32;
	
	// Verplaatsingssnelheid
	const int x_move = 5, y_move = 2;
	
	assert((x_img > 0) && (y_img > 0) && (x_move > 0) && (y_move > 0));
	
	// Bestandsnaam van de charactersprite
	const std::string char_img = "White_32.png";
	
	// Bestandsnaam van de muursprite
	const std::string wall_img = "Monotoid_64.png";
	
	// Bestandsnaam van de muursprite
	const std::string finish_img = "No_Regret_128.png";
	
	// Bestandsnaam van de muursprite
	const std::string exit_img = "Plinkett_128.png";
	
	assert((char_img != "") && (wall_img != ""));
	
	int checked_walls = 0;
	
	// const double coords_mult = 1, origins_mult_x = 0.91,  origins_mult_y = 1*origins_mult_x, wall_mult = 0.92;
	
	// const double x_wall_mult = 0.85;
	
	const double view_mult = 0.5;
	
	bool flicker = false;
	
	bool right_jump = false, left_jump = false;
	
	bool right_act = false, left_act = false;
	
	const double max_boost_x = 25, boost_dx = -1;
	
	double boost_x = 0;
	
	bool boostable = false;
	
	// Maak je Blox sprite aan maak het gereed voor gebruik.
	// Dit is je beweegbare character.
	Blox your_chara;
	
	your_chara.set_coords(halve_window_x, halve_window_y);
	
	your_chara.set_sizes(char_x_pix, char_y_pix);
	
	your_chara.set_steps(x_move + boost_x, y_move);
	
	your_chara.set_image(char_img);
	
	double chara_dx = 0, chara_dy = 0;
	
	const double jump_y = -8.5, max_y = 12, slip_y = 0;
	
	// const double chara_ddx = 0;
	
	const double chara_ddy = 0.25;
	
	
	
	// Maak meerdere Blox sprites aan maak ze gereed voor gebruik.
	// dit zijn muren maar werken nog niet zo.
	int wall_amount = 0;
	
	assert(wall_amount == 0);
	
	++wall_amount;
	std::vector<Blox> your_wall(wall_amount);
	

	your_wall[wall_amount - 1].set_coords(halve_window_x + 6*x_img, halve_window_y + 4*y_img);
	
	
	your_wall.resize(++wall_amount);
	your_wall[wall_amount - 1].set_coords(halve_window_x - 1*x_img, halve_window_y + 3*y_img);
	
	your_wall.resize(++wall_amount);
	your_wall[wall_amount - 1].set_coords(halve_window_x - 3*x_img, halve_window_y + 3*y_img);
	
	your_wall.resize(++wall_amount);
	your_wall[wall_amount - 1].set_coords(halve_window_x - 2*x_img, halve_window_y + 0*y_img);
	
	your_wall.resize(++wall_amount);
	your_wall[wall_amount - 1].set_coords(halve_window_x - 2*x_img, halve_window_y - 4*y_img);
	
	your_wall.resize(++wall_amount);
	your_wall[wall_amount - 1].set_coords(halve_window_x + 1*x_img, halve_window_y + 3*y_img);
	
	your_wall.resize(++wall_amount);
	your_wall[wall_amount - 1].set_coords(halve_window_x + 1*x_img, halve_window_y - 2*y_img);
	
	your_wall.resize(++wall_amount);
	your_wall[wall_amount - 1].set_coords(halve_window_x + 1*x_img, halve_window_y - 6*y_img);
	
	
	for (int a_sub = 0; a_sub < 10; a_sub++)
	{
		
		your_wall.resize(++wall_amount);
		your_wall[wall_amount - 1].set_coords(halve_window_x + (-3 + a_sub)*x_img, halve_window_y + 5*y_img);
	
	}
	
	const double finish_x = halve_window_x + (10 + 3*10 + 8)*x_img, finish_y = halve_window_y + (-10 + 5 - 4)*y_img;
	
	

	for (int a_sub = 0; a_sub <= 10; a_sub++)
	{
		
		your_wall.resize(++wall_amount);
		your_wall[wall_amount - 1].set_coords(halve_window_x + (10 + 3*a_sub)*x_img, halve_window_y + (-a_sub + 5)*y_img);
		
	}
	
	
	Blox your_finish;
	
	your_finish.set_coords(finish_x, finish_y);
	
	your_finish.set_sizes(finish_x_pix, finish_y_pix);
	
	your_finish.set_steps(0, 0);
	
	your_finish.set_image(finish_img);
	
	
	
	Blox your_exit;
	
	your_exit.set_coords(halve_window_x - 7*x_img, halve_window_y + -31*y_img);
	
	your_exit.set_sizes(finish_x_pix, finish_y_pix);
	
	your_exit.set_steps(0, 0);
	
	your_exit.set_image(exit_img);
	
	
	for (int a_sub = 0; a_sub <= 30; a_sub++)
	{
		
		if (a_sub < 10)
		{
			
			your_wall.resize(++wall_amount);
			your_wall[wall_amount - 1].set_coords(halve_window_x + 0*x_img, halve_window_y + (-a_sub - 15)*y_img);
						
			
		}
		
		your_wall.resize(++wall_amount);
		your_wall[wall_amount - 1].set_coords(halve_window_x + 3*x_img, halve_window_y + (-a_sub + 3)*y_img);
		
		if (a_sub < 15)
		{
			
			your_wall.resize(++wall_amount);
			your_wall[wall_amount - 1].set_coords(halve_window_x + 6*x_img, halve_window_y + (-a_sub + 3)*y_img);
			
		}
		
		
	
	}
	
	
	for (int a_sub = 0; a_sub <= 20; a_sub++)
	{
		
		
		your_wall.resize(++wall_amount);
		your_wall[wall_amount - 1].set_coords(halve_window_x + (-5 - 7*a_sub)*x_img, halve_window_y + 5*y_img);
		
		your_wall.resize(++wall_amount);
		your_wall[wall_amount - 1].set_coords(halve_window_x + (-5 - 2*a_sub)*x_img, halve_window_y - 10*y_img);
		
		
	}
	
	for (int a_sub = 0; a_sub < wall_amount; a_sub++)
	{
		
		
		// your_wall[a_sub].set_coords(halve_window_x + (a_sub - 2)*x_img, halve_window_y + 5*y_img);
	
		your_wall[a_sub].set_sizes(x_img, y_img);
		
		your_wall[a_sub].set_steps(x_move + boost_x, y_move);
		
		your_wall[a_sub].set_image(wall_img);
		
		
	}
	
	
	
	// Nieuwe window maken met afmeting volle_window_x keer volle_window_y en als opschrift programmanaam.
	// sf::Style::Default is een standardstijl.
	sf::RenderWindow window(sf::VideoMode(volle_window_x, volle_window_y), programmanaam, sf::Style::Default);
	
	/// Zie voor meer over windows beheren ook: http://www.sfml-dev.org/tutorials/2.3/window-window.php
	
	sf::View view(sf::Vector2f(your_chara.show_x_coord(), your_chara.show_x_coord()),
				sf::Vector2f(volle_window_x, volle_window_y));
	
	view.setViewport(sf::FloatRect(1*(0.5 - view_mult), 1*(0.5 - view_mult), 1*(0.5 + view_mult), 1*(0.5 + view_mult)));
	
	sf::Event event;
	
	//Open window en terwijl die open is: Doorloop de lus.
	while (window.isOpen())
    {
		
		
		
		
		/// De volgende code is een handige manier om veranderende regenboogkleuren aan de ahctergrond van je window
		/// toe te voegen.
		
		// Als rood is gelijk aan het maximum en groen is groter dan de minimum, dan groen verminderen.
		if ((regenboog_rood == regenboog_max) && (regenboog_groen > regenboog_min))
		{
				
			// Groen met stap verminderen.
			regenboog_groen = regenboog_groen - regenboog_stap;
			
			// Als groen kleiner dan het minimum is...
			if (regenboog_groen < regenboog_min)
			{
				
				// Dan wordt groen gelijk aan het minimum.
				regenboog_groen = regenboog_min;
				
			}
				
		}
		
		// Als rood is gelijk aan het maximum en groen is gelijk aan het minimum en blauw is kleiner dan het maximum,
		// dan blauw verhogen.	
		if ((regenboog_rood == regenboog_max) && (regenboog_groen == regenboog_min) && (regenboog_blauw < regenboog_max))
		{
			
			// Blauw met stap vermeerderen.
			regenboog_blauw = regenboog_blauw + regenboog_stap;
			
			// Als blauw groter dan het maximum is...
			if (regenboog_blauw > regenboog_max)
			{
				
				// Dan wordt blauw gelijk aan het maximum.
				regenboog_blauw = regenboog_max;
				
			}
		
		}
		
		// Als blauw is gelijk aan het maximum en rood is groter dan de minimum, dan groen verminderen.
		if ((regenboog_blauw == regenboog_max) && (regenboog_rood > regenboog_min))
		{
			
			// Rood met stap verminderen.	
			regenboog_rood = regenboog_rood - regenboog_stap;
			
			// Als rood kleiner dan het minimum is...
			if (regenboog_rood < regenboog_min)
			{
				
				// Dan wordt rood gelijk aan het minimum.
				regenboog_rood = regenboog_min;
				
			}
				
		}
		
		// Als blauw is gelijk aan het maximum en rood is gelijk aan het minimum en groen is kleiner dan het maximum,
		// dan blauw verhogen.	
		if ((regenboog_blauw == regenboog_max) && (regenboog_rood == regenboog_min) && (regenboog_groen < regenboog_max))
		{
			
			// Groen met stap vermeerderen.
			regenboog_groen = regenboog_groen + regenboog_stap;
			
			// Als groen groter dan het maximum is...
			if (regenboog_groen > regenboog_max)
			{
				
				// Dan wordt groen gelijk aan het maximum.
				regenboog_groen = regenboog_max;
				
			}
				
		}
		
		// Als groen is gelijk aan het maximum en blauw is groter dan de minimum, dan blauw verminderen.
		if ((regenboog_groen == regenboog_max) && (regenboog_blauw > regenboog_min))
		{
			
			// Blauw met stap verminderen.	
			regenboog_blauw = regenboog_blauw - regenboog_stap;
			
			// Als blauw kleiner dan het minimum is...
			if (regenboog_blauw < regenboog_min)
			{
				
				// Dan wordt blauw gelijk aan het minimum.
				regenboog_blauw = regenboog_min;
				
			}
				
		}
		
		// Als groen is gelijk aan het maximum en blauw is gelijk aan het minimum en rood is kleiner dan het maximum,
		// dan blauw verhogen.	
		if ((regenboog_groen == regenboog_max) && (regenboog_blauw == regenboog_min) && (regenboog_rood < regenboog_max))
		{
				
			// Rood met stap vermeerderen.
			regenboog_rood = regenboog_rood + regenboog_stap;
			
			// Als rood groter dan het maximum is...
			if (regenboog_rood > regenboog_max)
			{
				
				// Dan wordt rood gelijk aan het maximum.
				regenboog_rood = regenboog_max;
				
			}
					
		}
		
		/// Hier houdt deze veranderende regenboogkleurencode op.
		
		view.setCenter(your_chara.show_x_coord(), your_chara.show_y_coord());
		
		window.setView(view);
		
		// Wis de window schoon met de veranderende regenboogkleur.
		// window.clear(sf::Color(0, regenboog_groen, regenboog_blauw));
		
		// Wis de window schoon met zwart.
		window.clear(sf::Color(0, 0, 0));
		
		// Plaats de muren in de window.
		for (int a_sub = 0; a_sub < wall_amount; a_sub++)
		{
			
			// your_wall[a_sub].set_color(regenboog_rood, regenboog_groen, regenboog_blauw);
			
			if (true)
			{
				
				window.draw(your_wall[a_sub].show_image());
			
			}
			
		}
		
		// Plaats het character in de window.
		
		if (true)
		{
			
			your_chara.set_color(regenboog_rood, regenboog_groen, regenboog_blauw);
			
			window.draw(your_chara.show_image());
			
		}
		
		your_finish.move_to_coords(finish_x + 2*x_img*sin(2*PI*tau/period), finish_y - y_img*sin(2*PI*tau/period));
		
		window.draw(your_finish.show_image());
		
		window.draw(your_exit.show_image());
	
		// Geef de window daadwerkelijk weer.
		window.display();
		
		
		your_chara.bounding();
		
		your_finish.bounding();
		
		if (your_chara.show_bounds().intersects(your_finish.show_bounds()))
		{
			
			// Alleen te zien op de terminal.
			// std::cout << "You are 7zip!" << "\n";
			
			for (int a_sub = 0; a_sub < 250; a_sub++)
			{
				
				// Programma wacht wachttijd milliseconden af voor het verdergaat.
				std::this_thread::sleep_for(wachttijd);
				
				// Wis de window schoon met zwart.
				window.clear(sf::Color(0, 0, 0));
				
				// Plaats de muren in de window.
				for (int a_sub = 0; a_sub < wall_amount; a_sub++)
				{
					
					// your_wall[a_sub].set_color(regenboog_rood, regenboog_groen, regenboog_blauw);
					
					if (true)
					{
						
						window.draw(your_wall[a_sub].show_image());
					
					}
					
				}
				
				// Plaats het character in de window.
				
				if (true)
				{
					
					your_chara.set_color(regenboog_rood, regenboog_groen, regenboog_blauw);
					
					window.draw(your_chara.show_image());
					
				}
				
				window.draw(your_finish.show_image());
				
				window.draw(your_exit.show_image());
				
				
			
				// Geef de window daadwerkelijk weer.
				window.display();			
				
			}
			
			
			your_chara.set_coords(halve_window_x, halve_window_y);
			
			chara_dx = 0;
			chara_dy = 0;
			
			flicker = false;
			
			
			// sluit de window.
			// window.close();
					
			// Een 0 uitspugen, main() uitgaan en zo het programma verlaten.
			// return 0;
				
		}
		
		
		if (your_chara.show_bounds().intersects(your_exit.show_bounds()))
		{
			
			// Alleen te zien op de terminal.
			// std::cout << "You are 7zip!" << "\n";
			
			for (int a_sub = 0; a_sub < 250; a_sub++)
			{
				
				// Programma wacht wachttijd milliseconden af voor het verdergaat.
				std::this_thread::sleep_for(wachttijd);
				
				// Wis de window schoon met zwart.
				window.clear(sf::Color(0, 0, 0));
				
				// Plaats de muren in de window.
				for (int a_sub = 0; a_sub < wall_amount; a_sub++)
				{
					
					// your_wall[a_sub].set_color(regenboog_rood, regenboog_groen, regenboog_blauw);
					
					if (true)
					{
						
						window.draw(your_wall[a_sub].show_image());
					
					}
					
				}
				
				// Plaats het character in de window.
				
				if (true)
				{
					
					your_chara.set_color(regenboog_rood, regenboog_groen, regenboog_blauw);
					
					window.draw(your_chara.show_image());
					
				}
				
				window.draw(your_finish.show_image());
				
				window.draw(your_exit.show_image());
			
				// Geef de window daadwerkelijk weer.
				window.display();			
				
			}
			
			
			// sluit de window.
			window.close();
					
			// Een 0 uitspugen, main() uitgaan en zo het programma verlaten.
			return 0;
				
		}
		
		
		// Als de [Esc] knop ingedrukt wordt eindig main() en zo het programma.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
			(event.type == sf::Event::Closed))
		{
			
			/// http://www.sfml-dev.org/tutorials/2.3/window-inputs.php
			
			
			// Alleen te zien op de terminal.
			std::cout <<  programmanaam << " manually terminated!" << "\n";
			
			// sluit de window.
			window.close();
					
			// Een 0 uitspugen, main() uitgaan en zo het programma verlaten.
			return 0;
						
		}		
		
		
		// Druk op "d" of rechts om rechts te bewegen.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			
			checked_walls = -1;
			
			if (checked_walls < 0)
			{			
			
				your_chara.x_step_up();
				
			}
			
			
			
		}
		
		// Druk op "a" of links om links te bewegen.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			
			checked_walls = -1;
			
			if (checked_walls < 0)
			{			
			
				your_chara.x_step_down();
				
			}
			
		}
		
		// Druk op "w" om omhoog te bewegen.
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) &&
			(flicker || right_act || left_act))
		{
			
			checked_walls = -1;
			
			your_chara.bounding();
			
			for (int a_sub = 0; a_sub < wall_amount; a_sub++)
			{
				
				your_wall[a_sub].bounding();
				
				if (your_chara.show_bounds().intersects(your_wall[a_sub].show_bounds()))
				{
					
					checked_walls = a_sub;
						
				}
				
			}

			if (checked_walls < 0)
			{			
			
				chara_dy = jump_y;
				
				boostable = true;
				
				flicker = false;
				
				if (right_act)
				{
					
					right_act = false;
					left_jump = true;
					
				}
				
				
				if (left_act)
				{
					
					left_act = false;
					right_jump = true;
					
				}
				
			}
			
		}
		
		// Druk op "s" om omlaag te bewegen.
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) &&
			(chara_dy < 0))
			
		{
						
			chara_dy = 0;
			
			flicker = false;
			
		}
		
		
		// Druk op "s" om te 'boosten'.
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) &&
		boostable)			
		{
						
			boost_x = max_boost_x;
			
			boostable = false;
			
		}
		
		
		chara_dy = chara_dy + chara_ddy;
		
		if (chara_dy > slip_y)
		{
			
			flicker = false;
			
			right_jump = false;
			
			left_jump = false;
			
			right_act = false;
			
			left_act = false;
			
		}
		
		if (abs(chara_dy) >= max_y)
		{
			
			chara_dy = max_y*chara_dy/abs(chara_dy);
			
		}
		
		// std::cout << chara_dy << "\n";
		
		// std::cout << your_chara.show_x_coord() << ":" << your_chara.show_y_coord() << "\n";
		
		your_chara.set_steps(x_move + boost_x, chara_dy);
		
		your_chara.y_step_down();
		
		// your_chara.set_coords(your_chara.show_x_coord(), your_chara.show_y_coord() + chara_dy);
		
		
		
		
		// linkerkant
		
		checked_walls = -1;
		
		for (int a_sub = 0; a_sub < wall_amount; a_sub++)
		{				
			
		
								
			if (((your_chara.show_y_coord() + 0.5*your_chara.show_y_size()) >=
				(your_wall[a_sub].show_y_coord() - 0.6*0.5*your_wall[a_sub].show_y_size())) &&
				((your_chara.show_y_coord() - 0.5*your_chara.show_y_size()) <=
				(your_wall[a_sub].show_y_coord() + 0.7*0.5*your_wall[a_sub].show_y_size())))
			{
				
				if (((your_chara.show_x_coord() + 0.5*your_chara.show_x_size()) >
					(your_wall[a_sub].show_x_coord() - 0.5*your_wall[a_sub].show_x_size())) &&
					((your_chara.show_x_coord() + 0.5*your_chara.show_x_size()) <
					(your_wall[a_sub].show_x_coord() - 0.7*0.5*your_wall[a_sub].show_x_size())))
				{
				
					checked_walls = a_sub;				
					
				}
				
				
			}
			
					
		}
		
		if ((checked_walls >= 0))
		{			
						
			chara_dx = your_wall[checked_walls].show_x_coord() - 0.5*your_wall[checked_walls].show_x_size() -
			your_chara.show_x_coord() - 0.5*your_chara.show_x_size(); ///??????????????????????????????????????????????????????
			
			your_chara.set_steps(chara_dx, 0);
			
			your_chara.x_step_up();
			
			boost_x = 0;
			
			if (chara_dy < 0)
			{
				
				boostable = true;
				
			}
			
			your_chara.set_steps(x_move + boost_x, y_move);
			
			
			chara_dx = 0;
			
			// chara_dy = 0;
			
			if (left_jump)
			{
				
				left_act = true;
				
				left_jump = false;
				
				flicker = true;
				
			}						
			
			
			if (chara_dy > slip_y)
			{
				
				flicker = false;
				
			}
						
		}
		
		
		
		
		
		// rechterkant
		
		checked_walls = -1;
		
		for (int a_sub = 0; a_sub < wall_amount; a_sub++)
		{				
			
		
								
			if (((your_chara.show_y_coord() + 0.5*your_chara.show_y_size()) >=
				(your_wall[a_sub].show_y_coord() - 0.6*0.5*your_wall[a_sub].show_y_size())) &&
				((your_chara.show_y_coord() - 0.5*your_chara.show_y_size()) <=
				(your_wall[a_sub].show_y_coord() + 0.7*0.5*your_wall[a_sub].show_y_size())))
			{
				
				if (((your_chara.show_x_coord() - 0.5*your_chara.show_x_size()) <
					(your_wall[a_sub].show_x_coord() + 0.5*your_wall[a_sub].show_x_size())) &&
					((your_chara.show_x_coord() - 0.5*your_chara.show_x_size()) >
					(your_wall[a_sub].show_x_coord() + 0.7*0.5*your_wall[a_sub].show_x_size())))
				{
				
					checked_walls = a_sub;				
					
				}
				
				
			}
					
		}
		
		if ((checked_walls >= 0))
		{			
						
			chara_dx = your_wall[checked_walls].show_x_coord() + 0.5*your_wall[checked_walls].show_x_size() -
			your_chara.show_x_coord() + 0.5*your_chara.show_x_size(); ///??????????????????????????????????????????????????????
			
			your_chara.set_steps(chara_dx, 0);
			
			your_chara.x_step_up();
			
			boost_x = 0;
			
			if (chara_dy < 0)
			{
				
				boostable = true;
				
			}
			
			your_chara.set_steps(x_move + boost_x, y_move);
			
			
			chara_dx = 0;
			
			
			
			// chara_dy = 0;
			
			
			if (right_jump)
			{
				
				right_act = true;
				
				right_jump = false;
				
				flicker = true;
				
			}
			
			
			
			if (chara_dy > slip_y)
			{
				
				flicker = false;
				
			}
			
		}
		
		
		
		// bovenkant
		
		checked_walls = -1;
		
		for (int a_sub = 0; a_sub < wall_amount; a_sub++)
		{				
			
		
								
			if (((your_chara.show_y_coord() + 0.5*your_chara.show_y_size()) >
				(your_wall[a_sub].show_y_coord() - 0.5*your_wall[a_sub].show_y_size())) &&
				((your_chara.show_y_coord() + 0.5*your_chara.show_y_size()) <
				(your_wall[a_sub].show_y_coord() - 0.6*0.5*your_wall[a_sub].show_y_size())))
			{
				
				if (((your_chara.show_x_coord() - 0.5*your_chara.show_x_size()) <
					(your_wall[a_sub].show_x_coord() + 0.5*your_wall[a_sub].show_x_size())) &&
					((your_chara.show_x_coord() + 0.5*your_chara.show_x_size()) >
					(your_wall[a_sub].show_x_coord() - 0.5*your_wall[a_sub].show_x_size())))
				{
				
					checked_walls = a_sub;				
					
				}
				
				
			}
					
		}
		
		if ((checked_walls >= 0))
		{			
						
			chara_dy = your_wall[checked_walls].show_y_coord() - 0.5*your_wall[checked_walls].show_y_size() -
			your_chara.show_y_coord() - 0.5*your_chara.show_y_size(); ///??????????????????????????????????????????????????????
			
			your_chara.set_steps(0, chara_dy);
			
			your_chara.y_step_down();
			
			boost_x = 0;
						
			your_chara.set_steps(x_move + boost_x, y_move);
			
			
			chara_dx = 0;
			chara_dy = 0;
			
			
			
			flicker = true;
			
			right_jump = true;
			left_jump = true;
			
		}
		
		
		
		
		
		// onderkant
		
		checked_walls = -1;
		
		for (int a_sub = 0; a_sub < wall_amount; a_sub++)
		{				
			
			
			if (((your_chara.show_y_coord() - 0.5*your_chara.show_y_size()) >
				(your_wall[a_sub].show_y_coord() + 0.7*0.5*your_wall[a_sub].show_y_size())) &&
				((your_chara.show_y_coord() - 0.5*your_chara.show_y_size()) <
				(your_wall[a_sub].show_y_coord() + 0.5*your_wall[a_sub].show_y_size())))
			{
				
				if (((your_chara.show_x_coord() - 0.5*your_chara.show_x_size()) <
					(your_wall[a_sub].show_x_coord() + 0.5*your_wall[a_sub].show_x_size())) &&
					((your_chara.show_x_coord() + 0.5*your_chara.show_x_size()) >
					(your_wall[a_sub].show_x_coord() - 0.5*your_wall[a_sub].show_x_size())))
				{
				 
					checked_walls = a_sub;
					
				}
				
				
			}
					
		}
		
		if ((checked_walls >= 0))
		{			
			
			chara_dy = your_wall[checked_walls].show_y_coord() + 0.5*your_wall[checked_walls].show_y_size() -
			your_chara.show_y_coord() + 0.5*your_chara.show_y_size(); 
			
			your_chara.set_steps(0, chara_dy);
			
			your_chara.y_step_down();
			
			boost_x = 0;
						
			your_chara.set_steps(x_move + boost_x, y_move);
			
			
			chara_dx = 0;
			
			if (chara_dy < 0)
			{
				
				chara_dy = 0;
			
			}
						
			
		}
		
		if (your_chara.show_y_coord() > 1024)
		{
			
			your_chara.set_coords(halve_window_x, halve_window_y);
			
			chara_dx = 0;
			chara_dy = 0;
			
			flicker = false;
			
		}
		
		tau += wachttijt;
		
		while (tau > period)
		{
			
			tau -= period;
			
		}
		
		if (boost_x > 0)
		{
			
			boost_x += boost_dx;
			
			if (boost_x < 0)
			{
				
				boost_x = 0;
				
			}
						
		}
		
		// Programma wacht wachttijd milliseconden af voor het verdergaat.
		std::this_thread::sleep_for(wachttijd);
		
		// Einde lus.		
	}
	
	// Een 0 uitspugen, main() verlaten en dus programma einde.	
	// Alleen te zien op de terminal.
	return 0;
			
	
	// Einde programma.	
}
