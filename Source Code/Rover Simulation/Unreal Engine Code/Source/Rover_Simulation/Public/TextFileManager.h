/*
	Copyright [2021] [Andrei Lazar]

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
 */
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TextFileManager.generated.h"

UCLASS()
class ROVER_SIMULATION_API ATextFileManager : public AActor
{
public:	
	GENERATED_BODY()

	static bool SaveArrayText(FString SaveDirectory, FString FileName, TArray<FString> SaveText, bool AllowOverwriting);
};
