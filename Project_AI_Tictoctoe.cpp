#include<iostream>
#include<stdlib.h>
#include<conio.h>

using namespace std;
int check_if_player_gonna_win(char [][3],int,int,int [],bool);
int horizontal_check(char [][3],int,int,int *);
int vertical_check(char [][3],int,int,int *);
int left_diagonal_check(char [][3],int,int,int,int *);
int right_diagonal_check(char [][3],int,int,int,int *);
int check_if_cpu_gonna_win(char [][3],int [],int *);
void draw_mattrix(char [][3],char);
int vs_cpu(char [][3],int,int,int,int [],bool);
int is_someone_won(char [][3],int ,int ,int );
int game_over(int,char [][3]);
int user_input(char [][3],char,int &,int &);
int check_draw(char[][3]);

int zero_kata(){
	char mattrix[3][3]={{'1','2','3'}
	 					,{'4','5','6'},
						 {'7','8','9'}};
	cout<<"Enter Your Choice"<<endl;
	cout<<"1.Play With Player"<<endl<<"2.Play With Cpu"<<endl<<"3.Evil Cpu"<<endl;
	int choice; 
	cin>>choice;//2
	bool vs_plr=false,cpu=false,cpu_evil=false;
	int moves=1,flag=0,i=0,j=0;
	char input;
	char symbol='X';
	char pre_symbol='O';
	int cpu_move[2];
	switch(choice){
		case 1:
			vs_plr=true;
			break;
		case 2:
			cpu=true;
			break;
		case 3:
			cpu_evil=true;
			cpu=true;
			break;
	}
	
	cout<<"\n"<<"Player 1:"<<'X'<<endl;
	cout<<"Player2/Cpu:"<<'O'<<endl;
	cout<<endl;
	cout<<"Press Any key to continue............. \n\n";
	getch();
	while(1)
		{
			draw_mattrix(mattrix,'|');
			if(!user_input(mattrix,symbol,i,j)){
				user_input(mattrix,symbol,i,j);
			}
			
			//checking if someone won
			if(is_someone_won(mattrix,i,j,flag))
				{
												
					game_over(flag+1,mattrix);
					return 1;	
				}
				
				
				//vs cpu 		
			if(cpu){
				
				if(vs_cpu(mattrix,i,j,moves,cpu_move,cpu_evil)==100){
					
					game_over(3,mattrix);
					return 1;
				}
				   }
				   //vs plr
			else if(vs_plr){
				symbol=symbol+pre_symbol;
				pre_symbol=symbol-pre_symbol;
				symbol=symbol-pre_symbol;
				flag+=1;
				flag=flag%2;
				 }
		
			moves+=1;
			if(moves>3){
			//checking draw
			if(check_draw(mattrix)){
				game_over(4,mattrix);
			}
			}
			system("cls");
		}	
}

//taking user choice
int user_input(char mattrix[][3],char symbol,int &i, int &j){
	int input;
		cout<<"Enter Input "<<endl;
		input=getch();
		for(i=0;i<3;i++){
			for( j=0;j<3;j++){
				if(mattrix[i][j]==input){
					mattrix[i][j]=symbol;
					return 1;
					}
				}
			}
			return 0;
}

//terminating the game if anyone wons 
int game_over(int plr,char mattrix[][3]){
	system("cls");
	draw_mattrix(mattrix,'|');

		switch(plr){
			case 1:
				cout<<"\t*****************Player 1 won************************";
				break;
			case 2:
				cout<<"\t\t***************Player 2 won************************";
				break;
			case 3:
				cout<<"\t******************Cpu won*****************************";
				break;
			case 4:
				cout<<"\t******************DRAW********************************";
		}
		cout<<endl<<"1. Play Again  2.Exit"<<endl;
		int user_input;
		cin>>user_input;
		if(user_input==1){
			system("cls");
		zero_kata();
						}
		else{
			return 1;
			}
}
int check_draw(char mattrix[][3]){
	int i;
	int j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(mattrix[i][j]>'1' && mattrix[i][j]<='9'){
				return 0;
			}
		}
	}
	return 1;
}
//checking if anyone won the game
int is_someone_won(char mattrix[][3],int row,int col,int flag)
{
	if(horizontal_check(mattrix,row,flag,NULL)==100){
		return 1;
	}
	else if(vertical_check(mattrix,col,flag,NULL)==100){
		return 1;
	}
	else if(left_diagonal_check(mattrix,row,col,flag,NULL)==100){
		return 1;
	}
	else if(right_diagonal_check(mattrix,row,col,flag,NULL)==100){
		return 1;
	}
	return 0;
}


