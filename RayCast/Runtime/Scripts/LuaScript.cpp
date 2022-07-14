#include "LuaScript.h"

#include <iostream>

LuaScript::LuaScript()
{
}

LuaScript::LuaScript(lua_State* state)
{
	m_State = state;
}

LuaScript::LuaScript(lua_State* state, std::string className)
{
	m_State = state;
	CreateObject(className);
}

LuaScript::~LuaScript()
{
	DeleteObject();
}

void LuaScript::CreateObject(std::string className)
{
	lua_newtable(m_State);
	lua_getglobal(m_State, className.c_str());
	lua_pcall(m_State, 0, 1, 0);
	ref_idx = luaL_ref(m_State, LUA_REGISTRYINDEX);
	usable = true;
	class_name = std::string(className);

	RegisterPublicMembers();

	if (entity_id >= 0)
	{
		PrepareMethod("_SetupTheScriptComponent");
		lua_pushnumber(m_State, entity_id);
		CallMethod(1);
	}
	
}

void LuaScript::DeleteObject()
{
	luaL_unref(m_State, LUA_REGISTRYINDEX, ref_idx);
	usable = false;
}

void LuaScript::CallMethod(std::string methodName)
{
	if (!usable)
		return;
	//std::cerr << "CallMethod : " << methodName << "\n";
	lua_rawgeti(m_State, LUA_REGISTRYINDEX, ref_idx);
	lua_getfield(m_State, -1, methodName.c_str());
	lua_pushvalue(m_State, -2);
	if (lua_pcall(m_State, 1, 0, 0)) {
		std::cerr << "execution error : ";
		std::cerr << lua_tostring(m_State, -1) << std::endl;
		lua_pop(m_State, 1);
	}
	lua_pop(m_State, 0);
}

void LuaScript::Use()
{
	lua_rawgeti(m_State, LUA_REGISTRYINDEX, ref_idx);
}

void LuaScript::PrepareMethod(std::string methodName)
{
	prep_method = methodName;

	lua_rawgeti(m_State, LUA_REGISTRYINDEX, ref_idx);
	lua_getfield(m_State, -1, prep_method.c_str());
	lua_pushvalue(m_State, -2);
}

void LuaScript::CallMethod(int arg_length)
{
	if (lua_pcall(m_State, arg_length + 1, 0, 0)) {
		std::cerr << "execution error : ";
		std::cerr << lua_tostring(m_State, -1) << std::endl;
		lua_pop(m_State, 1);
	}
	lua_pop(m_State, 0);
}

void LuaScript::RegisterPublicMembers()
{

	Use();
	lua_getfield(m_State, -1, "_");

	if (!properties.empty())
		properties.clear();
	functions.clear();

	lua_pushnil(m_State);

	while (lua_next(m_State, -2) != 0)
	{
		//std::cout << luaL_typename(L, -2) << " = " << luaL_typename(L, -1) << std::endl;
		//std::cout << lua_tostring(L, -2) << " = " << lua_tonumber(L, -1) << std::endl;
		std::string var_name = lua_tostring(m_State, -2);

		if (lua_isfunction(m_State, -1) && var_name == "Start")
			hasStart = true;
		if (lua_isfunction(m_State, -1) && var_name == "Update")
			hasUpdate = true;
		if (lua_isfunction(m_State, -1) && var_name == "Destroy")
			hasDestroy = true;

		if (var_name[0] == '_' || lua_isfunction(m_State, -1))
		{
			lua_pop(m_State, 1);
			continue;
		}

		if (lua_isinteger(m_State, -1))
		{
			properties.push_back(ScriptVar(Int, var_name));
		}
		else if (lua_isnumber(m_State, -1))
		{
			properties.push_back(ScriptVar(Float, var_name));
		}
		else if (lua_isstring(m_State, -1))
		{
			properties.push_back(ScriptVar(String, var_name));
		}
		else if (lua_isboolean(m_State, -1))
		{
			properties.push_back(ScriptVar(Bool, var_name));
		}
		else if (lua_istable(m_State, -1))
		{
			properties.push_back(ScriptVar(Table, var_name));
		}
		else if (lua_isuserdata(m_State, -1))
		{
			properties.push_back(ScriptVar(USERDATA, var_name));
		}
		else if (lua_isfunction(m_State, -1))
			functions.push_back(var_name);
		else
			properties.push_back(ScriptVar(Null, var_name));
		
		lua_pop(m_State, 1);
	}


	for (size_t i = 0; i < properties.size(); i++)
	{
		if (properties[i].type == USERDATA)
		{
			lua_getglobal(m_State, "AssetType");
			if (lua_isfunction(m_State, -1))
			{
				Use();
				lua_pushstring(m_State, properties[i].name.c_str());
				lua_pcall(m_State, 2, 1, 0);
				std::string asset_type = lua_tostring(m_State, -1);
				//std::cout << "||" << asset_type << "||";
				if (asset_type == "asset")
					properties[i].type = ASSET;
				else if (asset_type == "VEC3")
					properties[i].type = VEC3;
				lua_pop(m_State, 0);
			}
		}
	}
}

