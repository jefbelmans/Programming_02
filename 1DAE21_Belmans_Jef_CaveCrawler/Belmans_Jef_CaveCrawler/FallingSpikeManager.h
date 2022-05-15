#pragma once
#include <vector>
#include "structs.h"

class Health;
class FallingSpike;
class FallingSpikeManager final
{
public:
	FallingSpikeManager() = default;
	~FallingSpikeManager();

	FallingSpikeManager(const FallingSpikeManager& other) = delete;
	FallingSpikeManager& operator=(const FallingSpikeManager& other) = delete;
	FallingSpikeManager(FallingSpikeManager&& other) = delete;
	FallingSpikeManager& operator=(FallingSpikeManager&& other) = delete;

	void Initialize(const std::string& filePath);
	FallingSpike* AddItem(const Point2f& bottomLeft);

	void Update(const Rectf& actorShape, const std::vector<std::vector<Point2f>>& verts, Health& actorHealth);
	void Draw() const;

	void Reset();
private:
	std::vector<FallingSpike*> m_pItems;

	void PlayerOverlapCheck(const Rectf& actorShape, Health& actorHealth) const;
	void LevelOverlapCheck(const std::vector<std::vector<Point2f>>& verts) const;
};

