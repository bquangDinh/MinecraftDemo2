#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::readHeightMap(const char* file)
{
	bitmap_image image(file);
	if (!image) {
		printf("Failed to read file\n");
		return;
	}

	unsigned int width = image.width();
	unsigned int height = image.height();

	printf("Height Map: %d x %d\n", width, height);

	for (std::size_t y = 600; y < 700; y++) {
		for (std::size_t x = 300; x < 400; x++) {
			rgb_t colour;

			image.get_pixel(x, y, colour);

			printf("%d ", colour.red);
		}
	}

	printf("\n");

}
