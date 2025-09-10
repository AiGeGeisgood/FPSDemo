// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XGFPSProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class XGFPS0DEMO_API AXGFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXGFPSProjectile();

	// 球体碰撞组件。
	UPROPERTY(VisibleDefaultsOnly, Category = XG)
	USphereComponent* CollisionComponent;


	// 发射物移动组件。
	UPROPERTY(VisibleAnywhere, Category = XG)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// 发射物网格体
	UPROPERTY(VisibleDefaultsOnly, Category = XG)
	UStaticMeshComponent* ProjectileMeshComponent;

	// 发射物材质
	UPROPERTY(VisibleDefaultsOnly, Category = XG)
	UMaterialInstanceDynamic* ProjectileMaterialInstance;





	// 初始化射击方向上发射物速度的函数。
	void FireInDirection(const FVector& ShootDirection);
	// UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector, NormalImpulse, const FHitResult&, Hit

	// 当发射物击中物体时会调用的函数。

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
