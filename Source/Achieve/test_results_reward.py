"""Check trial reward suppression using the actual branch and mocked reward services.

Usage: python3 Source/Achieve/test_results_reward.py <scratch-directory>
"""
from pathlib import Path
import subprocess
import sys
import tempfile
source = Path(__file__).with_name("results.cpp").read_text()
start = source.index("            Achieve_MarkLevelPlayed(")
end = source.index("            switch (g_selectedLevelId)", start)
routine = source[start:end]
harness = r'''#include <assert.h>
#include <stdio.h>
#include <string.h>
typedef struct {int alpha; char *text;} MenuWidget;
union ModelPreviewScreen {struct {MenuWidget *window;int player;struct {int model; char *image;} rows[1];int badge;};};
static union ModelPreviewScreen screen, *g_resultsModelPreviewScreen=&screen;
static struct {int recorded;} preset, *g_currentStagePreset=&preset;
static struct {int slot; unsigned char slotLevels[4][5];} g_localPlayerProfiles[4];
static int g_selectedLevelId=9, played, tested, awarded, texts, revealed, bitResult;
static MenuWidget widget;
static char g_resultPreviouslyCompletedText[]="complete";
#define PREVIEW_ID_SHIFT 0
#define RW_LOCALIZED_TEXT(a,b,c,d) (a)
static void Achieve_MarkLevelPlayed(int p){assert(p==screen.player);++played;}
static int Defs_TestBit(unsigned char *p,int bit){assert(p==g_localPlayerProfiles[screen.player].slotLevels[2]);assert(bit==9);++tested;return bitResult;}
static MenuWidget *Node_FindWidgetByResourceId(MenuWidget *m,int id){assert(m==screen.window && id==638);return &widget;}
static void Widget_SetWidgetFlag08(MenuWidget *m,int flag){assert(m==&widget && flag==1);++revealed;}
static int Match_ApplyLevelCompletionReward(int p){assert(p==screen.player);++awarded;return 77;}
static char *Match_GetResultText(int reward){assert(reward==77);++texts;return "reward";}
static void reward(void){int slot;MenuWidget *item;
'''
harness += routine + "\n}\n"
harness += r'''int main(void){int p,recorded,bit,checks=0;
 for(p=0;p<4;++p)for(recorded=0;recorded<2;++recorded)for(bit=0;bit<2;++bit){
  int completed=recorded && bit;
  memset(&screen,0,sizeof(screen));memset(&widget,0,sizeof(widget));screen.player=p;
  g_localPlayerProfiles[p].slot=2;preset.recorded=recorded;bitResult=bit;
  played=tested=awarded=texts=revealed=0;reward();
  assert(played==1 && tested==recorded && awarded==!completed && texts==!completed && revealed==completed);
  assert(screen.badge==-1);
  if(completed)assert(screen.rows[0].model==-1 && widget.alpha==175 && widget.text==g_resultPreviouslyCompletedText);
  else assert(screen.rows[0].model==77 && screen.rows[0].image);
  ++checks;
 }
 printf("trial rewards passed %d player, recorded and completion cases\n",checks);
 return 0;
}
'''
with tempfile.TemporaryDirectory(prefix="trial-reward-", dir=sys.argv[1]) as temporary:
    path=Path(temporary)
    (path / "test.c").write_text(harness)
    subprocess.run(["cc", "-std=gnu99", "-Wall", "-Werror", str(path / "test.c"), "-o", str(path / "test")], check=True)
    subprocess.run([str(path / "test")], check=True)
