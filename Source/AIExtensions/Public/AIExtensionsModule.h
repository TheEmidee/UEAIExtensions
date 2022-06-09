#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleInterface.h>
#include <Modules/ModuleManager.h>
#include <Stats/Stats.h>

class AIEXTENSIONS_API IAIExtensionsModule : public IModuleInterface
{

public:
    static IAIExtensionsModule & Get()
    {
        static auto & singleton = FModuleManager::LoadModuleChecked< IAIExtensionsModule >( "AIExtensions" );
        return singleton;
    }

    static bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded( "AIExtensions" );
    }
};
