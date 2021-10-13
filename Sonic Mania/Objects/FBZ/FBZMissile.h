#ifndef OBJ_FBZMISSILE_H
#define OBJ_FBZMISSILE_H

#include "SonicMania.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox1;
    Hitbox hitbox2;
    Hitbox hitbox3;
    TABLE(int velocities[8], { 0x10000, 0xE000, 0x12000, 0x14000, 0x10000, 0xE000, 0xC000, 0xE000 });
    int velocityID;
    ushort aniFrames;
    ushort sfxPush;
    ushort sfxPush2;
    ushort sfxExplosion;
} ObjectFBZMissile;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int type;
    byte interval;
    byte intervalOffset;
    int timer;
    Animator animator;
} EntityFBZMissile;

// Object Struct
extern ObjectFBZMissile *FBZMissile;

// Standard Entity Events
void FBZMissile_Update(void);
void FBZMissile_LateUpdate(void);
void FBZMissile_StaticUpdate(void);
void FBZMissile_Draw(void);
void FBZMissile_Create(void* data);
void FBZMissile_StageLoad(void);
void FBZMissile_EditorDraw(void);
void FBZMissile_EditorLoad(void);
void FBZMissile_Serialize(void);

// Extra Entity Functions
void FBZMissile_Unknown1(void);
void FBZMissile_Unknown2(void);
void FBZMissile_Unknown3(void);
void FBZMissile_Unknown4(void);
void FBZMissile_Unknown5(void);
void FBZMissile_Unknown6(void);
void FBZMissile_Unknown7(void);
void FBZMissile_Unknown8(void);

#endif //!OBJ_FBZMISSILE_H
