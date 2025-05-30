#include <iostream>
#include <climits>
using namespace std;

class tree
{
	int a[20][20],l,u,w,i,j,v,e,visited[20];
public:
	void input();
	void display();
	void minimum();
};

void tree::input()
{
	cout<<"Enter the no. of branches: ";
	cin>>v;

	for(i=0;i<v;i++)
	{
		visited[i]=0;
		for(j=0;j<v;j++)
		{
			a[i][j]=INT_MAX;
		}
	}

	cout<<"\nEnter the no. of connections: ";
	cin>>e;

	for(i=0;i<e;i++)
	{
		cout<<"Enter the end branches of connections:  "<<endl;
		cin>>l>>u;
		cout<<"Enter the phone company charges for this connection:  ";
		cin>>w;
		a[l-1][u-1]=a[u-1][l-1]=w;
	}
}

void tree::display()
{
	cout<<"\nAdjacency matrix:";
	for(i=0;i<v;i++)
	{
		cout<<endl;
		for(j=0;j<v;j++)
		{
			cout<<a[i][j]<<"   ";
		}
		cout<<endl;
	}
}
void tree::minimum() {
    int p = 0, q = 0, total = 0, min;
    int i, j;

    visited[0] = 1; // Assuming node 1 is the starting point (0-indexed)

    for (int count = 0; count < v - 1; count++) {
        min = INT_MAX;

        for (i = 0; i < v; i++) {
            if (visited[i] == 1) {
                for (j = 0; j < v; j++) {
                    if (visited[j] != 1 && a[i][j] != 0 && a[i][j] < min) {
                        min = a[i][j];
                        p = i;
                        q = j;
                    }
                }
            }
        }

        if (min == INT_MAX) {
            cout << "Graph is disconnected. MST not possible.\n";
            return;
        }

        visited[q] = 1;
        total += min;
        cout << "Minimum cost connection is " << (p + 1) << " -> " << (q + 1) << " with charge: " << min << endl;
    }
    cout << "The minimum total cost of connections of all branches is: " << total << endl;
}

int main()
{
	int ch;
	tree t;
	do
	{
		cout<<"==========PRIM'S ALGORITHM================="<<endl;
		cout<<"\n1.INPUT\n \n2.DISPLAY\n \n3.MINIMUM\n"<<endl;
		cout<<"Enter your choice :"<<endl;
		cin>>ch;
	
	switch(ch)
	{	
	case 1: cout<<"*******INPUT YOUR VALUES*******"<<endl;	
		t.input();
		break;

	case 2: cout<<"*******DISPLAY THE CONTENTS********"<<endl;
		t.display();
		break;

	case 3: cout<<"*********MINIMUM************"<<endl;
		t.minimum();
		break;
	}
	
	}while(ch!=4);
	return 0;
}


// ==========PRIM'S ALGORITHM=================

// 1.INPUT
 
// 2.DISPLAY
 
// 3.MINIMUM

// Enter your choice :
// 1
// *******INPUT YOUR VALUES*******
// Enter the no. of branches: 4

// Enter the no. of connections: 5
// Enter the end branches of connections:  
// 1 2
// Enter the phone company charges for this connection: 5

// Enter the end branches of connections:  
// 1 3
// Enter the phone company charges for this connection: 10

// Enter the end branches of connections:  
// 2 3
// Enter the phone company charges for this connection: 3

// Enter the end branches of connections:  
// 2 4
// Enter the phone company charges for this connection: 2

// Enter the end branches of connections:  
// 3 4
// Enter the phone company charges for this connection: 6

// ==========PRIM'S ALGORITHM=================

// 1.INPUT
 
// 2.DISPLAY
 
// 3.MINIMUM

// Enter your choice :
// 2
// *******DISPLAY THE CONTENTS********

// Adjacency matrix:
// 0   5   10  2147483647   
// 5   0   3   2   
// 10  3   0   6   
// 2147483647  2   6   0

// ==========PRIM'S ALGORITHM=================

// 1.INPUT
 
// 2.DISPLAY
 
// 3.MINIMUM

// Enter your choice :
// 3
// *********MINIMUM************
// Minimum cost connection is 1 -> 2 with charge: 5
// Minimum cost connection is 2 -> 3 with charge: 3
// Minimum cost connection is 2 -> 4 with charge: 2
// The minimum total cost of connections of all branches is: 10

// ==========PRIM'S ALGORITHM=================

// 1.INPUT
 
// 2.DISPLAY
 
// 3.MINIMUM

// Enter your choice :
// 4