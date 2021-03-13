#ifndef OBJ_STAIRCASE_H
#define OBJ_STAIRCASE_H

#include "../SonicMania.h"

// Object Class
typedef struct {
	RSDK_OBJECT
} ObjectStaircase;

// Entity Class
typedef struct {
	RSDK_ENTITY
} EntityStaircase;

// Object Struct
extern ObjectStaircase *Staircase;

// Standard Entity Events
void Staircase_Update();
void Staircase_LateUpdate();
void Staircase_StaticUpdate();
void Staircase_Draw();
void Staircase_Create(void* data);
void Staircase_StageLoad();
void Staircase_EditorDraw();
void Staircase_EditorLoad();
void Staircase_Serialize();

// Extra Entity Functions


#endif //!OBJ_STAIRCASE_H