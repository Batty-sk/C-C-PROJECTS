#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

void move(int,int,int,int,int [][4]);
int make_it_movable(int [][4]);
void patterns(int [][4],char);
char Pattern_Selecting(int);
int is_sorted(int [][4]);
int random_array_generator(int [][4]);
void Won_The_Game();
void Game_Header(char *,int);

//Making Continue Feature Logic  
struct Ques_and_Ans{
	char Ques[50];
	int Ans;
}que_ans[5];


void Game_Header(char *ptr,int Moves){
	//Giving MY Game A name 
	printf("----------------------------------------------\n");
	printf("**************THE GAME OF SORTING*************\n");
	printf("----------------------------------------------\n\n");
//Displaying rules 
	printf("*******************RULES**********************\n");
	printf("1-YOU CAN MOVE ONLY 1 STEP AT A TIME WITH THE ARROW KEY.\n");
	printf("2-YOU CAN MOVE NUMBERS AT AN EMPTY POSITION ONLY . \n");
	printf("3-FOR EACH VALID MOVES WILL DECREASE BY 1. \n");
	printf("-----------------------------------------------\n");
//Displaying player's name;
	printf("*******************PLAYER*********************\n");
	printf("-%s\n",ptr);
//Displating Moves 
	printf("***************MOVES-REMAINING*****************\n");
	printf("---------------------%d-----------------------\n\n",Moves);
		
}
//The Game Area
int make_it_movable(int mattrix[][4]){
	//Variables Declarations For Game-
	int free_row=3;
	int free_col=3;
	char key;
	int Moves=100;
	int valid=1;
	int pattern;
	char pttrn;
	int que_index=0;
	char username[20];
	printf("Player Name---------? \n");
	fgets(username,20,stdin);
	
	//Pattern Selecting For Mattrix
	printf("Select Pattern For Mattrix 1.'|'  2.'-'  3.'*'  4.'.'  5.'^' \n");
	scanf("%d",&pattern);
	printf("WINING CONDITION - SORT THE MATTRIX TO WIN \n");

	pttrn=Pattern_Selecting(pattern);
	printf("Press Any Key To Play ... ");
	getch();
	system("cls");
	
	//Making Moving Logic-	
	while(1){
		
		//GAME-HEADER--
		Game_Header(username,Moves);
		if(valid==0){
			printf("     \t\tInvalid Move !!    \n");
		}		
		else{
			Moves-=1;
		}
		
		// Printing The array after every move 
		patterns(mattrix,pttrn);
		
		valid=1;
		//I HAVE USED TWO GETCH SIR CAUSE THE SINGLE GETCH FUNCTION IS TAKING TWO INPUT AT ONCE uske waja se Moves Ka Logic kam nhi krr rha tha I don't know why this was happening
			getch();
			key=getch();
		switch(key){
			
			case(72):
			//up
				if(free_row+1<4){
					move(free_row+1, free_col, free_row, free_col , mattrix);
					free_row+=1;
				}
				else{
					valid=0;
				
				}
				break;
	
			case(80):
			//down
				
				if(free_row-1>=0){
					move(free_row-1, free_col, free_row, free_col, mattrix);
					free_row-=1;
				}
				else{
					
					valid=0;
				}
				break;
	
			case(75):
			//left
				if(free_col+1<4){
					
					move(free_row, free_col+1 , free_row, free_col, mattrix);
					free_col+=1;
				}
				else{
					valid=0;

				}
				break;
				
			case(77):
			//right
				if(free_col-1>=0){
					move(free_row, free_col-1, free_row, free_col, mattrix);
					free_col-=1;
				}
				else{
					valid=0;

				}
				break;
				
			case(27)://Ascii code for esc
				return 1;
			
			default:
				valid=0;
			
		}
	

	//clearing the screen after every move 
	system("cls");
	
	//checking if The Array is Sorted After Every Move?
	if(is_sorted(mattrix)){
		Won_The_Game();
		return 1;
	}
	
	//checking if player is out of Moves?
	
	if(Moves<=0){
		printf("---------------------------------------------------\n");
		printf("---------------------------------------------------\n");
		printf("---------------------------------------------------\n");
		printf("********************GAME OVER***********************\n");
		printf("---------------------------------------------------\n");
		printf("---------------------------------------------------\n");
		printf("---------------------------------------------------\n");
		printf("1.TRY AGAIN? 2.CONTINUE 3.PRESS ANY KEY TO EXIT \n");
		scanf("%d",&Moves);
		if(Moves==1){
			//calling random array_generator_function to make differnt array 
			random_array_generator(mattrix);
			Moves=100;
			//resetting the free_row,col to blank block 
			free_row=3;
			free_col=3;
		}
		//Continue Logic If The user Give the Correct Ans Then The User Can Continue The Game Without Sorting It From Start
		else if(Moves==2){
			printf("\nTo Continue You have to Ans The Given Ques \n\n");
			printf("%s \n",que_ans[que_index].Ques);
			int ans;
			scanf("%d",&ans);
			if(ans==que_ans[que_index].Ans){
				printf("Correct Ans \n");
				Moves=100;
				que_index+=1;
			}
			else{
				printf("Wrong Ans Taking You To New Game .... \n");
				random_array_generator(mattrix);
				Moves=100;
			}
			
			}
		else{
			break;
		}
	}

	}
}

