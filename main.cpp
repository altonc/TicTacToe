#include <iostream>
#include <ostream>
#include "GameState.h"
#include "Reward.h"
#include "Graph.h"
#include "Vertex.h"
#include "limits.h"
#include "AI.h"
using namespace std;

int sizeFunc(){
    system("clear");
        bool yes = false;
        int size = 0;
        while(!yes){
            cout<<"Enter grid size [3-4]: ";
            cin>>size;
            if(size==3 || size==4){
                yes = true;
            }
            else{
                system("clear");
                cout<<"Invalid number, please try again"<<endl;
            }
        }
        system("clear");
    return size;
}
int settingsScreen(string difficulty){
    int choice;
    int end;
    bool valid = true;  
    cout << "Select AI Difficulty Level: Currently "<<difficulty;
    cout<<"\n\t1. Easy"<<endl;
    cout<<"\t2. Hard\n"<<endl;
    cout << endl; cout << "Enter choice []: "; cin >> choice; 

    
    if(choice == 1){
        system("clear");
        cout << " " << endl; //space

        end = 0+10*sizeFunc(); 
        //hard
    }
    else if(choice == 2){
        system("clear");
        cout << " " << endl; //space
        end = 1+10*sizeFunc(); 
        //easy
    }
    else{
        system("clear");
        cout << "Not valid. Please select one of the available options" << endl;
        end = settingsScreen(difficulty);
    }
    
    return end;
    //return end;
}

void makeMenu(){
    int type;
    int choice; 
    string difficulty = "Easy";
    bool valid; 
    system("clear");
    while (!valid){

        cout << "Welcome to Tic-Tac-Toe: " << endl; cout << " " << endl; 

        cout << "1. Play against a computer" << endl;
        cout << "2. Play against a friend" << endl;
        cout << "3. Settings" << endl;
        cout << "4. Exit" << endl;
        cout << endl;
        cout << "Enter choice []: "; 
    
        cin >> choice; 
        //if anything but a number is input
        if (cin.fail()){
             system("clear"); 
             cout << "Your choice must be a number." << endl;
             cin.clear(); 
             cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        if (choice > 4 || choice < 1){
            system("clear");
            cout << "Not valid. Please select one of the available options: " << endl; 
            cout << " " << endl; 
        }
        //Gamestates
        else if (choice == 1){
            system("clear");
            //cout << type << endl;
            
            if (type == 30){    //easy 3x3
                easy3x3compact();
                makeMenu();
                
            }
            else if (type == 40){   //easy 4x4
                easy4x4compact();
                makeMenu();
                
            }
            else if (type == 31){   //hard 3x3
                
                hard3x3compact();
                makeMenu();
            }
            else if (type == 41){   //hard 4x4
                
                hard4x4compact();
                makeMenu();

            }
            else{
                easy3x3compact();
                makeMenu();
            }
            
            valid = true; 
        }
        else if (choice == 2){
            //system("clear");
            cout << "starting game..." << endl;
            int size = type/10;
            if(size == 0) size = 3;
            human(size);
            makeMenu();
        }
        //settings
        else if (choice == 3){
            system("clear");
            int choice = settingsScreen(difficulty); 
            type = choice;
            if(choice/10==3){
                //cout<<"3x3";
            }
            else{
                //cout<<"4x4";
            }
            if(choice%10==0){
                difficulty = "Easy";
                //cout<<"easy";
            }
            else{
                difficulty = "Hard";
                //cout<<"hard";
            }
            //cout << " " << endl; //space for readability

        }
        //exit
        else if (choice == 4){
            system("clear");
            cout << " " << endl; //space for readability
            cout << "Goodbye..." << endl;
            cout << endl;
            valid = true; 
            return; 
        }
    
    }
}


int main(){
    //GameState game;
    //int type = 30;
    int x, y;
    
    makeMenu();
    
    return 0;
}
