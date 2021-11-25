#include "SonicMania.h"

#if RETRO_USE_PLUS
ObjectEncoreGoodEnd *EncoreGoodEnd;

void EncoreGoodEnd_Update(void)
{
    void *states[] = { EncoreGoodEnd_CutsceneState_Unknown1,
                       EncoreGoodEnd_CutsceneState_Unknown2,
                       EncoreGoodEnd_CutsceneState_Unknown3,
                       EncoreGoodEnd_CutsceneState_Unknown4,
                       EncoreGoodEnd_CutsceneState_Unknown5,
                       EncoreGoodEnd_CutsceneState_Unknown6,
                       NULL };

    RSDK_THIS(EncoreGoodEnd);
    if (!self->activated) {
        foreach_active(Player, player)
        {
            if (Player_CheckCollisionTouch(player, self, &self->hitbox)) {
                CutsceneSeq_StartSequence((Entity *)self, states);

                EntityCutsceneSeq *seq = RSDK_GET_ENTITY(SLOT_CUTSCENESEQ, CutsceneSeq);
                if (seq->objectID) {
                    seq->skipType    = SKIPTYPE_CALLBACK;
                    seq->skipCallback = EncoreGoodEnd_SkipCB;
                }
                self->activated = true;
            }
        }
    }
}

void EncoreGoodEnd_LateUpdate(void) {}

void EncoreGoodEnd_StaticUpdate(void) {}

void EncoreGoodEnd_Draw(void) {}

void EncoreGoodEnd_Create(void *data)
{
    RSDK_THIS(EncoreGoodEnd);
    if (!SceneInfo->inEditor) {
        self->active        = ACTIVE_NORMAL;
        self->visible       = false;
        self->updateRange.x = 0x800000;
        self->updateRange.y = 0x800000;
        if (!self->size.x)
            self->size.x = 0x1A80000;
        if (!self->size.y)
            self->size.y = 0xF00000;
        self->updateRange.x       = 0x800000 + self->size.x;
        self->updateRange.y       = 0x800000 + self->size.y;
        SceneInfo->timeEnabled = false;
        EncoreGoodEnd->unused1      = 0;
        Player->playerCount         = 4;

        self->hitbox.left   = -self->size.x >> 17;
        self->hitbox.right  = self->size.x >> 17;
        self->hitbox.top    = -self->size.y >> 17;
        self->hitbox.bottom = self->size.y >> 17;
        EncoreGoodEnd_SetupDecorations();
    }
}

void EncoreGoodEnd_StageLoad(void) { EncoreGoodEnd->sfxSnap = RSDK.GetSfx("SPZ/ShBugSnap.wav"); }

void EncoreGoodEnd_SetupDecorations(void)
{
    int32 id = 0;
    foreach_all(Decoration, decor)
    {
        if (id >= 16)
            break;
        if (id == 12) {
            decor->drawFX = FX_NONE;
        }
        if (id >= 12)
            decor->visible = false;
        EncoreGoodEnd->decorations[id] = decor;
        ++id;
    }
}

void EncoreGoodEnd_Unknown2(int32 id)
{
    switch (id) {
        case ID_SONIC: EncoreGoodEnd->decorations[5]->visible = false; break;
        case ID_TAILS:
            EncoreGoodEnd->decorations[6]->visible = false;
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 23, &EncoreGoodEnd->decorations[1]->animator, false, 0);
            break;
        case ID_KNUCKLES:
            EncoreGoodEnd->decorations[7]->visible  = false;
            EncoreGoodEnd->decorations[10]->visible = false;
            break;
        case ID_MIGHTY:
            EncoreGoodEnd->decorations[8]->visible  = false;
            EncoreGoodEnd->decorations[11]->visible = false;
            break;
        case ID_RAY:
            EncoreGoodEnd->decorations[9]->visible = false;
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 23, &EncoreGoodEnd->decorations[4]->animator, false, 0);
            break;
        default: return;
    }
}

