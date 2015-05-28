#include<stdio.h>
#include<time.h>

#include"SolveSomaCube.h"
 
/* -----main----- */
 
int main(){
  clock_t start,end;
  double timer;
  start=clock();
  file=fopen("soma_cube_answers.txt","w");
 
  Cube space;
  int x,y,z;
  for(x=0;x<=4;x++){for(y=0;y<=4;y++){for(z=0;z<=4;z++){
	if(x==0||x==4||y==0||y==4||z==0||z==4){space.form[x][y][z]=9;} //outer wall
	else{space.form[x][y][z]=0;}
      }}}
 
  Piece p[8]={};
  int i;
  for(i=1;i<=PIECENUM;i++){
    p[i]=MakePiece(i);
  }
 
  Construct(space,p,1);
  WriteAns(ans,ansnum);
  fclose(file);
  end=clock();
  timer=difftime(end,start)/(double)CLOCKS_PER_SEC;
  printf("search time: %.3f\n",timer);
  printf("open \"soma_cube_answers.txt\"\nto view %d answers\n",ansnum);
 
  return 0;
}
 
/* -----functions----- */
 
Piece MakePiece(int p_num){
  Piece p;
  switch(p_num){
  case 1: //L
  p.foot[0][0]=1;p.foot[0][1]=0;p.foot[0][2]=0;
  p.foot[1][0]=-1;p.foot[1][1]=0;p.foot[1][2]=0;
  p.foot[2][0]=-1;p.foot[2][1]=0;p.foot[2][2]=1;
  return p; break;
  case 2: //Z
  p.foot[0][0]=1;p.foot[0][1]=0;p.foot[0][2]=0;
  p.foot[1][0]=0;p.foot[1][1]=0;p.foot[1][2]=1;
  p.foot[2][0]=-1;p.foot[2][1]=0;p.foot[2][2]=1;
  return p; break;
  case 3: //T
  p.foot[0][0]=1;p.foot[0][1]=0;p.foot[0][2]=0;
  p.foot[1][0]=-1;p.foot[1][1]=0;p.foot[1][2]=0;
  p.foot[2][0]=0;p.foot[2][1]=0;p.foot[2][2]=1;
  return p; break;
  case 4: //Y
  p.foot[0][0]=1;p.foot[0][1]=0;p.foot[0][2]=0;
  p.foot[1][0]=0;p.foot[1][1]=-1;p.foot[1][2]=0;
  p.foot[2][0]=0;p.foot[2][1]=0;p.foot[2][2]=1;
  return p; break;
  case 5: //chiral
  p.foot[0][0]=1;p.foot[0][1]=0;p.foot[0][2]=0;
  p.foot[1][0]=1;p.foot[1][1]=-1;p.foot[1][2]=0;
  p.foot[2][0]=0;p.foot[2][1]=0;p.foot[2][2]=1;
  return p; break;
  case 6: //chiral
  p.foot[0][0]=0;p.foot[0][1]=-1;p.foot[0][2]=0;
  p.foot[1][0]=1;p.foot[1][1]=-1;p.foot[1][2]=0;
  p.foot[2][0]=0;p.foot[2][1]=0;p.foot[2][2]=1;
  return p; break;
  case 7: //V
  p.foot[0][0]=1;p.foot[0][1]=0;p.foot[0][2]=0;
  p.foot[1][0]=0;p.foot[1][1]=0;p.foot[1][2]=1;
  p.foot[2][0]=0;p.foot[2][1]=0;p.foot[2][2]=0;
  return p; break;
  }
}
 
void Construct(Cube space,Piece p[8],int p_num){
  int x,y,z,rxy,rz;
  int next_p_num;
  int existing,i;
 
  for(z=1;z<=3;z++){for(y=1;y<=3;y++){for(x=1;x<=3;x++){
 
	for(rxy=0;rxy<6;rxy++){
	  for(rz=0;rz<4;rz++){
 
	    if(Judge(space,p,p_num,x,y,z)==1){
	      space=PutPiece(space,p,p_num,x,y,z);
	      printf("[[%d]] (%d,%d,%d)\n\n",p_num,x,y,z);
	      ShowSpace(space);
 
	      if(p_num<PIECENUM){
		if(ImpossibleBreak(space)==0){
		  next_p_num=p_num+1;
		  Construct(space,p,next_p_num);
		}
	      }else{ //completed
		existing=0;i=0;
		while(i<=ansnum&&existing==0){
		  if(CompareCube(space,ans[i])==1){existing=1;}
		  i++;
		}
		if(existing==0){ansnum++;ans[ansnum]=space;}
	      }
 
	      space=RemovePiece(space,p_num);
	      if(p_num==PIECENUM){goto noRotation;}
	    }
	    if(p_num==1){goto noRotation;}
 
	    p[p_num]=Rotate(p[p_num],2,0,1); //rotate z
	  }
	  if(rxy<=3){p[p_num]=Rotate(p[p_num],1,2,0);} //rotate x
	  else if(rxy==4){p[p_num]=Rotate(p[p_num],0,1,2);} //rotate y
	  else if(rxy==5){p[p_num]=Rotate(p[p_num],0,1,2);
	    p[p_num]=Rotate(p[p_num],0,1,2);}
	}
      noRotation:;
      }}}
}
 
