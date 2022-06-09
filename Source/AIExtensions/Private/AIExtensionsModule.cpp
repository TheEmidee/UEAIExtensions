#include "AIExtensionsModule.h"

class FAIExtensionsModule final : public IAIExtensionsModule
{
public:
    void StartupModule() override;
    void ShutdownModule() override;
};

IMPLEMENT_MODULE( FAIExtensionsModule, AIExtensions )

void FAIExtensionsModule::StartupModule()
{
}

void FAIExtensionsModule::ShutdownModule()
{
}