void EncoreGoodEnd_Unknown9(void)
{
    RSDK_THIS(Player);

    int32 id             = self->characterID;
    self->velocity.x = 0x18000;
    int32 playerID       = -1;
    for (self->groundVel = 0x18000; id > 0; ++playerID) id >>= 1;

    if (self->position.x >= EncoreGoodEnd->decorations[playerID + 5]->position.x) {
        self->position.x = EncoreGoodEnd->decorations[playerID + 5]->position.x;
        self->velocity.x = 0;
        self->groundVel  = 0;
        switch (self->characterID) {
            case ID_SONIC:
                self->visible                                   = false;
                EncoreGoodEnd->decorations[playerID + 5]->visible = true;
                RSDK.SetSpriteAnimation(Decoration->aniFrames, ANI_JOG, &EncoreGoodEnd->decorations[playerID + 5]->animator, true, 0);
                self->velocity.x = 0;
                self->groundVel  = 0;
                self->state      = EncoreGoodEnd_Unknown11;
                break;
            case ID_TAILS:
            case ID_KNUCKLES:
            case ID_MIGHTY:
            case ID_RAY:
                self->jumpPress = true;
                Player_State_Ground();
                self->jumpPress       = false;
                self->state           = EncoreGoodEnd_Unknown10;
                self->nextAirState    = EncoreGoodEnd_Unknown10;
                self->nextGroundState = Player_State_None;
                break;
            default: break;
        }
    }
    else {
        Player_State_Ground();
    }
}

void EncoreGoodEnd_Unknown10(void)
{
    RSDK_THIS(Player);
    Player_State_Air();
    if (self->velocity.y > 0) {
        int32 playerID       = -1;
        for (int32 id = self->characterID; id > 0; ++playerID) id >>= 1;

        if (self->position.y >= (EncoreGoodEnd->decorations[playerID + 5]->position.y - 0x80000)) {
            self->position.y                                = (EncoreGoodEnd->decorations[playerID + 5]->position.y - 0x80000);
            self->velocity.y                                = 0;
            self->visible                                   = false;
            EncoreGoodEnd->decorations[playerID + 5]->visible = true;
            switch (self->characterID) {
                case ID_TAILS:
                    RSDK.SetSpriteAnimation(Decoration->aniFrames, 22, &EncoreGoodEnd->decorations[playerID + 5]->animator, true, 0);
                    RSDK.SetSpriteAnimation(Decoration->aniFrames, 0, &EncoreGoodEnd->decorations[1]->animator, true, 0);
                    self->state = Player_State_None;
                    break;
                case ID_KNUCKLES:
                    RSDK.SetSpriteAnimation(Decoration->aniFrames, 13, &EncoreGoodEnd->decorations[playerID + 5]->animator, true, 0);
                    EncoreGoodEnd->decorations[10]->visible = true;
                    RSDK.SetSpriteAnimation(Decoration->aniFrames, 14, &EncoreGoodEnd->decorations[10]->animator, true, 0);
                    EncoreGoodEnd->decorations[10]->animator.speed = 0;
                    self->state                                           = Player_State_None;
                    break;
                case ID_MIGHTY:
                    RSDK.SetSpriteAnimation(Decoration->aniFrames, 18, &EncoreGoodEnd->decorations[playerID + 5]->animator, true, 0);
                    EncoreGoodEnd->decorations[11]->visible = true;
                    RSDK.SetSpriteAnimation(Decoration->aniFrames, 19, &EncoreGoodEnd->decorations[11]->animator, true, 0);
                    EncoreGoodEnd->decorations[11]->animator.speed = 0;
                    self->state                                           = Player_State_None;
                    break;
                case ID_RAY:
                    RSDK.SetSpriteAnimation(Decoration->aniFrames, 5, &EncoreGoodEnd->decorations[playerID + 5]->animator, true, 0);
                    RSDK.SetSpriteAnimation(Decoration->aniFrames, 0, &EncoreGoodEnd->decorations[4]->animator, true, 0);
                    self->state = Player_State_None;
                    break;
                default: self->state = Player_State_None; break;
            }
        }
    }
}

