// Fill out your copyright notice in the Description page of Project Settings.


#include "XGFPSProjectile.h"
#include "Components/SphereComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"

// Sets default values
AXGFPSProjectile::AXGFPSProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// 设置球体的碰撞半径。
	CollisionComponent->InitSphereRadius(15.0f);
	// 将根组件设置为碰撞组件。
	RootComponent = CollisionComponent;


	// 使用此组件驱动发射物的移动。
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;



	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Script/Engine.StaticMesh'/Game/FBX/Mesh_Projectile/Sphere.Sphere'"));

	if (Mesh.Succeeded())
	{
		ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("/Script/Engine.Material'/Game/Material/M_Sphere.M_Sphere'"));

	if (Material.Succeeded())
	{

		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);

	}
	ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);

	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));

	ProjectileMeshComponent->SetupAttachment(RootComponent);

	// 3 秒后删除发射物。
	InitialLifeSpan = 3.0f;

	// 将球体的碰撞配置文件名称设置为"Projectile"。
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("ProjectileFile"));

	// 组件击中某物时调用的事件。
	CollisionComponent->OnComponentHit.AddDynamic(this, &AXGFPSProjectile::OnHit);


}

void AXGFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;

}

void AXGFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}


	Destroy();
}

// Called when the game starts or when spawned
void AXGFPSProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AXGFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

