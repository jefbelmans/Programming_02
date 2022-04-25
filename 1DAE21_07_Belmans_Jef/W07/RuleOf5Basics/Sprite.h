#pragma once
#include <string>

class Texture;
class Sprite final
{
public:
	Sprite( const std::string& filename, int nrCols = 1, int nrRows = 1, float frameSec = 0 );
	~Sprite( );
	Sprite(const Sprite& other);
	Sprite& operator=(const Sprite& other);
	Sprite(Sprite&& other) noexcept;
	Sprite& operator=(Sprite&& other) noexcept;

	void Update( float elapsedSec );
	void Draw( const Point2f& pos, float scale = 1.0f );

	float GetFrameWidth( );
	float GetFrameHeight( );

private:
	Texture *m_pTexture;
	std::string m_TexturePath;
	int m_Cols;
	int m_Rows;
	float m_FrameSec;
	float m_AccuSec;
	int   m_ActFrame;

};