void EncoreGoodEnd_Unknown11(void)
{
    RSDK_THIS(Player);

    EntityDecoration *playerDecor = EncoreGoodEnd->decorations[5];
    switch (self->abilityValues[0]) {
        case 0:
            if (EncoreGoodEnd->decorations[5]->animator.frameID == 8) {
                self->abilityValues[0]                      = 1;
                EncoreGoodEnd->decorations[12]->visible    = true;
                EncoreGoodEnd->decorations[12]->velocity.y = -0x40000;
                self->abilityValues[1]                          = 0;
            }
            break;
        case 1:
            if (++self->abilityValues[1] >= 15) {
                self->abilityValues[1]                      = 0;
                self->abilityValues[0]                      = 2;
                EncoreGoodEnd->decorations[13]->visible    = true;
                EncoreGoodEnd->decorations[13]->velocity.y = -0x40000;
            }
            break;
        case 2:
            if (++self->abilityValues[1] >= 15) {
                self->abilityValues[1]                      = 0;
                self->abilityValues[0]                      = 3;
                EncoreGoodEnd->decorations[14]->visible    = true;
                EncoreGoodEnd->decorations[14]->velocity.y = -0x40000;
            }
            break;
        case 3:
            if (++self->abilityValues[1] >= 15) {
                self->abilityValues[1]                      = 0;
                self->abilityValues[0]                      = 4;
                EncoreGoodEnd->decorations[15]->visible    = true;
                EncoreGoodEnd->decorations[15]->velocity.y = -0x40000;
            }
            break;
        case 4:
            if (EncoreGoodEnd->decorations[5]->animator.frameID >= 22)
                self->state = Player_State_None;
            break;
        default: break;
    }

    int32 anim = playerDecor->animator.frameID;
    if (anim == ANI_RUN || anim == ANI_SKID || anim == ANI_DROPDASH)
        playerDecor->animator.speed = 0;

    // Sonic's Ice creams
    if (EncoreGoodEnd->decorations[12]->visible) {
        if (EncoreGoodEnd->decorations[12]->velocity.y < 0) {
            self->direction = FLIP_Y;
        }
        else {
            EncoreGoodEnd->decorations[12]->drawOrder = Zone->playerDrawHigh;
            self->direction                         = FLIP_NONE;
        }

        EncoreGoodEnd->decorations[12]->position.y += EncoreGoodEnd->decorations[12]->velocity.y;
        EncoreGoodEnd->decorations[12]->velocity.y += 0x3800;
        if (EncoreGoodEnd->decorations[12]->position.y >= playerDecor->position.y) {
            EncoreGoodEnd->decorations[12]->visible = 0;
            ++playerDecor->animator.frameID;
            playerDecor->animator.speed = 1;
        }
    }

    if (EncoreGoodEnd->decorations[13]->visible) {
        if (EncoreGoodEnd->decorations[13]->velocity.y < 0) {
            self->direction = FLIP_Y;
        }
        else {
            EncoreGoodEnd->decorations[13]->drawOrder = Zone->playerDrawHigh;
            self->direction                         = FLIP_NONE;
        }

        EncoreGoodEnd->decorations[13]->position.y += EncoreGoodEnd->decorations[13]->velocity.y;
        EncoreGoodEnd->decorations[13]->velocity.y += 0x3800;
        if (EncoreGoodEnd->decorations[13]->position.y >= playerDecor->position.y) {
            EncoreGoodEnd->decorations[13]->visible = false;
            ++playerDecor->animator.frameID;
            playerDecor->animator.speed = 1;
        }
    }

    if (EncoreGoodEnd->decorations[14]->visible) {
        if (EncoreGoodEnd->decorations[14]->velocity.y < 0) {
            self->direction = FLIP_Y;
        }
        else {
            EncoreGoodEnd->decorations[14]->drawOrder = Zone->playerDrawHigh;
            self->direction                         = FLIP_NONE;
        }

        EncoreGoodEnd->decorations[14]->position.y += EncoreGoodEnd->decorations[14]->velocity.y;
        EncoreGoodEnd->decorations[14]->velocity.y += 0x3800;
        if (EncoreGoodEnd->decorations[14]->position.y >= playerDecor->position.y - 0x40000) {
            EncoreGoodEnd->decorations[14]->visible = false;
            ++playerDecor->animator.frameID;
            playerDecor->animator.speed = 1;
        }
    }

    if (EncoreGoodEnd->decorations[15]->visible == 1) {
        if (EncoreGoodEnd->decorations[15]->velocity.y < 0) {
            self->direction = FLIP_Y;
        }
        else {
            EncoreGoodEnd->decorations[15]->drawOrder = Zone->playerDrawHigh;
            self->direction                         = FLIP_NONE;
        }

        EncoreGoodEnd->decorations[15]->position.y += EncoreGoodEnd->decorations[15]->velocity.y;
        EncoreGoodEnd->decorations[15]->velocity.y += 0x3800;
        if (EncoreGoodEnd->decorations[15]->position.y >= playerDecor->position.y - 0x80000) {
            EncoreGoodEnd->decorations[15]->visible = false;
            ++playerDecor->animator.frameID;
            playerDecor->animator.speed = 1;
        }
    }
}

