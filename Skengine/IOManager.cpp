#include "IOManager.h"
#include <fstream>
namespace Skengine{
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		file.seekg(0, std::ios::end);
		int fileSize = file.tellg();

		file.seekg(0, std::ios::beg); //reset to the beginning of the file

		fileSize -= file.tellg(); //remove header byte length from filesize

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;

	}
}