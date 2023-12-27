#ifndef AI_H
#define AI_H

#include <iostream>
#include <ostream>
#include "GameState.h"
#include "Reward.h"
#include "Graph.h"
#include "Vertex.h"
#include "limits.h"

Vec findBestMove_3x3(GameState game){

    Graph<GameState> stateSpace;
    Vertex<GameState>* start = new Vertex<GameState>(game);

    stateSpace.addVertex(start);

    Queue<Vertex<GameState>*> frontier;
    frontier.enqueue(start);

    ArrayList<Vertex<GameState>*> m;
    ArrayList<int> s;
    Vec BestMove;
    int bestReward = -INT_MAX;
    while (!frontier.isEmpty()){
        Vertex<GameState>* curr = frontier.dequeue();
        if (!curr->data.done){
            for(int i = 0; i < game.size; i++){
                for (int j = 0; j < game.size; j++){
                    if(curr->data.grid[i][j] == -1){
                        GameState next = curr->data;
                        next.play(i, j);
                        Vertex<GameState>* successor = new Vertex<GameState>(next);
                        stateSpace.addVertex(successor);
                        stateSpace.addDirectedEdge(curr, successor);
                        
                        if (!successor->data.done){
                            frontier.enqueue(successor);
                        }
                        
                        
                    }
                }
            }
        }
    }
    //return BestMove;
    for (int i = 0; i < stateSpace.vertices.size(); i++){
        if (game.turnCount + 1 == stateSpace.vertices[i]->data.turnCount){
            //std::cout<< stateSpace.vertices[i]->data << " " << getReward(stateSpace.vertices[i], 1) << std::endl;
            m.append(stateSpace.vertices[i]);
            s.append(getReward(stateSpace.vertices[i], 1));
        }
    }
    //std::cout<< m << std::endl;
    int bestScore = -INT_MAX;
    int score;
    int index;
    score = bestScore;
    //std::cout<< m << std::endl;
    for (int i = 0; i < s.size(); i++){
        //std::cout<< s[i] << std::endl;
        if (s[i] > score){
            score = s[i];
            index = i;
        }
    }
    
    return m[index]->data.lastMove;

}

Vec findBestMove_4x4(GameState game){

    Graph<GameState> stateSpace;
    Vertex<GameState>* start = new Vertex<GameState>(game);

    stateSpace.addVertex(start);

    Queue<Vertex<GameState>*> frontier;
    frontier.enqueue(start);

    ArrayList<Vertex<GameState>*> m;
    ArrayList<int> s;
    int depth = 0;
    while (depth < 6 && !frontier.isEmpty()){
        depth++;
        //std::cout<< depth << std::endl;
        Vertex<GameState>* curr = frontier.dequeue();
        if (!curr->data.done){
            for(int i = 0; i < game.size; i++){
                for (int j = 0; j < game.size; j++){
                    if(curr->data.grid[i][j] == -1){
                        GameState next = curr->data;
                        next.play(i, j);
                        Vertex<GameState>* successor = new Vertex<GameState>(next);
                        stateSpace.addVertex(successor);
                        stateSpace.addDirectedEdge(curr, successor);
                        
                        if (!successor->data.done){
                            frontier.enqueue(successor);
                        }
                    }
                }
            }
        }
    }
    //return BestMove;
    for (int i = 0; i < stateSpace.vertices.size(); i++){
        if (game.turnCount + 1 == stateSpace.vertices[i]->data.turnCount){
            //std::cout<< stateSpace.vertices[i]->data << " " << evaluateGameState(stateSpace.vertices[i], 1) << std::endl;
            m.append(stateSpace.vertices[i]);
            s.append(evaluateGameState(stateSpace.vertices[i], 1));
        }
    }
    //std::cout<< m << std::endl;
    int bestScore = -INT_MAX;
    int score;
    int index;
    score = bestScore;
    //std::cout<< m << std::endl;
    for (int i = 0; i < s.size(); i++){
        //std::cout<< s[i] << std::endl;
        if (s[i] > score){
            score = s[i];
            index = i;
        }
    }
    //std::cout<< s << std::endl;
    return m[index]->data.lastMove;

}

