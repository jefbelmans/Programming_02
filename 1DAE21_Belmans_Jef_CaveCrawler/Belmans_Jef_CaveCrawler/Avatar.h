#pragma once
#include <math.h>
#include "utils.h"
#include "Texture.h"
#include "Sprite.h"

class Level;
class Avatar
{
public:
	Avatar();
	~Avatar() = default;

	void Update(const Level& level);
	void Draw() const;

	bool ShouldTrack() const;

	Rectf GetShape() const;

private:
	Sprite m_Sprite;
	Rectf m_Shape{ 50.0f, 40.0f, 13.0f, 14.0f };

	float m_Gravity{ -250.0f };
	float m_GravityScale{ 1.0f };

	Vector2f m_Velocity{ 0.0f, 0.0f };
	float m_MaxVelocity{ 700.0f };
	float m_Damping{ 1.0f };

	const float m_HorCamDeadZone{ 10.0f };
	const float m_VerCamDeadZone{ 10.0f };

	bool m_TickMovementTimer{ false };
	const float m_StandStillDetectionTime{ 0.75f };
	float m_TimeSinceMovement{ 0.0f };
	Point2f m_StandStillPos{ 0.0f, 0.0f };

	GLfloat m_HorizontalScale{ 1 };
	int m_MovementDirection{ 0 };
	bool m_IsPressingJump{ false };
	bool m_IsGrounded{ false };
	bool m_HasJumped{ false };
	float m_MovementSpeed{ 50.0f };
	float m_JumpHeight{ 5.0f };
	float m_InitialJumpVelocity{ 120.0f };
	float m_TimeSinceGrounded{ 0.0f };
	const float m_CoyoteTime{ 0.1f };

	void GetInput();
	void ProcessInput(const Level& level);

	void Jump();
	void SetAnimation();
	void SetGravityScale();

	void ClampVelocity();
	void DampVelocity();
};