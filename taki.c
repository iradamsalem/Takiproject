//NAME:IRAD AMSALEM ID:209363639
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MAXNAMELEN 20
#define CARDS_AMMOUNT_AT_START 4
#define CARD_TYPES_AMMOUNT 14
#define COLORSAMMPUNT 4
// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

typedef struct CARD
{
	char color;//G green B blue Y yellow R red N no coloe card
	int cardnum;//1-14 1-9 numbers 10 plus 11 stop 12 change  direction 13 taki 14 change color
} CARD;
typedef struct STATISTICS
{
	int number;//card number
	int frequency;//frequencey
}  STATISTICS;
typedef struct PLAYERDATA
{
	CARD* player_cards;
	int cardsarraysize;
	int cardsammount;
	char name[MAXNAMELEN];
} PLAYER_DATA;
PLAYER_DATA* getplayersdata(int* playersammount);//the function prints welcome messege and gets the players array
void getrandomcard(CARD* c);//the function gives random card
void printcard(CARD c);//the function prints card
void splitingcards(CARD* player_cards, int size);//the function gives 4 random cards for each player
CARD* ALLOCcardsarray();//alocationg cards array
void game(PLAYER_DATA pdata[], int players_number);//the function runs the game
bool checkifthecardisvalid(CARD uppercard, CARD chosencard);//checking if the chosen card is valid
CARD* getcardfromdeck(CARD playercards[], PLAYER_DATA* player);//geting rendom card from the deck if there is need realloc more space for the cards array
void reorderafterremovingcard(CARD playercards[], int start, int end);//reorder player cards after removing one of them
void changecolorcard(CARD* c);//in case of change color card changing
PLAYER_DATA* changedirection(PLAYER_DATA playersarr[], int index, bool* direction, int size);//change direction with a support array
void printstatistc(STATISTICS arrgamedata[], int size);//print statistics
void sort(STATISTICS arr[], int size);//sorting by frequency
void main()
{
	srand(time(NULL));
	int playersammount;
	PLAYER_DATA* playersarray = NULL;
	playersarray = getplayersdata(&playersammount);
	for (int i = 0; i < playersammount; i++)
	{
		playersarray[i].cardsammount = CARDS_AMMOUNT_AT_START;
		playersarray[i].cardsarraysize = CARDS_AMMOUNT_AT_START;
		playersarray[i].player_cards = NULL;
		playersarray[i].player_cards = ALLOCcardsarray();
		splitingcards(playersarray[i].player_cards, CARDS_AMMOUNT_AT_START);
	}
	game(playersarray, playersammount);
	for (int i = 0; i < playersammount; i++)//free cards array memory after the game ends
	{
		free(playersarray[i].player_cards);
	}
	free(playersarray);//free players array memory after the game ends


}
PLAYER_DATA* getplayersdata(int* playersammount)//the function prints welcome messege and gets the players array
{
	PLAYER_DATA* playersarray = NULL;
	printf("************  Welcome to TAKI game !!! ***********\n");
	printf("Please enter the number of players:\n");
	scanf("%d", playersammount);
	playersarray = (PLAYER_DATA*)malloc(*playersammount * sizeof(PLAYER_DATA));
	if (playersarray == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	for (int i = 0; i < *playersammount; i++)
	{
		printf("Please enter the first name of player #%d:\n", i + 1);
		scanf("%s", playersarray[i].name);
	}
	return playersarray;


}
CARD* ALLOCcardsarray()//alocationg cards array
{
	CARD* cardsarray = NULL;
	cardsarray = (CARD*)malloc(CARDS_AMMOUNT_AT_START * sizeof(CARD));
	if (cardsarray == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	return cardsarray;
}
void splitingcards(CARD* player_cards, int size)//the function gives 4 random cards for each player
{
	for (int i = 0; i < size; i++)
	{
		getrandomcard(&player_cards[i]);
	}
}
void printcard(CARD c)//the function prints card
{
	switch (c.color) {
	case 'G':
		printf(GREEN);
		break;
	case 'B':
		printf(BLUE);
		break;
	case 'Y':
		printf(YELLOW);
		break;
	case 'R':
		printf(RED);
		break;
	defult:
		printf(RESET);
		break;
	}
	printf("*********\n");
	switch (c.cardnum)
	{
	case 10:
		printf("*       *\n");
		printf("*   +   *\n");
		printf("*   %c   *\n", c.color);
		printf("*       *\n");
		break;
	case 11:
		printf("*       *\n");
		printf("*  STOP *\n");
		printf("*   %c   *\n", c.color);
		printf("*       *\n");
		break;
	case 12:
		printf("*       *\n");
		printf("*  <_>  *\n");
		printf("*   %c   *\n", c.color);
		printf("*       *\n");
		break;
	case 13:
		printf("*       *\n");
		printf("*  TAKI *\n");
		printf("*   %c   *\n", c.color);
		printf("*       *\n");
		break;
	case 14:
		printf("*       *\n");
		printf("* COLOR *\n");
		if (c.color != 'N')
		{
			printf("*   %c   *\n", c.color);
		}
		else
		{
			printf("*       *\n");
		}
		printf("*       *\n");
		break;


	default:
		printf("*       *\n");
		printf("*   %d   *\n", c.cardnum);
		printf("*   %c   *\n", c.color);
		printf("*       *\n");
		break;
	}
	printf("*********\n");
	printf(RESET);
}
void getrandomcard(CARD* c)//the function gives random card
{

	(*c).cardnum = 1 + rand() % CARD_TYPES_AMMOUNT;;
	int randomcolor = rand() % COLORSAMMPUNT;
	if ((*c).cardnum != 14)//14 is change color and has no color
	{
		switch (randomcolor)
		{
		case 0:
			(*c).color = 'R';//red
			break;

		case 1:
			(*c).color = 'G';//green
			break;
		case 2:
			(*c).color = 'Y';//yellow
			break;
		case 3:
			(*c).color = 'B';//blue
			break;

		default:
			break;
		}
	}
	else
	{
		(*c).color = 'N';//if card number is 14 then it's change color and has no color
	}



}
void game(PLAYER_DATA pdata[], int players_number)//the function runs the game
{

	CARD uppercard;
	bool direction = 1;
	bool winner = 0;
	bool takiopen = 0;
	STATISTICS array[CARD_TYPES_AMMOUNT];
	for (int i = 0; i < CARD_TYPES_AMMOUNT; i++)
	{
		array[i].frequency = 0;
		array[i].number = 0;
		array[i].number = i + 1;

	}
	getrandomcard(&uppercard);
	while (uppercard.cardnum >= 10)//first card is between 1-9
	{
		getrandomcard(&uppercard);
	}

	while (winner != 1)//the game continues until there is a winner
	{

		for (int i = 0; i < players_number; i++)
		{
			printf("Upper card:\n");
			printcard(uppercard);//print upper card
			//printf(RESET);
			printf("%s turn:\n", pdata[i].name);
			int playerschoise = 0;

			for (int j = 0; j < pdata[i].cardsammount; j++)
			{
				printf("Card #%d:\n", j + 1);
				printcard(pdata[i].player_cards[j]);
				//printf(RESET);

			}
			if (takiopen == 0)
			{
				printf("Please enter 0 if you want to take a card from the deck\n");
				printf("or 1-%d if you want to put one of your cards in the middle:\n", pdata[i].cardsammount);
			}
			else
			{
				printf("Please enter 0 if you want to finish your turn\n");
				printf("or 1-%d if you want to put one of your cards in the middle:\n", pdata[i].cardsammount);
			}
			scanf("%d", &playerschoise);//getting the player's choise
			if (takiopen == 0)
			{
				if (playerschoise == 0)//getting card from the deck
				{
					pdata[i].player_cards = getcardfromdeck(pdata[i].player_cards, &pdata[i]);//getting card from the deck
					continue;
				}
			}
			if (takiopen == 1)
			{
				if (playerschoise == 0)
				{
					takiopen = 0;
					continue;

				}
			}
			if (playerschoise != 0)
			{
				bool isvalid = checkifthecardisvalid(uppercard, pdata[i].player_cards[playerschoise - 1]);
				while (isvalid == 0)//checking if card is valid
				{
					printf("Invalid card! Try again.\n");
					printf("Please enter 0 if you want to take a card from the deck\n");
					printf("or 1-4 if you want to put one of your cards in the middle:\n");
					scanf("%d", &playerschoise);//getting the player's choise
					isvalid = checkifthecardisvalid(uppercard, pdata[i].player_cards[playerschoise - 1]);
					if (playerschoise == 0)
					{
						isvalid = 1;
					}

				}
				if (playerschoise == 0)
				{
					pdata[i].player_cards = getcardfromdeck(pdata[i].player_cards, &pdata[i]);//getting card from the deck
					continue;
				}
				if (pdata[i].player_cards[playerschoise - 1].cardnum == 13)//taki card
				{
					takiopen = 1;
					uppercard = pdata[i].player_cards[playerschoise - 1];
					reorderafterremovingcard(pdata[i].player_cards, playerschoise - 1, pdata[i].cardsammount - 1);
					pdata[i].cardsammount--;
					array[12].frequency++;
					if (pdata[i].cardsammount == 0)
					{
						winner = 1;
						printf("The winner is... %s! Congratulations!\n", pdata[i].name);//print the winner name
						break;
					}
					i = i - 1;
					continue;



				}
				if (pdata[i].player_cards[playerschoise - 1].cardnum < 10)//if it's a valid no speicel card
				{

					uppercard = pdata[i].player_cards[playerschoise - 1];
					reorderafterremovingcard(pdata[i].player_cards, playerschoise - 1, pdata[i].cardsammount - 1);
					pdata[i].cardsammount--;
					array[pdata[i].player_cards[playerschoise - 1].cardnum - 1].frequency++;
					if (pdata[i].cardsammount == 0)
					{
						winner = 1;
						printf("The winner is... %s! Congratulations!\n", pdata[i].name);//print the winner name
						break;
					}
					if (takiopen == 1)//in case taki is open 
					{
						i = i - 1;
						continue;
					}
					continue;
				}
				if (pdata[i].player_cards[playerschoise - 1].cardnum == 14)//change color
				{
					uppercard = uppercard = pdata[i].player_cards[playerschoise - 1];
					changecolorcard(&uppercard);
					reorderafterremovingcard(pdata[i].player_cards, playerschoise - 1, pdata[i].cardsammount - 1);
					pdata[i].cardsammount--;
					array[13].frequency++;
					if (pdata[i].cardsammount == 0)
					{
						winner = 1;
						printf("The winner is... %s! Congratulations!\n", pdata[i].name);//print the winner name
						break;
					}
					if (takiopen == 1)//change color stops taki fall
					{
						takiopen = 0;
					}
					continue;

				}
				if (pdata[i].player_cards[playerschoise - 1].cardnum == 10)//PLUS card another turn
				{
					uppercard = pdata[i].player_cards[playerschoise - 1];
					reorderafterremovingcard(pdata[i].player_cards, playerschoise - 1, pdata[i].cardsammount - 1);
					pdata[i].cardsammount--;
					array[9].frequency++;
					if (pdata[i].cardsammount == 0)
					{
						CARD c;
						getrandomcard(&c);
						pdata[i].player_cards[0] = c;
						pdata[i].cardsammount++;
					}

					i = i - 1;//another turn or if taki open it calls it again anyway
					continue;
				}
				if (pdata[i].player_cards[playerschoise - 1].cardnum == 11)//STOP skips player
				{
					uppercard = pdata[i].player_cards[playerschoise - 1];
					reorderafterremovingcard(pdata[i].player_cards, playerschoise - 1, pdata[i].cardsammount - 1);
					pdata[i].cardsammount--;
					array[10].frequency++;
					if (pdata[i].cardsammount == 0)
					{
						CARD c;
						getrandomcard(&c);
						pdata[i].player_cards[0] = c;
						pdata[i].cardsammount++;
					}
					if (takiopen == 1)//in case taki open
					{
						i = i - 1;
						continue;
					}
					if (i == players_number - 1)//in case it's last player we skip the first player to the second
					{
						i = 0;
						continue;
					}
					else
					{
						i = i + 1;//skips player
						continue;
					}
				}
				if (pdata[i].player_cards[playerschoise - 1].cardnum == 12)//change direction
				{
					uppercard = pdata[i].player_cards[playerschoise - 1];
					reorderafterremovingcard(pdata[i].player_cards, playerschoise - 1, pdata[i].cardsammount - 1);
					pdata[i].cardsammount--;
					array[11].frequency++;
					if (pdata[i].cardsammount == 0)
					{
						winner = 1;
						printf("The winner is... %s! Congratulations!\n", pdata[i].name);//print the winner name
						break;
					}
					if (takiopen == 1)//in case taki is open 
					{
						i = i - 1;
						continue;
					}
					else
					{
						pdata = changedirection(pdata, i, &direction, players_number);
						i = -1;//by the rules the one that changed direction gets another turn
						continue;
					}


				}


			}

		}


	}
	printstatistc(array, CARD_TYPES_AMMOUNT);

}
bool checkifthecardisvalid(CARD uppercard, CARD chosencard)//checking if the chosen card is valid
{
	if ((chosencard.color == uppercard.color) || (chosencard.cardnum == 14) || (chosencard.cardnum == 0) || ((chosencard.cardnum < 10) && (chosencard.cardnum == uppercard.cardnum)))//if the card is at the same color as the upper or change color or take card from deck
	{
		return 1;
	}
	else
	{
		return 0;
	}


}
CARD* getcardfromdeck(CARD playercards[], PLAYER_DATA* player)//geting rendom card from the deck if there is need realloc more space for the cards array
{
	CARD rand;
	getrandomcard(&rand);
	(*player).cardsammount++;
	if ((*player).cardsammount > (*player).cardsarraysize)
	{
		(*player).cardsarraysize++;
		playercards = (CARD*)realloc(playercards, sizeof(CARD) * (*player).cardsarraysize);
		if (playercards == NULL)
		{
			printf("ERROR");
			exit(1);
		}
		playercards[(*player).cardsammount - 1] = rand;
	}
	else
	{
		playercards[(*player).cardsammount - 1] = rand;

	}
	return playercards;
}
void reorderafterremovingcard(CARD playercards[], int start, int end)//reordering cards after removing one
{
	while (start != end)
	{
		playercards[start] = playercards[start + 1];
		start++;
	}


}
void changecolorcard(CARD* c)//in case of change color card changing
{
	int colorchoise = 0;
	bool colorisvalid = 0;
	printf("Please enter your color choice:\n");
	printf("1 - Yellow\n");
	printf("2 - Red\n");
	printf("3 - Blue\n");
	printf("4 - Green\n");
	scanf("%d", &colorchoise);
	while (colorisvalid == 0)
	{
		switch (colorchoise)
		{
		case 1:
			(*c).color = 'Y';
			colorisvalid = 1;
			break;

		case 2:
			(*c).color = 'R';
			colorisvalid = 1;
			break;
		case 3:
			(*c).color = 'B';
			colorisvalid = 1;
			break;
		case 4:
			(*c).color = 'G';
			colorisvalid = 1;
			break;

		default:
			printf("Invalid color! Try again.\n");
			printf("1 - Yellow\n");
			printf("2 - Red\n");
			printf("3 - Blue\n");
			printf("4 - Green\n");
			scanf("%d", &colorchoise);
			break;
		}
	}
}
PLAYER_DATA* changedirection(PLAYER_DATA playersarr[], int index, bool* direction, int size)//change direction with a support array
{
	PLAYER_DATA* copy;
	int counter = 0;
	copy = (PLAYER_DATA*)malloc(size * sizeof(PLAYER_DATA));
	if (copy == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	copy[0] = playersarr[index];//the player that chenges the direction gets another turn by the rules
	counter++;
	if (*direction == 1)//dirction is to the right chnge to left
	{
		for (int i = index; i > 0; i--)
		{
			copy[counter] = playersarr[i - 1];
			counter++;
		}
		for (int i = size - 1; i > index; i--)
		{
			copy[counter] = playersarr[i];
			counter++;

		}
	}
	if (*direction == 0)//dirction is to the left chnge to right
	{
		for (int i = index; i < size - 1; i++)
		{
			copy[counter] = playersarr[i + 1];
			counter++;

		}
		for (int i = 0; i < index; i++)
		{
			copy[counter] = playersarr[i];
			counter++;
		}

	}
	return copy;
	direction = !*direction;
	index = 0;
}
void printstatistc(STATISTICS arrgamedata[], int size)//print statistics
{
	printf("************ Game Statistics ************\n");
	printf("Card # | Frequency\n");
	printf("__________________\n");
	sort(arrgamedata, size);
	for (int i = size - 1; i >= 0; i--)
	{

		switch (arrgamedata[i].number)
		{
		case 10:
			printf("   +   |    %d\n", arrgamedata[i].frequency);
			break;
		case 11:
			printf(" STOP  |    %d\n", arrgamedata[i].frequency);
			break;
		case 12:
			printf("  <->  |    %d\n", arrgamedata[i].frequency);
			break;
		case 13:
			printf(" TAKI  |    %d\n", arrgamedata[i].frequency);
			break;
		case 14:
			printf(" COLOR |    %d\n", arrgamedata[i].frequency);
			break;


		default:
			printf("   %d   |    %d\n", arrgamedata[i].number, arrgamedata[i].frequency);
			break;
		}

	}
}
void sort(STATISTICS arr[], int size)//sorting by frequency
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j].frequency > arr[j + 1].frequency)//swap
			{
				STATISTICS temp;
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

			}

		}




	}

}



