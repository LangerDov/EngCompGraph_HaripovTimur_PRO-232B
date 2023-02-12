#pragma once

#include "str.h"

enum font_attr_t
{

};

class Font
{
public:
	Font();
	~Font();
	bool LoadFromFile(UString path);
	bool RenderFont(font_attr_t attr);
	font_attr_t GetAttr();
	void Draw(double x, double y, UString text);
	void SetFontScale(double scale);
	double GetFontScale();
	void GetTextSize(UString text, double* width, double* height);
private:
	UString path;
	font_attr_t attr;
	double scale;
};