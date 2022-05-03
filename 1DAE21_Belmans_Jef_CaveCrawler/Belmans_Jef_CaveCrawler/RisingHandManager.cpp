#include "RisingHandManager.h"
#include "RisingHand.h"
#include "Health.h"
#include "Camera.h"
#include "Projectile.h"
#include "Avatar.h"

RisingHandManager::~RisingHandManager()
{
	for (RisingHand* element : m_pItems)
	{
		delete element;
		element = nullptr;
	}
}

RisingHand* RisingHandManager::AddItem(const Point2f& bottomLeft, int maxHealth)
{
	m_pItems.push_back(new RisingHand(bottomLeft, maxHealth));
	return m_pItems.back();
}

void RisingHandManager::Update(const Rectf& actorShape, std::vector<Projectile*> pProjectiles)
{
	for (RisingHand* element : m_pItems)
	{
		if (!element->IsDead())
		{
			element->Update(actorShape);
		}
	}

	PlayerOverlapCheck(actorShape);
	ProjectileCollisionCheck(pProjectiles);
}

void RisingHandManager::Draw() const
{
	for (RisingHand* element : m_pItems)
	{
		if (!element->IsDead())
		{
			element->Draw();
		}
	}
}

void RisingHandManager::Reset()
{
	for (RisingHand* element : m_pItems)
	{
		element->Reset();
	}
}

void RisingHandManager::PlayerOverlapCheck(const Rectf& actorShape) const
{
	for (RisingHand* element : m_pItems)
	{
		if (element->IsOverlapping(actorShape) && !element->IsDead())
		{
			Avatar::TakeDamage();
		}
	}
}

void RisingHandManager::ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles) const
{
	for (Projectile* proj : pProjectiles)
	{
		if (!proj->IsInstanciated()) continue;

		for (RisingHand* element : m_pItems)
		{
			if (!proj->IsInstanciated()) break;
			if (element->IsDead()) continue;

			if (proj->HitCheck(element->GetBoxCollider())) element->TakeDamage(1);
		}
	}
}
