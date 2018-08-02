#include "stdafx.h"
#include "Renderer.h"
#include <iostream>

//template<typename handler>
//ricardo::Renderer<handler>::Renderer(Scene & scene)
//{
//}

template<typename handler>
int ricardo::Renderer<handler>::render()
{
	return static_cast<handler*>(this)->render();
}

int ricardo::DX11Handler::render()
{
	std::cout << "DX11" << std::endl;
	return 0;
}
