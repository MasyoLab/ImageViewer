//==========================================================================
// .csoì«Ç›çûÇ› [LoadCso.cpp]
// author : MasyoLab
//==========================================================================
#include "LoadCso.h"

_MDX_COMMON_BEGIN

LoadCso::LoadCso(const std::string& cso_file_path) :
	cso_size(0), cso_data(nullptr)
{
	size_t start_pos = 0;
	size_t end_pos = 0;

	std::ifstream in(cso_file_path, std::ios::binary);
	if (!in)
	{
		in.close();
		return;
	}

	in.seekg(0, std::fstream::end);
	end_pos = (size_t)in.tellg();
	in.clear();

	in.seekg(0, std::fstream::beg);
	start_pos = (size_t)in.tellg();

	cso_size = end_pos - start_pos;
	cso_data = new char[cso_size];
	in.read(cso_data, cso_size);

	in.close();
}

LoadCso::~LoadCso()
{
	if (cso_data != nullptr)
		delete[] cso_data;
	cso_data = nullptr;
}

const char* LoadCso::GetData() const
{
	return cso_data;
}

size_t LoadCso::GetSize() const
{
	return cso_size;
}

_MDX_COMMON_END