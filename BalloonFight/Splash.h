#pragma once
class Splash
{
private:
	float x;
	int WaitTime;
	int WorkImg;
	int AnimImg;
	int images[3];
public:
	Splash(float _x);
	~Splash();
	void LoadImages();
	void Draw()const;
	bool Update();
};

