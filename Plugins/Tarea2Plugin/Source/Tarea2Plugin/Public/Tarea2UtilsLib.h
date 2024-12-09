// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Tarea2UtilsLib.generated.h"

/**
 * 
 */
UCLASS()
class TAREA2PLUGIN_API UTarea2UtilsLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Utiles")
	static void ListAssetsDependencies(const FString& InFileName);

	UFUNCTION(BlueprintCallable, Category = "Utiles")
	static void ExportStringArrayToFile(const TArray<FString>& InExportList, const FString& InFileName);
};


