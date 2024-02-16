// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "DodgeballCharacter.h"
#include "DodgeballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("SightSource"));
	SightSource->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	bCanSeePlayer = LookAtActor(PlayerCharacter);

	if(bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if(bCanSeePlayer)
		{
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, \
				this,
				&AEnemyCharacter::ThrowDodgeball,
				ThrowingInterval,
				true,
				ThrowingDelay);
		}

		else
		{
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}
	
	bPreviousCanSeePlayer = bCanSeePlayer;
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemyCharacter::LookAtActor(AActor* TargetActor)
{
	if(TargetActor == nullptr) return false;

	if(CanSeeActor(TargetActor))
	{
		FRotator BaseRotator = GetActorRotation();
		
		FVector Start = SightSource->GetComponentLocation();
		FVector End = TargetActor->GetActorLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
		LookAtRotation.Pitch = BaseRotator.Pitch;
		LookAtRotation.Roll = BaseRotator.Roll;
		SetActorRotation(LookAtRotation);
		return true;
	}

	return false;
}

bool AEnemyCharacter::CanSeeActor(const AActor* TargetActor) const
{
	if(TargetActor == nullptr)
	{
		return false;
	}

	FHitResult Hit;

	FVector Start = SightSource->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(TargetActor);
	
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	
	return !Hit.bBlockingHit;
}

void AEnemyCharacter::ThrowDodgeball()
{
	if(DodgeballClass == nullptr) return;

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform((GetActorRotation(), SpawnLocation));
	
	ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);
	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2200.0f;
	Projectile->FinishSpawning(SpawnTransform);
}