//drawing the mattrix
void draw_mattrix(char mattrix[][3],char pattern){ 

int i,j;
int row=0,col=0;
for(i=1;i<15;i++){//5 
	cout<<"\t\t";
	if(i%5==0){
		row+=1;
	}
	for(j=1;j<27;j++){//23
		if(i%5==0){
			cout<<'-';
			//1
		}
		else if(j%9==0){
			cout<<'|';
		}
		else if((i==3 || i==8 || i==13) && (j==5 || j==14 || j==23)){//3 14 2
			cout<<mattrix[row][col];
			col+=1;//3
			//2
		}
		else{
			cout<<" ";
		}
		
	}
	col=0;
	//col=0;
	cout<<endl;
}
}

// if player wants to play with cpu 
int vs_cpu(char mattrix[][3],int plr_row,int plr_col,int moves,int cpu_move[],bool evil){
	int arr[4]={plr_row,plr_col};
	int blank_space[2]={-1,-1};

	int flag=0;
	// if move==1 then randomly anywhere move
	if(moves==1){
		int random_row,random_col;
		while(1){
			random_row=rand()%3;
			random_col=rand()%3;
			if(mattrix[random_row][random_col]!='X'){
				
					break;
					}	
			}
			cpu_move[0]=random_row;
			cpu_move[1]=random_col;
			mattrix[cpu_move[0]][cpu_move[1]]='O';
			return 1;
		}
	
	if(check_if_cpu_gonna_win(mattrix,cpu_move,blank_space)){
		mattrix[cpu_move[0]][cpu_move[1]]='O';
			return 100;//returning 100 if cpu is won;
		}
		
	flag=check_if_player_gonna_win(mattrix,plr_row,plr_col,arr,evil);
		//checking cpu gonna win also ?

		//checking if flag ==1 
	if(flag){
			mattrix[arr[0]][arr[1]]='O';
			cpu_move[0]=arr[0];
			cpu_move[1]=arr[1];
			if(flag==4){
				mattrix[arr[2]][arr[3]]='O';
				cpu_move[0]=arr[2];
				cpu_move[1]=arr[3];
			}
			cout<<cpu_move[0]<<cpu_move[1];
			return 1;
		}
	else{
		cout<<blank_space[0]<<blank_space[1];
		//taking smart decision by putting next move in right direction. it will increase the cpu chances to win
		if(blank_space[0]!=-1)
		{
			cpu_move[0]=blank_space[0];
			cpu_move[1]=blank_space[1];
			mattrix[cpu_move[0]][cpu_move[1]]='O';
		}
		else{
			int i,j;
			for(i=0;i<3;i++)
				for(j=0;j<3;j++){
					if(mattrix[i][j]!='O' && mattrix[i][j]!='X'){
						cpu_move[0]=i;
						cpu_move[1]=j;
						mattrix[i][j]='O';
						return 1;
					}
				}				
			}
				

		}


}

//logic for player gonna win 
int check_if_player_gonna_win(char mattrix[][3],int plr_row,int plr_col,int arr[],bool evil){
	
	int blank_col,blank_row,blank_left,blank_right;
	int temp=0;
	if(blank_col=horizontal_check(mattrix,plr_row,0,NULL)){
		arr[temp]=plr_row;
		temp+=1;
		arr[temp]=blank_col-1;
		temp+=1;
		if(!evil){
			return 1;
		}
	}
	
	if(blank_row=vertical_check(mattrix,plr_col,0,NULL)){
		 arr[temp]=blank_row-1;
		 temp+=1;
		 arr[temp]=plr_col;
		 temp+=1;
		 if(!evil)
			 return 1;
		//indicates vertically gonna win;
		
	}
	 if(blank_left=left_diagonal_check(mattrix,plr_row,plr_col,0,NULL)){
			blank_left-=1;
			arr[temp]=blank_left;
			temp+=1;
			arr[temp]=blank_left;
			temp+=1;
			if(!evil)
				return 1;
	}
	
	 if(blank_right=right_diagonal_check(mattrix,plr_row,plr_col,0,NULL)){
		blank_right-=1;
			arr[temp]=blank_right;
			temp+=1;
			arr[temp]=2-blank_right;
			temp+=1;
			if(!evil)
				return 1;
	}
	if(temp){
		return temp;
	}
	return 0;
}

