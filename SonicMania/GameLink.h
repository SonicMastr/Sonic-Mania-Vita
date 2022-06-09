#ifndef GAMELINK_H
#define GAMELINK_H

// -------------------------
// STANDARD LIBS
// -------------------------

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define sprintf_s(x, _,...) sprintf(x, __VA_ARGS__)

#if defined _WIN32
#undef sprintf_s
#endif

// -------------------------
// STANDARD TYPES
// -------------------------

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;

typedef uint32 bool32;
#define true 1
#define false 0

typedef uint32 color;

// -------------------------
// CONSTANTS
// -------------------------

#define SCREEN_XMAX    (1280)
#define SCREEN_YSIZE   (240)
#define SCREEN_YCENTER (SCREEN_YSIZE / 2)

#define LAYER_COUNT     (8)
#define DRAWGROUP_COUNT (16)

#if RETRO_REV02
#define SCREEN_COUNT (4)
#else
#define SCREEN_COUNT (2)
#endif

#define PLAYER_COUNT (4)
#define CAMERA_COUNT (4)

// 0x800 scene objects, 0x40 reserved ones, and 0x100 spare slots for creation
#define RESERVE_ENTITY_COUNT (0x40)
#define TEMPENTITY_COUNT     (0x100)
#define SCENEENTITY_COUNT    (0x800)
#define ENTITY_COUNT         (RESERVE_ENTITY_COUNT + SCENEENTITY_COUNT + TEMPENTITY_COUNT)
#define TEMPENTITY_START     (ENTITY_COUNT - TEMPENTITY_COUNT)

#define TYPE_COUNT      (0x100)
#define TYPEGROUP_COUNT (0x104)

#define CHANNEL_COUNT (0x10)

#define TILE_SIZE (16)

// -------------------------
// MACROS
// -------------------------

#define minVal(a, b)                      ((a) < (b) ? (a) : (b))
#define maxVal(a, b)                      ((a) > (b) ? (a) : (b))
#define clampVal(value, minimum, maximum) (((value) < (minimum)) ? (minimum) : (((value) > (maximum)) ? (maximum) : (value)))
#define fabs(a)                           ((a) > 0 ? (a) : -(a))

#define setBit(value, set, pos) ((value) ^= (-(int32)(set) ^ (value)) & (1 << (pos)))
#define getBit(b, pos)          ((b) >> (pos)&1)

#define intToVoid(x)   (void *)(size_t)(x)
#define floatToVoid(x) intToVoid(*(int32 *)&(x))
#define voidToInt(x)   (int32)(size_t)(x)
#define voidToFloat(x) *(float *)&(x)

#define unused(x) (void)x

// -------------------------
// STRUCTS
// -------------------------

typedef struct {
    int32 x;
    int32 y;
} Vector2;

typedef struct {
    Vector2 position;
    Vector2 scale;
    Vector2 velocity;
    Vector2 updateRange;
    int32 angle;
    int32 alpha;
    int32 rotation;
    int32 groundVel;
    int32 depth;
    uint16 group;
    uint16 classID;
    bool32 inBounds;
    bool32 isPermanent;
    bool32 tileCollisions;
    bool32 interaction;
    bool32 onGround;
    uint8 active;
#if RETRO_REV02
    uint8 filter;
#endif
    uint8 direction;
    uint8 drawOrder;
    uint8 collisionLayers;
    uint8 collisionPlane;
    uint8 collisionMode;
    uint8 drawFX;
    uint8 inkEffect;
    uint8 visible;
    uint8 activeScreens;
} Entity;

typedef struct {
    uint16 classID;
    uint8 active;
} Object;

#define RSDK_OBJECT                                                                                                                                  \
    uint16 classID;                                                                                                                                  \
    uint8 active;

#if RETRO_REV02
#define RSDK_ENTITY                                                                                                                                  \
    Vector2 position;                                                                                                                                \
    Vector2 scale;                                                                                                                                   \
    Vector2 velocity;                                                                                                                                \
    Vector2 updateRange;                                                                                                                             \
    int32 angle;                                                                                                                                     \
    int32 alpha;                                                                                                                                     \
    int32 rotation;                                                                                                                                  \
    int32 groundVel;                                                                                                                                 \
    int32 depth3D;                                                                                                                                   \
    uint16 group;                                                                                                                                    \
    uint16 classID;                                                                                                                                  \
    bool32 inBounds;                                                                                                                                 \
    bool32 isPermanent;                                                                                                                              \
    bool32 tileCollisions;                                                                                                                           \
    bool32 interaction;                                                                                                                              \
    bool32 onGround;                                                                                                                                 \
    uint8 active;                                                                                                                                    \
    uint8 filter;                                                                                                                                    \
    uint8 direction;                                                                                                                                 \
    uint8 drawOrder;                                                                                                                                 \
    uint8 collisionLayers;                                                                                                                           \
    uint8 collisionPlane;                                                                                                                            \
    uint8 collisionMode;                                                                                                                             \
    uint8 drawFX;                                                                                                                                    \
    uint8 inkEffect;                                                                                                                                 \
    uint8 visible;                                                                                                                                   \
    uint8 activeScreens;
#else
#define RSDK_ENTITY                                                                                                                                  \
    Vector2 position;                                                                                                                                \
    Vector2 scale;                                                                                                                                   \
    Vector2 velocity;                                                                                                                                \
    Vector2 updateRange;                                                                                                                             \
    int32 angle;                                                                                                                                     \
    int32 alpha;                                                                                                                                     \
    int32 rotation;                                                                                                                                  \
    int32 groundVel;                                                                                                                                 \
    int32 depth3D;                                                                                                                                   \
    uint16 group;                                                                                                                                    \
    uint16 classID;                                                                                                                                  \
    bool32 inBounds;                                                                                                                                 \
    bool32 isPermanent;                                                                                                                              \
    bool32 tileCollisions;                                                                                                                           \
    bool32 interaction;                                                                                                                              \
    bool32 onGround;                                                                                                                                 \
    uint8 active;                                                                                                                                    \
    uint8 direction;                                                                                                                                 \
    uint8 drawOrder;                                                                                                                                 \
    uint8 collisionLayers;                                                                                                                           \
    uint8 collisionPlane;                                                                                                                            \
    uint8 collisionMode;                                                                                                                             \
    uint8 drawFX;                                                                                                                                    \
    uint8 inkEffect;                                                                                                                                 \
    uint8 visible;                                                                                                                                   \
    uint8 activeScreens;
#endif

#define ENTITY_SIZE (sizeof(Entity) + (0x100 * sizeof(void *)))

#if RETRO_REV02
#define Unknown_pausePress  UnknownInfo->pausePress
#define Unknown_anyKeyPress UnknownInfo->anyKeyPress

typedef struct {
    int32 platform;
    int32 language;
    int32 region;
} RSDKSKUInfo;

// None of these besides the named 2 are even used
// and even then they're not even set in plus
typedef struct {
    int32 unknown1;
    int32 unknown2;
    int32 unknown3;
    int32 unknown4;
    bool32 pausePress;
    int32 unknown5;
    int32 unknown6;
    int32 unknown7;
    int32 unknown8;
    int32 unknown9;
    bool32 anyKeyPress;
    int32 unknown10;
} RSDKUnknownInfo;
#else
#define Unknown_pausePress  TouchInfo->pausePress
#define Unknown_anyKeyPress TouchInfo->anyKeyPress
#endif

typedef struct {
    char engineInfo[0x40];
    char gameSubname[0x100];
    char version[0x10];
#if !RETRO_REV02
    uint8 platform;
    uint8 language;
    uint8 region;
#endif
} RSDKGameInfo;

typedef struct {
    Entity *entity;
    void *listData;
    void *listCategory;
    int32 timeCounter;
    int32 currentDrawGroup;
    int32 currentScreenID;
    uint16 listPos;
    uint16 entitySlot;
    uint16 createSlot;
    uint16 classCount;
    bool32 inEditor;
    bool32 effectGizmo;
    bool32 debugMode;
    bool32 useGlobalScripts;
    bool32 timeEnabled;
    uint8 activeCategory;
    uint8 categoryCount;
    uint8 state;
#if RETRO_REV02
    uint8 filter;
#endif
    uint8 milliseconds;
    uint8 seconds;
    uint8 minutes;
} RSDKSceneInfo;

typedef struct {
    bool32 down;
    bool32 press;
    int32 keyMap;
} InputState;

typedef struct {
    InputState keyUp;
    InputState keyDown;
    InputState keyLeft;
    InputState keyRight;
    InputState keyA;
    InputState keyB;
    InputState keyC;
    InputState keyX;
    InputState keyY;
    InputState keyZ;
    InputState keyStart;
    InputState keySelect;

    // Rev01 hasn't split these into different structs yet
#if !RETRO_REV02
    InputState bumperL;
    InputState bumperR;
    InputState keyTriggerL;
    InputState keyTriggerR;
    InputState stickL;
    InputState stickR;
#endif
} RSDKControllerState;

