#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>


//Global variables
using namespace std;
int start = 0;
int stop = 0; 
const int maxT = 100;
const int maxS = 100;
const int infin = 500;
const int MIN_MENU = 0;    
const int MAX_MENU = 4;
const int CLEAR_LINES = 20;
int stationcount = 0;		//set when loading stations
const int y = 100;
int x = 0;
int H;
int M;
int pH;
int pM;
int ampm;
int printampm;
int a[y];
int b[y];
int arrl;
int dep;
float timetaken;
float initial;






struct TRAINSREC
{
	int DStat;
	int AStat;
	int Dtime;
	int Atime;
	int travel;
};

TRAINSREC trains[maxS][maxS];
string stations[maxS];
int A[maxS][maxS];
int P[maxS][maxS];
int hourmin[maxS];

int PK[maxS];
int PKcount = 0;


int printtime ( int mytime )
{
	TRAINSREC train[maxT][maxT];
	int time;
	int a[y];
	int b[y];


	time = mytime;
	
	pH = time/60;
	pM = time%60;
	
	if( time < 1200)
		ampm = 1;    //AM
	else
	{
		ampm = 0;    //PM
		pH = pH - 12;
	}
	
	if( pH > 12 )
		pH = pH-12;

	pH = time/60;
	pM = time%60; 
		
		return pH, pM;
}

int printHM ( int gettime )
{
	int thetime;
	int i = 0;
	 
	
	thetime = gettime;
	
	
	if( gettime < 60 )
	{
		H = 0;
		M = gettime;
	}
	else
	{
		H = gettime/60;
		M = gettime%60;
	}
	
		H = gettime/60;
		M = gettime%60;
		
		return H, M;
}

void readinStations ()
{
	
 	int count = 0;
 	//string stat[maxS]; 
 
	ifstream infile;
	infile.open("stations.dat");
	
	if(!infile)
	{
		cout<<"No station information available!"<<endl;
		return;
	}
	count = -1;

	int num;
	string name;	
	
	while(!infile.eof())
	{
		infile>>num;
		infile>>name;
		stations[num] = name;
		count++;
	}	
	infile.close();
	
	for (int i = 0; i < count; i++)
		cout << i << ": " << stations[i] << endl;
	

	stationcount = count;
	
}



int shortest ( int a[maxS][maxS], TRAINSREC c[maxS][maxS], int p[maxS][maxS] )
{
	int i;
	int k;
	int j; 
	int R;
	int S;
	
	
	for( int i = 0; i < stationcount; i++ )
	{
		for( int j = 0; j <stationcount; j++ )
		{
			a[i][j] = c[i][j].travel;
			p[i][j] = -1;
		}
	}
	
	for( int i = 0; i < stationcount; i++ )  // setting major diagonal to zeros
	{
		a[i][i] = 0; 
	}
	
	
	for( int k = 0; k < stationcount; k++ )
	{
		for( int i = 0; i < stationcount; i++ )
		{
			for( int j = 0; j <stationcount; j++ )
			{
				if( a[i][k] + a[k][j] < a[i][j] )
				{
					a[i][j] =a[i][k] + a[k][j];
					p[i][j] = k;
					R=a[i][j];
					S=p[i][j];
				}	
			}
		}
	}
			
	return R, S;
}

void path ( int i, int j )  // find midpoints
{
	int k;
	k = P[i][j];
	
	if( k == -1 )
	{
		cout << "This is a direct path!*" << endl;
		return;				//ground the recursion if there is a  direct path
	}

		
	path( i, k );			//get the midpoint between i -> k
	PK[PKcount++] = k;		//process the midpoint
	path( k, j );			//get the midpoint between k -> j
	
	
}


void readinTrainInfo( void )
{
	TRAINSREC train[maxT][maxT];
	int a, b;
	ifstream infile; 
	
	for (int i = 0; i < maxT; i++)
		for (int j = 0; j < maxT; j++)
			trains[i][j].travel = infin;
			

	infile.open("trains.dat");
	if(!infile)
	{
		cout<<"No train information available!"<<endl;
		return;
	}
	
	while(!infile.eof())
	{
		infile>>a;
		infile>>b;
	
		infile>>trains[a][b].Dtime;
		infile>>trains[a][b].Atime;
		trains[a][b].DStat = a;
		trains[a][b].AStat = b;
		trains[a][b].travel = trains[a][b].Atime - trains[a][b].Dtime;
		cout << trains[a][b].travel << endl;
	}
	
}

void firstmes ( int ds, int as )
{
	int i = 0;
	
	cout << "***" << A[ds][as] << endl;
	
	hourmin[x] = A[ds][as];
	
	int gettime = A[ds][as];
		
	cout << endl;
	cout << "*****************************" << endl;
	cout << endl;
	
	cout << "To go from " << stations[start] << " to " << stations[stop] << ", you will need to ride on a train for " << endl;
		printHM( gettime ); 
		cout << H << " hours and " << M << " minutes" << endl;
		cout << endl;
		cout << endl;
}

