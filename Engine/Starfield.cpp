#include "Starfield.h"



const double Starfield::maxDiagonalDist = sqrt(pow(Starfield::screenWidth / 2, 2.0) + (Starfield::screenHeight / 2, 2.0));

Starfield::Starfield() 

{

	

}


Starfield::~Starfield()
{
}

void Starfield::Update()
{
	
	for (int i = 0; i < noStars; i++) {

		stars[i].Update();
	}

}

void Starfield::Draw(Graphics& gfx)
{
	for (int i = 0; i < noStars; i++) {

		stars[i].Draw(gfx);
	}

}


Starfield::Star::Star()
	:
	rng(rd()),
	angDist(0, 360),
	starVelDistX(1, 3),
	starVelDistY(1, 3),
	starRadiusDist(10, 20),
	starRColourDist(0, 255)
{
	SpawnNew(); // new vector and origin coords for every new star
	
	

}

void Starfield::Star::SpawnNew()
{

	float angDeg = angDist(rng);
	float starVelX = starVelDistX(rng);
	float starVelY = starVelDistY(rng);
	radius = starRadiusDist(rng);
	starRColour = starRColourDist(rng);
	vector.x = cos(angDeg * radConv) * starVelX; // create a new vector for the current star... (times our random velocity)
	vector.y = sin(angDeg * radConv) * starVelY;
	normDist = 0.0;
	location.x = originX + (wormholeSize * vector.x); // create initial location, with offset so they don't start right from the middle
	location.y = originY + (wormholeSize * vector.y);
}

void Starfield::Star::Draw(Graphics& gfx)
{
	
	int colR;

	int a = 255;
	int b = 0;

	colR = round(normDist * a); // RGB colour 0-255 scaled to fadelevel, i.e. distance travelled

	 //gfx.DrawCircle(round(location.x), round(location.y), radius, Color(colR, colR, colR));
	gfx.PutPixel(round(location.x), round(location.y), Color(colR, colR, colR));
	//gfx.DrawRect(round(location.x), round(location.y), radius, radius, Color(colR, abs(starRColour-colR), starRColour));
}

void Starfield::Star::Update()
{
	location.x = location.x + vector.x;
	location.y = location.y + vector.y;

	distTravelled = sqrtf(pow(abs(location.x - originX), 2.0) + pow(abs(location.y - originY), 2.0)); // pythag to calculate dist travelled from origin
	normDist = distTravelled / maxDiagonalDist; // distance normalised to between 0.0 and 1.0 to be used as fade and other stuff
	vector.x = vector.x * (1 + normDist / 10); // we accelerate as we get further away from the origin (i.e. 'nearer' to the observer)
	vector.y = vector.y * (1 + normDist / 10);

	if (location.x < radius || location.y < radius || location.x > Starfield::screenWidth - 1 - radius || location.y > Starfield::screenHeight - 1 - radius) {

		SpawnNew();
	}

}