typedef struct {
    InputState keyUp;
    InputState keyDown;
    InputState keyLeft;
    InputState keyRight;
#if RETRO_REV02
    InputState keyStick;
    float deadzone;
    float hDelta;
    float vDelta;
#else
    float deadzone;
    float triggerDeltaL;
    float triggerDeltaR;
    float hDeltaL;
    float vDeltaL;
    float hDeltaR;
    float vDeltaR;
#endif
} RSDKAnalogState;

#if RETRO_REV02
typedef struct {
    InputState keyBumper;
    InputState keyTrigger;
    float bumperDelta;
    float triggerDelta;
} RSDKTriggerState;
#endif

typedef struct {
    float x[0x10];
    float y[0x10];
    bool32 down[0x10];
    uint8 count;
#if !RETRO_REV02
    bool32 pauseHold;
    bool32 pausePress;
    bool32 unknown1;
    bool32 anyKeyHold;
    bool32 anyKeyPress;
    bool32 unknown2;
#endif
} RSDKTouchInfo;

typedef struct {
    // uint16 *frameBuffer;
    uint16 frameBuffer[SCREEN_XMAX * SCREEN_YSIZE];
    Vector2 position;
    int32 width;
    int32 height;
    int32 centerX;
    int32 centerY;
    int32 pitch;
    int32 clipBound_X1;
    int32 clipBound_Y1;
    int32 clipBound_X2;
    int32 clipBound_Y2;
    int32 waterDrawPos;
} RSDKScreenInfo;

#if RETRO_REV02
typedef struct {
    void *functionTable;
    void *APITable;

    RSDKGameInfo *gameInfo;
    RSDKSKUInfo *currentSKU;
    RSDKSceneInfo *sceneInfo;

    RSDKControllerState *controllerInfo;
    RSDKAnalogState *stickInfoL;
    RSDKAnalogState *stickInfoR;
    RSDKTriggerState *triggerInfoL;
    RSDKTriggerState *triggerInfoR;
    RSDKTouchInfo *touchInfo;

    RSDKUnknownInfo *unknownInfo;

    RSDKScreenInfo *screenInfo;

#if RETRO_USE_MOD_LOADER
    void *modTable;
#endif
} EngineInfo;
#else
typedef struct {
    void *functionTable;

    RSDKGameInfo *gameInfo;
    RSDKSceneInfo *sceneInfo;

    RSDKControllerState *controllerInfo;
    RSDKAnalogState *stickInfoL;

    RSDKTouchInfo *touchInfo;

    RSDKScreenInfo *screenInfo;

#if RETRO_USE_MOD_LOADER
    void *modTable;
#endif
} EngineInfo;
#endif

typedef struct {
    int32 values[4][4];
} Matrix;

typedef struct {
    uint16 *chars;
    uint16 length;
    uint16 size;
} String;

typedef struct {
    int16 left;
    int16 top;
    int16 right;
    int16 bottom;
} Hitbox;

typedef struct {
    int16 sprX;
    int16 sprY;
    int16 width;
    int16 height;
    int16 pivotX;
    int16 pivotY;
    uint16 delay;
    int16 id;
    uint8 sheetID;
} SpriteFrame;

typedef struct {
    void *frames;
    int32 frameID;
    int16 animationID;
    int16 prevAnimationID;
    int16 speed;
    int16 timer;
    int16 frameDuration;
    int16 frameCount;
    uint8 loopIndex;
    uint8 rotationFlag;
} Animator;

typedef struct {
    int32 tilePos;
    int32 parallaxFactor;
    int32 scrollSpeed;
    int32 scrollPos;
    uint8 deform;
    uint8 unknown;
} ScrollInfo;

typedef struct {
    Vector2 position;
    Vector2 deform;
} ScanlineInfo;

typedef struct {
    uint8 behaviour;
    uint8 drawLayer[4];
    uint8 widthShift;
    uint8 heightShift;
    uint16 width;
    uint16 height;
    Vector2 position;
    int32 parallaxFactor;
    int32 scrollSpeed;
    int32 scrollPos;
    int32 deformationOffset;
    int32 deformationOffsetW;
    int32 deformationData[0x400];
    int32 deformationDataW[0x400];
    void (*scanlineCallback)(ScanlineInfo *);
    uint16 scrollInfoCount;
    ScrollInfo scrollInfo[0x100];
    uint32 name[4];
    uint16 *layout;
    uint8 *lineScroll;
} TileLayer;

typedef struct {
    uint8 idPS4;     // achievement ID (PS4)
    int32 idUnknown; // achievement ID (unknown platform)
    const char *id;  // achievement ID (as a string, used for most platforms)
} AchievementID;

typedef struct {
    int32 idPS4;        // leaderboard id (PS4)
    int32 idUnknown;    // leaderboard id (unknown platform)
    int32 idSwitch;     // leaderboard id (switch)
    const char *idXbox; // Xbox One Leaderboard id (making an assumption based on the MS docs)
    const char *idPC;   // Leaderboard id (as a string, used for PC platforms)
} LeaderboardID;

typedef struct {
    int32 start;
    int32 length;
} LeaderboardAvail;

typedef struct {
    String username;
#if RETRO_REV02
    String userID;
#endif
    int32 globalRank;
    int32 score;
    bool32 isUser;
    int32 status;
} LeaderboardEntry;

typedef struct {
    uint8 statID;
    const char *name;
    void *data[64];
} StatInfo;

// -------------------------
// ENUMS
// -------------------------

typedef enum {
    PLATFORM_PC,
    PLATFORM_PS4,
    PLATFORM_XB1,
    PLATFORM_SWITCH,

    PLATFORM_DEV = 0xFF,
} GamePlatforms;

typedef enum {
    SCOPE_NONE,
    SCOPE_GLOBAL,
    SCOPE_STAGE,
} Scopes;

typedef enum {
    INK_NONE,
    INK_BLEND,
    INK_ALPHA,
    INK_ADD,
    INK_SUB,
    INK_TINT,
    INK_MASKED,
    INK_UNMASKED,
} InkEffects;

typedef enum { FX_NONE = 0, FX_FLIP = 1, FX_ROTATE = 2, FX_SCALE = 4 } DrawFX;

typedef enum { FLIP_NONE, FLIP_X, FLIP_Y, FLIP_XY } FlipFlags;

typedef enum { TYPE_BLANK } DefaultObjTypes;

typedef enum {
    INPUT_UNASSIGNED = -2,
    INPUT_AUTOASSIGN = -1,
    INPUT_NONE       = 0,
} InputIds;

typedef enum {
    CONT_ANY,
    CONT_P1,
    CONT_P2,
    CONT_P3,
    CONT_P4,
} ControllerIDs;

typedef enum {
    DEVICE_TYPE_NONE,
    DEVICE_TYPE_KEYBOARD,
    DEVICE_TYPE_CONTROLLER,
    DEVICE_TYPE_UNKNOWN,
    DEVICE_TYPE_STEAMOVERLAY,
} InputDeviceTypes;

typedef enum {
    DEVICE_KEYBOARD,
    DEVICE_XBOX,
    DEVICE_PS4,
    DEVICE_SATURN,
    DEVICE_SWITCH_HANDHELD,
    DEVICE_SWITCH_JOY_GRIP,
    DEVICE_SWITCH_JOY_L,
    DEVICE_SWITCH_JOY_R,
    DEVICE_SWITCH_PRO,
} InputDeviceIDs;

typedef enum {
    DEVICE_API_NONE,
    DEVICE_API_KEYBOARD,
    DEVICE_API_XINPUT,
    DEVICE_API_RAWINPUT,
    DEVICE_API_STEAM,
} InputDeviceAPIs;

typedef enum {
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER,
} Alignments;

#if RETRO_REV02
typedef enum {
    PRINT_NORMAL,
    PRINT_POPUP,
    PRINT_ERROR,
    PRINT_FATAL,
} PrintModes;
#else
typedef enum {
    MESSAGE_STRING,
    MESSAGE_INT32,
    MESSAGE_UINT32,
    MESSAGE_FLOAT,
} PrintMessageTypes;
#endif

typedef enum {
    VAR_UINT8,
    VAR_UINT16,
    VAR_UINT32,
    VAR_INT8,
    VAR_INT16,
    VAR_INT32,
    VAR_ENUM,
    VAR_BOOL,
    VAR_STRING,
    VAR_VECTOR2,
    VAR_FLOAT,
    VAR_COLOR,
} VarTypes;

