// Fill out your copyright notice in the Description page of Project Settings.

#include "Tarea2UtilsLib.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/Engine.h"

#pragma region ListAssetsHelpers
FString GenerateIndentation(int32 Level)
{
	FString Indentation;
	for (int32 i = 0; i < Level; ++i)
	{
		Indentation += TEXT("   "); // Tres espais per nivell
	}
	return Indentation;
}

void ListDependenciesStack(const FName& RootAssetName, IAssetRegistry& AssetRegistry, TArray<FString>& OutputLines)
{
	// Pila para procesar los assets
	TArray<TPair<FName, int32>> Stack_AssetLevel; 
	Stack_AssetLevel.Push(TPair<FName, int32>(RootAssetName, 0));

	while (Stack_AssetLevel.Num() > 0)
	{
		TPair<FName, int32> Current = Stack_AssetLevel.Pop(); 
		FName CurrentAssetName = Current.Key;
		int32 Level = Current.Value;

		FString Indentation = GenerateIndentation(Level);
		OutputLines.Add(FString::Printf(TEXT("%s|- %s"), *Indentation, *CurrentAssetName.ToString()));

		TArray<FName> Dependencies;
		AssetRegistry.GetDependencies(CurrentAssetName, Dependencies);

		for (const FName& DependencyName : Dependencies)
		{
			Stack_AssetLevel.Push(TPair<FName, int32>(DependencyName, Level + 1));
		}
	}
}
#pragma endregion ListAssetsHelpers

void UTarea2UtilsLib::ListAssetsDependencies(const FARFilter& Filter, const FString& InFileName)
{
	const auto& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssets(Filter,AssetDataList);

	TArray<FString> OutputLines;
	
	for (const FAssetData& AssetData : AssetDataList)
	{
		FString RootAssetName = AssetData.AssetName.ToString();
		OutputLines.Add( FString::Printf(TEXT("AssetRoot [ROOT]: %s\n"), *RootAssetName));

		//Recursiva
		ListDependenciesStack(AssetData.PackageName, AssetRegistry, OutputLines);
	}
	
	FString OutputText = FString::Join(OutputLines, TEXT("\n"));	

	FString FilePath = FPaths::ProjectSavedDir() / InFileName + FDateTime::Now().ToString() + TEXT(".log");

	if (FFileHelper::SaveStringToFile(OutputText, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Archivo generado correctamente: %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No se pudo generar el archivo: %s"), *FilePath);
	}
}

void UTarea2UtilsLib::ExportStringArrayToFile(const TArray<FString>& InExportList, const FString& InFileName)
{
	if (InExportList.IsEmpty())
		return;

	FString OutputText;
	for (const auto& AssetName : InExportList)
	{
		OutputText.Append(AssetName + '\n');
	}

	FString FilePath = FPaths::ProjectSavedDir() / InFileName + FDateTime::Now().ToString() + TEXT(".log");
	if (FFileHelper::SaveStringToFile(OutputText, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Archivo generado correctamente: %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No se pudo generar el archivo: %s"), *FilePath);
	}
}