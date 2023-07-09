// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include <DesktopPlatform/Public/IDesktopPlatform.h>
#include <DesktopPlatform/Public/DesktopPlatformModule.h>
//#include <PriorityQueueCPP.h>



#include "FileDialogHandler.generated.h"
/**
 * Entidad que permite crear ventanas para realizar operaciones de E/S con el sistema operativo.
 */
UCLASS(BlueprintType)
class RACINGAI_API UFileDialogHandler : public UObject
{
	GENERATED_BODY()

private:
	/**
	* Abre la ventana de di�logo del sistema operativo para guardar un archivo.
	*/
	bool SaveFileDialogRewrite(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames);

	/**
	* Abre la ventana de di�logo del sistema operativo para abrir un archivo.
	*/
	bool OpenFileDialogRewrite(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames);

	/**
	* Mezcla ambos m�todos privados para poder llamarse desde uno.
	*/
	bool FileDialogSharedRewrite(bool bSave, const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex);
public:
	UFileDialogHandler();

	/**
	* Abre la ventana de di�logo para abrir un archivo.
	* 
	* @param DialogTitle T�tulo que aparecer� en la ventana de di�logo.
	* @param FileTypes Tipos de archivos aceptados.
	* 
	* @return Valor booleano que indica si la operaci�n ha tenido �xito y la ruta en la que se encuentra el archivo cargado.
	*/
	UFUNCTION(BlueprintCallable)
	bool abrirArchivo(FString& filePath, const FString& DialogTitle = FString("Select a file"), const FString& FileTypes = FString("All Files(*.*) | *.*"));

	/**
	* Abre la ventana de di�logo para guardar un archivo.
	*
	* @param DialogTitle T�tulo que aparecer� en la ventana de di�logo.
	* @param FileTypes Tipos de archivos aceptados.
	*
	* @return Valor booleano que indica si la operaci�n ha tenido �xito y la ruta en la que se encuentra el archivo guardado.
	*/
	UFUNCTION(BlueprintCallable)
	bool guardarArchivo(FString& fileName, const FString& FileTypes = FString("All Files(*.*) | *.*"), const FString& DialogTitle = FString("Select file save location"));
};