#if RETRO_REV02
typedef enum {
    DBVAR_UNKNOWN, // unused (in Sonic Mania)
    DBVAR_BOOL,    // unused (in Sonic Mania)
    DBVAR_UINT8,   // used (in Sonic Mania)
    DBVAR_UINT16,  // unused (in Sonic Mania)
    DBVAR_UINT32,  // used (in Sonic Mania)
    DBVAR_UINT64,  // unimplemented in RSDKv5
    DBVAR_INT8,    // unused (in Sonic Mania)
    DBVAR_INT16,   // unused (in Sonic Mania)
    DBVAR_INT32,   // unused (in Sonic Mania)
    DBVAR_INT64,   // unimplemented in RSDKv5
    DBVAR_FLOAT,   // unused (in Sonic Mania)
    DBVAR_DOUBLE,  // unimplemented in RSDKv5
    DBVAR_VECTOR2, // unimplemented in RSDKv5
    DBVAR_VECTOR3, // unimplemented in RSDKv5
    DBVAR_VECTOR4, // unimplemented in RSDKv5
    DBVAR_COLOR,   // unused (in Sonic Mania)
    DBVAR_STRING,  // unused (in Sonic Mania)
    DBVAR_HASHMD5, // unimplemented in RSDKv5
} DBVarTypes;

typedef enum {
    VIEWVAR_INVALID,
    VIEWVAR_BOOL,
    VIEWVAR_UINT8,
    VIEWVAR_UINT16,
    VIEWVAR_UINT32,
    VIEWVAR_INT8,
    VIEWVAR_INT16,
    VIEWVAR_INT32,
} ViewableVarTypes;
#endif

typedef enum {
    ACTIVE_NEVER,
    ACTIVE_ALWAYS,
    ACTIVE_NORMAL,
    ACTIVE_PAUSED,
    ACTIVE_BOUNDS,
    ACTIVE_XBOUNDS,
    ACTIVE_YBOUNDS,
    ACTIVE_RBOUNDS,

    // Not really even a real active value, but some objects set their active states to this so here it is I suppose
    ACTIVE_DISABLED = 0xFF,
} ActiveFlags;

typedef enum {
    LAYER_HSCROLL,
    LAYER_VSCROLL,
    LAYER_ROTOZOOM,
    LAYER_BASIC,
} LayerTypes;

typedef enum {
    CMODE_FLOOR,
    CMODE_LWALL,
    CMODE_ROOF,
    CMODE_RWALL,
} CModes;

typedef enum {
    C_NONE,
    C_TOP,
    C_LEFT,
    C_RIGHT,
    C_BOTTOM,
} CSides;

typedef enum {
    S3D_WIREFRAME,
    S3D_SOLIDCOLOR,

    S3D_UNUSED_1,
    S3D_UNUSED_2,

    S3D_WIREFRAME_SHADED,
    S3D_SOLIDCOLOR_SHADED,

    S3D_SOLIDCOLOR_SHADED_BLENDED,

    S3D_WIREFRAME_SCREEN,
    S3D_SOLIDCOLOR_SCREEN,

    S3D_WIREFRAME_SHADED_SCREEN,
    S3D_SOLIDCOLOR_SHADED_SCREEN,

    S3D_SOLIDCOLOR_SHADED_BLENDED_SCREEN,
} Scene3DDrawTypes;

typedef enum {
    VIDEOSETTING_WINDOWED,
    VIDEOSETTING_BORDERED,
    VIDEOSETTING_EXCLUSIVEFS,
    VIDEOSETTING_VSYNC,
    VIDEOSETTING_TRIPLEBUFFERED,
    VIDEOSETTING_WINDOW_WIDTH,
    VIDEOSETTING_WINDOW_HEIGHT,
    VIDEOSETTING_FSWIDTH,
    VIDEOSETTING_FSHEIGHT,
    VIDEOSETTING_REFRESHRATE,
    VIDEOSETTING_SHADERSUPPORT,
    VIDEOSETTING_SHADERID,
    VIDEOSETTING_SCREENCOUNT,
#if RETRO_REV02
    VIDEOSETTING_DIMTIMER,
#endif
    VIDEOSETTING_STREAMSENABLED,
    VIDEOSETTING_STREAM_VOL,
    VIDEOSETTING_SFX_VOL,
    VIDEOSETTING_LANGUAGE,
    VIDEOSETTING_STORE,
    VIDEOSETTING_RELOAD,
    VIDEOSETTING_CHANGED,
    VIDEOSETTING_WRITE,
} VideoSettingsValues;

typedef enum {
    GROUP_ALL = 0,

    GROUP_CUSTOM0 = TYPE_COUNT,
    GROUP_CUSTOM1,
    GROUP_CUSTOM2,
    GROUP_CUSTOM3,
} TypeGroups;

typedef enum {
    STATUS_NONE      = 0,
    STATUS_CONTINUE  = 100,
    STATUS_OK        = 200,
    STATUS_FORBIDDEN = 403,
    STATUS_NOTFOUND  = 404,
    STATUS_ERROR     = 500,
    STATUS_NOWIFI    = 503,
    STATUS_TIMEOUT   = 504,
    STATUS_CORRUPT   = 505,
    STATUS_NOSPACE   = 506,
} StatusCodes;

typedef enum {
    REGION_US,
    REGION_JP,
    REGION_EU,
} GameRegions;

typedef enum {
    LANGUAGE_EN,
    LANGUAGE_FR,
    LANGUAGE_IT,
    LANGUAGE_GE,
    LANGUAGE_SP,
    LANGUAGE_JP,
#if MANIA_GAMEVER != VER_100
    LANGUAGE_KO,
    LANGUAGE_SC,
    LANGUAGE_TC,
#endif
} GameLanguages;

typedef enum {
    ENGINESTATE_LOAD,
    ENGINESTATE_REGULAR,
    ENGINESTATE_PAUSED,
    ENGINESTATE_FROZEN,
    ENGINESTATE_STEPOVER = 4,
    ENGINESTATE_DEVMENU  = 8,
    ENGINESTATE_VIDEOPLAYBACK,
    ENGINESTATE_SHOWIMAGE,
#if RETRO_REV02
    ENGINESTATE_ERRORMSG,
    ENGINESTATE_ERRORMSG_FATAL,
#endif
    ENGINESTATE_NONE,
} EngineStates;

