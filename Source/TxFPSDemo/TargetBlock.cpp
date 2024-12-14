// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetBlock.h"

#include "TxFPSDemoProjectile.h"
#include "Components/BoxComponent.h"


// Sets default values
ATargetBlock::ATargetBlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 初始化碰撞检测用的网格体组件
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComponent->SetBoxExtent(FVector(55.0));
	BoxComponent->SetCollisionProfileName(FName("TargetBlock"));
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetNotifyRigidBodyCollision(true);
	BoxComponent->OnComponentHit.AddDynamic(this, &ATargetBlock::OnHit);
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void ATargetBlock::BeginPlay()
{
	Super::BeginPlay();
}

void ATargetBlock::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                         FVector NormalImpulse, const FHitResult& Hit)
{
	// 只接受来自投射物的碰撞
	ATxFPSDemoProjectile* Projectile = Cast<ATxFPSDemoProjectile>(OtherActor);
	if (Projectile == nullptr)
	{
		return;
	}

	if (bIsBeenHit)
	{
		Destroy();
	}
	else
	{
		bIsBeenHit = true;
		SetActorRelativeScale3D(FVector(ScaleScalar));
	}
}

// Called every frame
void ATargetBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
