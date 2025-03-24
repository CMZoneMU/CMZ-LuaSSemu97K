#pragma once


class CElemental
{
public:
	CElemental();
	~CElemental();

	void				DrawBox(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float Arg5, int Arg6);
	bool				DrawButton(float PosX, float PosY, float TextX, float TextY, float SizeButton, int SizeButtonY, char* ButtonText);
	DWORD				LockMouse;
	bool				LockButtonHover;

	void				DrawTexts(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
private:

};
extern CElemental gElemental;

void pSetTextColor(DWORD color);
void pSetBGTextColor(DWORD bkcolor);