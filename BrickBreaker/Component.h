#pragma once
struct position
{
	float posX;
	float posY;
};

struct velocity
{
	float veloX;
	float veloY;
};

struct size
{
	float width;
	float height;
};

struct color
{
	int red;
	int green;
	int blue;
	int alpha;
};

struct bonus {
	bool active;
	std::string type; 
};

struct texture
{
	char* texture;
};