// see: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// for value list & descriptions
typedef enum {
    KEYMAP_AUTO_MAPPING                    = -1,
    KEYMAP_NO_MAPPING                      = 0,
    KEYMAP_LBUTTON                         = 0x01,
    KEYMAP_RBUTTON                         = 0x02,
    KEYMAP_CANCEL                          = 0x03,
    KEYMAP_MBUTTON                         = 0x04,
    KEYMAP_XBUTTON1                        = 0x05,
    KEYMAP_XBUTTON2                        = 0x06,
    KEYMAP_BACK                            = 0x08,
    KEYMAP_TAB                             = 0x09,
    KEYMAP_CLEAR                           = 0x0C,
    KEYMAP_RETURN                          = 0x0D,
    KEYMAP_SHIFT                           = 0x10,
    KEYMAP_CONTROL                         = 0x11,
    KEYMAP_MENU                            = 0x12,
    KEYMAP_PAUSE                           = 0x13,
    KEYMAP_CAPITAL                         = 0x14,
    KEYMAP_KANA                            = 0x15,
    KEYMAP_HANGEUL                         = 0x15,
    KEYMAP_HANGUL                          = 0x15,
    KEYMAP_JUNJA                           = 0x17,
    KEYMAP_FINAL                           = 0x18,
    KEYMAP_HANJA                           = 0x19,
    KEYMAP_KANJI                           = 0x19,
    KEYMAP_ESCAPE                          = 0x1B,
    KEYMAP_CONVERT                         = 0x1C,
    KEYMAP_NONCONVERT                      = 0x1D,
    KEYMAP_ACCEPT                          = 0x1E,
    KEYMAP_MODECHANGE                      = 0x1F,
    KEYMAP_SPACE                           = 0x20,
    KEYMAP_PRIOR                           = 0x21,
    KEYMAP_NEXT                            = 0x22,
    KEYMAP_END                             = 0x23,
    KEYMAP_HOME                            = 0x24,
    KEYMAP_LEFT                            = 0x25,
    KEYMAP_UP                              = 0x26,
    KEYMAP_RIGHT                           = 0x27,
    KEYMAP_DOWN                            = 0x28,
    KEYMAP_SELECT                          = 0x29,
    KEYMAP_PRINT                           = 0x2A,
    KEYMAP_EXECUTE                         = 0x2B,
    KEYMAP_SNAPSHOT                        = 0x2C,
    KEYMAP_INSERT                          = 0x2D,
    KEYMAP_DELETE                          = 0x2E,
    KEYMAP_HELP                            = 0x2F,
    KEYMAP_0                               = 0x30,
    KEYMAP_1                               = 0x31,
    KEYMAP_2                               = 0x32,
    KEYMAP_3                               = 0x33,
    KEYMAP_4                               = 0x34,
    KEYMAP_5                               = 0x35,
    KEYMAP_6                               = 0x36,
    KEYMAP_7                               = 0x37,
    KEYMAP_8                               = 0x38,
    KEYMAP_9                               = 0x39,
    KEYMAP_A                               = 0x41,
    KEYMAP_B                               = 0x42,
    KEYMAP_C                               = 0x43,
    KEYMAP_D                               = 0x44,
    KEYMAP_E                               = 0x45,
    KEYMAP_F                               = 0x46,
    KEYMAP_G                               = 0x47,
    KEYMAP_H                               = 0x48,
    KEYMAP_I                               = 0x49,
    KEYMAP_J                               = 0x4A,
    KEYMAP_K                               = 0x4B,
    KEYMAP_L                               = 0x4C,
    KEYMAP_M                               = 0x4D,
    KEYMAP_N                               = 0x4E,
    KEYMAP_O                               = 0x4F,
    KEYMAP_P                               = 0x50,
    KEYMAP_Q                               = 0x51,
    KEYMAP_R                               = 0x52,
    KEYMAP_S                               = 0x53,
    KEYMAP_T                               = 0x54,
    KEYMAP_U                               = 0x55,
    KEYMAP_V                               = 0x56,
    KEYMAP_W                               = 0x57,
    KEYMAP_X                               = 0x58,
    KEYMAP_Y                               = 0x59,
    KEYMAP_Z                               = 0x5A,
    KEYMAP_LWIN                            = 0x5B,
    KEYMAP_RWIN                            = 0x5C,
    KEYMAP_APPS                            = 0x5D,
    KEYMAP_SLEEP                           = 0x5F,
    KEYMAP_NUMPAD0                         = 0x60,
    KEYMAP_NUMPAD1                         = 0x61,
    KEYMAP_NUMPAD2                         = 0x62,
    KEYMAP_NUMPAD3                         = 0x63,
    KEYMAP_NUMPAD4                         = 0x64,
    KEYMAP_NUMPAD5                         = 0x65,
    KEYMAP_NUMPAD6                         = 0x66,
    KEYMAP_NUMPAD7                         = 0x67,
    KEYMAP_NUMPAD8                         = 0x68,
    KEYMAP_NUMPAD9                         = 0x69,
    KEYMAP_MULTIPLY                        = 0x6A,
    KEYMAP_ADD                             = 0x6B,
    KEYMAP_SEPARATOR                       = 0x6C,
    KEYMAP_SUBTRACT                        = 0x6D,
    KEYMAP_DECIMAL                         = 0x6E,
    KEYMAP_DIVIDE                          = 0x6F,
    KEYMAP_F1                              = 0x70,
    KEYMAP_F2                              = 0x71,
    KEYMAP_F3                              = 0x72,
    KEYMAP_F4                              = 0x73,
    KEYMAP_F5                              = 0x74,
    KEYMAP_F6                              = 0x75,
    KEYMAP_F7                              = 0x76,
    KEYMAP_F8                              = 0x77,
    KEYMAP_F9                              = 0x78,
    KEYMAP_F10                             = 0x79,
    KEYMAP_F11                             = 0x7A,
    KEYMAP_F12                             = 0x7B,
    KEYMAP_F13                             = 0x7C,
    KEYMAP_F14                             = 0x7D,
    KEYMAP_F15                             = 0x7E,
    KEYMAP_F16                             = 0x7F,
    KEYMAP_F17                             = 0x80,
    KEYMAP_F18                             = 0x81,
    KEYMAP_F19                             = 0x82,
    KEYMAP_F20                             = 0x83,
    KEYMAP_F21                             = 0x84,
    KEYMAP_F22                             = 0x85,
    KEYMAP_F23                             = 0x86,
    KEYMAP_F24                             = 0x87,
    KEYMAP_NAVIGATION_VIEW                 = 0x88,
    KEYMAP_NAVIGATION_MENU                 = 0x89,
    KEYMAP_NAVIGATION_UP                   = 0x8A,
    KEYMAP_NAVIGATION_DOWN                 = 0x8B,
    KEYMAP_NAVIGATION_LEFT                 = 0x8C,
    KEYMAP_NAVIGATION_RIGHT                = 0x8D,
    KEYMAP_NAVIGATION_ACCEPT               = 0x8E,
    KEYMAP_NAVIGATION_CANCEL               = 0x8F,
    KEYMAP_NUMLOCK                         = 0x90,
    KEYMAP_SCROLL                          = 0x91,
    KEYMAP_OEM_NEC_EQUAL                   = 0x92,
    KEYMAP_OEM_FJ_JISHO                    = 0x92,
    KEYMAP_OEM_FJ_MASSHOU                  = 0x93,
    KEYMAP_OEM_FJ_TOUROKU                  = 0x94,
    KEYMAP_OEM_FJ_LOYA                     = 0x95,
    KEYMAP_OEM_FJ_ROYA                     = 0x96,
    KEYMAP_LSHIFT                          = 0xA0,
    KEYMAP_RSHIFT                          = 0xA1,
    KEYMAP_LCONTROL                        = 0xA2,
    KEYMAP_RCONTROL                        = 0xA3,
    KEYMAP_LMENU                           = 0xA4,
    KEYMAP_RMENU                           = 0xA5,
    KEYMAP_BROWSER_BACK                    = 0xA6,
    KEYMAP_BROWSER_FORWARD                 = 0xA7,
    KEYMAP_BROWSER_REFRESH                 = 0xA8,
    KEYMAP_BROWSER_STOP                    = 0xA9,
    KEYMAP_BROWSER_SEARCH                  = 0xAA,
    KEYMAP_BROWSER_FAVORITES               = 0xAB,
    KEYMAP_BROWSER_HOME                    = 0xAC,
    KEYMAP_VOLUME_MUTE                     = 0xAD,
    KEYMAP_VOLUME_DOWN                     = 0xAE,
    KEYMAP_VOLUME_UP                       = 0xAF,
    KEYMAP_MEDIA_NEXT_TRACK                = 0xB0,
    KEYMAP_MEDIA_PREV_TRACK                = 0xB1,
    KEYMAP_MEDIA_STOP                      = 0xB2,
    KEYMAP_MEDIA_PLAY_PAUSE                = 0xB3,
    KEYMAP_LAUNCH_MAIL                     = 0xB4,
    KEYMAP_LAUNCH_MEDIA_SELECT             = 0xB5,
    KEYMAP_LAUNCH_APP1                     = 0xB6,
    KEYMAP_LAUNCH_APP2                     = 0xB7,
    KEYMAP_OEM_1                           = 0xBA,
    KEYMAP_OEM_PLUS                        = 0xBB,
    KEYMAP_OEM_COMMA                       = 0xBC,
    KEYMAP_OEM_MINUS                       = 0xBD,
    KEYMAP_OEM_PERIOD                      = 0xBE,
    KEYMAP_OEM_2                           = 0xBF,
    KEYMAP_OEM_3                           = 0xC0,
    KEYMAP_GAMEPAD_A                       = 0xC3,
    KEYMAP_GAMEPAD_B                       = 0xC4,
    KEYMAP_GAMEPAD_X                       = 0xC5,
    KEYMAP_GAMEPAD_Y                       = 0xC6,
    KEYMAP_GAMEPAD_RIGHT_SHOULDER          = 0xC7,
    KEYMAP_GAMEPAD_LEFT_SHOULDER           = 0xC8,
    KEYMAP_GAMEPAD_LEFT_TRIGGER            = 0xC9,
    KEYMAP_GAMEPAD_RIGHT_TRIGGER           = 0xCA,
    KEYMAP_GAMEPAD_DPAD_UP                 = 0xCB,
    KEYMAP_GAMEPAD_DPAD_DOWN               = 0xCC,
    KEYMAP_GAMEPAD_DPAD_LEFT               = 0xCD,
    KEYMAP_GAMEPAD_DPAD_RIGHT              = 0xCE,
    KEYMAP_GAMEPAD_MENU                    = 0xCF,
    KEYMAP_GAMEPAD_VIEW                    = 0xD0,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_BUTTON  = 0xD1,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_BUTTON = 0xD2,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_UP      = 0xD3,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_DOWN    = 0xD4,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_RIGHT   = 0xD5,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_LEFT    = 0xD6,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_UP     = 0xD7,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_DOWN   = 0xD8,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_RIGHT  = 0xD9,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_LEFT   = 0xDA,
    KEYMAP_OEM_4                           = 0xDB,
    KEYMAP_OEM_5                           = 0xDC,
    KEYMAP_OEM_6                           = 0xDD,
    KEYMAP_OEM_7                           = 0xDE,
    KEYMAP_OEM_8                           = 0xDF,
    KEYMAP_OEM_AX                          = 0xE1,
    KEYMAP_OEM_102                         = 0xE2,
    KEYMAP_ICO_HELP                        = 0xE3,
    KEYMAP_ICO_00                          = 0xE4,
    KEYMAP_PROCESSKEY                      = 0xE5,
    KEYMAP_ICO_CLEAR                       = 0xE6,
    KEYMAP_PACKET                          = 0xE7,
    KEYMAP_OEM_RESET                       = 0xE9,
    KEYMAP_OEM_JUMP                        = 0xEA,
    KEYMAP_OEM_PA1                         = 0xEB,
    KEYMAP_OEM_PA2                         = 0xEC,
    KEYMAP_OEM_PA3                         = 0xED,
    KEYMAP_OEM_WSCTRL                      = 0xEE,
    KEYMAP_OEM_CUSEL                       = 0xEF,
    KEYMAP_OEM_ATTN                        = 0xF0,
    KEYMAP_OEM_FINISH                      = 0xF1,
    KEYMAP_OEM_COPY                        = 0xF2,
    KEYMAP_OEM_AUTO                        = 0xF3,
    KEYMAP_OEM_ENLW                        = 0xF4,
    KEYMAP_OEM_BACKTAB                     = 0xF5,
    KEYMAP_ATTN                            = 0xF6,
    KEYMAP_CRSEL                           = 0xF7,
    KEYMAP_EXSEL                           = 0xF8,
    KEYMAP_EREOF                           = 0xF9,
    KEYMAP_PLAY                            = 0xFA,
    KEYMAP_ZOOM                            = 0xFB,
    KEYMAP_NONAME                          = 0xFC,
    KEYMAP_PA1                             = 0xFD,
    KEYMAP_OEM_CLEAR                       = 0xFE,
} KeyMappings;

