class CfgPatches
{
	class CustomHUD
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 1.0;
		requiredAddons[] = {"DZ_Data", "DZ_Scripts"};
	};
};

class CfgMods
{
	class CustomHUD
	{
		dir = "CustomHUD";
		picture = "";
		hideName = 1;
		hidePicture = 1;
		name = "Custom HUD (stats)";
		credits = "";
		author = "";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";

		dependencies[] = {"Game", "World", "Mission"};
		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {"CustomHUD/scripts/5_Mission"};
			};
		};
	};
};