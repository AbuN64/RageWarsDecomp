#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/NAME.H"
#include "TYPES.H"

/* Receives player p's 0x648-byte packet through Note_ReadNoteData into the buffer at 0x2E28 of the
   records g_pakProfileScreenState points to and, when Note_Crc32_PakinterfaceBuildsavepacket checksums its first 0x640 bytes to the
   word stored after them, copies those bytes to the data at 0x18 of the player's 2920-byte record
   at 0x58 and the trailing word at 0x640 to the record's last word, returning 1; otherwise it reports the failure through
   Note_DeleteNote, marks both of the record's states at 0x0 and 0x14 as 2 and returns 0. Written
   from the assembly with nested tests each reporting the failure, which GCC cross-jumps into one
   call. */







extern s32 Note_ReadNoteData(s32 slot, s32 noteIndex, s32 destination, s32 length);
extern u32 Note_Crc32(u8 *data, u32 byteCount, u32 initialCrc);
extern s32 Note_DeleteNote(s32, s32);

s32 PAKInterface_ReadRecordsNote(s32 player, s32 channel) {
    PakSavePacket *packet;
    s32 received;

    received = 0;
    packet = &g_pakProfileScreenState->packet;
    if (Note_ReadNoteData(player, channel, packet, 1608) == 0) {
        if (Note_Crc32(packet, 1600, 7) == packet->checksum) {
            XPlus_CopyBytes(g_pakProfileScreenState->players[player].slots, &g_pakProfileScreenState->packet, 1600);
            received = 1;
            g_pakProfileScreenState->players[player].profile = g_pakProfileScreenState->packet.savedProfile;
        } else {
            Note_DeleteNote(player, channel);
        }
    } else {
        Note_DeleteNote(player, channel);
    }
    if (received == 0) {
        g_pakProfileScreenState->players[player].back = 2;
        g_pakProfileScreenState->players[player].state = 2;
    }
    return received;
}
