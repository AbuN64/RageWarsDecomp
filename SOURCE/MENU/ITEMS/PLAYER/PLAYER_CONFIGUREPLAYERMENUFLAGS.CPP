#include "COMMON/ACTORRECAT260.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PLAYER_GETPLAYERINDEX.H"
#include "TYPES.H"
#include "../../../../sdk/include/PFS/PLAYER_CONFIGUREPLAYERMENUFLAGS.H"
#include "ENGINE/DEFS.H"

/* Sets bit 24 of the flag word at offset 0x120 of the object at offset 0xC of a record when
   g_resultExitPending is set, and clears it otherwise. */






/* Marks the attached actor visible, clears its subpart visibility bits, and applies the paused-state flag. */





s32 Player_FormatPlayerFirstHalfword(Shared_DebugWidget *field, Shared_MenuHandle *holder) {
    s32 player = Player_GetPlayerIndex(&g_playerViewRenderContext, holder->owner);
    /* g_playerSettings_Achieve is the hub's SlotSelectionPlayerConfig array (0x96-byte records); index player*150 then reads the record's first halfword */
    s32 value = *(s16 *) &g_playerSettings[player];
    char *text;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    text = field->inner->text[g_playerViewRenderContext.object.language];
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuValueFormat, value);
#else
    text = *field->inner->text;
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtDec4Pad, value);
#endif
    return 0;
}

/* Does nothing. Nothing in the cartridge image calls it or stores its address as a word. */
void Player_MenuFlagsNoOp(void) {
}

void Player_SetFragTagItemFlag(struct MenuPromptKindView *record) {
    if (g_gameSettings.counters.m_bFragTagOn != 0) {
        record->target->flags |= 0x01000000;
    } else {
        record->target->flags &= ~0x01000000;
    }
}

void Player_ConfigurePlayerMenuFlags(PlayerMenuFlagContext *object) {
 if(object->parent) object->parent->playerStateDirty=1;
 object->actor->flags1c0 |= 0x01800000;
 object->actor->flags1c0 &= 0xFEFFFFFF;
 object->actor->flags58 |= 0x01800000;
 object->actor->flags210 &= 0xFE7FFFFF;
 object->actor->flags238 &= 0xFE7FFFFF;
 object->actor->flags260 &= 0xFE7FFFFF;
 if(g_gameSettings.counters.m_bFragTagOn) {object->actor->flags120 |= 0x01000000; return;}
 object->actor->flags120 &= 0xFEFFFFFF;
}
