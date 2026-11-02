#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/OBJRECV5.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
extern s32 Actor_RequestActorState(void *actor, void *stateController, s32 action);
extern void Graphu64_TransformPoint(void *matrix, void *inputPoint, void *transformedPoint);

#include "TYPES.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"

typedef struct { f32 x, y, z; } Position;
typedef struct { u8 pad0[0x34]; Position pos; f32 height; u8 pad44[0x1A]; u8 duration; } TravelTarget;
typedef struct { u8 pad0[0x6C]; f32 yaw; u8 pad70[0x2E4]; f32 bodyYaw; u8 pad358[0x390]; Position pos; u8 pad6F4[0x100]; f32 elapsed, targetYaw; TravelTarget *target; Position start; } TravelPlayer;
extern f32 g_playerTravelPositiveYawPeriod, g_playerTravelNegativeYawPeriod, g_playerTravelYawRiseScale, g_playerTravelYawFallScale, g_playerTravelArcHeightScale;

extern void Player_UpdateViewAngles(void *, void *, void *);

void Playerai_UpdateTravelSequence(TravelPlayer *player, void *body) {
    f32 yaw, targetYaw, distance, otherDistance, alternate, duration, t;
    Position pos;
    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    if (player->target != 0) {
        player->elapsed += g_frameElapsedTime;
        yaw = player->yaw;
        targetYaw = player->targetYaw;
        if (targetYaw != yaw) {
            Graphu64_WrapPeriodicValue(&yaw);
            Graphu64_WrapPeriodicValue(&targetYaw);
            if (yaw > targetYaw) {
                alternate = targetYaw + g_playerTravelPositiveYawPeriod;
                if (alternate - yaw < yaw - targetYaw) targetYaw = alternate;
            } else {
                alternate = targetYaw - g_playerTravelNegativeYawPeriod;
                if (yaw - alternate < targetYaw - yaw) targetYaw = alternate;
            }
            if (targetYaw > yaw) {
                yaw += (targetYaw - yaw) * g_playerTravelYawRiseScale;
                if (targetYaw < yaw) yaw = targetYaw;
            } else {
                yaw -= (yaw - targetYaw) * g_playerTravelYawFallScale;
                if (yaw < targetYaw) yaw = targetYaw;
            }
            Graphu64_WrapPeriodicValue(&yaw);
        }
        player->bodyYaw = yaw;
        player->yaw = yaw;
        duration = (f32)(player->target->duration * 15);
        if (player->elapsed < duration) {
            t = player->elapsed / duration;
            pos.x = player->start.x + (player->target->pos.x - player->start.x) * t;
            pos.z = player->start.z + (player->target->pos.z - player->start.z) * t;
            pos.y = player->start.y + (player->target->pos.y - player->start.y) * t + player->target->height * ((t - t * t) * g_playerTravelArcHeightScale);
            player->pos = pos;
            return;
        }
    }
    Player_SetPlayerState(player, body, 2);
}