bool32 EncoreGoodEnd_CutsceneState_Unknown1(EntityCutsceneSeq *host)
{
    RSDK_THIS(EncoreGoodEnd);
    RSDK_GET_PLAYER(player1, player2, camera);

    if (!host->timer) {
        player1->state      = Player_State_None;
        player1->stateInput = StateMachine_None;
        CutsceneSeq_LockAllPlayerControl();
        EncoreGoodEnd_Unknown2(player1->characterID);
        EncoreGoodEnd_Unknown2(player2->characterID);
        camera->targetPtr  = (Entity *)EncoreGoodEnd->decorations[5];
        self->position.y = EncoreGoodEnd->decorations[0]->position.y;
        EncoreGoodEnd->decorations[0]->position.y += 0x500000;
        RSDK.SetSpriteAnimation(Decoration->aniFrames, 7, &EncoreGoodEnd->decorations[5]->animator, true, 21);
        foreach_all(UICreditsText, label) { label->active = ACTIVE_NEVER; }
    }
    else if (host->timer == 120) {
        player1->position.x = 0x300000;
        player1->velocity.x = 0x30000;
        player1->groundVel  = 0x30000;
        player1->drawOrder  = Zone->playerDrawHigh;
        player1->state      = Player_State_Ground;
        if (player2->objectID == Player->objectID) {
            player2->position.x = -0x800000;
            player2->velocity.x = 0x30000;
            player2->groundVel  = 0x30000;
            player2->drawOrder  = Zone->playerDrawHigh;
            player2->state      = Player_State_Ground;
            player2->stateInput = StateMachine_None;
        }
    }
    else if (host->timer > 120 && player1->groundVel <= 0x18000) {
        player1->state = EncoreGoodEnd_Unknown9;
        if (player2->objectID == Player->objectID)
            player2->state = EncoreGoodEnd_Unknown9;
        return true;
    }
    return false;
}

bool32 EncoreGoodEnd_CutsceneState_Unknown2(EntityCutsceneSeq *host)
{
    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *player2 = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    return player1->state == Player_State_None && (player2->state == Player_State_None || player2->objectID != Player->objectID);
}

bool32 EncoreGoodEnd_CutsceneState_Unknown3(EntityCutsceneSeq *host)
{
    if (host->timer == 60) {
        RSDK.SetSpriteAnimation(Decoration->aniFrames, 10, &EncoreGoodEnd->decorations[7]->animator, true, 0);
        RSDK.SetSpriteAnimation(Decoration->aniFrames, 11, &EncoreGoodEnd->decorations[10]->animator, true, 0);
        RSDK.SetSpriteAnimation(Decoration->aniFrames, 16, &EncoreGoodEnd->decorations[8]->animator, true, 0);
        RSDK.SetSpriteAnimation(Decoration->aniFrames, 17, &EncoreGoodEnd->decorations[11]->animator, true, 0);
    }
    else if (host->timer == 120) {
        RSDK.SetSpriteAnimation(Decoration->aniFrames, 9, &EncoreGoodEnd->decorations[7]->animator, true, 0);
        RSDK.SetSpriteAnimation(Decoration->aniFrames, 14, &EncoreGoodEnd->decorations[10]->animator, true, 0);
        RSDK.SetSpriteAnimation(Decoration->aniFrames, 15, &EncoreGoodEnd->decorations[8]->animator, true, 0);
        RSDK.SetSpriteAnimation(Decoration->aniFrames, 19, &EncoreGoodEnd->decorations[11]->animator, true, 0);
    }
    else if (host->timer == 180) {
        EncoreGoodEnd->decorations[0]->velocity.y = -0x60000;
        return true;
    }
    return false;
}

