// Copyright (c) 2022 Use Your Imagination

#include "BaseRangedBot.h"

ABaseRangedBot::ABaseRangedBot()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> blackboardFinder(TEXT("BlackboardData'/Game/AI/Base/Ranged/BaseRangedBlackboard.BaseRangedBlackboard'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> behaviorTreeFinder(TEXT("BehaviorTree'/Game/AI/Base/Ranged/BaseRangedBehaviorTree.BaseRangedBehaviorTree'"));

	blackboard = blackboardFinder.Object;
	behaviorTree = behaviorTreeFinder.Object;
}