Vec validMove(GameState game){
    for (int i = 0; i < game.size; i++){
        for (int j = 0; j < game.size; j++){
            if (game.grid[i][j] == -1){
                return Vec(i, j);
            }
        }
    }
    return Vec(-1,-1);
}

void easyai_3x3(GameState& game){
    Vec tmp = validMove(game);
    if(tmp.x==-1&&tmp.y==-1){
        return;
    }
    else{
        game.play(tmp.x, tmp.y);
    }
    
}

void ai_3x3(GameState& game){
    Vec tmp = findBestMove_3x3(game);
    game.play(tmp.x, tmp.y);
    //std::cout<< game << std::endl;
}

void ai_4x4(GameState& game){
    Vec tmp = findBestMove_4x4(game);
    game.play(tmp.x, tmp.y);
    //std::cout<< game << std::endl;
}

void easy3x3compact(){
    GameState game;
    int x, y;
    system("clear");
    std::cout<<game<<std::endl;
    while(!game.done){
        if (game.currentTurn == 0){
            std::cout<< "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
            std::cin >> x >> y;
            if(std::cin.fail()){
                system("clear");
                std::cout<<game<<std::endl;
                std::cout<<"Invalid input type, please input two numbers"<<std::endl;
                std::cin.clear();
                std::cin.ignore(256,'\n');
                continue;
            }
            if (!(x >= 0 && x < game.size) || !(y >= 0 || y < game.size)||game.grid[x][y] != -1){
                system("clear");
                std::cout<<game<<std::endl;
                std::cout<<"Invalid move, try again"<<std::endl;
                continue;
            }
            system("clear");
            game.play(x,y);
        }
        else{
            easyai_3x3(game);
            system("clear");
        }
        std::cout<< game << std::endl;
    }
    if (game.hasWon(0)){
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "Human wins" << std::endl;
        std::cout<< std::endl;
    }
    else if (game.hasWon(1)){
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "AI wins" << std::endl;      //ai is maximizing 
        std::cout<< std::endl;
    }
    else{
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "It's a tie" << std::endl;
        std::cout<< std::endl;
    }
    
    std::string exit = " ";
    do{
        std::cout<<"Press [enter] to continue"<<std::endl;
        std::cout<<"\n";
        std::cin.ignore();
    } while (std::cin.get() != '\n');
               
}

void easy4x4compact(){
    GameState game(4);
    int x, y;
    system("clear");
    std::cout<<game<<std::endl;
    while(!game.done){
        if (game.currentTurn == 0){
            std::cout<< "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
            std::cin >> x >> y;
            if(std::cin.fail()){
                system("clear");
                std::cout<<game<<std::endl;
                std::cout<<"Invalid input type, please input two numbers"<<std::endl;
                std::cin.clear();
                std::cin.ignore(256,'\n');
                continue;
            }
            if (!(x >= 0 && x < game.size) || !(y >= 0 || y < game.size)||game.grid[x][y] != -1){
                system("clear");
                std::cout<<game<<std::endl;
                std::cout<<"Invalid move, try again"<<std::endl;
                continue;
            }
            system("clear");
            game.play(x,y);
        }
        else{
            easyai_3x3(game);
            system("clear");
        }
        std::cout<< game << std::endl;
    }
    if (game.hasWon(0)){
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "Human wins" << std::endl;
        std::cout<< std::endl;
    }
    else if (game.hasWon(1)){
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "AI wins" << std::endl;      //ai is maximizing 
        std::cout<< std::endl;
    }
    else{
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "It's a tie" << std::endl;
        std::cout<< std::endl;
    }
    
    std::string exit = " ";
    do{
        std::cout<<"Press [enter] to continue"<<std::endl;
        std::cout<<"\n";
        std::cin.ignore();
    } while (std::cin.get() != '\n');
}

