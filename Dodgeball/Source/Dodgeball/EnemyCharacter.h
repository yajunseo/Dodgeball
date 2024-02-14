// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DODGEBALL_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = true))
	USceneComponent* SightSource;
	
public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	bool LookAtActor(AActor* TargetActor);
	bool CanSeeActor(const AActor* TargetActor) const;

protected:
	bool bCanSeePlayer = false;
	bool bPreviousCanSeePlayer = false;

protected:
	FTimerHandle ThrowTimerHandle;
	float ThrowingInterval = 2.f;
	float ThrowingDelay = 0.5f;

	void ThrowDodgeball();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DodgeBall)
	TSubclassOf<class ADodgeballProjectile> DodgeballClass;
};
