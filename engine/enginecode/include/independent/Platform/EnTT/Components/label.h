/* \file label.h */
#pragma once

namespace Engine
{
	class LabelComponent
	{
	public:
		LabelComponent(std::string Label) : label(Label) {} //!< Constructor, initialises label variable
		std::string label; //!< Label, stored as a string
	};

	class TagComponent
	{
	public:
		TagComponent(const char* Tag) : tag(Tag) {} //!< Constructor, initialises tag varaible
		const char* tag; //!< tag variable, stored as a const char pointer
	};
}