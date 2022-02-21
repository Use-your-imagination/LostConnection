// Copyright (c) 2022 Arkadiy Zakharov

#include "Settings/AnimSequenceSettingsParser.h"

#include "LogAnimationCutter.h"

void AnimSequenceSettingsParser::parse(const TSharedPtr<FJsonObject>& settings)
{
	FString type;

	if (!settings->TryGetStringField("animationType", type))
	{
		animationType = EAdditiveAnimationType::AAT_None;

		UE_LOG(LogAnimationCutter, Warning, TEXT("Missing animationType field, set animationType to None"));
	}
	else
	{
		if (type == "localSpace")
		{
			animationType = EAdditiveAnimationType::AAT_LocalSpaceBase;
		}
		else if (type == "meshSpace")
		{
			animationType = EAdditiveAnimationType::AAT_RotationOffsetMeshSpace;
		}
		else if (type == "none")
		{
			animationType = EAdditiveAnimationType::AAT_None;
		}
		else if (type.IsEmpty())
		{
			animationType = EAdditiveAnimationType::AAT_None;

			UE_LOG(LogAnimationCutter, Warning, TEXT("animationType field is empty, set animationType to None"));
		}
		else
		{
			errors.Add(TEXT("Wrong animationType field value"));
		}
	}

	if (!settings->TryGetStringField("basePoseType", type))
	{
		if (animationType != EAdditiveAnimationType::AAT_None)
		{
			basePoseType = EAdditiveBasePoseType::ABPT_RefPose;

			UE_LOG(LogAnimationCutter, Warning, TEXT("Missing basePoseType field, set basePoseType to skeletonReferencePose"));
		}
		else
		{
			basePoseType = EAdditiveBasePoseType::ABPT_None;
		}
	}
	else
	{
		if (animationType == EAdditiveAnimationType::AAT_None)
		{
			basePoseType = EAdditiveBasePoseType::ABPT_None;

			UE_LOG(LogAnimationCutter, Log, TEXT("animationType is None so basePoseType must be None too"));
		}
		else
		{
			if (type == "skeletonReferencePose")
			{
				basePoseType = EAdditiveBasePoseType::ABPT_RefPose;
			}
			else if (type == "animationScaled")
			{
				basePoseType = EAdditiveBasePoseType::ABPT_AnimScaled;
			}
			else if (type == "animationFrame")
			{
				basePoseType = EAdditiveBasePoseType::ABPT_AnimFrame;
			}
			else if (type == "none")
			{
				basePoseType = EAdditiveBasePoseType::ABPT_None;
			}
			else if (type.IsEmpty())
			{
				basePoseType = EAdditiveBasePoseType::ABPT_RefPose;

				UE_LOG(LogAnimationCutter, Warning, TEXT("basePoseType field is empty, set basePoseType to skeletonReferencePose"));
			}
			else
			{
				errors.Add(TEXT("Wrong basePoseType field value"));
			}
		}
	}

	if (!settings->TryGetStringField("interpolationType", type))
	{
		interpolationType = EAnimInterpolationType::Linear;
	}
	else
	{
		if (type == "linear")
		{
			interpolationType = EAnimInterpolationType::Linear;
		}
		else if (type == "step")
		{
			interpolationType = EAnimInterpolationType::Step;
		}
		else
		{
			errors.Add(TEXT("Wrong interpolationType field value"));
		}
	}
}

AnimSequenceSettingsParser::AnimSequenceSettingsParser(const TSharedPtr<FJsonObject>& settings)
{
	this->parse(settings);
}

void AnimSequenceSettingsParser::initAnimSequence(UAnimSequence* animSequence) const
{
	animSequence->AdditiveAnimType = animationType;

	animSequence->RefPoseType = basePoseType;

	animSequence->Interpolation = interpolationType;
}
