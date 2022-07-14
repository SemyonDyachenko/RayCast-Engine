#ifndef WATER_TILE_H
#define WATER_TILE_H


class WaterTile
{
public:
	WaterTile(float centerX,float centerZ,float height,float scale);
	virtual ~WaterTile() = default;

	float& GetX() { return m_X; };
	float& GetZ() { return m_Z; };

	float& GetHeight() { return m_Height; }
	float& GetScale() { return m_Scale; }

private:
	float m_Height;
	float m_X, m_Z;
	float m_Scale;
};

#endif