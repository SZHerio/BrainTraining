#pragma once

class ABTClickableCircle;
class ABTClickableCirclesSpawnManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClickableCircleSphereReleasedSignature, const ABTClickableCircle*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClickableCircleSelectedSignature, const ABTClickableCircle*)

UENUM()
enum class EBackgroundMusicType : uint8
{
	Main,
	Difficult
};