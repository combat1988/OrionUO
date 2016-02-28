/****************************************************************************
**
** MapObject.h
**
** Copyright (C) September 2015 Hotride
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
*****************************************************************************
*/
//---------------------------------------------------------------------------
#ifndef MapObjectH
#define MapObjectH
//---------------------------------------------------------------------------
//����� ������� �������
class TVector
{
private:
	//����������
	double m_X;
	double m_Y;
	double m_Z;

public:
	TVector(double x = 0, double y = 0, double z = 0);
	~TVector() {}

	//����������� ��������
	void Link(TVector &v);

	//��������� ���������
	void Link(double x, double y, double z);

	//����������� ��������
	void Add(TVector &v);

	//����������� ���������
	void Add(double x, double y, double z);

	//������� ��������
	void Merge(TVector &v);

	//������� ���������
	void Merge(double x, double y, double z);

	//������������
	void Normalize();
	
	SETGET(double, X);
	SETGET(double, Y);
	SETGET(double, Z);
};
//---------------------------------------------------------------------------
//����� ������� �����
class TMapObject : public TRenderWorldObject
{
public:
	TMapObject(RENDER_OBJECT_TYPE type, DWORD serial, WORD graphic, WORD color, short x, short y, char z);
	virtual ~TMapObject();
};
//---------------------------------------------------------------------------
//����� ���������
class TLandObject : public TMapObject
{
protected:
	//���������� �������� ������
	RECT m_Rect;

	//����������� Z ����������
	char m_MinZ;

	//���� ����������� (true - �������� �� texmaps, false - �� art.mul)
	bool m_IsStretched;
public:
	TLandObject(DWORD serial, WORD graphic, WORD color, short x, short y, char z);
	virtual ~TLandObject() {}

	//������� �������
	TVector m_Normals[4];

	SETGET(RECT, Rect);
	SETGET(char, MinZ);
	SETGET(bool, IsStretched);

	//��������� �������
	virtual int Draw(bool &mode, int &drawX, int &drawY, DWORD &ticks);

	//��� ������ ���������
	bool IsLandObject() {return true;}

	//������������� ��� ��������� ��������
	bool Ignored() {return (Graphic == 2 || Graphic == 0x1DB || (Graphic >= 0x1AE && Graphic <= 0x1B5));}
};
//---------------------------------------------------------------------------
//����� ����������� ������� ������ �������
class TRenderStaticObject : public TMapObject
{
protected:
	//������ ������������ ����� ������
	char m_FoliageTransparentIndex;

	//��������� �� ��������� ������ ��������
	STATIC_TILES *m_TiledataPtr;

public:
	TRenderStaticObject(RENDER_OBJECT_TYPE renderType, DWORD serial, WORD graphic, WORD color, short x, short y, char z);
	virtual ~TRenderStaticObject();
	
	TTextContainer *m_TextControl; //������ �� ��������� ��� ������
	
	SETGET(char, FoliageTransparentIndex);

	//�������� ����� � ���������
	virtual void AddText(TTextData *td);

	//�������� �������� ������ �� ��� X
	int GetTextOffsetX(TTextData *text);

	//�������� �������� ������ �� ��� Y
	int GetTextOffsetY(TTextData *text);

	//��������, ����� �� ����� ���� ����������
	bool TextCanBeTransparent(TRenderTextObject *text);

	STATIC_TILES *GetStaticData() { return m_TiledataPtr; }

	//�������� ������ ������� (�� ������ �� ��������)
	BYTE GetStaticHeight() { return m_TiledataPtr->Height; }

	//�������� ������ �����
	BYTE GetLightID() {return m_TiledataPtr->Quality;}
	
	//����������� ��������� �� ������ �� �������� (�������)
	bool IsBackground() {return (m_TiledataPtr->Flags & 0x00000001);}
	bool IsWeapon() {return (m_TiledataPtr->Flags & 0x00000002);}
	bool IsTransparent() {return (m_TiledataPtr->Flags & 0x00000004);}
	bool IsTranslucent() {return (m_TiledataPtr->Flags & 0x00000008);}
	bool IsWall() {return (m_TiledataPtr->Flags & 0x00000010);}
	bool IsDamaging() {return (m_TiledataPtr->Flags & 0x00000020);}
	bool IsImpassable() {return (m_TiledataPtr->Flags & 0x00000040);}
	bool IsWet() {return (m_TiledataPtr->Flags & 0x00000080);}
	bool IsUnknown() {return (m_TiledataPtr->Flags & 0x00000100);}
	bool IsSurface() {return (m_TiledataPtr->Flags & 0x00000200);}
	bool IsBridge() {return (m_TiledataPtr->Flags & 0x00000400);}
	bool IsStackable() {return (m_TiledataPtr->Flags & 0x00000800);}
	bool IsWindow() {return (m_TiledataPtr->Flags & 0x00001000);}
	bool IsNoShoot() {return (m_TiledataPtr->Flags & 0x00002000);}
	bool IsPrefixA() {return (m_TiledataPtr->Flags & 0x00004000);}
	bool IsPrefixAn() {return (m_TiledataPtr->Flags & 0x00008000);}
	bool IsInternal() {return (m_TiledataPtr->Flags & 0x00010000);}
	bool IsFoliage() {return (m_TiledataPtr->Flags & 0x00020000);}
	bool IsPartialHue() {return (m_TiledataPtr->Flags & 0x00040000);}
	bool IsUnknown1() {return (m_TiledataPtr->Flags & 0x00080000);}
	bool IsMap() {return (m_TiledataPtr->Flags & 0x00100000);}
	bool IsContainer() {return (m_TiledataPtr->Flags & 0x00200000);}
	bool IsWearable() {return (m_TiledataPtr->Flags & 0x00400000);}
	bool IsLightSource() {return (m_TiledataPtr->Flags & 0x00800000);}
	bool IsAnimated() {return (m_TiledataPtr->Flags & 0x01000000);}
	bool IsNoDiagonal() {return (m_TiledataPtr->Flags & 0x02000000);}
	bool IsUnknown2() {return (m_TiledataPtr->Flags & 0x04000000);}
	bool IsArmor() {return (m_TiledataPtr->Flags & 0x08000000);}
	bool IsRoof() {return (m_TiledataPtr->Flags & 0x10000000);}
	bool IsDoor() {return (m_TiledataPtr->Flags & 0x20000000);}
	bool IsStairBack() {return (m_TiledataPtr->Flags & 0x40000000);}
	bool IsStairRight() {return (m_TiledataPtr->Flags & 0x80000000);}

	//��� ������ ������ �������� �������
	bool IsStaticGroupObject() {return true;}
};
//---------------------------------------------------------------------------
//����� ������� �������
class TStaticObject : public TRenderStaticObject
{
private:
	//����� �� ���� ����������
	char m_CanBeTransparent;
public:
	TStaticObject(DWORD serial, WORD graphic, WORD color, short x, short y, char z);
	virtual ~TStaticObject() {}

	//��������� �������
	virtual int Draw(bool &mode, int &drawX, int &drawY, DWORD &ticks);

	//�������� ������������ (��� ����� ������������)
	virtual bool TranparentTest(int &playerZ);

	//��� ������ �������
	bool IsStaticObject() {return true;}
	
	SETGET(char, CanBeTransparent);
};
//---------------------------------------------------------------------------
#endif