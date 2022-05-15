#include <iostream>
#include <sstream>
#include <fstream>
#include "pch.h"
#include "CollectibleManager.h"
#include "Collectible.h"
#include "Health.h"
#include "SoundManager.h"
#include "FileReader.h"

CollectibleManager::~CollectibleManager()
{
	for (Collectible* collectible : m_pItems)
	{
		DeleteCollectible(collectible);
	}
}

void CollectibleManager::Initliaze(const std::string& filePath)
{
	std::ifstream file{ filePath };

	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string line;
			std::getline(file, line, '>');
			
			int type{ std::stoi(FileReader::GetAttributeValue("Type", line)) };
			const Point2f pos{ FileReader::ToPoint2f(FileReader::GetAttributeValue("Position", line)) };

			if (type != 0)
			{
				AddItem(pos, CollectibleType(type));
			}
		}
	}
}

Collectible* CollectibleManager::AddItem(const Point2f& bottomLeft, CollectibleType type)
{
	m_pItems.push_back(new Collectible(bottomLeft, type));
	return m_pItems.back();
}

void CollectibleManager::Update(const Rectf& actorShape, Health& actorHealth)
{
	HitItem(actorShape, actorHealth);
}

void CollectibleManager::Draw() const
{
	for (Collectible* collectible : m_pItems)
	{
		if (collectible->GetIsPickedUp()) continue;
		collectible->Draw();
	}
}

void CollectibleManager::Reset()
{
	for (Collectible* collectible : m_pItems)
	{
		collectible->SetIsPickedUp(false);
	}

	m_NrPointsCollected = 0;
}

bool CollectibleManager::HitItem(const Rectf& rect, Health& actorHealth)
{
	for (Collectible* collectible : m_pItems)
	{
		if (collectible->GetIsPickedUp()) continue;

		if (collectible->IsOverlapping(rect))
		{
			collectible->SetIsPickedUp(true);

			switch (collectible->GetType())
			{
			case CollectibleType::points:
				m_NrPointsCollected++;
				SoundManager::GetInstance()->PlaySound(SoundType::coinPickup);
				break;
			case CollectibleType::health:
				actorHealth.Heal(1);
				break;
			default:
				break;
			}

			return true;
		}
	}
	
	return false;
}

void CollectibleManager::DeleteCollectible(const Collectible* collectible) const
{
	delete collectible;
	collectible = nullptr;
}
