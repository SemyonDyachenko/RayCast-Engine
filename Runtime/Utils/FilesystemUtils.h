#pragma once

#include <filesystem>
#include <string>

#include "PlatformUtils.h"


namespace RayCast {

	static const  std::string CORE_TEXTURE_PATH = "resources/images/textures/";
	static const std::string CORE_MATERIAL_PATH = "resources/images/materials/";
	static const std::string CORE_DEFAULT_MODEL_PATH = "resources/vanilla/obj/";

	class RAYCAST_API FilesystemUtils {
	public:

		virtual ~FilesystemUtils() = default;

		static std::string GetTexturePath()
		{
			const std::string pathString = FileDialogs::OpenFile("Image File (*.jpg)\0*.jpg\0(*.png)\0*.png\0");
			const std::filesystem::path systemPath = pathString;
			const std::string filename = systemPath.filename().string();

			std::string texturePath = CORE_TEXTURE_PATH + filename;

			return texturePath;
		}

		static std::string GetMaterialPath()
		{
			const std::string pathString = FileDialogs::OpenFile("Image File (*.png)\0*.png\0(*.jpg)\0*.jpg\0");
			const std::filesystem::path systemPath = pathString;
			const std::string filename = systemPath.filename().string();

			std::string materialPath = CORE_MATERIAL_PATH + filename;

			return materialPath;
		}

		static std::string GetModelPath()
		{
			const std::string pathString = FileDialogs::OpenFile("Image File (*.jpg)\0*.jpg\0(*.png)\0*.png\0");
			const std::filesystem::path systemPath = pathString;
			const std::string filename = systemPath.filename().string();

			std::string materialPath = CORE_DEFAULT_MODEL_PATH + filename;

			return materialPath;
		}

	};

}