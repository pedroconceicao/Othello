/*File generated automatically in pedro-ux303ln by pedro on Seg Nov 13 15:57:01 WET 2017*/
#ifdef __cplusplus
extern "C" {
#endif
/* pcolor.c */
void HighLightText (void);
void PrintRedLine (void);
void ResetTextColors (void);
void textcolor (int attr, int fg, int bg);
/* main.c */
int main (int argc, char *argv[]);
/* othello.c */
int CheckDown (othello * jg, int l, int c, int player);
int CheckDownLeft (othello * jg, int l, int c, int player);
int CheckDownRight (othello * jg, int l, int c, int player);
int CheckLeft (othello * jg, int l, int c, int player);
int CheckMove (othello * jg, int move, int player);
int CheckRight (othello * jg, int l, int c, int player);
int CheckUp (othello * jg, int l, int c, int player);
int CheckUpLeft (othello * jg, int l, int c, int player);
int CheckUpRight (othello * jg, int l, int c, int player);
int GenerateMove (othello * jg);
int GetPlayerMove (othello * jg);
void InitGame (othello * jg);
int LoadGame (othello * jg, char *filename);
char Option (void);
void PrintGameBoard (othello * jg);
void ReversePieces (othello * jg, int move, int player);
int SaveGame (othello * jg, char *filename);
int WinGame (othello * jg, int player);
/* Etapa */
/* 1/main.c */
/* Etapa */
/* 1/othello.c */
#ifdef __cplusplus
}
#endif
