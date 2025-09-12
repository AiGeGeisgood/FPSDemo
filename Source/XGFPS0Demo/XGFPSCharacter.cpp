// Fill out your copyright notice in the Description page of Project Settings.


#include "XGFPSCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "XGFPSProjectile.h"


// Sets default values
AXGFPSCharacter::AXGFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建第一人称摄像机组件。
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// 将摄像机组件附加到我们的胶囊体组件。
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// 将摄像机置于略高于眼睛上方的位置。

	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// 允许Pawn控制摄像机旋转。
	FPSCameraComponent->bUsePawnControlRotation = true;


	// 为所属玩家创建第一人称网格体组件。

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));

	check(FPSMesh != nullptr);

	// 只有所属玩家可以看见此网格体。
	FPSMesh->SetOnlyOwnerSee(true);

	// 将FPS网格体附加到FPS摄像机。
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// 禁用某些环境阴影以便实现只有一个网格体的感觉。
	FPSMesh->bCastDynamicShadow = false;

	FPSMesh->CastShadow = false;



	// 所属玩家看不到常规（第三人称）全身网格体。
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AXGFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);



	// 显示调试消息五秒。 

	// -1"键"值参数可以防止更新或刷新消息。

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
}

void AXGFPSCharacter::Move(const FInputActionValue& Value)
{
}

void AXGFPSCharacter::Look(const FInputActionValue& Value)
{
}

void AXGFPSCharacter::MoveForward(float Value)
{
	// 找出"前进"方向，并记录玩家想向该方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);

}

void AXGFPSCharacter::MoveRight(float Value)
{

	// 找出"右侧"方向，并记录玩家想向该方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AXGFPSCharacter::StartJump()
{
	bPressedJump = true;
	
}

void AXGFPSCharacter::StopJump()
{
	bPressedJump = false;

}


void AXGFPSCharacter::Fire()
{
	// 试图发射发射物。
	if (ProjectileClass)
	{
		
		// 获取摄像机变换。
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// 设置MuzzleOffset，在略靠近摄像机前生成发射物。
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		// 将MuzzleOffset从摄像机空间变换到世界空间。
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		
		// 使目标方向略向上倾斜。
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;

			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// 在枪口位置生成发射物。
			AXGFPSProjectile* Projectile = World->SpawnActor<AXGFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Projectile)
			{
				// 设置发射物的初始轨迹。
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}



		}


	}



}

// Called every frame
void AXGFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
 
// Called to bind functionality to input
void AXGFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// // 设置"移动"绑定。
	//
	// PlayerInputComponent->BindAxis("MoveForward", this, &AXGFPSCharacter::MoveForward);
	//
	// PlayerInputComponent->BindAxis("MoveRight", this, &AXGFPSCharacter::MoveRight);
	//
	// // 设置"观看"绑定。
	//
	// PlayerInputComponent->BindAxis("Turn", this, &AXGFPSCharacter::AddControllerYawInput);
	//
	// PlayerInputComponent->BindAxis("LookUp", this, &AXGFPSCharacter::AddControllerPitchInput);
	//
	// // 设置"操作"绑定。
	// PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	// PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//
	//
	// PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AXGFPSCharacter::Fire);


}