void LuaScript::SetVar(std::string var_name, int val)
{
	Use();
	// Type check
	lua_getfield(m_State, -1, var_name.c_str());
	if (!lua_isnumber(m_State, -1))	return;

	// Set the field
	PrepareMethod("set");
	lua_pushstring(m_State, var_name.c_str());
	lua_pushinteger(m_State, val);
	CallMethod(2);
}

void LuaScript::SetVar(std::string var_name, float val)
{
	Use();
	// Type check
	lua_getfield(m_State, -1, var_name.c_str());
	if (!lua_isnumber(m_State, -1))	return;

	// Set the field
	PrepareMethod("set");
	lua_pushstring(m_State, var_name.c_str());
	lua_pushnumber(m_State, val);
	CallMethod(2);
}

void LuaScript::SetVar(std::string var_name, bool val)
{
	Use();
	// Type check
	lua_getfield(m_State, -1, var_name.c_str());
	if (!lua_isboolean(m_State, -1))	return;

	// Set the field
	PrepareMethod("set");
	lua_pushstring(m_State, var_name.c_str());
	lua_pushboolean(m_State, (int)val);
	CallMethod(2);
}

void LuaScript::SetVar(std::string var_name, std::string val)
{
	Use();
	// Type check
	lua_getfield(m_State, -1, var_name.c_str());
	if (!lua_isstring(m_State, -1))	return;

	// Set the field
	PrepareMethod("set");
	lua_pushstring(m_State, var_name.c_str());
	lua_pushstring(m_State, val.c_str());
	CallMethod(2);
}

bool LuaScript::HasVar(std::string var_name, ScriptVarType var_type)
{
	for (size_t i = 0; i < properties.size(); i++)
	{
		if (properties[i].name == var_name && properties[i].type == var_type)
			return true;
	}
	return false;
}

bool LuaScript::HasFunc(std::string name)
{
	for (size_t i = 0; i < functions.size(); i++)
		if (functions[i] == name)
			return true;
	return false;
}

glm::vec3 LuaScript::GetVec3(std::string& var_name)
{
	float xx, yy, zz;
	for (size_t i = 0; i < 3; i++)
	{
		lua_getglobal(m_State, "GetVec3XYZ");
		Use();
		lua_pushstring(m_State, var_name.c_str());
		lua_pushinteger(m_State, i);
		lua_pcall(m_State, 3, 1, 0);

		if (i == 0)	xx = (float)lua_tonumber(m_State, -1);
		else if (i == 1)	yy = (float)lua_tonumber(m_State, -1);
		else zz = (float)lua_tonumber(m_State, -1);

		lua_pop(m_State, 0);
	}
	return glm::vec3(xx, yy, zz);
}

void LuaScript::SetVec3(std::string& var_name, glm::vec3& v)
{
	for (size_t i = 0; i < 3; i++)
	{
		lua_getglobal(m_State, "SetVec3XYZ");
		Use();
		lua_pushstring(m_State, var_name.c_str());
		lua_pushinteger(m_State, i);

		if (i == 0)	lua_pushnumber(m_State, v.x);
		else if (i == 1)	lua_pushnumber(m_State, v.y);
		else lua_pushnumber(m_State, v.z);

		lua_pcall(m_State, 4, 1, 0);
		lua_pop(m_State, 0);
	}
}