//checking if cpu gonna win by anylizing players's next move
int check_if_cpu_gonna_win(char mattrix[][3],int cpu_move[],int *ptr){
	int temp;
	if(temp=horizontal_check(mattrix,cpu_move[0],1,ptr)){
			temp--;
			cpu_move[1]=temp;
			return 1;		
	}
    if(temp=vertical_check(mattrix,cpu_move[1],1,ptr)){
			temp--;
			cpu_move[0]=temp;
			return 1;
	}
    if(temp=left_diagonal_check(mattrix,cpu_move[0],cpu_move[1],1,ptr)){
			temp--;
			cpu_move[0]=temp;
			cpu_move[1]=temp;
			return 1;
	}
    if(temp=right_diagonal_check(mattrix,cpu_move[0],cpu_move[1],1,ptr)){
			temp--;//row=0 col=2, row=1,col=1, row=2,col=0
			cpu_move[0]=temp;//row
			cpu_move[1]=2-temp;
			return 1;
	}
	return 0;
}

//check_horizontal
int horizontal_check(char mattrix[][3],int curr_row,int flag,int *ptr){
		
	int temp_col=0;
	int len=0;
	int blank_space;
	char zero='O';
	char kata='X';
	if(flag==1){
		zero='X';
		kata='O';
	}
	while(temp_col<3){
		if(mattrix[curr_row][temp_col]==zero){
			return 0;
		}
		else if(mattrix[curr_row][temp_col]==kata){
			len+=1;
			
		}
		else{
			blank_space=temp_col;//2
		}
		temp_col+=1;
	}
	if(len==2){
		return blank_space+1;
	}
	else if(len==3){
		return 100;
	}
	else if(ptr!=NULL){
			ptr[0]=curr_row;
			ptr[1]=blank_space;	
		}
	return 0;
}

//check vertical 
int vertical_check(char mattrix[][3],int curr_col,int flag,int *ptr){
		
	int curr_row=0;
	int len=0;
	int blank_space;
	char zero='O';
	char kata='X';
	if(flag==1){
		zero='X';
		kata='O';
	}
	while(curr_row<3){
		if(mattrix[curr_row][curr_col]==zero){
			return 0;
		}
		else if(mattrix[curr_row][curr_col]==kata){
			len+=1;
		}
		
		else{
			blank_space=curr_row;//2
		}
		curr_row+=1;
	}
	if(len==2){
		return blank_space+1;
	}
	else if(len==3){
			return 100;
	}
	else if(ptr!=NULL){

		ptr[0]=curr_col;
		ptr[1]=blank_space;	
		}
	return 0;
}

//check right diagonal
int right_diagonal_check(char mattrix[][3],int curr_row,int curr_col,int flag,int *ptr){

	if (curr_row==2 && curr_col==0 || curr_row==0 && curr_col==2 || curr_row==1 && curr_col==1){
		cout<<"why";
		int len=0;
		int blank_space;
		curr_row=2;
		curr_col=0;
			char zero='O';
			char kata='X';
			if(flag==1){
				zero='X';
				kata='O';
			}
			while(curr_row>=0){
				if(mattrix[curr_row][curr_col]==zero){
					return 0;
				}
				else if(mattrix[curr_row][curr_col]==kata){
					len+=1;
				}
				else{
					blank_space=curr_row;//1
					
				}
				curr_row-=1;
				curr_col+=1;
			}
		if(len==2){
				return blank_space+1;
			}
		else if(len==3){
				return 100;
			}
		else if(ptr!=NULL){
			ptr[0]=blank_space;
			ptr[1]=2-blank_space;	
			}	
		}
	return 0;
}

//check left diagonal 
int left_diagonal_check(char mattrix[][3],int curr_row,int curr_col,int flag,int *ptr){
	if ((curr_col==0 && curr_row==0 ) || (curr_row==2 && curr_col==2) || (curr_row==1 && curr_col==1)){
		int len=0;
		int blank_space;
		char zero='O';
		char kata='X';
		if(flag==1){
			zero='X';
			kata='O';
		}
		curr_row=0;
		curr_col=0;
		while(curr_row<3){
			if(mattrix[curr_row][curr_col]==zero){
				return 0;
			}
			else if(mattrix[curr_row][curr_col]==kata){
				len+=1;
			}
			else{
				blank_space=curr_row;//1
			}
			curr_row+=1;
			curr_col+=1;
		}
		if(len==2){
			return blank_space+1;
		}
		else if(len==3){
				return 100;
		}
		else if(ptr!=NULL){
			ptr[0]=blank_space;
			ptr[1]=blank_space;	
		}
}
	return 0;
}



int main(){

	zero_kata();
}