int Judge(Cube space,Piece p[8],int p_num,int x,int y,int z){
  Piece fp=FootPoint(space,p,p_num,x,y,z);
  if(space.form[x][y][z]==0&&
     space.form[fp.foot[0][0]][fp.foot[0][1]][fp.foot[0][2]]==0&&
     space.form[fp.foot[1][0]][fp.foot[1][1]][fp.foot[1][2]]==0&&
     space.form[fp.foot[2][0]][fp.foot[2][1]][fp.foot[2][2]]==0
     ){return 1;}
  else return 0;
}
 
Cube PutPiece(Cube space,Piece p[8],int p_num,int x,int y,int z){
  Piece fp=FootPoint(space,p,p_num,x,y,z);
  int f_num;
  space.form[x][y][z]=p_num;
  for(f_num=0;f_num<3;f_num++){
    space.form[fp.foot[f_num][0]][fp.foot[f_num][1]][fp.foot[f_num][2]]=p_num;
  }
  return space;
}
 
Piece FootPoint(Cube space,Piece p[8],int p_num,int x,int y,int z){
  Piece fp;
  int f_num;
  for(f_num=0;f_num<3;f_num++){
    fp.foot[f_num][0]=x+p[p_num].foot[f_num][0];
    fp.foot[f_num][1]=y+p[p_num].foot[f_num][1];
    fp.foot[f_num][2]=z+p[p_num].foot[f_num][2];
  }
  return fp;
}
 
void ShowSpace(Cube space){
  int x,y,z;
  for(z=3;z>=1;z--){for(y=3;y>=1;y--){for(x=1;x<=3;x++){
       printf("%d ",space.form[x][y][z]);
      }printf("\n\n");}printf("\n");}printf("\n");
}
 
int ImpossibleBreak(Cube space){
  int x,y,z;
  int impossible=0;
  for(z=1;z<=3;z++){for(y=1;y<=3;y++){for(x=1;x<=3;x++){
	if(space.form[x][y][z]==0&&
           space.form[x+1][y][z]>0&&
           space.form[x-1][y][z]>0&&
	   space.form[x][y+1][z]>0&&
	   space.form[x][y-1][z]>0&&
	   space.form[x][y][z+1]>0&&
	   space.form[x][y][z-1]>0
	   ){impossible=1;}
      }}}
  return impossible;
}
 
int CompareCube(Cube a,Cube b){
  int x,y,z;
  int same=1;
  for(x=1;x<=3;x++){for(y=1;y<=3;y++){for(z=1;z<=3;z++){
	if(a.form[x][y][z]!=b.form[x][y][z]){same=0;}
      }}}
  return same;
}
 
Cube RemovePiece(Cube space,int p_num){
  int x,y,z;
  for(z=1;z<=3;z++){for(y=1;y<=3;y++){for(x=1;x<=3;x++){
	if(space.form[x][y][z]==p_num){space.form[x][y][z]=0;}
      }}}
  return space;
}
 
Piece Rotate(Piece before,int axis,int exchange_a,int exchange_b){
  Piece after;
  int f_num;
  for(f_num=0;f_num<3;f_num++){
    after.foot[f_num][axis]=before.foot[f_num][axis];
    after.foot[f_num][exchange_a]=before.foot[f_num][exchange_b];
    after.foot[f_num][exchange_b]=before.foot[f_num][exchange_a]*(-1);
  }
  return after;
}
 
void WriteAns(Cube ans[ANSNUMMAX],int ansnum){
  int i;
  int x,y,z;
  for(i=1;i<=ansnum;i++){
    fprintf(file,"%d:\n\n",i);
    for(z=3;z>=1;z--){for(y=3;y>=1;y--){for(x=1;x<=3;x++){
	  fprintf(file,"%d ",ans[i].form[x][y][z]);
	}fprintf(file,"\n\n");}fprintf(file,"\n");}fprintf(file,"\n");
  }
}
