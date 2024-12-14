// Copyright Epic Games, Inc. All Rights Reserved.

#include "TxFPSDemoProjectile.h"

#include "ScoreComponent.h"
#include "TargetBlock.h"
#include "TxFPSDemoCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerState.h"

ATxFPSDemoProjectile::ATxFPSDemoProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATxFPSDemoProjectile::OnHit);
	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ATxFPSDemoProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		// 先看看OwnerActor是不是玩家, OtherActor是不是TargetBlock
		const ATxFPSDemoCharacter* Player = Cast<ATxFPSDemoCharacter>(GetOwner());
		const ATargetBlock* TargetBlock = Cast<ATargetBlock>(OtherActor);
		if (Player != nullptr && TargetBlock != nullptr)
		{
			// 给Player加分
			float Score = TargetBlock->GetScore();
			Player->GetScoreComponent()->AddScore(Score);
			if (GEngine)
			{
				FString DebugMsg = FString::Printf(
					TEXT("Current player's score: %f"), Player->GetScoreComponent()->GetScore());
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, DebugMsg);
			}
		}

		Destroy();
	}
}
