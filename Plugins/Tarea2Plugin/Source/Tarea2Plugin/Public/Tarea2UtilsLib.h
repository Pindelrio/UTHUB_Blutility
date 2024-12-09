// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Tarea2UtilsLib.generated.h"

class AStaticMeshActor;
class FJsonObject;

UCLASS()
class TAREA2PLUGIN_API UTarea2UtilsLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tarea2Utils")
	TArray<FString> SMJsonList;
	
	UFUNCTION(BlueprintCallable, Category = "Tarea2Utils")
	static void ListAssetsDependencies(const FARFilter& Filter, const FString& InFileName);

	UFUNCTION(BlueprintCallable, Category = "Tarea2Utils")
	static void ExportStringArrayToFile(const TArray<FString>& InExportList, const FString& InFileName);

	UFUNCTION(BlueprintCallable, Category = "Tarea2Utils")
	static bool EvaluateSMConditions(const AStaticMeshActor* InStaticMeshActor);
};


