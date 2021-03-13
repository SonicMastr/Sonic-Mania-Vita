#ifndef OBJ_KANABUN_H
#define OBJ_KANABUN_H

#include "../SonicMania.h"

// Object Class
typedef struct {
	RSDK_OBJECT
} ObjectKanabun;

// Entity Class
typedef struct {
	RSDK_ENTITY
} EntityKanabun;

// Object Struct
extern ObjectKanabun *Kanabun;

// Standard Entity Events
void Kanabun_Update();
void Kanabun_LateUpdate();
void Kanabun_StaticUpdate();
void Kanabun_Draw();
void Kanabun_Create(void* data);
void Kanabun_StageLoad();
void Kanabun_EditorDraw();
void Kanabun_EditorLoad();
void Kanabun_Serialize();

// Extra Entity Functions


#endif //!OBJ_KANABUN_H