extern void Player_UpdateViewAngles(void *,void *,void *);
extern void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate);
extern f32 g_playerRideInitialSpeedHalf;
extern f32 g_playerRideBumpThreshold;
extern Triple g_playerRideBaseOffset;
extern f32 g_playerRideWaveFrequency,g_playerRideWaveInputOffset,g_playerRideWaveInputScale,g_playerRideWaveOutputOffset,g_playerRideWaveOutputScale,g_playerRideYawScale,g_playerRideSteeringScale,g_playerRideDefaultLift,g_playerRideSpeedDamping,g_playerRideReverseShakeScale,g_playerRideForwardShakeScale,g_playerRideShakeMaximum,g_playerRideShakeDuration,g_playerRideReverseLiftThreshold,g_playerRideForwardLiftThreshold,g_playerRideRaisedLift;
void Playerai_UpdateMountedMovement(SharedPlayer *player,PlayerBodyPositionYawView *body) {
    Matrix rotation;
    struct Mount *mount;
    CVector3 *offset;
    SharedMovement *movement;
    f32 wave,yaw,unit,forward,side,bump,result,force,absolute,sway,rawForward,rawSide,time;
    mount=player->views5E8.view80C_108.mount;
    wave=Math_Cosf(player->views5E8.view838_114.rideTime*g_playerRideWaveFrequency);
    wave=(((wave+g_playerRideWaveInputOffset)*g_playerRideWaveInputScale+g_playerRideWaveOutputOffset)*g_playerRideWaveOutputScale);
    time=player->views5E8.view838_114.rideTime;
    sway=player->views5E8.view69C_40.stick; sway*=wave;
    time+=g_frameElapsedTime;player->views5E8.view838_114.rideTime=time;
    unit=g_playerRideYawScale;
    yaw=body->yaw;
    sway*=unit;force=yaw+sway;
    Graphu64_EaseValueToward(&body->yaw,force,0.9f);
    yaw=((yaw-body->yaw)+player->views5E8.view69C_40.stick*g_playerRideSteeringScale)*unit;
    Graphu64_EaseValueToward(&player->views5E8.view72C_76.kickRoll,yaw,0.1f);
    Player_UpdateViewAngles(player,body,&g_playerRideViewAngleParameters);
    offset=0;
    if(player->views5E8.view6B8_50.input&8) {
        Actor_RequestActorState(mount,&mount->animation,46);
        player->views5E8.view704_68.lift=g_playerRideDefaultLift;
        player->views5E8.view6C0_51.movementSpeed=g_playerRideInitialSpeedHalf+g_playerRideInitialSpeedHalf;
    }
    absolute=player->views5E8.view6C0_51.movementSpeed;
    bump=player->views5E8.view83C_116.bump;
    if(absolute<0.0f)absolute=-absolute;
    side=2.0f*player->views5E8.view6C4_54.sideSpeed;
    if(side<0.0f ? -side<absolute : side<absolute) {
        rawForward=player->views5E8.view6C0_51.movementSpeed;
        if(rawForward<0.0f)result=bump-rawForward;
        else result=bump+rawForward;
    } else {
        rawSide=2.0f*player->views5E8.view6C4_54.sideSpeed;
        if(rawSide<0.0f)result=bump-rawSide;
        else result=bump+rawSide;
    }
    player->views5E8.view83C_116.bump=result;
    if(g_playerRideBumpThreshold<result) {
        player->views5E8.view83C_116.bump=result-g_playerRideBumpThreshold;
        if(mount->animationId!=46) {
            player->views5E8.view6C0_51.movementSpeed*=g_playerRideSpeedDamping;
            player->views5E8.view6C4_54.sideSpeed*=g_playerRideSpeedDamping;
        }
        forward=player->views5E8.view6C0_51.movementSpeed;
        if(forward<0.0f)force=-forward*g_playerRideReverseShakeScale;
        else force=forward*g_playerRideForwardShakeScale;
        if(g_playerRideShakeMaximum<force)force=g_playerRideShakeMaximum;
        if(player->views5DC.view5DC_6.storage)Gsky_StartScaledShake(player->views5DC.view5DC_6.storage,0.0f,force,0.0f,g_playerRideShakeDuration,1,body->position);
    }
    if(0.0f<player->views5E8.view6C0_51.movementSpeed)Player_UpdateGroundThrustAndBoost(player,body,&g_playerRideMovementParameters[0]);
    else Player_UpdateGroundThrustAndBoost(player,body,&g_playerRideMovementParameters[1]);
    forward=player->views5E8.view6C0_51.movementSpeed;
    if(forward<0.0f ? g_playerRideReverseLiftThreshold < -forward : g_playerRideForwardLiftThreshold < forward)player->views5E8.view704_68.lift=g_playerRideRaisedLift;
    if(player->views5E8.view810_110.kind==310) {
        offset=&g_playerRideOffset;
        player->views5E8.view814_112.offset=g_playerRideBaseOffset;
    }
    if(offset) {
        BuildYawMatrix(&rotation,body->yaw);
        Graphu64_TransformPoint(&rotation,offset,&player->views5E8.view73C_82.weapon);
        Graphu64_ScaleVector(&player->views5E8.view73C_82.weapon,&player->views5E8.view73C_82.weapon,10.24f);
    }
}
