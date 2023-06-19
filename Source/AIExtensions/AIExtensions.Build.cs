namespace UnrealBuildTool.Rules
{
    public class AIExtensions : ModuleRules
    {
        public AIExtensions( ReadOnlyTargetRules Target )
            : base( Target )
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PrivateIncludePaths.Add("AIExtensions/Private");
            
            PublicDependencyModuleNames.AddRange(
                new string[] { 
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "AIModule",
                    "GameplayTasks",
                    "GameplayAbilities",
                    "GameplayBehaviorsModule"
                }
            );
        }
    }
}