bool32 EncoreGoodEnd_CutsceneState_Unknown4(EntityCutsceneSeq *host)
{
    RSDK_THIS(EncoreGoodEnd);
    EntityDecoration *decor = EncoreGoodEnd->decorations[0];
    decor->position.y += decor->velocity.y;
    decor->velocity.y += 0x3800;
    if (decor->velocity.y > 0) {
        if (decor->position.y >= self->position.y) {
            decor->position.y = self->position.y;
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 8, &EncoreGoodEnd->decorations[5]->animator, true, 0);
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 21, &EncoreGoodEnd->decorations[6]->animator, true, 0);
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 12, &EncoreGoodEnd->decorations[7]->animator, true, 0);
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 20, &EncoreGoodEnd->decorations[8]->animator, true, 0);

            EncoreGoodEnd->decorations[9]->direction = FLIP_NONE;
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 6, &EncoreGoodEnd->decorations[9]->animator, true, 0);
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 23, &EncoreGoodEnd->decorations[1]->animator, false, 0);
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 23, &EncoreGoodEnd->decorations[4]->animator, false, 0);
            RSDK.SetSpriteAnimation(Decoration->aniFrames, 24, &EncoreGoodEnd->decorations[10]->animator, true, 0);
            EncoreGoodEnd->decorations[10]->drawFX |= FX_SCALE;
            EncoreGoodEnd->decorations[10]->position.x += 0x80000;
            EncoreGoodEnd->decorations[10]->rotation = -32;

            RSDK.SetSpriteAnimation(Decoration->aniFrames, 25, &EncoreGoodEnd->decorations[11]->animator, true, 0);
            EncoreGoodEnd->decorations[11]->drawFX |= FX_SCALE;
            EncoreGoodEnd->decorations[11]->position.x -= 0x80000;
            EncoreGoodEnd->decorations[11]->rotation = 32;

            foreach_all(UICreditsText, label)
            {
                label->active    = ACTIVE_NORMAL;
                label->state     = UICreditsText_State_SetupCharPos;
                label->drawOrder = Zone->hudDrawOrder;
            }

            EntityFXFade *fxFade = CREATE_ENTITY(FXFade, intToVoid(0xF0F0F0), self->position.x, self->position.y);
            fxFade->speedIn      = 256;
            fxFade->speedOut     = 64;
            fxFade->drawOrder    = Zone->drawOrderHigh;
            RSDK.PlaySfx(EncoreGoodEnd->sfxSnap, false, 255);
            return true;
        }
    }
    return false;
}

bool32 EncoreGoodEnd_CutsceneState_Unknown5(EntityCutsceneSeq *host)
{
    RSDK_THIS(EncoreGoodEnd);
    if (host->timer < 22) {
        foreach_active(Decoration, decor)
        {
            if (decor->type >= 25) {
                decor->drawOrder = Zone->drawOrderHigh + 1;
                if (decor->position.y >= self->position.y)
                    decor->position.y -= 0x20000;
                else
                    decor->position.y += 0x20000;
            }
        }
        RSDK.SetActivePalette(0, 0, ScreenInfo->height);
        RSDK.SetActivePalette(1, 2 * host->timer, ScreenInfo->height - 2 * host->timer);
    }
    return host->timer == 240;
}

bool32 EncoreGoodEnd_CutsceneState_Unknown6(EntityCutsceneSeq *host)
{
    if (API.CheckDLC(DLC_PLUS))
        RSDK.SetScene("Presentation", "Encore Summary");
    else
        RSDK.SetScene("Presentation", "Menu");
    Zone_StartFadeOut(10, 0x000000);
    Music_FadeOut(0.025);
    return true;
}

void EncoreGoodEnd_SkipCB(void) { EncoreGoodEnd_CutsceneState_Unknown6(NULL); }

#if RETRO_INCLUDE_EDITOR
void EncoreGoodEnd_EditorDraw(void) {}

void EncoreGoodEnd_EditorLoad(void) {}
#endif

void EncoreGoodEnd_Serialize(void) { RSDK_EDITABLE_VAR(EncoreGoodEnd, VAR_VECTOR2, size); }
#endif