//Pattern Selecting Logic 
char Pattern_Selecting(int pattern){
	if(pattern==1){
		return '|';
	}
	else if(pattern==2){
		return '-';
	}
	else if(pattern==3){
		return '*';
	}
	else if(pattern==4){
		return '.';
	}
	else if(pattern==5){
		return '^';
	}
	else{
		return '|';
	}
}
//Moving Logic!!
void move(int ele_row,int ele_col,int free_row,int free_col,int mattrix[][4]){
			mattrix[free_row][free_col]=mattrix[ele_row][ele_col];
			mattrix[ele_row][ele_col]='\0';
}

//
void patterns(int mattrix[][4],char pattern){ 
	
int i,j,row=0,col=0;	
for(i=0;i<=12;i++){
	printf("\t ");
	for(j=0;j<25;j++){//6
		if(j%6==0)//*
			printf("%c",pattern);
		else if(i%3==0)
			printf("*");
		else{
			if(j%2!=0 && j%3==0 && (i-1)%3==0){
				//finding length of a no if len is greater than 1 then skip the 1 space to avoid disturbance in pattern
				if(len_of_element(mattrix[row][col])){
					j+=1;	
				}
				//checking if no is zero 
				if(mattrix[row][col]==0)
					printf(" ");
				else{
				printf("%d",mattrix[row][col]);
					}
				col=(col+1)%4;
				if(col==0)
					row=(row+1)%4;
			}
			else{
			printf(" ");//*  19  *'
		}
		}
		
		
	}
	printf("\n");
}
}
int len_of_element(int no){
	int len=0;
	while(no>0){
		no=no/10;
		len++;
}
if(len>1){
	return 1;
}
return 0;
}


//CONTINUE FEATURE QUESTIONS IF USER GIVE THE ANSWER CORRECT OF ONE OF THESE QUESTION THEN HE/SHE WILL GONNA CHANCE TO CONTINUE THE GAMES 
// WITH FULL MOVES AND WITHOUT NEW ARRAY

void question_and_answers(){
	
	strcpy(que_ans[0].Ques,"What's The Size Of Int In 64 Bit Architecture? \n");
	que_ans[0].Ans=4;
	
	strcpy(que_ans[1].Ques,"What's The Size Of Char Data-Type ? (IN-BYTE)?\n");
	que_ans[1].Ans=1;
	
	strcpy(que_ans[2].Ques,"What's The Size of Float Data-Type? (IN-BYTE)?\n");
	que_ans[2].Ans=4;
	
	strcpy(que_ans[3].Ques,"What's The Size Of A Pointer Variable In 64 Bit Architectur?\n");
	que_ans[3].Ans=8;
	
	strcpy(que_ans[4].Ques,"What's The Value Of Null Character In Ascii?\n");
	que_ans[4].Ans=0;
	
}

//Logic To Generate Random Array After Every Play-Again Option
int random_array_generator(int mattrix[][4]){
	int nos[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int row=0,col=0,rno=0;
	while(row<4){
		rno=rand()%15;
		if(nos[rno]!=NULL){
			mattrix[row][col]=nos[rno];
			nos[rno]=NULL;
			col=(col+1)%4;
			if(col==0){
				row++;
			}
			//breaking Loop after reacinh to 
			if(col==3 && row==3)
			{
				mattrix[row][col]=0;
				break;
			}
		}
	}
}

//Logic To Check If The Array Is Sorted Or Not

int is_sorted(int mattrix[][4]){
	int i,j,pre_block=0;
	for(i=0;i<4;i++)
	{
		for(j=1;j<4;j++)
		{
			if(i==3 && j==3){
				return 1;
				}
			else if(mattrix[i][j]<pre_block){
					return 0;
			}
			pre_block=mattrix[i][j];
		}
	}
}
void Won_The_Game(){
system("cls");
printf("******************************************\n");
printf("******************************************\n");
printf("******************************************\n");
printf("*************CONGRATULATIONS**************\n");
printf("*****************YOU-WON******************\n");
printf("******************************************\n");
printf("******************************************\n");
printf("******************************************\n\n\n");

printf("-----------------THANK-YOU----------------\n");
printf("----------------FOR PLAYING---------------\n");
printf("---------------YOU'RE LEGEND---------------\n");
}
int main(){
	int mattrix[4][4]={{1, 2, 4, 3},
					   {5,10,11,13},
					   {9, 7, 8, 6},
					   {12,14,15  },
						};
	question_and_answers();
	make_it_movable(mattrix);
	printf("\nTHANK-YOU SIR FOR THIS AWSOME PROJECT MAJA AGYA KRKE\n");
	//80-down , 72-up , 77 - right , 75-left
	printf("CREATED BY SAURAV KUMAR \n");
	return 0;
}
