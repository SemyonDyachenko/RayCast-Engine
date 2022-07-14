#include "NoiseGenerator.h"


std::shared_ptr<float[]> NoiseGenerator::PerlinNoise2D(const int width, const int height, const int octaves, const float bias)
{
	std::mt19937 rnd_end(std::random_device{}());
	std::uniform_real_distribution<float> dist(0, 1);

	std::shared_ptr<float[]> seed(generateSeed(width, height, rnd_end, dist));
	std::shared_ptr<float[]> height_map(new float[width * height]);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			float noise = 0.0f;
			float scale_acc = 0.0f;
			float scale = 1.f;

			for (int o = 0; o < octaves; o++) {
				int pitch = width >> o;
				int sample_x1 = (x / pitch) * pitch;
				int sample_y1 = (y / pitch) * pitch;

				int sample_x2 = (sample_x1 + pitch) % width;
				int sample_y2 = (sample_y1 + pitch) % width;

				float blend_x = (float)(x - sample_x1) / (float)pitch;
				float blend_y = (float)(y - sample_y1) / (float)pitch;

				float sample_t = (1.0f - blend_x) * seed[sample_y1 * width + sample_x1] + blend_x * seed[sample_y1 * width + sample_x2];
				float sample_b = (1.0f - blend_x) * seed[sample_y2 * width + sample_x1] + blend_x * seed[sample_y2 * width + sample_x2];

				scale_acc += scale;
				noise += (blend_y * (sample_b - sample_t) + sample_t) * scale;
				scale = scale / bias;
			}

			height_map[y * width + x] = noise / scale_acc;
 		}
	}

	return height_map;
}

NoiseGenerator::NoiseGenerator() {

}

NoiseGenerator::~NoiseGenerator()
{
}

std::shared_ptr<float[]> NoiseGenerator::generateSeed(const int _width, const int _height, std::mt19937& rnd_eng, std::uniform_real_distribution<float>& dist)
{
	std::shared_ptr<float[]> sp_seed(new float[_width * _height]);

	for (int i = 0; i < _width * _height; i++)
	{
		sp_seed[i] = dist(rnd_eng);
	}

	return sp_seed;
}

double NoiseGenerator::fade(const double& _t)
{
	return 6 * pow(_t, 5) - 15 * pow(_t, 4) + 10 * pow(_t, 3);
}

double NoiseGenerator::lerp(const double& _lo, const double& _hi, const double& _t)
{
	return _lo + _t * (_hi - _lo);
}

double NoiseGenerator::grad(const int _hash, const double _x, const double _y, const double _z)
{
	int h = _hash & 15;
	double u = h < 8 ? _x : _y;
	double v = h < 4 ? _y : h == 12 || h == 14 ? _x : _z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
