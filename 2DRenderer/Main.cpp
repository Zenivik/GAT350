#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	std::unique_ptr<Image> image = std::make_unique<Image>();
	image->Load("../Resources/flower.bmp");
	image->Flip();

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear({ 0, 0 , 0, 0 });

		/*for (int i = 0; i < 50; i++)
		{
			framebuffer->DrawPoint(rand() % renderer->width, rand() % renderer->height, { 255, 0, 0, 255 });
		}
		 
		for (int i = 0; i < 10; i++)
		{
			framebuffer->DrawRect(rand() % renderer->width, rand() % renderer->height, 50, 50, { 255, 0, 0, 255 });
		}
		
		for (int i = 0; i < 50; i++)
		{
			framebuffer->DrawLine(renderer->width >> 1, renderer->height >> 1, rand() % renderer->width, rand() % renderer->height, { 0, 0, 255, 255 });
		}

		for (int i = 0; i < 1; i++)
		{
			framebuffer->DrawTriangle(300, 300, 400, 400, 400, 300, { 255, 155, 0, 155 });
		}

		for (int i = 0; i < 2; i++)
		{
			framebuffer->DrawCircle(renderer->width >> 1, renderer->height >> 1, rand() % renderer->height, { 0, 255, 0, 255 });
		}

		framebuffer->DrawSimpleCurve(200, 200, 300, 100, 3, { 255, 255, 255, 255 });

		for (int i = 0; i < 10; i++)
		{
			framebuffer->DrawQuadraticCurve(
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height, 30, { 255, 255, 0, 255 });
		}
		for (int i = 0; i < 10; i++)
		{
			framebuffer->DrawCubicCurve(
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height,
				30, { 0, 255, 255, 255 });
		}*/

		framebuffer->DrawImage(30, 30, image.get());

		std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
		PostProcess::BoxBlur(image1->colorBuffer);
		framebuffer->DrawImage(0, 300, image1.get());

		std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
		PostProcess::GaussianBlur(image2->colorBuffer);
		framebuffer->DrawImage(200, 300, image2.get());

		std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
		PostProcess::Sharpen(image3->colorBuffer);
		framebuffer->DrawImage(400, 300, image3.get());

		//PostProcess::Invert(framebuffer->colorBuffer);
		//PostProcess::Monochrome(framebuffer->colorBuffer);
		//PostProcess::Noise(framebuffer->colorBuffer, 100);
		//PostProcess::Brightness(framebuffer->colorBuffer, -100);
		//PostProcess::ColorBalance(framebuffer->colorBuffer, 0, 0, 100);
		//PostProcess::Threshold(framebuffer->colorBuffer, 200);

		framebuffer->Update();

		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}