void hard3x3compact(){
    GameState game;
    int x, y;
    system("clear");
    std::cout<<game<<std::endl;
    while(!game.done){
        if (game.currentTurn == 0){
            std::cout<< "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
            std::cin >> x >> y;
            if(std::cin.fail()){
                system("clear");
                std::cout<<game<<std::endl;
                std::cout<<"Invalid input type, please input two numbers"<<std::endl;
                std::cin.clear();
                std::cin.ignore(256,'\n');
                continue;
            }
            if (!(x >= 0 && x < game.size) || !(y >= 0 || y < game.size)||game.grid[x][y] != -1){
                system("clear");
                std::cout<<game<<std::endl;
                std::cout<<"Invalid move, try again"<<std::endl;
                continue;
            }
            system("clear");
            game.play(x,y);
        }
        else{
            ai_3x3(game);
            system("clear");
        }
        std::cout<< game << std::endl;
    }
    if (game.hasWon(0)){
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "Human wins" << std::endl;
        std::cout<< std::endl;
    }
    else if (game.hasWon(1)){
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "AI wins" << std::endl;      //ai is maximizing 
        std::cout<< std::endl;
    }
    else{
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "It's a tie" << std::endl;
        std::cout<< std::endl;
    }
    
    std::string exit = " ";
    do{
        std::cout<<"Press [enter] to continue"<<std::endl;
        std::cout<<"\n";
        std::cin.ignore();
    } while (std::cin.get() != '\n');
}

void hard4x4compact(){
    GameState game(4);
    int x, y;
    system("clear");
    std::cout<<game<<std::endl;
    while(!game.done){
        if (game.currentTurn == 0){
            std::cout<< "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
            std::cin >> x >> y;
            if(std::cin.fail()){
                system("clear");
                std::cout<<game<<std::endl;
                std::cout<<"Invalid input type, please input two numbers"<<std::endl;
                std::cin.clear();
                std::cin.ignore(256,'\n');
                continue;
            }
            if (!(x >= 0 && x < game.size) || !(y >= 0 || y < game.size)||game.grid[x][y] != -1){
                system("clear");
                std::cout<<game<<std::endl;
                std::cout<<"Invalid move, try again"<<std::endl;
                continue;
            }
            system("clear");
            game.play(x,y);
        }
        else{
            ai_4x4(game);
            system("clear");
        }
        std::cout<< game << std::endl;
    }
    if (game.hasWon(0)){
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "Human wins" << std::endl;
        std::cout<< std::endl;
    }
    else if (game.hasWon(1)){
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "AI wins" << std::endl;      //ai is maximizing 
        std::cout<< std::endl;
    }
    else{
        //std::cout<< std::endl;
        system("clear");
        std::cout<< game<< std::endl;
        std::cout<< "It's a tie" << std::endl;
        std::cout<< std::endl;
    }
    
    std::string exit = " ";
    do{
        std::cout<<"Press [enter] to continue"<<std::endl;
        std::cout<<"\n";
        std::cin.ignore();
    } while (std::cin.get() != '\n');
}

void human(int size){
    GameState game(size);
    while(!game.done){
    system("clear");
    std::cout << game << std::endl;

    int x, y;
    std::cout << std::endl;
    std::cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
    std::cin >> x >> y;

    game.play(x, y);
    }

    std::cout << game << std::endl;
    std::cout << std::endl;
    if (game.hasWon(0)){
        system("clear");
        std::cout<< game<< std::endl;
        std::cout << "Player X has won" << std::endl;
        std::cout<< std::endl;
        
    }
    else if (game.hasWon(1)){
        system("clear");
        std::cout<< game<< std::endl;
        std::cout << "Player O has won" << std::endl;
        std::cout<< std::endl;
    }
    else {
        system("clear");
        std::cout<< game<< std::endl;
        std::cout << "It's a tie" << std::endl;
        std::cout<< std::endl;
    }

    std::string exit = " ";
    do{
        std::cout<<"Press [enter] to continue"<<std::endl;
        std::cout<<"\n";
        std::cin.ignore();
    } while (std::cin.get() != '\n');
}
#endif