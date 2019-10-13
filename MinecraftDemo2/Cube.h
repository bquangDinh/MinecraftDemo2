#pragma once

class Cube
{
public:
	/*Verticles of each side*/
	static const float FRONTSIDE[12];
	static const float BACKSIDE[12];
	static const float TOPSIDE[12];
	static const float BOTTOMSIDE[12];
	static const float LEFTSIDE[12];
	static const float RIGHTSIDE[12];
	static const unsigned int FRONT_INDICATES[6];
	static const unsigned int BACK_INDICATES[6];

	enum CUBESIDE {
		FRONT,
		BACK,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NOT_THING
	};

	Cube() {}
};

