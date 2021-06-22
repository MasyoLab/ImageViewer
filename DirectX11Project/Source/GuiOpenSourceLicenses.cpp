//==========================================================================
// ÉâÉCÉZÉìÉXÉäÉXÉg [GuiOpenSourceLicenses.cpp]
// author : MasyoLab
//==========================================================================
#include "GuiOpenSourceLicenses.h"

GuiOpenSourceLicenses::GuiOpenSourceLicenses()
{
	SetObjectName("OpenSourceLicenses");
}

GuiOpenSourceLicenses::~GuiOpenSourceLicenses()
{
}

void GuiOpenSourceLicenses::GUI(float width)
{
	if (mdx_imgui::BeginMenu("Open Source Licenses"))
	{
		if (mdx_imgui::MenuItem("DirectXTex"))
			std::system("start https://github.com/microsoft/DirectXTex");
		mdx_imgui::SetNextWindowSize({ width,-1 });
		if (mdx_imgui::IsItemHovered())
		{
			mdx_imgui::BeginTooltip();
			mdx_imgui::TextWrapped("The MIT License (MIT)");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("Copyright (c) 2011-2019 Microsoft Corp");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the ÅhSoftwareÅh), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,");
			mdx_imgui::TextWrapped("publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("THE SOFTWARE IS PROVIDED ÅhAS ISÅh, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.");
			mdx_imgui::TextWrapped("IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
			mdx_imgui::TextWrapped("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("You can contact the author at :");
			mdx_imgui::TextWrapped("DirectXTex source repository : https://github.com/microsoft/DirectXTex");
			mdx_imgui::EndTooltip();
		}

		mdx_imgui::Separator();
		if(mdx_imgui::MenuItem("Lumino.Math"))
			std::system("start https://github.com/lriki/Lumino.Math");
		mdx_imgui::SetNextWindowSize({ width,-1 });
		if (mdx_imgui::IsItemHovered())
		{
			mdx_imgui::BeginTooltip();
			mdx_imgui::TextWrapped("The Zlib License (Zlib)");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("Copyright(c) 2015 - 2019");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.");
			mdx_imgui::TextWrapped("2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.");
			mdx_imgui::TextWrapped("3. This notice may not be removed or altered from any source distribution.");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("You can contact the author at :");
			mdx_imgui::TextWrapped("Lumino.Math source repository : https://github.com/lriki/Lumino.Math");
			mdx_imgui::EndTooltip();
		}

		mdx_imgui::Separator();
		if(mdx_imgui::MenuItem("dear imgui"))
			std::system("start https://github.com/ocornut/imgui");
		mdx_imgui::SetNextWindowSize({ width,-1 });
		if (mdx_imgui::IsItemHovered())
		{
			mdx_imgui::BeginTooltip();
			mdx_imgui::TextWrapped("The MIT License (MIT)");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("Copyright(c) 2014 - 2019 Omar Cornut");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the ÅhSoftwareÅh), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,");
			mdx_imgui::TextWrapped("publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("THE SOFTWARE IS PROVIDED ÅhAS ISÅh, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.");
			mdx_imgui::TextWrapped("IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
			mdx_imgui::TextWrapped("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("You can contact the author at :");
			mdx_imgui::TextWrapped("dear imgui source repository : https://github.com/ocornut/imgui");
			mdx_imgui::EndTooltip();
		}

		mdx_imgui::Separator();
		if(mdx_imgui::MenuItem("Native File Dialog"))
			std::system("start https://github.com/mlabbe/nativefiledialog");
		mdx_imgui::SetNextWindowSize({ width,-1 });
		if (mdx_imgui::IsItemHovered())
		{
			mdx_imgui::BeginTooltip();
			mdx_imgui::TextWrapped("The Zlib License (Zlib)");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("Copyright(c) 2014 - 2019");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.");
			mdx_imgui::TextWrapped("2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.");
			mdx_imgui::TextWrapped("3. This notice may not be removed or altered from any source distribution.");
			mdx_imgui::Text("");
			mdx_imgui::TextWrapped("You can contact the author at :");
			mdx_imgui::TextWrapped("Native File Dialog source repository : https://github.com/mlabbe/nativefiledialog");
			mdx_imgui::EndTooltip();
		}

		mdx_imgui::EndMenu();
	}
}
