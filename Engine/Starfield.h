#pragma once
#include "Graphics.h"
#include <random>
#include <cmath>


class Starfield
{
public:
	Starfield();
	~Starfield();

	static int constexpr screenWidth = Graphics::ScreenWidth;
	static int constexpr screenHeight = Graphics::ScreenHeight;
	
	static double const maxDiagonalDist;
	

	void Update(); // update the whole starfield (i.e. loop through update for each star)
	void Draw(Graphics& gfx); // draw the starfield (loop through the draw method for each star)


private:


	static constexpr float originX = Graphics::ScreenWidth / 2;
	static constexpr float originY = Graphics::ScreenHeight / 2;
	static constexpr int wormholeSize = 0;
	
	
	

	class Star {
	
	private:


		std::random_device rd;
		std::mt19937 rng;
		std::uniform_real_distribution<> angDist;
		std::uniform_real_distribution<> starVelDistX;
		std::uniform_real_distribution<> starVelDistY;
		std::uniform_int_distribution<int> starRadiusDist;
		std::uniform_int_distribution<int> starRColourDist;


		static constexpr float M_PI = 3.14159265358979323846;
		static constexpr float radConv = M_PI / 180;



		struct Loc { // struct for storing location

			float x;
			float y;

		};
		
		struct StarVect {

			float x; // unit vectors - floating point
			float y;

		};

		float normDist;
		double distTravelled = 0;

		StarVect vector;
		Loc location;
		int radius; // radius of star
		int starRColour;

		void SpawnNew(); // spawn a new star i.e. just return a new random vector to plug into

	public:
		Star();
		void Draw(Graphics& gfx); // draw an individual star

		void Update(); // update the position of the star based on the vector and spawn a new star when an old one "dies"
	
		
	
	};

private:
	static constexpr int noStars = 100000; //number of stars to display
	std::vector<Star> stars = std::vector<Star>(noStars); // define our array of stars



};

