// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: OOZ2Outro Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "SonicMania.h"

#if RETRO_USE_PLUS
ObjectOOZ2Outro *OOZ2Outro;

void OOZ2Outro_Update(void)
{
    RSDK_THIS(OOZ2Outro);

    EntityMegaOctus *boss = MegaOctus->bossPtr;
    if (globals->gameMode < MODE_TIMEATTACK && boss && !boss->objectID) {
        self->scrollOffset.x = self->moveOffset.x & 0xFFFF0000;
        self->scrollOffset.y = self->moveOffset.y & 0xFFFF0000;

        StateMachine_Run(self->state);

        foreach_active(Player, player)
        {
            TileLayer *layer = self->moveLayer;
            if (!player->sidekick) {
                layer->scrollPos               = -self->scrollOffset.y;
                layer->scrollInfo[0].scrollPos = -self->scrollOffset.x;
            }
            player->collisionLayers |= Zone->moveMask;
            player->moveLayerPosition.x = -(int32)(self->moveOffset.x & 0xFFFF0000);
            player->moveLayerPosition.y = -(int32)(self->moveOffset.y & 0xFFFF0000);
        }

        if (self->prisonPtr) {
            self->prisonPtr->position.x = self->scrollOffset.x + self->prisonPos.x;
            self->prisonPtr->position.y = self->scrollOffset.y + self->prisonPos.y;
        }
    }
}

void OOZ2Outro_LateUpdate(void) {}

void OOZ2Outro_StaticUpdate(void) {}

void OOZ2Outro_Draw(void) {}

void OOZ2Outro_Create(void *data)
{
    RSDK_THIS(OOZ2Outro);
    if (!SceneInfo->inEditor) {
        if (globals->gameMode < MODE_TIMEATTACK) {
            self->active  = ACTIVE_BOUNDS;
            self->visible = false;
            if (!self->size.x)
                self->size.x = WIDE_SCR_XSIZE << 16;
            if (!self->size.y)
                self->size.y = SCREEN_YSIZE << 16;
            self->moveLayer   = RSDK.GetSceneLayer(Zone->moveLayer);
            self->updateRange = self->size;
            foreach_all(EggPrison, prison)
            {
                self->prisonPtr = prison;
                self->prisonPos = prison->position;
            }

            self->state = OOZ2Outro_State_SubFloat;
        }
        else {
            destroyEntity(self);
        }
    }
}

void OOZ2Outro_StageLoad(void)
{
    OOZ2Outro->sfxGlug      = RSDK.GetSfx("OOZ/Glug.wav");
    OOZ2Outro->sfxSubLaunch = RSDK.GetSfx("OOZ/SubLaunch.wav");
}

void OOZ2Outro_StageFinishCB_Act2(void)
{
    Zone->cameraBoundsR[0] = 0x4000;
    foreach_active(Player, player)
    {
        player->state      = Player_State_Air;
        player->stateInput = 0;
        player->left       = false;
        player->right      = true;
        player->up         = false;
        player->down       = false;
        player->jumpPress  = false;
        player->jumpHold   = false;
    }

    foreach_active(OOZ2Outro, outro) { outro->state = OOZ2Outro_State_BoardSub; }

    foreach_active(HUD, hud) { hud->state = HUD_State_GoOffScreen; }
}

void OOZ2Outro_State_SubFloat(void)
{
    RSDK_THIS(OOZ2Outro);
    self->moveOffset.y = RSDK.Sin256(Zone->timer) << 10;
}

void OOZ2Outro_CheckSkip(void)
{
    if (ControllerInfo->keyStart.press && !(SceneInfo->state & ENGINESTATE_REGULAR)) {
        globals->suppressTitlecard = false;
        globals->suppressAutoMusic = false;
        globals->enableIntro       = false;
        RSDK.SetGameMode(ENGINESTATE_FROZEN);
        Zone_StartFadeOut(20, 0);
        Music_FadeOut(0.03);
    }
}

