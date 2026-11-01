#include "COMMON/MTX.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

/* Builds a player's aiming marker matrices for the current view g_lightingBufferIndex and turns the marker on at
   0x1214: a beam from the eye (the view position at 0x128, or Player_GetPlayerViewTranslation without a view) toward the
   target point, pitched straight up or down when nearly vertical, is stored in the table at 0x1480; the
   laser from the weapon muzzle at 0x260 to the aim point at 0x1464 (lowered by the view's height above
   the muzzle) in the table at 0x1500; and with a surface normal given, a dot flattened against the
   surface and lifted along the normal is stored in the table at 0x1580. */
static inline f32 aimAbs(f32 value) { return value < 0.0f ? -value : value; }

#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/OBJ.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"







extern f32 g_playerAimMarkerDepth;
extern void Player_GetPlayerViewTranslation(SharedPlayer *, CVector3 *);
extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
extern void Graphu64_IdentityMatrix(Matrix *);
extern void Graphu64_MatrixFromEulerXYZ(Matrix *, f32, f32, f32);
extern void BuildDirectionMatrix(Matrix *, CVector3 *);
extern void TranslateMatrix(Matrix *, CVector3);
extern void ScaleMatrixLocal(Matrix *, f32, f32, f32);
extern f32 Graphu64_GetPointDistance(CVector3 *, CVector3 *);
extern void Graphu64_ConvertMatrixToFixed(Matrix *, Matrix *);
extern CQuatern Graphu64_BuildDirectionQuaternion(CVector3 *);
extern void MatrixFromQuaternion(f32 *q, f32 *m);
extern void PitchMatrixLocal(Matrix *, f32);
extern void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);
extern void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);

void Player_BuildAimMarkerMatrices(SharedPlayer *player, CVector3 *target, CVector3 *normal) {
    CVector3 to;
    CVector3 eye;
    CVector3 lift;
    CVector3 direction;
    CVector3 aim;
    CVector3 origin;
    Matrix matrix;
    CQuatern turn;
    f32 scale;
    f32 height;
    f32 aimHeight;

    if (player->views5DC.view5DC_2.view != 0) {
        origin = player->views5DC.view5DC_2.view->position;
    } else {
        Player_GetPlayerViewTranslation(player, &origin);
    }
    eye = origin;
    to = *target;
    Graphu64_SubtractVectors(&direction, &to, &eye);
    Graphu64_NormalizeVec3(&direction);
    Graphu64_IdentityMatrix(&matrix);
    if (0.99999899f <= direction.y) {
        Graphu64_MatrixFromEulerXYZ(&matrix, -1.57079649f, player->views1C.view6C_5.heading, 0.0f);
    } else if (direction.y <= -0.99999899f) {
        Graphu64_MatrixFromEulerXYZ(&matrix, 1.57079649f, player->views1C.view6C_5.heading, 0.0f);
    } else {
        BuildDirectionMatrix(&matrix, &direction);
    }
    TranslateMatrix(&matrix, eye);
    TranslateMatrixLocal(&matrix, 0.0f, 0.0f, g_playerAimMarkerDepth);
    ScaleMatrixLocal(&matrix, 0.05f, 1.0f, g_playerAimMarkerDepth - Graphu64_GetPointDistance(&eye, &to));
    Graphu64_ConvertMatrixToFixed(&matrix, &player->views1480.view1480_1.beams[g_lightingBufferIndex]);

    aim = player->views1464.view1464_1.aim;
    if (player->views5DC.view5DC_2.view != 0) {
        height = player->views5DC.view5DC_2.view->position.y - player->views1C.view260_26.muzzle.y;
        aimHeight = aim.y;
        height = height < 0.0f ? aimHeight + height : aimHeight - height;
        aim.y = height;
    }
    Graphu64_SubtractVectors(&direction, &aim, &player->views1C.view260_26.muzzle);
    Graphu64_NormalizeVec3(&direction);
    Graphu64_IdentityMatrix(&matrix);
    BuildDirectionMatrix(&matrix, &direction);
    TranslateMatrix(&matrix, player->views1C.view260_26.muzzle);
    scale = 1.0f;
    ScaleMatrixLocal(&matrix, scale, scale, -Graphu64_GetPointDistance(&origin, &player->views1464.view1464_1.aim));
    Graphu64_ConvertMatrixToFixed(&matrix, &player->views1500.view1500_1.lasers[g_lightingBufferIndex]);

    if (normal != 0) {
        lift = *normal;
        turn = Graphu64_BuildDirectionQuaternion(&lift);
        MatrixFromQuaternion(&turn, &matrix);
        PitchMatrixLocal(&matrix, 1.57079649f);
        Graphu64_NormalizeVec3(&lift);
        Graphu64_ScaleVector(&lift, &lift, 2.048f);
        Graphu64_AddVec3(&eye, &eye, &lift);
        TranslateMatrix(&matrix, to);
        ScaleMatrixLocal(&matrix, 1.536f, scale, 1.536f);
        Graphu64_ConvertMatrixToFixed(&matrix, &player->views1580.view1580_1.dots[g_lightingBufferIndex]);
    }
    player->views5E8.view1214_155.marker = 1;
}
