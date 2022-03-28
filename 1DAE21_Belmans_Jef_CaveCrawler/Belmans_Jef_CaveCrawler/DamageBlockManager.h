#pragma once
#include "pch.h"
#include <vector>

class Health;
class DamageBlock;
class Camera;
class DamageBlockManager final
{
public:
	DamageBlockManager();
	~DamageBlockManager();
	DamageBlockManager(const DamageBlockManager& other) = delete;
	DamageBlockManager& operator=(const DamageBlockManager& other) = delete;
	DamageBlockManager(DamageBlockManager&& other) = delete;
	DamageBlockManager& operator=(DamageBlockManager&& other) = delete;

	DamageBlock* AddItem(const Point2f& bottomLeft);
	bool AddItemsFromSvgFile(const std::string& filePath);

	void Draw() const;
	void Update(const Rectf& actorShape, Health& actorHealth, Camera& cam);
	void CollisionCheck(const Rectf& acotrShape, Health& actorHealth, Camera& cam);

private:
	std::vector<DamageBlock*> m_pItems;

	void DeleteBlock(const DamageBlock* block) const;
};