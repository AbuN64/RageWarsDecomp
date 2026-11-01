#ifndef MENU_GNU_VA_ARG_H
#define MENU_GNU_VA_ARG_H
/* Historical GNU va_arg expansions over a plain byte-pointer cursor. */
#define VA(ap, T) (((T *)(void *)((ap) = (u8 *)((((s32)(ap) + 3) & -4) + 4)))[-1])
#define VA8(ap, T) (((T *)(void *)((ap) = (u8 *)((((s32)(ap) + 7) & -8) + 8)))[-1])
#endif
