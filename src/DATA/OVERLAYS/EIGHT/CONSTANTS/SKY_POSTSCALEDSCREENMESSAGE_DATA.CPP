
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800D7028 */
extern char g_screenMessageSubstitutionReplacement[];
extern char s_menuTimesTextFragmentUsRev1[];
void *g_skyPostscaledscreenmessageDataAddressWords[3] = {
    0, g_screenMessageSubstitutionReplacement, (void *)(s_menuTimesTextFragmentUsRev1 + 12),
};
#endif
