#include "ScriptManager.h"


static void Lua_LoadScript(lua_State*state,std::string path)
{
	if(luaL_loadfile(state,path.c_str()))
	{
		std::cerr << "Failed To load lua class type" << std::endl;
		std::cerr << lua_tostring(state, -1) << std::endl;
		lua_pop(state, 1);
	}

	if (lua_pcall(state, 0, LUA_MULTRET, 0)) {
		std::cerr << "Failed To load lua class type" << std::endl;
		std::cerr << lua_tostring(state, -1) << std::endl;
		lua_pop(state, 1);
	}
}

static void ReplaceSTR(std::string& str, const std::string& oldStr, const std::string& newStr)
{
	std::string::size_type pos = 0u;
	while ((pos = str.find(oldStr, pos)) != std::string::npos)
	{
		str.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}
}

ScriptManager::ScriptManager()
{
	
}

ScriptManager::~ScriptManager()
{
}

void ScriptManager::Init()
{
	State = luaL_newstate();
	luaL_openlibs(State);
	luaopen_io(State);
}

void ScriptManager::LoadMainScripts()
{
	Lua_LoadScript(State, "resources/core/Class.lua");
	Lua_LoadScript(State, "resources/core/ScriptComponent.lua");
}

void ScriptManager::GetScriptInPath(std::string& path)
{
}

void ScriptManager::Start()
{
	for (size_t i = 0; i < m_Instances.size(); i++)
	{
		if (!m_Instances[i]->hasStart) continue;

		m_Instances[i]->CallMethod("Start");
	}
}


void ScriptManager::Update(float DeltaTime)
{
	for (size_t i = 0; i < m_Instances.size(); i++)
	{
		if (!m_Instances[i]->hasUpdate) continue;

		m_Instances[i]->PrepareMethod("Update");
		lua_pushnumber(State, DeltaTime);
		m_Instances[i]->CallMethod(1);
	}
}

void ScriptManager::InstanceUpdate()
{
	for (size_t i = 0; i < m_Instances.size(); i++)
	{
		if (m_Instances[i]->gc == true)
		{
			//DeleteInstance(m_Instances[i]->ref_idx);
			m_Instances[i]->DeleteObject();
			delete m_Instances[i];
			m_Instances.erase(m_Instances.begin() + i);
		}
	}
}

LuaScript* ScriptManager::ScriptInstance(std::string class_name)
{
	bool class_found = false;
	for(size_t i =0;i < m_LoadedScripts.size();i++)
	{
		if(m_LoadedScripts[i].m_ClassName == class_name)
		{
			class_found = true;
			break;
		}
	}

	if (!class_found) return nullptr;

	LuaScript* instance = new LuaScript(State, class_name);
	if(!instance->usable)
	{
		instance->DeleteObject();
		delete instance;
		return nullptr;
	}

	m_Instances.push_back(instance);
	return instance;
}

LuaScript* ScriptManager::ScriptInstanceClass(unsigned int id, std::string class_name)
{
	LuaScript* script = ScriptInstance(class_name);
	script->entity_id = id;
	script->PrepareMethod("_SetupTheScriptComponent");
	lua_pushnumber(State, id);
	script->CallMethod(1);

	return script;
}


void ScriptManager::DeleteScript(unsigned int id)
{
	for (size_t i = 0; i < m_Instances.size(); i++)
	{
		if (m_Instances[i]->ref_idx == id)
		{
			m_Instances[i]->DeleteObject();
			delete m_Instances[i];
			m_Instances.erase(m_Instances.begin() + i);
		}
	}
}

void ScriptManager::ClearScripts()
{
	for (size_t i = 0; i < m_Instances.size(); i++)
	{
		m_Instances[i]->DeleteObject();
		delete m_Instances[i];
	}
	m_Instances.clear();
}

void ScriptManager::ReloadInterpreter()
{
	m_RecompileScripts = true;

	if (initialized) {
		for (size_t i = 0; i < m_Instances.size(); i++)
		{
			m_Instances[i]->DeleteObject();
		}
		lua_close(State);
	}

	Init();
}

