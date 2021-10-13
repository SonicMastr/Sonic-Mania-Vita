#ifndef OBJ_HEAVYKING_H
#define OBJ_HEAVYKING_H

#include "SonicMania.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    TABLE(int value1[32], { 0, 0, 1, 0, 2, 2, 1, 0, 0, 1, 1, 2, 0, 2, 0, 0, 2, 1, 1, 2, 1, 0, 1, 0, 2, 2, 0, 1, 0, 0, 2, 1 });
	int value2;
	Hitbox value3;
	Hitbox value4;
	Hitbox value5;
	int value6;
	int value7;
	int value8;
	int value9;
	int value10;
	ushort value11;
	ushort value12;
	ushort value13;
	ushort value14;
	ushort value15;
	ushort value16;
	ushort value17;
	ushort value18;
	ushort value19;
	ushort value20;
	ushort value21;
	ushort value22;
	ushort value23;
} ObjectHeavyKing;

// Entity Class
typedef struct {
	RSDK_ENTITY
} EntityHeavyKing;

// Object Struct
extern ObjectHeavyKing *HeavyKing;

// Standard Entity Events
void HeavyKing_Update(void);
void HeavyKing_LateUpdate(void);
void HeavyKing_StaticUpdate(void);
void HeavyKing_Draw(void);
void HeavyKing_Create(void* data);
void HeavyKing_StageLoad(void);
void HeavyKing_EditorDraw(void);
void HeavyKing_EditorLoad(void);
void HeavyKing_Serialize(void);

// Extra Entity Functions


#endif //!OBJ_HEAVYKING_H
