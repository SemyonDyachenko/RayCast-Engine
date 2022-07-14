#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include <string>

#include "LuaScript.h"
#include "../Core/Log.h"

#include <fstream>
#include <sstream>
#include <dirent.h>

struct LuaScriptProps
{
	std::string m_Path;
	std::string m_ClassName;
	bool valide = false;

	LuaScriptProps(std::string path,std::string className)
	{
		m_Path = path;
		m_ClassName = className;
	}
};

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void Init();

	void LoadMainScripts();

	void GetScriptInPath(std::string& path);

	void Start();
	void Update(float DeltaTime);

	void InstanceUpdate();

	LuaScript* ScriptInstance(std::string class_name);
	LuaScript* ScriptInstanceClass(unsigned int id,std::string class_name);

	void ImportScriptsFromResources(std::string path);

	void DeleteScript(unsigned int id);
	void ClearScripts();

	void ReloadInterpreter();

	void RecompileScripts(bool reinstance = true);
	void ReinstanceScript();

	bool AddLuaScript(std::string& path, std::string class_name);
	bool LoadLuaFile(std::string& path, std::string class_name);

	
	void Close();

public:
	lua_State* State = nullptr;
	std::vector<LuaScript*> m_Instances;
	std::vector<LuaScriptProps> m_LoadedScripts;


	bool initialized = false;
private:
	bool m_RecompileScripts = false;
	
};



#endif