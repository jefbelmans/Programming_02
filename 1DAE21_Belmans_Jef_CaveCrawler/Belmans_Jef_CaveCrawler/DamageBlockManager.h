#pragma once
#include <vector>
#include "structs.h"

class Health;
class DamageBlock;
class Camera;
class DamageBlockManager final
{
public:
	DamageBlockManager() = default;
	~DamageBlockManager();
	DamageBlockManager(const DamageBlockManager& other) = delete;
	DamageBlockManager& operator=(const DamageBlockManager& other) = delete;
	DamageBlockManager(DamageBlockManager&& other) = delete;
	DamageBlockManager& operator=(DamageBlockManager&& other) = delete;

	DamageBlock* AddItem(const Point2f& bottomLeft);
	bool AddItemsFromSvgFile(const std::string& filePath);

	void Draw() const;
	void Update(const Rectf& actorShape);

private:
	std::vector<DamageBlock*> m_pItems;

	void PlayerCollisionCheck(const Rectf& acotrShape);
	void DeleteBlock(const DamageBlock* block) const;
};