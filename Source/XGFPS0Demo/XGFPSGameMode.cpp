// Fill out your copyright notice in the Description page of Project Settings.


#include "XGFPSGameMode.h"

void AXGFPSGameMode::StartPlay()
{
    Super::StartPlay();

    check(GEngine != nullptr);

    // 显示调试消息五秒。 
    // 参数中的-1"键"值类型参数能防止该消息被更新或刷新。
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode1!"));

    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode2!"));
}
