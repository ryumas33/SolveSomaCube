#define PIECENUM 7
#define ANSNUMMAX 512
 
FILE *file;
 
typedef struct{
  int form[5][5][5];
}Cube;
typedef struct{
  int foot[3][3]; //foot cube and its vector from core
}Piece;
 
Cube ans[ANSNUMMAX];
int ansnum;
 
/* -----prototype----- */
 
Piece MakePiece(int p_num);
 
void Construct(Cube space,Piece p[8],int p_num);
int Judge(Cube space,Piece p[8],int p_num,int x,int y,int z);
Cube PutPiece(Cube space,Piece p[8],int p_num,int x,int y,int z);
Piece FootPoint(Cube space,Piece p[8],int p_num,int x,int y,int z);
void ShowSpace(Cube space);
int ImpossibleBreak(Cube space);
int CompareCube(Cube a,Cube b);
Cube RemovePiece(Cube space,int p_num);
Piece Rotate(Piece before,int axis,int exchange_a,int exchange_b);
 
void WriteAns(Cube ans[ANSNUMMAX],int ansnum);
