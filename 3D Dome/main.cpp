#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "Shape3D.h"


int main() {
	Shape3D game3D;
	
	if (game3D.Construct(600, 480, 1, 1))
		game3D.Start();
		
	return 0;
}