void OOZ2Outro_State_BoardSub(void)
{
    RSDK_THIS(OOZ2Outro);
    OOZ2Outro_CheckSkip();
    self->moveOffset.y = RSDK.Sin256(Zone->timer) << 10;

    bool32 keepMoving = false;
    foreach_active(Player, player)
    {
        player->jumpPress = false;
        if (player->animator.animationID == ANI_PUSH) {
            player->jumpPress = true;
            player->jumpHold  = true;
        }
        else if (player->velocity.y > -0x20000) {
            player->jumpHold = false;
        }

        if (player->position.x > self->position.x - 0x100000 && player->velocity.x > 0x20000)
            player->right = false;

        if (player->position.x < self->position.x + 0x400000) {
            if (!player->right) {
                if (player->groundVel < 0x20000)
                    player->groundVel = 0x20000;
                if (player->velocity.x < 0x20000)
                    player->velocity.x = 0x20000;
            }
            keepMoving |= true;
        }
        else {
            player->groundVel  = 0;
            player->velocity.x = 0;
            player->right      = false;
        }
    }

    if (!keepMoving)
        ++self->timer;

    if (self->timer > 60) {
        self->timer = 0;
        self->state = OOZ2Outro_State_SubActivate;
        foreach_active(Player, player)
        {
            player->groundVel  = 0;
            player->velocity.x = 0;
            player->right      = false;
            player->state      = Player_State_None;
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_BALANCE1, &player->animator, false, 0);
            Zone->playerBoundActiveR[player->playerID] = 0;
            EntityCamera *camera                       = player->camera;
            if (camera)
                camera->state = StateMachine_None;
        }
    }
}

void OOZ2Outro_State_SubActivate(void)
{
    RSDK_THIS(OOZ2Outro);
    OOZ2Outro_CheckSkip();
    self->moveOffset.y -= 0x6000;

    if (!(Zone->timer & 0xF)) {
        Camera_ShakeScreen(0, 0, 4);
        RSDK.PlaySfx(OOZ2Outro->sfxGlug, false, 255);
    }

    if (++self->timer == 140)
        RSDK.PlaySfx(OOZ2Outro->sfxSubLaunch, false, 255);

    if (self->timer > 180) {
        self->timer      = 0;
        self->velocity.y = -0x30000;
        self->state      = OOZ2Outro_State_SubLaunch;
        foreach_active(Player, player) { RSDK.SetSpriteAnimation(player->aniFrames, ANI_BALANCE2, &player->animator, false, 0); }
    }
}

void OOZ2Outro_State_SubLaunch(void)
{
    RSDK_THIS(OOZ2Outro);

    if (self->velocity.y < -0x8000)
        self->velocity.y += 0x3800;
    self->velocity.x += 0x1800;
    self->moveOffset.x += self->velocity.x;
    self->moveOffset.y += self->velocity.y;
    foreach_active(Player, player) { player->position.x += self->velocity.x; }

    if (++self->timer > 140) {
        self->timer = 0;
        self->state = 0;
        Zone_StartFadeOut(10, 0x000000);
        foreach_active(Player, player) { player->active = ACTIVE_NEVER; }
    }
}

void OOZ2Outro_EditorDraw(void)
{
    RSDK_THIS(OOZ2Outro);
    Vector2 drawPos;

    drawPos.x = self->position.x;
    drawPos.y = self->position.y;
    drawPos.x -= self->size.x >> 1;
    drawPos.y -= self->size.y >> 1;
    RSDK.DrawLine(drawPos.x, drawPos.y, drawPos.x + self->size.x, drawPos.y, 0xFFFF00, 0, INK_NONE, false);
    RSDK.DrawLine(drawPos.x, self->size.y + drawPos.y, drawPos.x + self->size.x, self->size.y + drawPos.y, 0xFFFF00, 0, INK_NONE, false);
    RSDK.DrawLine(drawPos.x, drawPos.y, drawPos.x, drawPos.y + self->size.y, 0xFFFF00, 0, INK_NONE, false);
    RSDK.DrawLine(drawPos.x + self->size.x, drawPos.y, drawPos.x + self->size.x, drawPos.y + self->size.y, 0xFFFF00, 0, INK_NONE, false);
}

void OOZ2Outro_EditorLoad(void) {}

void OOZ2Outro_Serialize(void) { RSDK_EDITABLE_VAR(OOZ2Outro, VAR_VECTOR2, size); }
#endif
