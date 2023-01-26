#include "main.h"
#include <cmath>

#define PI 3.1415

#define VERMELHO 255,0,0,255
#define VERDE 0,255,0,255
#define AZUL 0,0,255,255
#define BRANCO 255,255,255,255

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
/*	static double a = 0.0;
	static int ColorShift = 0;
	if ((a+=.01) > 360){
		a = 0;
		if((ColorShift += 51) > 255)
			ColorShift = 0;
	}

	Line l1(new Pixel(VERMELHO,counter,IMAGE_HEIGHT), new Pixel(VERDE,IMAGE_WIDTH-counter,0));
	l1.DrawLine();
*
//	Line l1(new Pixel(255,0,0,255,200,0), new Pixel(0,255,0,255,200,IMAGE_HEIGHT));
//	l1.DrawLine();

//	Pixel a(255, 255, 0, 255, 256, 256);
//	a.PutPixel();
	Line *LBuffer;
	int x, y, r = IMAGE_HEIGHT/2;

	Line l5(new Pixel(VERMELHO,0,0), new Pixel(VERMELHO,IMAGE_WIDTH,IMAGE_HEIGHT));
	Line l6(new Pixel(VERMELHO,0,IMAGE_HEIGHT), new Pixel(VERMELHO,IMAGE_WIDTH,0));
	l5.DrawLine();
	l6.DrawLine();

	for(int a = 0; a < 360; a += 30){
		x = round(r*cos((PI*a)/180));
		y = round(r*sin((PI*a)/180));
		//std::cout << a << ", " << x << ", " << y << std::endl;
		LBuffer = new Line(new Pixel(BRANCO,IMAGE_WIDTH/2,IMAGE_HEIGHT/2), new Pixel(BRANCO,(IMAGE_WIDTH/2 + x),(IMAGE_HEIGHT/2 + y)));
		LBuffer->DrawLine();
		delete LBuffer;
	}*/

	Triangle t(new Pixel(VERMELHO,IMAGE_WIDTH/2 - 150,IMAGE_HEIGHT/2 + 150),new Pixel(VERDE,IMAGE_WIDTH/2,IMAGE_HEIGHT/2 - 150),new Pixel(AZUL,IMAGE_WIDTH/2 + 150,IMAGE_HEIGHT/2 +150));
	t.DrawTriangle();


/*
	Line l1(new Pixel(255, 0, 0, 255, 0, 256), new Pixel(0, 255, 0, 255, 30, 0));
	Line l2(new Pixel(255, 255, 0, 255, 0, 256), new Pixel(255, 255, 0, 255, 256, 206));
	Line l3(new Pixel(255, 255, 0, 255, 0, 256), new Pixel(255, 255, 0, 255, 256, 306));
	Line l4(new Pixel(255, 255, 0, 255, 0, 256), new Pixel(255, 255, 0, 255, 30, 512));
	l1.DrawLine();
	l2.DrawLine();
	l3.DrawLine();
	l4.DrawLine();
*/

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