void shorttime( int ds, int as )
{	
	int i = 0;
	
	hourmin[x] = trains[start][stop].travel;
	int gettime = hourmin[x];
	
		
	a[x] = trains[ds][as].Dtime;
	b[x] = trains[ds][as].Atime;
		
	arrl = a[x];
	dep = b[x];
	
		cout << endl;
		cout << "Leave " << stations[ds] << " at ";
		printtime( arrl );
		cout << pH << ":";
		if( pM < 10)
			cout << "0" << pM;
		else
			cout << pM;
		if( ampm == 1)
	 	cout << "AM" << endl;
		else
	 	cout << "PM" << endl;
		cout << " and arrive at " << stations[as] << " at ";
		printtime( dep ); 
		cout << pH << ":" ;
		if( pM < 10)
			cout << "0" << pM;
		else
			cout << pM;
		if( ampm == 1)
	 	cout << "AM" << endl;
		else 
	 	cout << "PM" << endl;
		cout << endl;
	}
		
	


void shorttravel ( void )
{
	cout << endl;
	cout << "*****************************" << endl;
	cout << endl;
	
	cout << "To go from " <<  stations[start] << ", " << "starting at " << trains[start][stop].Dtime << ", to" << stations[stop] << " you will arrive in " << 
	stations[stop] << " at " << trains[start][stop].Atime << "." << endl;
	timetaken = stop-initial;
	cout << "Your total time to destination will be " << printHM(timetaken)  << endl;

	cout << "You will take the following trains:" << endl;
	cout << endl;
	
	cout << "Leave" << stations[start] << "at " << trains[start][stop].Dtime << " and arrive " << PK[0] << trains[start][stop].Atime << endl;

}

void myclear(void)
{
  int i;
  for (i=0;i<CLEAR_LINES;i++)
  {
    printf("\n");
  }
}

void myPause(void)
{
  int key;
  printf("\nEnter the 1 key to continue..");
  scanf("%i",&key);
  printf("\n");
}


int menu ( void )
{
	int key=-1; // menu value picked
  	while ((key < MIN_MENU) || (key > MAX_MENU))
    {
    myclear();
    printf("**********************************\n");
    printf("*          Train Station         *\n");
    printf("*------------Bre Adsit-----------*\n");
    printf("**********************************\n");
    printf(" 1. View the Stations Numbers \n");
    printf(" 2. Find the Shortest Travel Times on Trains \n");
    printf(" 3. Find the Shortest Travel Time Overall \n");
    printf(" 0. Exit \n\n\n");
	printf(" Enter a choice: ");
    scanf("%i",&key);
  	
    }
  return key;
}

int main ( void )
{
	int key = -1;
	int count = 0;


	readinStations ( );
	readinTrainInfo ( );	
	shortest ( A, trains, P );


	
  while (key != 0)
  {
  	int sevenkey = -1;
    // get menu pick
    key=menu();
	// process menu pick
    switch (key)	
    {
    case 0:
	  	//end the program
	  	break;
	  	
    case 1:
    	cout << "View the Stations Numbers" << endl;
		readinStations();   
		myPause();
    	break;	
    	
    case 2:
    	//Find the Shortest Travel Times on Trains
    	cout << "Where would you like to go?" <<endl;
    	printf(" Enter a starting point: ");
    	scanf("%i", &start);
    	printf(" Enter a ending point: ");
    	scanf("%i", &stop);
    	
    	
    	
    	
    	if ( start == stop )
    	{
    		cout << "These are the same place! Go review the train station information!" << endl;
    		myPause();
    		break;
    	}
		
		PKcount = 0;
    	for (int i =0; i< maxT; i++)
    	{
    	  PK[i] = -1;
		}
		
		path (start, stop);
			
    	if(A[start][stop] == infin)
		{				
    		cout << "There is no path between " << start << " and " << stop  << endl;
    		myPause();
    		break;
    	}
    		   		
    	if (PK[0] == -1)  // no midpoints
		{
			cout << endl;
			cout << A[start][stop] << endl;
			firstmes( start, stop );  
			cout << "You will take the following trains:" << endl;
			shorttime( start, stop );
		}
 		else
		  {	
		    PKcount = 1;
		    cout << A[start][stop] << endl;
			firstmes( start, stop); 
			cout << "You will take the following trains:" << endl;
			shorttime(start, PK[0] );
			
		    while( PK[PKcount] != -1)
    	    {
		      shorttime(PK[PKcount-1], PK[PKcount]);
    	      PKcount++;
			}  
    	    shorttime( PK[PKcount-1] ,stop); 		// BREAKS AFTER THIS
		  } 
		
		shorttime( count - 1, stop );
    	
    	myPause();
    	break;
    	
    case 3:
    	//Find the Shortest Travel Time Overall
    	cout << "this was the optional function :D " <<endl;
    	printf("Enter a Starting point:");
		scanf("%i", & start);
		printf("Enter a ending point:");
		scanf("%i", & stop);
		
		if (start == stop)
		{
			cout <<"review the train Station"<<endl;
			
    	myPause();
    	break;
		
	}
	}

}