#if RETRO_USE_MOD_LOADER
typedef enum {
    MODCB_GAME_STARTUP,
    MODCB_STAGELOAD,
    MODCB_ONUPDATE,
    MODCB_ONLATEUPDATE,
    MODCB_ONSTATICUPDATE,
    MODCB_ONDRAW,
    MODCB_STAGEUNLOAD,
    MODCB_ONSHADERLOAD,
} ModCallbackEvents;

typedef enum {
    SUPER_UPDATE,
    SUPER_LATEUPDATE,
    SUPER_STATICUPDATE,
    SUPER_DRAW,
    SUPER_CREATE,
    SUPER_STAGELOAD,
    SUPER_EDITORDRAW,
    SUPER_EDITORLOAD,
    SUPER_SERIALIZE
} ModSuper;
#endif

// -------------------------
// FUNCTION TABLES
// -------------------------

#if RETRO_USE_MOD_LOADER
// Mod Table
typedef struct {
    // Registration & Core
    void (*RegisterGlobals)(const char *globalsPath, void **globals, uint32 size);
    void (*RegisterObject)(Object **staticVars, const char *name, uint32 entityClassSize, uint32 staticClassSize, void (*update)(void),
                           void (*lateUpdate)(void), void (*staticUpdate)(void), void (*draw)(void), void (*create)(void *), void (*stageLoad)(void),
                           void (*editorDraw)(void), void (*editorLoad)(void), void (*serialize)(void), const char *inherited);
    void *RegisterObject_STD;
    void *(*GetGlobals)(void);
    void (*Super)(int32 classID, ModSuper callback, void *data);

    // Mod Info
    bool32 (*LoadModInfo)(const char *id, String *name, String *description, String *version, bool32 *active);
    void (*GetModPath)(const char *id, String *result);
    int32 (*GetModCount)(bool32 active);
    const char *(*GetModIDByIndex)(uint32 index);
    bool32 (*ForeachModID)(String *id);

    // Mod Callbacks & Public Functions
    void (*AddModCallback)(int32 callbackID, void (*callback)(void *));
    void *AddModCallback_STD;
    void (*AddPublicFunction)(const char *functionName, void *functionPtr);
    void *(*GetPublicFunction)(const char *id, const char *functionName);

    // Mod Settings
    bool32 (*GetSettingsBool)(const char *id, const char *key, bool32 fallback);
    int32 (*GetSettingsInteger)(const char *id, const char *key, int32 fallback);
    void (*GetSettingsString)(const char *id, const char *key, String *result, const char *fallback);
    void (*SetSettingsBool)(const char *key, bool32 val);
    void (*SetSettingsInteger)(const char *key, int32 val);
    void (*SetSettingsString)(const char *key, String *val);
    void (*SaveSettings)(void);

    // Config
    bool32 (*GetConfigBool)(const char *key, bool32 fallback);
    int32 (*GetConfigInteger)(const char *key, int32 fallback);
    void (*GetConfigString)(const char *key, String *result, const char *fallback);
    bool32 (*ForeachConfig)(String *textInfo);
    bool32 (*ForeachConfigCategory)(String *textInfo);

    Object *(*GetObject)(const char *name);

    // Achievements
    void (*RegisterAchievement)(const char *identifier, const char *name, const char *desc);
    void (*GetAchievementInfo)(uint32 id, String *name, String *description, String *identifer, bool32 *achieved);
    int32 (*GetAchievementIndexByID)(const char *identifier);
    int32 (*GetAchievementCount)(void);

    // Shaders
    void (*LoadShader)(const char *shaderName, bool32 linear);
} ModFunctionTable;
#endif

#if RETRO_REV02
// API Table
typedef struct {
    // API Core
    int32 (*GetUserLanguage)(void);
    bool32 (*GetConfirmButtonFlip)(void);
    void (*ExitGame)(void);
    void (*LaunchManual)(void);
    bool32 (*IsOverlayEnabled)(uint32 inputID);
    bool32 (*CheckDLC)(int32 dlc);
#if MANIA_USE_EGS
    bool32 (*SetupExtensionOverlay)(void);
    bool32 (*CanShowExtensionOverlay)(int32 overlay);
#endif
    bool32 (*ShowExtensionOverlay)(int32 overlay);
#if MANIA_USE_EGS
    bool32 (*CanShowAltExtensionOverlay)(int32 overlay);
    bool32 (*ShowAltExtensionOverlay)(int32 overlay);
    int32 (*GetConnectingStringID)(void);
    void (*ShowLimitedVideoOptions)(int32 id);
#endif

    // Achievements
    void (*UnlockAchievement)(AchievementID *id);
    bool32 (*GetAchievementsEnabled)(void);
    void (*SetAchievementsEnabled)(bool32 enabled);
#if MANIA_USE_EGS
    bool32 (*CheckAchievementsEnabled)(void);
    void (*SetAchievementNames)(String **names, int32 count);
#endif

    // Leaderboards
#if MANIA_USE_EGS
    bool32 (*CheckLeaderboardsEnabled)(void);
#endif
    void (*InitLeaderboards)(void);
    void (*FetchLeaderboard)(LeaderboardID *leaderboard, bool32 isUser);
    void (*TrackScore)(LeaderboardID *leaderboard, int32 score, void (*callback)(bool32 success, int32 rank));
    int32 (*GetLeaderboardsStatus)(void);
    LeaderboardAvail (*LeaderboardEntryViewSize)(void);
    LeaderboardAvail (*LeaderboardEntryLoadSize)(void);
    void (*LoadLeaderboardEntries)(int32 start, uint32 end, int32 type);
    void (*ResetLeaderboardInfo)(void);
    LeaderboardEntry *(*ReadLeaderboardEntry)(uint32 entryID);

    // Rich Presence
    void (*SetRichPresence)(int32 id, String *text);

    // Stats
    void (*TryTrackStat)(StatInfo *stat);
    bool32 (*GetStatsEnabled)(void);
    void (*SetStatsEnabled)(bool32 enabled);

    // Authorization
    void (*ClearPrerollErrors)(void);
    void (*TryAuth)(void);
    int32 (*GetUserAuthStatus)(void);
    bool32 (*GetUsername)(String *userName);

    // Storage
    void (*TryInitStorage)(void);
    int32 (*GetStorageStatus)(void);
    int32 (*GetSaveStatus)(void);
    void (*ClearSaveStatus)(void);
    void (*SetSaveStatusContinue)(void);
    void (*SetSaveStatusOK)(void);
    void (*SetSaveStatusForbidden)(void);
    void (*SetSaveStatusError)(void);
    void (*SetNoSave)(bool32 noSave);
    bool32 (*GetNoSave)(void);

    // User File Management
    void (*LoadUserFile)(const char *name, void *buffer, int32 size, void (*callback)(int32 status)); // load user file from game dir
    void (*SaveUserFile)(const char *name, void *buffer, int32 size, void (*callback)(int32 status), bool32 compressed); // save user file to game dir
    void (*DeleteUserFile)(const char *name, void (*callback)(int32 status)); // delete user file from game dir

    // User DBs
    uint16 (*InitUserDB)(const char *name, ...);
    uint16 (*LoadUserDB)(const char *filename, void (*callback)(int32 status));
    void (*SaveUserDB)(uint16 tableID, void (*callback)(int32 status));
    void (*ClearUserDB)(uint16 tableID);
    void (*ClearAllUserDBs)(void);
    void (*SetupUserDBRowSorting)(uint16 tableID);
    bool32 (*GetUserDBRowsChanged)(uint16 tableID);
    void (*AddRowSortFilter)(uint16 tableID, int32 type, const char *name, void *value);
    void (*SortDBRows)(uint16 tableID, int32 type, const char *name, bool32 sortAscending);
    int32 (*GetSortedUserDBRowCount)(uint16 tableID);
    int32 (*GetSortedUserDBRowID)(uint16 tableID, uint16 row);
    int32 (*AddUserDBRow)(uint16 tableID);
    void (*SetUserDBValue)(uint16 tableID, int32 row, int32 type, const char *name, void *value);
    void (*GetUserDBValue)(uint16 tableID, int32 row, int32 type, const char *name, void *value);
    uint32 (*GetUserDBRowUUID)(uint16 tableID, uint16 row);
    int32 (*GetUserDBRowByID)(uint16 tableID, uint32 uuid);
    void (*GetUserDBRowCreationTime)(uint16 tableID, uint16 row, char *buffer, uint32 bufferSize, const char *format);
    void (*RemoveDBRow)(uint16 tableID, uint16 row);
    void (*RemoveAllDBRows)(uint16 tableID);
} APIFunctionTable;
#endif

