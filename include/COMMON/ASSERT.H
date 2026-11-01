#ifndef COMMON_ASSERT_H
#define COMMON_ASSERT_H
/* The engine's ASSERT(expr). In the developers' debug build it tested expr and, on failure, stopped with
 * "ASSERTION FAILED!!", the source file, the line and the expression text (the eu and eu-x ROMs still carry that
 * build's read-only data: the message, the ZLR/BLR/ALR prompt, the C:/Projects/DM/n64/Source/Engine/... file names
 * and hundreds of expression strings such as "DistFromCamera >= 0.0f"). The release build, which every shipped ROM
 * is, compiles it out: no release function calls the failure handler, and expr is not evaluated. */
#define ASSERT(expr) ((void)0)
#endif
