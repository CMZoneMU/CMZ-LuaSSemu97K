#include "stdafx.h"
#include "InterfaceElemental.h"
#include "Offsets.h"
#include "Interface.h"
#include "Util.h"
#include "Protect.h"
#include "Enums.h"

CElemental gElemental;

CElemental::CElemental()
{
	this->LockMouse = 0;
	this->LockButtonHover = 0;
}


CElemental::~CElemental()
{
}


void CElemental::DrawBox(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float Arg5, int Arg6)
{
	float Red = (float)((bkcolor & 0xff000000) >> 24) / 255.0f;
	float Green = (float)((bkcolor & 0x00ff0000) >> 16) / 255.0f;
	float Blue = (float)((bkcolor & 0x0000ff00) >> 8) / 255.0f;
	float Alpha = (float)(bkcolor & 0x000000ff) / 255.0f;
	EnableAlphaTest(1);
	if (bkcolor)
	{
		glColor4f(Red, Green, Blue, Alpha);
		pDrawFormat(PosX, PosY, Width + 6.5, Height + 5, Arg5, Arg6); //central
	}
	float RightX = PosX - 2.0f;
	float LeftX = (PosX + Width) - 2.0f;
	float TopY = PosY - 2.0f;
	float DownY = (PosY + Height) - 2.0f;
	bool horizontal = true;
	bool vertical = true;
	//--
	float IniciarX = PosX - 2.0f;
	float w = 14.0f;
	//--
	float IniciarY = PosY - 2.0f;
	float H = 14.0f;

	EnableAlphaTest(true);
	glColor3f(1.0, 1.0, 1.0);

	while (vertical || horizontal)
	{
		if (vertical)
		{
			IniciarX += 14.0f;

			if ((IniciarX + w) > LeftX)
			{
				vertical = false;
				w = LeftX - IniciarX;
			}
			RenderBitmap(1344, IniciarX, TopY, w, 14.0f, 0, 0, 14.0f / 16.0f, 14.0f / 16.0f, 1, 1);

			RenderBitmap(1345, IniciarX, DownY, w, 14.0f, 0, 0, 14.0f / 16.0f, 14.0f / 16.0f, 1, 1);
		}
		//-- abajo
		if (horizontal)
		{
			IniciarY += 14.0f;

			if ((IniciarY + H) > DownY)
			{
				horizontal = false;
				H = DownY - IniciarY;
			}

			RenderBitmap(1346, RightX, IniciarY, 14.0f, H, 0, 0, 14.0f / 16.0f, 14.0f / 16.0f, 1, 1);

			RenderBitmap(1347, LeftX, IniciarY, 14.0f, H, 0, 0, 14.0f / 16.0f, 14.0f / 16.0f, 1, 1);
		}
	}
	RenderBitmap(1340, RightX, TopY, 14.0f, 14.0f, 0, 0, 14.0f / 16.0f, 14.0f / 16.0f, 1, 1);

	RenderBitmap(1341, LeftX, TopY, 14.0f, 14.0f, 0, 0, 14.0f / 16.0f, 14.0f / 16.0f, 1, 1);

	RenderBitmap(1342, RightX, DownY, 14.0f, 14.0f, 0, 0, 14.0f / 16.0f, 14.0f / 16.0f, 1, 1);

	RenderBitmap(1343, LeftX, DownY, 14.0f, 14.0f, 0, 0, 14.0f / 16.0f, 14.0f / 16.0f, 1, 1);

	DisableAlphaBlend();
	EnableAlphaTest(0);
}

bool CElemental::DrawButton(float PosX, float PosY, float TextX, float TextY, float SizeButton, int SizeButtonY, char* ButtonText)
{
	EnableAlphaTest(true);
	glColor3f(1.0, 1.0, 1.0);
	//============Button
	float SizeButtonW = SizeButton;
	float SizeButtonH = (SizeButton * 20) / 100;
	if (SizeButtonY != 0)
	{
		SizeButtonW = SizeButtonY;
	}

	float StartX = PosX;
	float StartY = PosY;
	bool mreturn = false;

	//=====================Button 1
	if (pCheckMouseOver(StartX, StartY, SizeButton, SizeButtonY) == 1 && !this->LockButtonHover)
	{
		glColor3f(1.0f, 0.6742f, 0.15f);
		if (GetTickCount() - gInterface.Data[eWindowElemental].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(0.72f, 0.438f, 0.0432f);


				gInterface.Data[eWindowElemental].EventTick = GetTickCount();
				mreturn = true;
			}
		}
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);

	}
//	if (gProtect.m_MainInfo.ModeUpgrade == 1)
//	{

	RenderBitmap(1563, StartX, StartY, SizeButton, SizeButtonY, 0.0, 0.0, 170.0f / 256.0f, 28.0f / 32.0f, 1, 1);
	gInterface.DrawFormat(eGold, StartX + TextX, StartY + TextY, SizeButton, 3, ButtonText);
	//}
	/*
	else
	{
		RenderBitmap(1595, StartX, StartY, SizeButton, SizeButtonY, 0.0, 0.0, 0.765, 0.9375, 1, 1);
		gInterface.DrawFormat(eWhite, StartX + TextX, StartY + TextY, SizeButton, 3, ButtonText);
	}
	*/
	//=====================================
	glColor3f(1.0f, 1.0f, 1.0f); //Xoa mau
	DeleteObject(ButtonText);
	DisableAlphaBlend();
	EnableAlphaTest(0);
	return mreturn;
}



typedef void(__thiscall* SetColorFunction)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h);

// Invocar pSetTextColor
void pSetTextColor(DWORD color)
{
	BYTE r = (color & 0xFF000000) >> 24;
	BYTE g = (color & 0x00FF0000) >> 16;
	BYTE b = (color & 0x0000FF00) >> 8;
	BYTE a = (color & 0x000000FF);

	SetTextColor = Color4b(r, g, b, a);
	
}

// Invocar pSetBGTextColor
void pSetBGTextColor(DWORD bkcolor)
{
	BYTE r = (bkcolor & 0xFF000000) >> 24;
	BYTE g = (bkcolor & 0x00FF0000) >> 16;
	BYTE b = (bkcolor & 0x0000FF00) >> 8;
	BYTE a = (bkcolor & 0x000000FF);


	SetBackgroundTextColor = Color4b(r, g, b, a);
	
}

void CElemental::DrawTexts(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...)
{

	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char* Line = strtok(Buff, "\n");

	SelectObject(m_hFontDC, font);


	while (Line != NULL)
	{

		pSetBGTextColor(bkcolor);
		pSetTextColor(color);
		EnableAlphaTest(true);
		RenderText(PosX, PosY, Line, 0, 0, 0);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}


}