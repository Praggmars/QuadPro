#pragma once

#include "quad_quad.h"
#include <list>

namespace quad
{
	struct QuadAction
	{
		int legID;
		mth::float2 goalPos;
		float rot;
	};
	
	class WalkScript
	{
		float m_maxTurnAtOnce;
		float m_bellyy;
		float m_legLift;
		float m_legXPos;
		float m_legZRetracted;
		float m_legStretchHalf;
		bool m_rightBalanced;
		std::list<QuadAction> m_script;

	private:
		void AddPathElementLegMovement(LegID legid, mth::float2 pos);
		void AddPathElementBodyMovement(mth::float2 pos, float turn);
		void AddLegTurnRightBalanced(mth::float2x2 rotmat);
		void AddLegTurnLeftBalanced(mth::float2x2 rotmat);
		void AddLegBodyElementsTurn(float angle);
		void AddLegWalkStraightRightBalanced(float ratio);
		void AddLegWalkStraightLeftBalanced(float ratio);
		void AddLegBodyElementsWalkStraight(float distance);

	public:
		WalkScript();
		void AddPathElementTurn(float angle);
		void AddPathElementWalkStraight(float distance);
		void AddPathElementCircle(float circleR, float rotation);
		void Clear();
		bool NextAction(QuadAction& action);
		mth::float3 getLegRFStartPos();
		mth::float3 getLegLFStartPos();
		mth::float3 getLegRBStartPos();
		mth::float3 getLegLBStartPos();
		float getBellyY();
		float LegY(float t);
	};

	class WalkManager
	{
		float m_time;
		float m_speed;
		WalkScript m_script;
		Quadruped *m_quad;
		QuadAction m_action;
		QuadAction m_prevAction;
		bool m_running;

	private:
		void MoveBody(float deltaTime);
		void MoveLeg();
		void ReceiveNextAction();
		float FinishPreviousAction(float timeLeft);
		void ExecuteAction(float deltaTime);

	public:
		void Init(Quadruped *quadruped);
		void Update(float deltaTime);
		WalkScript& getWalkScript();
	};
}