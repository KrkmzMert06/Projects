#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int system_random()
//This is for game 1
{
int choise;

choise=rand()%3;
if(choise==0)
{
    return 0;
}
else if(choise==1)
{
    return 1;
}
else
{
    return 2;
}
}
int system_random2()
//This is for game 2
{

int choise2;
choise2=rand()%100;
return choise2;

}
int main() {
int pick,pick2,num,random;
int pc=0,you=0;
srand(time(NULL));

do{
printf("************************\n");
printf("**********MENU**********\n");
printf("************************\n\n");
printf("1.Rock Paper Scissors\n2.Number Guessing Game\n3.Exit the game\n\n");
printf("Please pick the game:");
scanf("%d",&pick);
switch(pick)
{
case 1:
    printf("-----Welcome to Rock Paper Scissors game-----\n");
    you=0;
    pc=0;
    do{
    	printf("Raund : %d\n",you+pc +1);
    	printf("Choose one :\n0.Rock\n1.Paper\n2.Scissors\n");
    scanf("%d",&pick2);
    if(pick2==2 && system_random()==0 ){
        printf("You won raund the %d \n",you+pc +1);
        you++;
    }
    else if(pick2==0 && system_random()==2){
        printf("You lost raund the %d\n",you+pc +1);
        pc++;
    }
    else if(pick2>system_random()){
        printf("You won raund the %d\n",you+pc +1);
        you++;
    }
    else{
        printf("You lost raund the %d\n",you+pc +1);
        pc++;
    }	
	}while(you+pc<=4);
	printf("The result is you %d - %d computer\n\n",you,pc);
    break;
case 2:
    printf("-----Welcome to Number Guessing Game-----\n");
    random=system_random2();
    do{
        
    printf("Please guess a number between 1-100 :");
    scanf("%d",&num);
    
    if(num>random){
    	
        printf("It is less than the number you chose\n\n");
    }
    else if(num<random){
        printf("It is more than the number you chose\n\n");
    }else{
        printf("Congratulations!! You guessed the number correctly!!!!\n");
        break;
    }
    }while(1);
    break;
case 3:
    printf("You quit the game\n\n");
 
    break;
    
}
}while(pick!=3);

    return 0;
}