void LuaScript::CheckVarType(std::string var_name)
{
	Use();
	lua_getfield(m_State, -1, var_name.c_str());
	for (size_t i = 0; i < properties.size(); i++)
	{
		if (properties[i].name == var_name)
		{
			if (lua_isnumber(m_State, -1))
				properties[i].type = Float;

			else if (lua_isstring(m_State, -1))
				properties[i].type = String;

			else if (lua_isboolean(m_State, -1))
				properties[i].type = Bool;
			else
				properties[i].type = Null;

			break;
		}
	}
}

bool LuaScript::GetVarBool(std::string var_name)
{
	Use();
	lua_getfield(m_State, -1, var_name.c_str());

	if (!lua_isboolean(m_State, -1))
	{
		CheckVarType(var_name);
		return false;
	}

	int luavar = lua_toboolean(m_State, -1);
	lua_pop(m_State, 1);

	if (luavar == 1) return true;
	else return false;
}

int LuaScript::GetVarInt(std::string var_name)
{
	Use();
	lua_getfield(m_State, -1, var_name.c_str());

	if (!lua_isnumber(m_State, -1))
	{
		CheckVarType(var_name);
		return 0;
	}

	int luavar = (int)lua_tointeger(m_State, -1);
	lua_pop(m_State, 1);
	return luavar;
}

float LuaScript::GetVarFloat(std::string var_name)
{
	Use();
	lua_getfield(m_State, -1, var_name.c_str());

	if (!lua_isnumber(m_State, -1))
	{
		CheckVarType(var_name);
		return 0.0f;
	}

	float luavar = (float)lua_tonumber(m_State, -1);
	lua_pop(m_State, 1);
	return luavar;
}

std::string LuaScript::GetVarString(std::string var_name)
{
	Use();
	lua_getfield(m_State, -1, var_name.c_str());

	if (!lua_isstring(m_State, -1))
	{
		CheckVarType(var_name);
		return std::string("");
	}

	std::string luavar = lua_tostring(m_State, -1);
	lua_pop(m_State, 1);
	return luavar;
}

void LuaScript::CacheVarsValues()
{
	for (size_t i = 0; i < properties.size(); i++)
	{
		if (properties[i].type == ScriptVarType::Null || properties[i].type == ScriptVarType::Table)
			continue;

		cached_properties.emplace_back();
		int o = cached_properties.size() - 1;
		cached_properties[o].type = properties[i].type;
		cached_properties[o].name = properties[i].name;

		if (properties[i].type == ScriptVarType::Float)
			cached_properties[o].f = GetVarFloat(properties[i].name.c_str());

		else if (properties[i].type == ScriptVarType::Bool)
			cached_properties[o].b = GetVarBool(properties[i].name.c_str());
		
		else if (properties[i].type == ScriptVarType::Int)
			cached_properties[o].i = GetVarInt(properties[i].name.c_str());

		else if (properties[i].type == ScriptVarType::String)
			cached_properties[o].str = GetVarString(properties[i].name.c_str());

		else if (properties[i].type == ScriptVarType::VEC3)
			cached_properties[o].v3 = GetVec3(properties[i].name);

		//else if (properties[i].type == ScriptVarType::ASSET)
		//	cached_properties[o].str = GetAssetPath(properties[i].name);
	}
}

void LuaScript::ResetVarsValues()
{
	for (size_t i = 0; i < cached_properties.size(); i++)
	{
		if (cached_properties[i].type == ScriptVarType::Float)
			SetVar(cached_properties[i].name.c_str(), cached_properties[i].f);
		else if (cached_properties[i].type == ScriptVarType::Int)
			SetVar(cached_properties[i].name.c_str(), cached_properties[i].i);
		else if (cached_properties[i].type == ScriptVarType::Bool)
			SetVar(cached_properties[i].name.c_str(), cached_properties[i].b);
		else if (cached_properties[i].type == ScriptVarType::String)
			SetVar(cached_properties[i].name.c_str(), cached_properties[i].str);
		else if (cached_properties[i].type == ScriptVarType::VEC3)
			SetVec3(cached_properties[i].name, cached_properties[i].v3);
	}
	cached_properties.clear();
	cached_properties.shrink_to_fit();
}
