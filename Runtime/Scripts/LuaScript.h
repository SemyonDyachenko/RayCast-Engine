#ifndef LUA_SCRIPT_H
#define LUA_SCRIPT_H

#include <string>
#include <glm.hpp>
#include <vector>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


enum ScriptVarType
{
	Null,
	Int,
	String,
	Float,
	Bool,
	Table,
	USERDATA,
	ASSET,
	VEC3
};

struct SavedScriptVar
{
	ScriptVarType type;
	std::string name;

	std::string str;
	float f;
	int i;
	bool b;
	glm::vec3 v3;
};


struct ScriptVar
{
	ScriptVarType type;
	std::string name;

	ScriptVar()
	{
		type = Null;
		name = "";
	}
	ScriptVar(ScriptVarType _type, std::string _name)
	{
		type = _type;
		name = _name;
	}
};


class LuaScript
{

public:
	LuaScript();
	LuaScript(lua_State * state);
	LuaScript(lua_State * state,std::string className);
	~LuaScript();
public:
	

	void CreateObject(std::string className);

	void DeleteObject();
	
	void CallMethod(std::string methodName);
	
	void Use();
	
	void PrepareMethod(std::string methodName);

	void CallMethod(int arg_length);

	void RegisterPublicMembers();
	
	void SetVar(std::string var_name, int val);
	void SetVar(std::string var_name, float val);
	void SetVar(std::string var_name, bool val);
	void SetVar(std::string var_name, std::string val);

	bool HasVar(std::string var_name, ScriptVarType var_type);
	bool HasFunc(std::string name);
	
	glm::vec3 GetVec3(std::string& var_name);
	void SetVec3(std::string& var_name, glm::vec3& v);

	void CheckVarType(std::string var_name);

	bool GetVarBool(std::string var_name);
	int GetVarInt(std::string var_name);
	float GetVarFloat(std::string var_name);
	std::string GetVarString(std::string var_name);
	
	void CacheVarsValues();
	void ResetVarsValues();
public:
	std::string class_name;
	std::string prep_method;


	lua_State* m_State;
	
	int ref_idx;
	
	bool gc = false;

	unsigned int entity_id = -2;
	bool hasUpdate = false;
	bool hasStart = false;
	bool hasDestroy = false;

	std::vector<ScriptVar> properties;
	std::vector<SavedScriptVar> cached_properties;
	std::vector<std::string> functions;
	
	bool usable = false;
};

#endif