// Function Table
typedef struct {
    // Registration
    void (*RegisterGlobalVariables)(void **globals, int32 size);
    void (*RegisterObject)(Object **staticVars, const char *name, uint32 entityClassSize, uint32 staticClassSize, void (*update)(void),
                           void (*lateUpdate)(void), void (*staticUpdate)(void), void (*draw)(void), void (*create)(void *), void (*stageLoad)(void),
                           void (*editorDraw)(void), void (*editorLoad)(void), void (*serialize)(void));
#if RETRO_REV02
    void (*RegisterStaticVariables)(void **varClass, const char *name, uint32 classSize);
#endif

    // Entities & Objects
    bool32 (*GetActiveEntities)(uint16 group, Entity **entity);
    bool32 (*GetEntities)(uint16 classID, Entity **entity);
    void (*BreakForeachLoop)(void);
    void (*SetEditableVar)(uint8 type, const char *name, uint8 classID, int32 storeOffset);
    void *(*GetEntity)(uint16 slot);
    int32 (*GetEntitySlot)(void *entity);
    int32 (*GetEntityCount)(uint16 classID, bool32 isActive);
    int32 (*GetDrawListRef)(uint8 drawGroup, uint16 entitySlot);
    void *(*GetDrawListRefPtr)(uint8 drawGroup, uint16 entitySlot);
    void (*ResetEntityPtr)(void *entity, uint16 classID, void *data);
    void (*ResetEntitySlot)(uint16 slot, uint16 classID, void *data);
    Entity *(*CreateEntity)(uint16 classID, void *data, int32 x, int32 y);
    void (*CopyEntity)(void *destEntity, void *srcEntity, bool32 clearSrcEntity);
    bool32 (*CheckOnScreen)(void *entity, Vector2 *range);
    bool32 (*CheckPosOnScreen)(Vector2 *position, Vector2 *range);
    void (*AddDrawListRef)(uint8 drawGroup, uint16 entityID);
    void (*SwapDrawListEntries)(uint8 drawGroup, uint16 startSlotID, uint16 endSlotID, uint16 count);
    void (*SetDrawLayerProperties)(uint8 drawGroup, bool32 sorted, void (*callback)(void));

    // Scene Management
    void (*SetScene)(const char *categoryName, const char *sceneName);
    void (*SetEngineState)(uint8 state);
#if RETRO_REV02
    void (*ForceHardReset)(bool32 shouldHardReset);
#endif
    bool32 (*CheckValidScene)(void);
    int32 (*CheckStageFolder)(const char *folderName);
    int32 (*LoadScene)(void);
    int32 (*FindObject)(const char *name);

    // Cameras
    void (*ClearCameras)(void);
    void (*AddCamera)(Vector2 *targetPos, int32 offsetX, int32 offsetY, bool32 worldRelative);

    // API (Rev01 only)
#if !RETRO_REV02
    void *(*GetAPIFunction)(const char *funcName);
#endif

    // Window/Video Settings
    int32 (*GetVideoSetting)(int32 id);
    void (*SetVideoSetting)(int32 id, int32 value);
    void (*UpdateWindow)(void);

    // Math
    int32 (*Sin1024)(int32 angle);
    int32 (*Cos1024)(int32 angle);
    int32 (*Tan1024)(int32 angle);
    int32 (*ASin1024)(int32 angle);
    int32 (*ACos1024)(int32 angle);
    int32 (*Sin512)(int32 angle);
    int32 (*Cos512)(int32 angle);
    int32 (*Tan512)(int32 angle);
    int32 (*ASin512)(int32 angle);
    int32 (*ACos512)(int32 angle);
    int32 (*Sin256)(int32 angle);
    int32 (*Cos256)(int32 angle);
    int32 (*Tan256)(int32 angle);
    int32 (*ASin256)(int32 angle);
    int32 (*ACos256)(int32 angle);
    int32 (*Rand)(int32 min, int32 max);
    int32 (*RandSeeded)(int32 min, int32 max, int32 *randSeed);
    void (*SetRandSeed)(int32 key);
    uint8 (*ATan2)(int32 x, int32 y);

    // Matrices
    void (*SetIdentityMatrix)(Matrix *matrix);
    void (*MatrixMultiply)(Matrix *dest, Matrix *matrixA, Matrix *matrixB);
    void (*MatrixTranslateXYZ)(Matrix *matrix, int32 x, int32 y, int32 z, bool32 setIdentity);
    void (*MatrixScaleXYZ)(Matrix *matrix, int32 scaleX, int32 scaleY, int32 scaleZ);
    void (*MatrixRotateX)(Matrix *matrix, int32 angle);
    void (*MatrixRotateY)(Matrix *matrix, int32 angle);
    void (*MatrixRotateZ)(Matrix *matrix, int32 angle);
    void (*MatrixRotateXYZ)(Matrix *matrix, int32 angleX, int32 angleY, int32 angleZ);
    void (*MatrixInverse)(Matrix *dest, Matrix *matrix);
    void (*MatrixCopy)(Matrix *matDest, Matrix *matSrc);

    // Strings
    void (*InitString)(String *string, const char *text, uint32 textLength);
    void (*CopyString)(String *dst, String *src);
    void (*SetString)(String *string, const char *text);
    void (*AppendString)(String *string, String *appendString);
    void (*AppendText)(String *string, const char *appendText);
    void (*LoadStringList)(String *stringList, const char *filePath, uint32 charSize);
    bool32 (*SplitStringList)(String *splitStrings, String *stringList, int32 startStringID, int32 stringCount);
    void (*GetCString)(char *destChars, String *string);
    bool32 (*CompareStrings)(String *string1, String *string2, bool32 exactMatch);

    // Screens & Displays
    void (*GetDisplayInfo)(int32 *displayID, int32 *width, int32 *height, int32 *refreshRate, char *text);
    void (*GetWindowSize)(int32 *width, int32 *height);
    int32 (*SetScreenSize)(uint8 screenID, uint16 width, uint16 height);
    void (*SetClipBounds)(uint8 screenID, int32 x1, int32 y1, int32 x2, int32 y2);
#if RETRO_REV02
    void (*SetScreenRenderVertices)(uint8 startVert2P_S1, uint8 startVert2P_S2, uint8 startVert3P_S1, uint8 startVert3P_S2, uint8 startVert3P_S3);
#endif

    // Spritesheets
    int16 (*LoadSpriteSheet)(const char *path, Scopes scope);

    // Palettes & Colors
#if RETRO_REV02
    void (*SetTintLookupTable)(uint16 *lookupTable);
#else
    uint16 *(*GetTintLookupTable)(void);
#endif
    void (*SetPaletteMask)(uint32 maskColor);
    void (*SetPaletteEntry)(uint8 bankID, uint8 index, uint32 color);
    uint32 (*GetPaletteEntry)(uint8 bankID, uint8 index);
    void (*SetActivePalette)(uint8 newActiveBank, int32 startLine, int32 endLine);
    void (*CopyPalette)(uint8 sourceBank, uint8 srcBankStart, uint8 destinationBank, uint8 destBankStart, uint16 count);
#if RETRO_REV02
    void (*LoadPalette)(uint8 bankID, const char *path, uint16 rowFlags);
#endif
    void (*RotatePalette)(uint8 bankID, uint8 startIndex, uint8 endIndex, bool32 right);
    void (*SetLimitedFade)(uint8 destBankID, uint8 srcBankA, uint8 srcBankB, int16 blendAmount, int32 startIndex, int32 endIndex);
#if RETRO_REV02
    void (*BlendColors)(uint8 destBankID, uint32 *srcColorsA, uint32 *srcColorsB, int32 blendAmount, int32 startIndex, int32 count);
#endif

    // Drawing
    void (*DrawRect)(int32 x, int32 y, int32 width, int32 height, uint32 color, int32 alpha, InkEffects inkEffect, bool32 screenRelative);
    void (*DrawLine)(int32 x1, int32 y1, int32 x2, int32 y2, uint32 color, int32 alpha, InkEffects inkEffect, bool32 screenRelative);
    void (*DrawCircle)(int32 x, int32 y, int32 radius, uint32 color, int32 alpha, InkEffects inkEffect, bool32 screenRelative);
    void (*DrawCircleOutline)(int32 x, int32 y, int32 innerRadius, int32 outerRadius, uint32 color, int32 alpha, InkEffects inkEffect,
                              bool32 screenRelative);
    void (*DrawFace)(Vector2 *verticies, int32 vertCount, int32 r, int32 g, int32 b, int32 alpha, InkEffects inkEffect);
    void (*DrawBlendedFace)(Vector2 *verticies, color *vertColors, int32 vertCount, int32 alpha, InkEffects inkEffect);
    void (*DrawSprite)(Animator *animator, Vector2 *position, bool32 screenRelative);
    void (*DrawDeformedSprite)(uint16 sheet, InkEffects inkEffect, bool32 screenRelative);
    void (*DrawText)(Animator *animator, Vector2 *position, String *info, int32 startFrame, int32 endFrame, int32 align, int32 spacing, void *unused,
                     Vector2 *charOffsets, bool32 screenRelative);
    void (*DrawTile)(uint16 *tileInfo, int32 countX, int32 countY, Vector2 *position, Vector2 *offset, bool32 screenRelative);
    void (*CopyTile)(uint16 dest, uint16 src, uint16 count);
    void (*DrawAniTiles)(uint16 sheetID, uint16 tileIndex, uint16 srcX, uint16 srcY, uint16 width, uint16 height);
    void (*FillScreen)(uint32 color, int32 alphaR, int32 alphaG, int32 alphaB);

    // Meshes & 3D Scenes
    uint16 (*LoadMesh)(const char *filename, uint8 scope);
    uint16 (*Create3DScene)(const char *identifier, uint16 faceCount, uint8 scope);
    void (*Prepare3DScene)(uint16 index);
    void (*SetDiffuseColor)(uint16 index, int32 x, int32 y, int32 z);
    void (*SetDiffuseIntensity)(uint16 index, int32 x, int32 y, int32 z);
    void (*SetSpecularIntensity)(uint16 index, int32 x, int32 y, int32 z);
    void (*AddModelTo3DScene)(uint16 modelFrames, uint16 sceneIndex, uint8 drawMode, Matrix *matWorld, Matrix *matNormal, color color);
    void (*SetModelAnimation)(uint16 modelFrames, Animator *animator, int16 speed, uint8 loopIndex, bool32 forceApply, uint16 frameID);
    void (*AddMeshFrameTo3DScene)(uint16 modelFrames, uint16 sceneIndex, Animator *animator, uint8 drawMode, Matrix *matWorld, Matrix *matNormal,
                                  color color);
    void (*Draw3DScene)(uint16 index);

    // Sprite Animations & Frames
    uint16 (*LoadSpriteAnimation)(const char *path, Scopes scope);
    uint16 (*CreateSpriteAnimation)(const char *filename, uint32 frameCount, uint32 listCount, Scopes scope);
    void (*SetSpriteAnimation)(uint16 aniFrames, uint16 listID, Animator *animator, bool32 forceApply, int16 frameID);
    void (*EditSpriteAnimation)(uint16 aniFrames, uint16 listID, const char *name, int32 frameOffset, uint16 frameCount, int16 speed, uint8 loopIndex,
                                uint8 rotationFlag);
    void (*SetSpriteString)(uint16 aniFrames, uint16 listID, String *info);
    uint16 (*FindSpriteAnimation)(uint16 aniFrames, const char *name);
    SpriteFrame *(*GetFrame)(uint16 aniFrames, uint16 listID, int32 frameID);
    Hitbox *(*GetHitbox)(Animator *animator, uint8 hitboxID);
    int16 (*GetFrameID)(Animator *animator);
    int32 (*GetStringWidth)(uint16 aniFrames, uint16 listID, String *info, int32 startIndex, int32 length, int32 spacing);
    void (*ProcessAnimation)(Animator *animator);

    // Tile Layers
    int32 (*GetTileLayerID)(const char *name);
    TileLayer *(*GetTileLayer)(int32 layerID);
    void (*GetLayerSize)(uint16 layer, Vector2 *size, bool32 usePixelUnits);
    uint16 (*GetTileInfo)(uint16 layer, int32 x, int32 y);
    void (*SetTileInfo)(uint16 layer, int32 x, int32 y, uint16 tile);
    int32 (*CopyTileLayer)(uint16 dstLayerID, int32 dstStartX, int32 dstStartY, uint16 srcLayerID, int32 srcStartX, int32 srcStartY, int32 countX,
                           int32 countY);
    void (*ProcessParallax)(TileLayer *TileLayer);
    ScanlineInfo *(*GetScanlines)(void);

    // Object & Tile Collisions
    bool32 (*CheckObjectCollisionTouchBox)(void *thisEntity, Hitbox *thisHitbox, void *otherEntity, Hitbox *otherHitbox);
    bool32 (*CheckObjectCollisionTouchCircle)(void *thisEntity, int32 thisOffset, void *otherEntity, int32 otherOffset);
    uint8 (*CheckObjectCollisionBox)(void *thisEntity, Hitbox *thisHitbox, void *otherEntity, Hitbox *otherHitbox, bool32 setPos);
    bool32 (*CheckObjectCollisionPlatform)(void *thisEntity, Hitbox *thisHitbox, void *otherEntity, Hitbox *otherHitbox, bool32 setPos);
    bool32 (*ObjectTileCollision)(void *entity, uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset,
                                  bool32 setPos);
    bool32 (*ObjectTileGrip)(void *entity, uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset,
                             int32 tolerance);
    void (*ProcessObjectMovement)(void *entity, Hitbox *outer, Hitbox *inner);
    int32 (*GetTileAngle)(uint16 tileID, uint8 cPlane, uint8 cMode);
    void (*SetTileAngle)(uint16 tileID, uint8 cPlane, uint8 cMode, uint8 angle);
    uint8 (*GetTileFlags)(uint16 tileID, uint8 cPlane);
    void (*SetTileFlags)(uint16 tileID, uint8 cPlane, uint8 flags);

    // Audio
    int32 (*GetSfx)(const char *path);
    int32 (*PlaySfx)(uint16 sfx, int32 loopPoint, int32 priority);
    void (*StopSfx)(uint16 sfx);
    int32 (*PlayStream)(const char *filename, uint32 channel, uint32 startPos, uint32 loopPoint, bool32 loadASync);
    void (*SetChannelAttributes)(uint8 channel, float volume, float pan, float speed);
    void (*StopChannel)(uint32 channel);
    void (*PauseChannel)(uint32 channel);
    void (*ResumeChannel)(uint32 channel);
    bool32 (*IsSfxPlaying)(uint16 sfxID);
    bool32 (*ChannelActive)(uint32 channel);
    uint32 (*GetChannelPos)(uint32 channel);

    // Videos & "HD Images"
    void (*LoadVideo)(const char *filename, double startDelay, bool32 (*skipCallback)(void));
    bool32 (*LoadImage)(const char *filename, double displayLength, double speed, bool32 (*skipCallback)(void));

    // Input
#if RETRO_REV02
    int32 (*ControllerIDForInputID)(uint8 controllerID);
    int32 (*MostRecentActiveControllerID)(bool32 confirmOnly, bool32 unassignedOnly, uint32 maxInactiveTimer);
    int32 (*GetControllerType)(uint32 inputID);
    int32 (*GetAssignedControllerID)(uint32 inputID);
    int32 (*GetInputUnknown)(uint32 inputID);
    int32 (*InputUnknown1)(uint32 inputID, int32 unknown1, int32 unknown2);
    int32 (*InputUnknown2)(uint32 inputID, int32 unknown1, int32 unknown2);
    int32 (*GetControllerUnknown)(void);
    int32 (*ControllerUnknown1)(uint8 controllerID, int32 unknown1, int32 unknown2);
    int32 (*ControllerUnknown2)(uint8 controllerID, int32 unknown1, int32 unknown2);
    void (*AssignControllerID)(uint8 controllerID, uint32 inputID);
    bool32 (*ControllerIsAssigned)(uint8 controllerID);
    void (*ResetControllerAssignments)(void);
#endif
#if !RETRO_REV02
    void (*GetUnknownInputValue)(int32 controllerID, int32 type, int32 *value);
#endif

    // User File Management
    int32 (*LoadUserFile)(const char *filename, void *buffer, uint32 size); // load user file from exe dir
    int32 (*SaveUserFile)(const char *fileName, void *buffer, uint32 size); // save use file to exe dir

    // Printing (Rev02)
#if RETRO_REV02
    void (*PrintLog)(PrintModes printType, const char *message, ...);
    void (*PrintText)(PrintModes printType, const char *message);
    void (*PrintString)(PrintModes printType, String *message);
    void (*PrintUInt32)(PrintModes printType, const char *message, uint32 i);
    void (*PrintInt32)(PrintModes printType, const char *message, int32 i);
    void (*PrintFloat)(PrintModes printType, const char *message, float f);
    void (*PrintVector2)(PrintModes printType, const char *message, int32 x, int32 y);
    void (*PrintHitbox)(PrintModes printType, const char *message, Hitbox *hitbox);
#endif

    // Editor
    void (*SetActiveVariable)(int32 classID, const char *name);
    void (*AddVarEnumValue)(const char *name);

    // Debugging
#if RETRO_REV02
    void (*ClearViewableVariables)(void);
    void (*AddViewableVariable)(const char *name, void *value, ViewableVarTypes type, int32 min, int32 max);
#endif

    // Printing (Rev01)
#if !RETRO_REV02
    void (*PrintMessage)(void *message, uint8 type);
#endif
} RSDKFunctionTable;