void ScriptManager::ImportScriptsFromResources(std::string path)
{
	m_LoadedScripts.clear();

	struct dirent** files;

	int n = scandir(path.c_str(), &files, nullptr, alphasort);
	if (n > 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (files[i]->d_type == DT_REG)
			{
				std::string fname = files[i]->d_name;

				int point_pos = 0;
				for (size_t i = fname.length() - 1; i > 0; i--)
				{
					if (fname[i] == '.')
					{
						point_pos = i;
						break;
					}
				}
				std::string tp = fname.substr(point_pos + 1, std::string::npos);
				fname = fname.substr(0, point_pos);

				if (tp == "lua" || tp == "LUA")
				{
					tp = path; tp += "\\"; tp += files[i]->d_name;
					AddLuaScript(tp, fname.c_str());
					//std::cout << "script : " << tp << std::endl;
				}
			}
			free(files[i]);
		}
		free(files);
	}
}



void ScriptManager::RecompileScripts(bool reinstance)
{
	for (size_t i = 0; i < m_Instances.size(); i++)
		m_Instances[i]->CacheVarsValues();

	LoadMainScripts();
	ImportScriptsFromResources("resources/scripts");
	// recompile scripts
	for (size_t i = 0; i < m_LoadedScripts.size(); i++)
	{
		LoadLuaFile(m_LoadedScripts[i].m_Path, m_LoadedScripts[i].m_ClassName);
	}
	if (reinstance)
		ReinstanceScript();

	m_RecompileScripts = false;
}

void ScriptManager::ReinstanceScript()
{
	for (size_t i = 0; i < m_Instances.size(); i++)
	{
		m_Instances[i]->m_State = State;
		m_Instances[i]->CreateObject(m_Instances[i]->class_name.c_str());
		m_Instances[i]->ResetVarsValues();
	}
}

bool ScriptManager::AddLuaScript(std::string& path, std::string class_name)
{
	for(size_t i =0;i < m_LoadedScripts.size();i++)
	{
		if(m_LoadedScripts[i].m_Path == path)
		{
			ENGINE_ERROR("Script already added!");
			return false;
		}
	}
	m_LoadedScripts.push_back(LuaScriptProps(path,class_name));
	m_LoadedScripts[m_LoadedScripts.size() - 1].valide = true;
	return true;
}

bool ScriptManager::LoadLuaFile(std::string& path, std::string class_name)
{
	if(!m_RecompileScripts)
	{
		for(size_t i =0;i < m_LoadedScripts.size();i++)
		{
			if(m_LoadedScripts[i].m_Path == path)
			{
				ENGINE_ERROR("Script already loaded!");
				return true;
			}
		}
	}

	bool svalid = true;

	std::ifstream infile(path);
	std::stringstream strs;
	strs << infile.rdbuf();
	std::string str = strs.str();
	infile.close();

	ReplaceSTR(str, "//", "--");
	ReplaceSTR(str, "!=", "~=");
	ReplaceSTR(str, "@:", "self:");
	ReplaceSTR(str, "::", "self:");
	ReplaceSTR(str, "@", "self.");
	ReplaceSTR(str, "else if", "elseif");
	ReplaceSTR(str, ")\n{", ")\n");
	ReplaceSTR(str, "};\n", "end");

	if(luaL_loadstring(State,str.c_str()))
	{
		svalid = false;
		std::cout << "error : ";
		std::cout << lua_tostring(State, -1) << std::endl;
		lua_pop(State, 1);
	}

	if (svalid && lua_pcall(State, 0, LUA_MULTRET, 0)) {
		svalid = false;
		//std::cerr << "Something went wrong during execution" << std::endl;
		std::cout << "(execution) error : ";
		std::cout << lua_tostring(State, -1) << std::endl;
		lua_pop(State, 1);
	}

	if(svalid)
	{
		bool found = false;
		for(size_t i = 0; i < m_LoadedScripts.size();i++)
		{
			if(m_LoadedScripts[i].m_Path == path)
			{
				m_LoadedScripts[i].valide = true;
				found = true;
				return true;
			}
		}
		if(!found)
		{
			m_LoadedScripts.push_back(LuaScriptProps(path, class_name));
			m_LoadedScripts[m_LoadedScripts.size() - 1].valide = true;
		}
	}
	else
	{
		for (size_t i = 0; i < m_LoadedScripts.size(); i++)
		{
			if (m_LoadedScripts[i].m_Path == path)
			{
				m_LoadedScripts[i].valide = false;
			}
		}
	}
	return svalid;
}

void ScriptManager::Close()
{
	if (!initialized) return;

	ClearScripts();
	// Close lua
	lua_close(State);
}
