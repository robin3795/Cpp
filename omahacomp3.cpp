#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DeckOfCard
{
public:
	struct omahaResults 
	{
		int rank;
    	int highCard;
	};
	
	int higher(int a, int b)
	{
		int c;
		if (a>b)
			c=a;
		else
			c=b;
		return c;
	}
	
	omahaResults max(omahaResults t, omahaResults r)
	{
		if(t.rank > r.rank)
			r = t;
		else if(t.rank == r.rank)
		{
			if(t.highCard > r.highCard)
				r = t;
		}
		return r;
	}

	omahaResults ifHighCard(int cards[5][2])
	{
		omahaResults r;
		r.rank = 0;
		r.highCard = cards[4][0];
		return r;
	}
	
	omahaResults ifOnePair(int cards[5][2])
	{
		omahaResults r;
		if(cards[0][0]==cards[1][0])
		{
			r.rank = 1;
			r.highCard = cards[1][0];
		}
		else if(cards[1][0]==cards[2][0])
		{
			r.rank = 1;
			r.highCard = cards[2][0];
		}
		if(cards[2][0]==cards[3][0])
		{
			r.rank = 1;
			r.highCard = cards[3][0];
		}
		if(cards[3][0]==cards[4][0])
		{
			r.rank = 1;
			r.highCard = cards[4][0];
		}
		return r;
	}
    
	omahaResults ifTwoPair(int cards[5][2])
	{
		omahaResults r;
		if(cards[0][0]==cards[1][0] && cards[2][0]==cards[3][0])
		{
			r.rank =2;
			r.highCard = higher(cards[0][0],cards[2][0]);
		}
		if(cards[1][0]==cards[0][0] && cards[3][0]==cards[4][0])
		{
			r.rank =2;
			r.highCard = higher(cards[0][0],cards[3][0]);
		};
		if(cards[1][0]==cards[2][0] && cards[3][0]==cards[4][0])
		{
			r.rank =2;
			r.highCard = higher(cards[1][0],cards[3][0]);
		}
		return r;
	}

	omahaResults if3ofAKind(int cards[5][2])
	{
		omahaResults r;
		if(cards[0][0]==cards[1][0] && cards[1][0]==cards[2][0]) 
		{
			r.rank = 3;
			r.highCard = cards[0][0];
		}
		if(cards[1][0]==cards[2][0] && cards[2][0]==cards[3][0])
		{
			r.rank = 3;
			r.highCard = cards[1][0];
		}
		if(cards[2][0]==cards[3][0] && cards[3][0]==cards[4][0])
		{
			r.rank = 3;
			r.highCard = cards[2][0];
		}
		return r;
	}

	omahaResults ifStraight(int cards[5][2])
	{ 
		omahaResults r;
		if(cards[1][0]==cards[0][0]+1 && cards[2][0]==cards[1][0]+1 && cards[3][0]==cards[2][0]+1 && cards[4][0]==cards[3][0]+1)
		{
			r.rank = 4;
			r.highCard = cards[4][0];
		}
		return r;
	}
	
	omahaResults ifFlush(int cards[5][2])
	{
		omahaResults r;
		if(cards[1][1]==cards[0][1] && cards[2][1]==cards[0][1] && cards[3][1]==cards[0][1] && cards[4][1]==cards[0][1])
		{
			r.rank = 5;
			r.highCard = cards[4][0];
		}
		return r;
	}

	omahaResults ifFullHouse(int cards[5][2])
	{
		omahaResults r;
		if(cards[0][0]==cards[1][0] && cards[1][0]==cards[2][0] && cards[3][0]==cards[4][0])   
		{
			r.rank = 6;
			r.highCard = cards[2][0];
		}
		if(cards[0][0]==cards[1][0] && cards[2][0]==cards[3][0] && cards[3][0]==cards[4][0])
		{
			r.rank = 6;
			r.highCard = cards[2][0];
		}
		return r;
	}
	
	omahaResults if4ofAKind(int cards[5][2])
	{
		omahaResults r;
		if(cards[0][0]==cards[1][0] && cards[1][0]==cards[2][0] && cards[2][0]==cards[3][0] )   
		{
			r.rank = 7;
			r.highCard = cards[3][0];
		}
		if(cards[1][0]==cards[2][0] && cards[2][0]==cards[3][0] && cards[3][0]==cards[4][0] )
		{
			r.rank = 7;
			r.highCard = cards[4][0];
		}
		return r;
	}

	omahaResults ifStraightFlush(int cards[5][2])
	{
		omahaResults r;
		if (ifStraight(cards).rank==4 && ifFlush(cards).rank==5)
		{
			r.rank = 8;
			r.highCard = cards[4][0];
		}	
		return r;
	}
	
	omahaResults findRank(int cards[5][2])
	{
		omahaResults r;
		
		if (ifStraightFlush(cards).rank==8)
			r = ifStraightFlush(cards);
		else if(if4ofAKind(cards).rank==7)
			r = if4ofAKind(cards);
		else if(ifFullHouse(cards).rank==6)
			r = ifFullHouse(cards);
		else if(ifFlush(cards).rank==5)
			r = ifFlush(cards);
		else if(ifStraight(cards).rank==4)
			r = ifStraight(cards);
		else if(if3ofAKind(cards).rank==3)
			r = if3ofAKind(cards);
		else if(ifTwoPair(cards).rank==2)
			r = ifTwoPair(cards);
		else if(ifOnePair(cards).rank==1)
			r = ifOnePair(cards);
		else
			r= ifHighCard(cards);
		return r;
	}
	
	int sortCard(int cards[5][2])
	{
		bool swapped = false;
		do
		{
			swapped = false;
			for (int i=0; i<4; i++)
			{
				if (cards[i][0] > cards[i+1][0])
				{
					int tempRank = cards[i][0];
					int tempSuit = cards[i][1];
					cards[i][0] = cards[i+1][0];
					cards[i][1] = cards[i+1][0];
					cards[i+1][0] = tempRank;
					cards[i+1][1] = tempSuit;
					swapped = true;
				}
			}
		}
		while(swapped== true);
	}
	
	void moveAces(int cards[5][2])
    {
        int aces = 0;

        for(int i = 0; i < 5; ++i)
            if(cards[i][0] == 0)
                aces++;

        while(aces != 0)
        {
            int tempRank, tempSuit;

            tempSuit = cards[0][1];

            for(int i = 0; i < 4; i++)
            {
                cards[i][0] = cards[i+1][0];
                cards[i][1] = cards[i+1][1];
            }

            cards[4][0] = 13;
            cards[4][1] = tempSuit;

            aces--;
        }
    }

	
	/*int digitalCard(char charCard[5][2])
	{
		int cards[5][2];
		static const char cardSuit[4] = {'s', 'h', 'd', 'c'};
    	static const char cardRank[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
		for (int i=0; i<5; i++)
		{
			for (int j=0; j<13; j++)	
			{
				if (charCard[i][0]==cardRank[j])
					cards[i][0]=j;
			}		
			for (int j=0; j<4; j++)	
			{
				if (charCard[i][1]==cardSuit[j])
					cards[i][1]=j;
			}		
		}
		return cards;
	}*/
	
	omahaResults omahaRank(string hand, string board)
	{
		omahaResults r;
		omahaResults tmp;
	
		r.rank=0;
		r.highCard=0;
		
		char handCard[4][2];
		char boardCard[5][2];
		char charCard[5][2];
		int  cards[5][2];
		
		for(int i=0; i<4; i++)
		{
			handCard[i][0] = hand[3*i];
			handCard[i][1] = hand[3*i+1];
		}
		for(int i=0; i<5; i++)
		{
			boardCard[i][0] = board[3*i];
			boardCard[i][1] = board[3*i+1];
		}
		
		//There is no stragies for picking cards, do all possible choices
		for (int i=0; i<3; i++)
		{
			charCard[0][0] = boardCard[i][0]; //first card from board
			charCard[0][1] = boardCard[i][1];
			for (int j=1; j<5-i; j++)
			{
				charCard[1][0] = boardCard[i+j][0];  //secord card from board
				charCard[1][1] = boardCard[i+j][1];
				for (int k=1; k<5-i-j; k++)
				{
					charCard[2][0] = boardCard[i+j+k][0]; //last card from board
					charCard[2][1] = boardCard[i+j+k][1];
					for (int m=0; m<3; m++)
					{
						charCard[3][0] = handCard[m][0]; //first card from hand
						charCard[3][1] = handCard[m][1];
						for (int n=1; n<4-m; n++)
						{
							charCard[4][0] = handCard[m+n][0];//second card from hand
							charCard[4][1] = handCard[m+n][1];
							
							//Transfer char array to int array for sorting
							static const char cardSuit[4] = {'s', 'h', 'd', 'c'};
    						static const char cardRank[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
							for (int i=0; i<5; i++)
							{
								for (int j=0; j<13; j++)	
								{
									if (charCard[i][0]==cardRank[j])
										cards[i][0]=j;
								}		
								for (int j=0; j<4; j++)	
								{	
									if (charCard[i][1]==cardSuit[j])
										cards[i][1]=j;
								}		
							}
							
							//cards = digitalCard(charCard);
							sortCard(cards);
							tmp = findRank(cards);
							r = max(tmp,r);
							moveAces(cards);
							tmp = findRank(cards);
							r = max(tmp,r);	
						}
					}
					
				}
			}
		}
		return r;
	}
	
	string rankToString(int rank)
	{
		string stringRank;
		switch(rank)
		{
			case 8:	stringRank = "Straight Flush";
				break;
			case 7:	stringRank = "4-of-a-Kind";
				break;
			case 6:	stringRank = "Full House";
				break;
			case 5:	stringRank = "Flush";
				break;
			case 4:	stringRank = "Straight";
				break;
			case 3:	stringRank = "3-of-a-Kind";
				break;
			case 2:	stringRank = "Two Pair";
				break;
			case 1:	stringRank = "One Pair";
				break;
			default: stringRank = "High Card";
				break;
		}
		return stringRank;
	}
	
    string runGame(string s)
    {
    	string results;
		string strHandA = s.substr(6,11);
		string strHandB = s.substr(24,11);
		string strBoard = s.substr(42,14);
    	results = "HandA:"+strHandA+" HandB:"+strHandB+" Board:"+strBoard;
    	string winner ="None";
    	omahaResults omahaRankA = omahaRank(strHandA,strBoard);
    	omahaResults omahaRankB = omahaRank(strHandB,strBoard);
    	if (omahaRankA.rank > omahaRankB.rank)
    		winner = "HandA wins (" +rankToString(omahaRankA.rank)+")";    
       	else if (omahaRankA.rank < omahaRankB.rank)
    		winner = "HandB wins (" +rankToString(omahaRankB.rank)+")";
    	else
    	{
    		if(omahaRankA.highCard > omahaRankB.highCard)
    			winner = "HandA wins (" +rankToString(omahaRankA.rank)+")";
    		else if(omahaRankA.highCard < omahaRankB.highCard)
    			winner = "HandB wins (" +rankToString(omahaRankA.rank)+")";
    		else
    			winner = "Split Pot (" +rankToString(omahaRankA.rank)+")";
    	}
		results += " => "+winner+ "\n";
    	return results;
    }
};

int main ()
{
	string s;
	DeckOfCard deck;
	ifstream inFile;
	inFile.open ("input.txt",ios::in);
	ofstream outFile;
	outFile.open ("output.txt");
    while(!inFile.eof()) // To get all the lines.
    {
        getline(inFile,s); // Saves the line in s.
	    outFile<< deck.runGame(s);
    }
	inFile.close();
	outFile.close();
	return 0;
}