// -------------------------
// HELPERS
// -------------------------

// used for casts and etc
#define Type_StateMachine void (*)(void)
// used for variable decl
#define StateMachine(name) void (*name)(void)
#define StateMachine_Run(func)                                                                                                                       \
    if (func) {                                                                                                                                      \
        func();                                                                                                                                      \
    }
#define StateMachine_None NULL

// Fancy macro + build magic to make tables & static vars
#define TABLE(var, ...)  var
#define STATIC(var, val) var

#define RSDK_EDITABLE_VAR(object, type, var) RSDK.SetEditableVar(type, #var, (uint8)object->classID, offsetof(Entity##object, var))
#define RSDK_EDITABLE_ARRAY(object, type, var, count, arrType)                                                                                       \
    for (int i = 0; i < (count); ++i) {                                                                                                              \
        char buffer[0x40];                                                                                                                           \
        sprintf_s(buffer, (int32)sizeof(buffer), "%s%d", #var, i);                                                                                   \
        RSDK.SetEditableVar(type, buffer, (uint8)object->classID, offsetof(Entity##object, var) + sizeof(arrType) * i);                              \
    }

#if RETRO_INCLUDE_EDITOR
// Some extra precaution to prevent crashes in editor
#define RSDK_ACTIVE_VAR(object, var)                                                                                                                 \
    if (object) {                                                                                                                                    \
        RSDK.SetActiveVariable(object->classID, #var);                                                                                               \
    }                                                                                                                                                \
    else {                                                                                                                                           \
        RSDK.SetActiveVariable(-1, #var);                                                                                                            \
    }
#define RSDK_ENUM_VAR(name, var) RSDK.AddVarEnumValue(name)

#define RSDK_DRAWING_OVERLAY(isDrawingOverlay) SceneInfo->debugMode = isDrawingOverlay

#define RSDK_REGISTER_OBJECT(object)                                                                                                                 \
    RSDK.RegisterObject((Object **)&object, #object, sizeof(Entity##object), sizeof(Object##object), object##_Update, object##_LateUpdate,           \
                        object##_StaticUpdate, object##_Draw, object##_Create, object##_StageLoad, object##_EditorDraw, object##_EditorLoad,         \
                        object##_Serialize)
#else
#define RSDK_REGISTER_OBJECT(object)                                                                                                                 \
    RSDK.RegisterObject((Object **)&object, #object, sizeof(Entity##object), sizeof(Object##object), object##_Update, object##_LateUpdate,           \
                        object##_StaticUpdate, object##_Draw, object##_Create, object##_StageLoad, NULL, NULL, object##_Serialize)
#endif

#if RETRO_USE_MOD_LOADER
#define MOD_REGISTER_OBJECT(object, inherit)                                                                                                         \
    Mod.RegisterObject((Object **)&object, #object, sizeof(Entity##object), sizeof(Object##object), object##_Update, object##_LateUpdate,            \
                       object##_StaticUpdate, object##_Draw, object##_Create, object##_StageLoad, object##_EditorDraw, object##_EditorLoad,          \
                       object##_Serialize, inherit)
#endif

#if RETRO_REV02
#define RSDK_REGISTER_STATIC_VARIABLES(variables) RSDK.RegisterStaticVariables((void **)&variables, #variables, sizeof(Object##variables))
#endif

#define RSDK_THIS(class)                  Entity##class *self = (Entity##class *)SceneInfo->entity
#define RSDK_THIS_GEN()                   Entity *self = SceneInfo->entity
#define RSDK_GET_ENTITY(slot, class)      ((Entity##class *)RSDK.GetEntity(slot))
#define RSDK_GET_ENTITY_GEN(slot)         ((Entity *)RSDK.GetEntity(slot))
#define CREATE_ENTITY(object, data, x, y) ((Entity##object *)RSDK.CreateEntity(object->classID, data, x, y))

#define INIT_STRING(string)                                                                                                                          \
    string.chars  = NULL;                                                                                                                            \
    string.length = 0;                                                                                                                               \
    string.size   = 0

// Initializes entity values to the defaults
#define INIT_ENTITY(entity)                                                                                                                          \
    (entity)->active        = ACTIVE_BOUNDS;                                                                                                         \
    (entity)->visible       = false;                                                                                                                 \
    (entity)->updateRange.x = 0x800000;                                                                                                              \
    (entity)->updateRange.y = 0x800000;

#define foreach_active(type, entityOut)                                                                                                              \
    Entity##type *entityOut = NULL;                                                                                                                  \
    while (RSDK.GetActiveEntities(type->classID, (Entity **)&entityOut))
#define foreach_all(type, entityOut)                                                                                                                 \
    Entity##type *entityOut = NULL;                                                                                                                  \
    while (RSDK.GetEntities(type->classID, (Entity **)&entityOut))

#define foreach_active_group(group, entityOut)                                                                                                       \
    Entity *entityOut = NULL;                                                                                                                        \
    while (RSDK.GetActiveEntities(group, (Entity **)&entityOut))
#define foreach_all_group(group, entityOut)                                                                                                          \
    Entity *entityOut = NULL;                                                                                                                        \
    while (RSDK.GetEntities(group, (Entity **)&entityOut))

#if RETRO_USE_MOD_LOADER
#define foreach_config(text)                                                                                                                         \
    String *text = NULL;                                                                                                                             \
    while (Mod.ForeachConfig(&text))
#define foreach_configCategory(text)                                                                                                                 \
    String *text = NULL;                                                                                                                             \
    while (Mod.ForeachConfigCategory(&text))
#endif

#define foreach_break                                                                                                                                \
    RSDK.BreakForeachLoop();                                                                                                                         \
    break
#define foreach_return                                                                                                                               \
    RSDK.BreakForeachLoop();                                                                                                                         \
    return

#define destroyEntity(entity)   RSDK.ResetEntityPtr(entity, TYPE_BLANK, NULL)
#define destroyEntitySlot(slot) RSDK.ResetEntitySlot(slot, TYPE_BLANK, NULL)

#if RETRO_INCLUDE_EDITOR
#define showGizmos() (SceneInfo->listPos == SceneInfo->entitySlot || SceneInfo->effectGizmo)
#endif

// -------------------------
// ENGINE VARIABLES
// -------------------------

extern RSDKFunctionTable RSDK;
#if RETRO_REV02
extern APIFunctionTable API;
#endif
#if RETRO_USE_MOD_LOADER
extern ModFunctionTable Mod;
#endif

extern RSDKSceneInfo *SceneInfo;
extern RSDKGameInfo *GameInfo;
#if MANIA_USE_PLUS
extern RSDKSKUInfo *SKU;
#endif
extern RSDKControllerState *ControllerInfo;
extern RSDKAnalogState *AnalogStickInfoL;
#if MANIA_USE_PLUS
extern RSDKAnalogState *AnalogStickInfoR;
extern RSDKTriggerState *TriggerInfoL;
extern RSDKTriggerState *TriggerInfoR;
#endif
extern RSDKTouchInfo *TouchInfo;
#if MANIA_USE_PLUS
extern RSDKUnknownInfo *UnknownInfo;
#endif
extern RSDKScreenInfo *ScreenInfo;

#endif /* GAMELINK_H */