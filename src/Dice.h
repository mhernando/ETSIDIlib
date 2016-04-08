#pragma once



//A 2D quad that can be rendered to the screen
class Dice
{
public:
    
    static double Double(double max=1.0, double min=0.0F);
	static int Int(int max, int min=1);
	static bool Bool();
private:
	static bool initialized;


};

