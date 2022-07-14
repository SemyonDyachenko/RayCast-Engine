#pragma once

#include <filesystem>
#include <string>

#include "PlatformUtils.h"


static const  std::string CORE_TEXTURE_PATH = "resources/images/textures/";
static const std::string CORE_MATERIAL_PATH = "resources/images/materials/";
static const std::string CORE_DEFAULT_MODEL_PATH = "resources/vanilla/obj/";

class FilesystemUtils {
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

	static std::string GetFilenameFromPath(std::string path)
	{
		const std::filesystem::path systemPath = path;
		const std::string filename = systemPath.filename().stem().string();
		return filename;
	}

	static bool FileCopy(std::string existingPath,std::string newPath)
	{
		std::filesystem::path m_path = existingPath;
		std::string filename = m_path.filename().string();
		std::string newFilePath = newPath;

		std::ifstream in(existingPath, std::ios_base::in | std::ios_base::binary);
		std::ofstream out(newFilePath, std::ios_base::out | std::ios_base::binary);

		char buf[8192];

		do {

			in.read(&buf[0], 8192);

			out.write(&buf[0], in.gcount());

		} while (in.gcount() > 0);

		in.close();

		out.close();

		return true;
	}

	static bool NewFile(std::string path,std::string baseContent = "")
	{
		std::ofstream out(path);
		
		if (baseContent.length() > 0)
			out << baseContent;
		
		out.close();

		return true;
	}
};