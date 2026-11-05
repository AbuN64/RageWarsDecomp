#ifndef COMMON_MODEL_PREVIEW_TRANSFORM_H
#define COMMON_MODEL_PREVIEW_TRANSFORM_H
#include "Common/small_records.h"
struct ModelPreviewRotationSpeedView {
    char pad[0x28];
    struct Triple vector;
};
struct ModelPreviewPositionView {
    char pad[0x10];
    struct Triple vector;
};
struct StateFrontendInitModelPreviewTransform {
    s32 unused;
    Triple first;
    Triple second;
    s32 rotationXBits;
    s32 rotationYBits;
    s32 rotationZBits;
    s32 rotationSpeedXBits;
    s32 rotationSpeedYBits;
    s32 rotationSpeedZBits;
    s32 modelId;
};
struct PreviewRotationView {
    char pad0[0x1C];
    Triple rotation;
};
typedef struct StateFrontendInitModelPreviewTransform StateFrontendInitModelPreviewTransform;
#endif
