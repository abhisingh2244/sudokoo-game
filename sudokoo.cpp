#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<iostream>
#include<time.h>
#include<windows.h>
using namespace std;
void random()
{
    srand((unsigned)time(0));
}
// Interchange

void interchange(int (*a)[9],int (*q)[9])
{
    int arr[9],i,j;
    for(i=0;i<9;i++)
    {
        do
        {
            arr[i]=rand()%9+1;
            for(j=0;j<i;j++)
            {
                if(arr[i]==arr[j])
                    break;
            }
        }while(j!=i);
    }
     for(i=0;i<9;i++)
     {
         for(int j=0;j<9;j++)
         {
             a[i][j]=arr[a[i][j]-1];
             if(q[i][j]!=0)
                q[i][j]=a[i][j];
         }
     }
	return;
}
//for rows exchange within its set of three
void row(int (*a)[9],int (*q)[9])
{
  int principal=rand()%3;
  int sub=rand()%3;
  int sub1,temp;
  do
  {
    sub1=rand()%3;
  }while(sub1==sub);
  int row1=principal*3+sub;
  int row2=principal*3+sub1;
  for(int j=0;j<9;j++)
  {
    //for solution
    temp= a[row1][j];
    a[row1][j]=a[row2][j];
    a[row2][j]=temp;
    //for question
    temp= q[row1][j];
    q[row1][j]=q[row2][j];
    q[row2][j]=temp;
  }
  return;
}
//for column exchange within its set of three
void col(int (*a)[9],int (*q)[9])
{
  int principal=rand()%3;
  int sub=rand()%3;
  int sub1,temp;
  do
  {
    sub1=rand()%3;
  }while(sub1==sub);
  int col1=principal*3+sub;
  int col2=principal*3+sub1;
  for(int j=0;j<9;j++)
  {
    //for solution
    temp= a[j][col1];
    a[j][col1]=a[j][col2];
    a[j][col2]=temp;
    //for question
    temp= q[j][col1];
    q[j][col1]=q[j][col2];
    q[j][col2]=temp;
  }
  return;
}
//for whole 3*9 swap with next 3*9
void rows3(int (*a)[9],int (*q)[9])
{
    int sub=rand()%3;
    int sub1;
    do
    {
       sub1=rand()%3;
    }while(sub1==sub);
    int temp,i,k;
    for( i=sub*3,k=sub1*3;i<sub*3+3&&k<sub1*3+3;i++,k++)
    {
        for(int j=0;j<9;j++)
        {
            temp=a[i][j];
            a[i][j]=a[k][j];
            a[k][j]=temp;
            temp=q[i][j];
            q[i][j]=q[k][j];
            q[k][j]=temp;
        }
    }
   return ;
}
//for whole 3*9 swap with next 3*9
void cols3(int (*a)[9],int (*q)[9])
{
    int sub=rand()%3;
    int sub1;
    do
    {
       sub1=rand()%3;
    }while(sub1==sub);
    int temp,i,k;
    for( i=sub*3,k=sub1*3;i<sub*3+3&&k<sub1*3+3;i++,k++)
    {
        for(int j=0;j<9;j++)
        {
            temp=a[j][i];
            a[j][i]=a[j][k];
            a[j][k]=temp;
            temp=q[j][i];
            q[j][i]=q[j][k];
            q[j][k]=temp;
        }
    }
}
int main(void)
{
    random();
    int ne=1;
    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");
   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
   }
    while(ne)
    {
//ShowWindow(FindWindow(NULL,"Windows BGI"),SW_MAXIMIZE);
  //  DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    //DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
   // initwindow(screenWidth,screenHeight,"");
   /* request auto detection */
   int midx, midy;
   int radius = 100,fl=0;
   int i,j,tempx=0,tempy=0;
   int activex=0,activey=0;
   char inp[5];
   char arrow,ch;
   int a[9][9];
   int q[9][9],cpy[9][9];
   int esc=0,ng=0;
   int cl=3 ;   //color for input
   //-------------------------------------------------LOADING----------------------------------------------------------------
   FILE *fp;
   if((fp=fopen("students.txt","r"))==NULL)
   {
       cout<<"error";
   }
       for(i=0;i<9;i++)
        for(j=0;j<9;j++)
       {
           fscanf(fp,"%d",&a[i][j]);
       }
       for(i=0;i<9;i++)
        for( j=0;j<9;j++)
       {
           fscanf(fp,"%d",&q[i][j]);
       }
    fclose(fp);
    //----------------------------------------------------------------------
    //-----------------------------------------------------PROCESSING---------------------------------------------------------
     for( j=0;j<10000;j++)
      {
      interchange(a,q);
      row(a,q);
      col(a,q);
      rows3(a,q);
      cols3(a,q);
     }
     //---------------------------------------------------------------------------------------------------------
     //------------------------------------------------------UPDATE---------------------------------------------
      if((fp=fopen("students.txt","w"))==NULL)
     {
       cout<<"error";
     }
    for(i=0;i<9;i++)
    {
     for( j=0;j<9;j++)
       fprintf(fp,"%d ",a[i][j]);
    }
    for( i=0;i<9;i++)
    {
     for( j=0;j<9;j++)
    fprintf(fp,"%d ",q[i][j]);
    }
  fclose(fp);
  for(i=0;i<9;i++)
        for( j=0;j<9;j++)
       {
           cpy[i][j]=q[i][j];
       }
    //-----------------------------------------------------------------------------------------------------------------------
   /* initialize graphics and local variables */
   cleardevice();
   midx = getmaxx() /2-153;
   midy = getmaxy() / 2-153;
   //gotoxy(midx+15+activex*30,midy+15+activey*30);
   //setcolor(getmaxcolor());
   setcolor(YELLOW);
   setlinestyle(0,0,4);
   line(0,2,getmaxx(),2);
   rectangle(0,0,getmaxx(),getmaxy());
   setcolor(WHITE);
   setlinestyle(0,0,0);
   settextstyle(6,HORIZ_DIR,5);
   setcolor(9);
   outtextxy(midx+20,20,"SUDOKU");
   setcolor(WHITE);
   /* draw the circle */
  // circle(midx, midy, radius);
  for(i=midx,j=0;i<=midx+306;i=i+34,j++)
    {          if(j%3==0)
	       setlinestyle(0,0,3);
           line(i,midy,i,midy+306);
           setlinestyle(0,0,0);
     }
  for(i=midy,j=0;i<=midy+306;i=i+34,j++)
      {         if(j%3==0)
	        setlinestyle(0,0,3);
            line(midx,i,midx+306,i);
            setlinestyle(0,0,0);
      }
      //setfillstyle(SOLID_FILL,RED);
 // floodfill(midx+3,midy+3,WHITE);
   setcolor(WHITE);
  settextstyle(0,HORIZ_DIR,3);
 // outtextxy(100+i,100+j,"RAJ");
  for(i=0;i<9;i++)
    for(j=0;j<9;j++)
  {
      if(q[i][j]==0)
        continue;
      sprintf(inp,"%d",q[i][j]);
      outtextxy(midx+5+i*34,midy+5+j*34,inp);
  }
  settextstyle(0,HORIZ_DIR,2);
   outtextxy(10,200,"S-Submit");
   outtextxy(10,230,"N-New Game");
   outtextxy(10,260,"Esc-Exit");
  //movement of box;
   setcolor(WHITE);
  settextstyle(0,HORIZ_DIR,3);
    while (1) {
        if ( kbhit() ) {
            // Stores the pressed key in ch
	    ch = getch();
	     if(int(ch)==0)
	       continue;
	       //-------------------------------------------------------submssion-----------------------------------------------------------------------------------------------
	       if(ch=='s')
           {
               fl=0;
               for(i=0;i<9;i++)
                for(j=0;j<9;j++)
               {
                   if(a[i][j]!=q[i][j])
                   {
                       fl=1;
                       break;
                   }
               }
               if(fl==0)
               {
                 //cleardevice();
                   setcolor(6);
                   settextstyle(1,HORIZ_DIR,2);
                   outtextxy(170,midy+330,"HURRAY!!!! YOU SOLVED IT");
               }
               else
                               {
                 //cleardevice();
                   setcolor(BLUE);
                   setlinestyle(0,0,4);
                   rectangle(90,midy+320,530,midy+360);
                   setcolor(RED);
                   settextstyle(0,HORIZ_DIR,2);
                   outtextxy(170,midy+330,"OOPS!!!! THAT'S WRONG");
                   setfillstyle(SOLID_FILL,BLACK);
                   delay(1000);
                   floodfill(100,midy+325,BLUE);
                   setcolor(GREEN);
                   outtextxy(180,midy+330,"COMEON YOU CAN!!!!!");
                   settextstyle(0,HORIZ_DIR,3);
               }
           }
           if(ch=='n'||ch=='N')
           {
               break;
           }
            // Terminates the loop
            // when escape is pressed
            tempx=activex;
            tempy=activey;
            if (int(ch) == 27)
               {
                   cleardevice();
                   setcolor(GREEN);
                   settextstyle(0,HORIZ_DIR,3);
                   outtextxy(midx-100,midy,"THANKYOU FOR PLAYING");
                   setcolor(RED);
                   settextstyle(0,0,3);
                   outtextxy(midx-30,midy+100,"Press any key");
                   ne=0;
                   break;
               }
                if(int(ch)==72)
                 {
                    setfillstyle(SOLID_FILL,0);
                     floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                       if(q[activex][activey]!=0)
                       {
                           if(cpy[activex][activey]==0)
                            setcolor(cl);
                           else
                            setcolor(WHITE);
                         sprintf(inp,"%d",q[activex][activey]);
                       outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                       }
                    if(activey==0)
                       activey=8;
                    else
                       activey--;
                     //  gotoxy(midx+15+activex*30,midy+15+activey*30);
                    setfillstyle(SOLID_FILL,RED);
                  if(cpy[activex][activey]==0)
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                     sprintf(inp,"%d",q[activex][activey]);
                     if(q[activex][activey]!=0)
                       {
                           if(cpy[activex][activey]==0)
                            setcolor(cl);
                           else
                            setcolor(WHITE);
                            outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                       }
                 }
                 if(int(ch)==80)
                 {
                    setfillstyle(SOLID_FILL,0);
                     floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                     if(q[activex][activey]!=0)
                       {
                           if(cpy[activex][activey]==0)
                            setcolor(cl);
                           else
                            setcolor(WHITE);
                        sprintf(inp,"%d",q[activex][activey]);
                       outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                       }
                    if(activey==8)
                       activey=0;
                    else
                       activey++;
                      // gotoxy(midx+15+activex*30,midy+15+activey*30);
                    setfillstyle(SOLID_FILL,RED);
                  if(cpy[activex][activey]==0)
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                       {
                           if(cpy[activex][activey]==0)
                            setcolor(cl);
                           else
                            setcolor(WHITE);
                             sprintf(inp,"%d",q[activex][activey]);
                       outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                       }
                 }
                 if(int(ch)==75)
                 {
                    setfillstyle(SOLID_FILL,0);
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                       {
                           if(cpy[activex][activey]==0)
                            setcolor(cl);
                           else
                            setcolor(WHITE);
                            sprintf(inp,"%d",q[activex][activey]);
                       outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                       }
                    if(activex==0)
                       activex=8;
                    else
                       activex--;
                      // gotoxy(midx+15+activex*30,midy+15+activey*30);
                    setfillstyle(SOLID_FILL,RED);
                    if(cpy[activex][activey]==0)
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                       {
                           if(cpy[activex][activey]==0)
                            setcolor(cl);
                           else
                            setcolor(WHITE);
                            sprintf(inp,"%d",q[activex][activey]);
                       outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                       }
                 }
                 if(int(ch)==77)
                 {
                    setfillstyle(SOLID_FILL,0);
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                       {
                           if(cpy[activex][activey]==0)
                            setcolor(cl);
                           else
                            setcolor(WHITE);
                            sprintf(inp,"%d",q[activex][activey]);
                       outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                       }
                    if(activex==8)
                       activex=0;
                    else
                       activex++;
                      // gotoxy(midx+15+activex*30,midy+15+activey*30);
                    setfillstyle(SOLID_FILL,RED);
                   if(cpy[activex][activey]==0)
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                       {
                           if(cpy[activex][activey]==0)
                            setcolor(cl);
                           else
                            setcolor(WHITE);
                            sprintf(inp,"%d",q[activex][activey]);
                       outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                       }
                 }
                 if(int(ch)>=int('1')&&int(ch)<=('9')&&cpy[activex][activey]==0)
                 {
                     setfillstyle(SOLID_FILL,BLACK);
                     floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                      q[activex][activey]=int(ch)-int('1')+1;
                      sprintf(inp,"%d",q[activex][activey]);
                       setcolor(cl);
                    //   settextstyle(0,HORIZ_DIR,3);
                      outtextxy(midx+5+tempx*34,midy+5+tempy*34,inp);
                     // fl=1;
                 }
          /* if(q[tempx][tempy]!=0)
            {
                setcolor(WHITE);
                sprintf(inp,"%d",q[tempx][tempy]);
                outtextxy(midx+5+tempx*34,midy+5+tempy*34,inp);
            }*/
            fl=0;
	   // cout << "\nKey pressed= " << fl;
        }
    }
  /*cin>>arrow;
  if(arrow=='e')
    fl=1;
  if(arrow==24)
  {
      setfillstyle(SOLID_FILL,0);
      floodfill(midx+15+activex*30,midy+15+activey*30,WHITE);
      if(activex==0)
        activex=8;
      else
        activex--;
        gotoxy(midx+15+activex*30,midy+15+activey*30);
        setfillstyle(SOLID_FILL,RED);
        floodfill(midx+15+activex*30,midy+15+activey*30,WHITE);
  }*/
  // rectangle(midx,midy,midx+300,midy+300);
    //getch();
   /* clean up */
    }
    getch();
closegraph();
   return 0;
}
