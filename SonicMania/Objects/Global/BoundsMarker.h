#ifndef OBJ_BOUNDSMARKER_H
#define OBJ_BOUNDSMARKER_H

#include "Game.h"

typedef enum {
    BOUNDSMARKER_BOTTOM,
    BOUNDSMARKER_BOTTOM_OFFSET,
    BOUNDSMARKER_TOP_OFFSET,
    BOUNDSMARKER_TOP,
} BoundsMarkerTypes;

// Object Class
struct ObjectBoundsMarker {
    RSDK_OBJECT
    uint16 aniFrames;
};

// Entity Class
struct EntityBoundsMarker {
    RSDK_ENTITY
    uint8 type;
    int32 width;
    bool32 vsDisable;
    int32 offset;
};

// Object Struct
extern ObjectBoundsMarker *BoundsMarker;

// Standard Entity Events
void BoundsMarker_Update(void);
void BoundsMarker_LateUpdate(void);
void BoundsMarker_StaticUpdate(void);
void BoundsMarker_Draw(void);
void BoundsMarker_Create(void *data);
void BoundsMarker_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void BoundsMarker_EditorDraw(void);
void BoundsMarker_EditorLoad(void);
#endif
void BoundsMarker_Serialize(void);

// Extra Entity Functions
void BoundsMarker_CheckBounds(EntityPlayer *player, EntityBoundsMarker *marker, bool32 setPos);
void BoundsMarker_CheckAllBounds(EntityPlayer *player, bool32 setPos);

#endif //! OBJ_BOUNDSMARKER_H
