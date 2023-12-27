#ifndef REWARD_H
#define REWARD_H
#include <iostream>
#include <ostream>
#include "GameState.h"
#include "Graph.h"
#include "Vertex.h"
#include "limits.h"

int getReward(Vertex<GameState>* start, int player){
    if (start->neighbors.size() == 0){
        int currPlayer = start->data.currentTurn;
        if (start->data.hasWon(player)){
            return 100;
        }
        else if (start->data.hasWon(!player)){
            return -100;
        }
        else{
            return 50;
        }
    }
    else{
        int reward = getReward(start->neighbors[0]->location, player);
        for (int i = 1; i < start->neighbors.size(); i++){
            int curr = getReward(start->neighbors[i]->location, player);
            if (start->data.currentTurn == player){
                if (curr > reward){
                    reward = curr;
                }
            }
            else{
                if (curr < reward){
                    reward = curr;
                }
            }
        }
        return reward;
    }
}

int getCellWeight(int i, int j) {
    // Assign higher weights to the center and corners of the board
    if ((i == 1 || i == 2) && (j == 1 || j == 2)) {
        return 10;
    }
    else if ((i == 0 || i == 3) && (j == 0 || j == 3)) {
        return 5; // Decrease the weight of the corners
    }
    // Assign higher weights to the cells on the diagonals
    else if (i == j || i + j == 3) {
        return 7;
    }
    else {
        return 1;
    }
}
bool impossible_win(GameState game, int player){
    for (int i = 0; i < 4; i++){
        int x = 0;      //player 0 is x
        int o = 0;      //player 1 is o
        for (int j = 0; j < 4; j++){
            if (game.grid[i][j] == 0){
                x++;
            }
            else if (game.grid[i][j] == 1){
                o++;
            }
        }
        if (x > 0 && o >0){
            return true;
        }
    }
    for (int i = 0; i < 4; i++){
        int x = 0;      //player 0 is x
        int o = 0;      //player 1 is o
        for (int j = 0; j < 4; j++){
            if (game.grid[i][j] == 0){
                x++;
            }
            else if (game.grid[i][j] == 1){
                o++;
            }
        }
        if (x > 0 && o >0){
            return true;
        }
        
    }
    int mainDiagCount = 0;
    
    for (int i = 0; i < 4; i++){
        int x = 0;     
        int o = 0; 
        if (game.grid[i][i] == 0){
            x++;
        }
        else if (game.grid[i][i] == 1){
            o++;
        }
        if (x > 0 && o >0){
            return true;
        }
    }
    

    int secondaryDiagCount = 0;
    for (int i = 0; i < 4; i++){
        int x = 0;     
        int o = 0; 
        if (game.grid[i][4-1-i] == 0){
            x++;
        }
        else if (game.grid[i][4-1-i] == 1){
            o++;
        }
        if (x > 0 && o >0){
            return true;
        }
    }
    
    

    return false;
}
bool isTwoInARow(GameState game, int player) {
    int count;

    // Check rows and columns
    for (int i = 0; i < 4; i++) {
        count = 0;
        for (int j = 0; j < 4; j++) {
            if (game.grid[i][j] == player) {
                count++;
            }
        }
        if (count == 2) {
            return true;
        }

        count = 0;
        for (int j = 0; j < 4; j++) {
            if (game.grid[j][i] == player) {
                count++;
            }
        }
        if (count == 2) {
            return true;
        }
    }

    // Check diagonals
    count = 0;
    for (int i = 0; i < 4; i++) {
        if (game.grid[i][i] == player) {
            count++;
        }
    }
    if (count == 2) {
        return true;
    }

    count = 0;
    for (int i = 0; i < 4; i++) {
        if (game.grid[i][3-i] == player) {
            count++;
        }
    }
    if (count == 2) {
        return true;
    }

    return false;
}

bool isThreeInARow(GameState game, int player) {
    
    for (int i = 0; i < 4; i++) {   //rows
        int count = 0;
        for (int j = 0; j < 4; j++) {
            if (game.grid[i][j] == player) {
                count++;
            }
        }
        if (count >= 3) {
            return true;
        }
    }

    for (int j = 0; j < 4; j++) {   //cols
        int count = 0;
        for (int i = 0; i < 4; i++) {
            if (game.grid[i][j] == player) {
                count++;
            }
        }
        if (count >= 3) {
            return true;
        }
    }

    int count1 = 0, count2 = 0;
    for (int i = 0; i < 4; i++) {       //diags
        if (game.grid[i][i] == player) {
            count1++;
        }
        if (game.grid[i][3-i] == player) {
            count2++;
        }
    }
    if (count1 >= 3 || count2 >= 3) {
        return true;
    }

    return false;
}

int evaluateGameState(Vertex<GameState>* start, int player) {
    GameState game = start->data;
    int score = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (game.grid[i][j] == player) {    //ai
                score += getCellWeight(i, j);
            }
            else if (game.grid[i][j] != 0) {
                score -= getCellWeight(i, j);
            }
        }
    }
    if (game.hasWon(player)) {
        score += 1000;
    }
    else if (game.hasWon(!player)) {
        score -= 1000;
    }
    
    
    GameState temp;
    if (isTwoInARow(game, !player)) {       //check 2 in a row
        temp = game;
        Vec last = game.lastMove;
        temp.grid[last.x][last.y] = !player;
        if (isThreeInARow(temp, !player)) {     //check 3 in a row
            score += 800;
        }
        // if (impossible_win(temp, !player)){
        //     score += 1500;
        // }
        
    }
    if (isThreeInARow(game, !player)) {     //check 3 in a row
        temp = game;
        Vec last = game.lastMove;
        //std::cout << last << std::endl;
        //player = !player;
        //temp.play(last.x, last.y);
        temp.grid[last.x][last.y] = !player;  // Simulate the move for player X
        //std::cout << temp << std::endl;
        if (temp.hasWon(!player)) {  // Check if this move results in a win for player X
            score += 5000;
        }
}
    
    // if (isThreeInARow(game, player)) {
    //     score += 800;
    // }

    return score;
}

// //backup eval function
// int evaluateGameState(Vertex<GameState>* start, int player){
//     int total;
//     int opp;
//     if(player ==0){
//         opp=1;
//     }
//     else{
//         opp=0;
//     }
//     for(int i = 0; i<start->data.size; i++){
//         int counter = 0;
//         int oppCounter = 0;
//         for(int j = 0; j<start->data.size; j++){
//             if(start->data.grid[i][j]==player){
//                 counter++;
//             }
//             else if(start->data.grid[i][j]==opp){
//                 oppCounter++;
//             }
//         }
//         if(counter == 2 && oppCounter == 0){
//             total += 50;
//         }
//         else if(counter ==1 && oppCounter ==0){
//             total+=1;
//         }
//         else if(counter == 4 && oppCounter ==0){
//             return 10000;
//         }
//         else if(counter == 0 && oppCounter == 3){
//             return 10001;
//         }
//     }
//     for(int i = 0; i<start->data.size; i++){
//         int counter = 0;
//         int oppCounter = 0;
//         for(int j = 0; j<start->data.size; j++){
//             if(start->data.grid[j][i]==player){
//                 counter++;
//             }
//             else if(start->data.grid[j][i]==opp){
//                 oppCounter++;
//             }
//         }
//         if(counter == 2 && oppCounter == 0){
//             total += 50;
//         }
//         else if(counter ==1 && oppCounter ==0){
//             total+=1;
//         }
//         else if(counter == 4 && oppCounter ==0){
//             return 10000;
//         }
//         else if(counter == 0 && oppCounter == 3){
//             return 10001;
//         }
//     }
//         int diagCounter = 0;
//         int diagOppCounter = 0;
//         for(int i = 0; i<start->data.size; i++){
//             if(start->data.grid[i][i]==player){
//                 diagCounter++;
//             }
//             else if(start->data.grid[i][i]==opp){
//                 diagOppCounter++;
//             }
//         }
//         if(diagCounter == 2 && diagOppCounter == 0){
//             total += 50;
//         }
//         else if(diagCounter ==1 && diagOppCounter ==0){
//             total+=1;
//         }
//         else if(diagCounter == 4 && diagOppCounter == 0){
//             return 10000;
//         }
//         else if(diagCounter == 0 && diagOppCounter == 3){
//             return 10001;
//         }
//         diagCounter = 0;
//         diagOppCounter = 0;
//         for(int i = 0; i<start->data.size; i++){
//             if(start->data.grid[i][start->data.size-1-i]==player){
//                 diagCounter++;
//             }
//             else if(start->data.grid[i][start->data.size-1-i]==opp){
//                 diagOppCounter++;
//             }
//         }
//         if(diagCounter == 2 && diagOppCounter == 0){
//             total += 50;
//         }
//         else if(diagCounter ==1 && diagOppCounter ==0){
//             total+=1;
//         }
//         else if(diagCounter == 4 && diagOppCounter == 0){
//             return 10000;
//         }
//         else if(diagCounter == 0 && diagOppCounter == 3){
//             return 10001;
//         }

//     return total;
// }

// int getReward(Vertex<GameState>* start, int player){
//     if (start->neighbors.size() == 0){
//         int currPlayer = start->data.currentTurn;
//         if (start->data.hasWon(player)){
//             return 100;
//         }
//         else if (start->data.hasWon(!player)){
//             return -100;
//         }
//         else{
//             return 0;
//         }
//     }
//     else{
//         int reward = getReward(start->neighbors[0]->location, player);
//         for (int i = 1; i < start->neighbors.size(); i++){
//             int curr = getReward(start->neighbors[i]->location, player);
//             if (start->data.currentTurn == player){
//                 if (curr > reward){
//                     reward = curr;
//                 }
//             }
//             else{
//                 if (curr < reward){
//                     reward = curr;
//                 }
//             }
//         }
//         return reward;
//     }
// }
// bool isWinningConditionBlocked(GameState game) {
//     // Check rows and columns
//     for (int i = 0; i < 4; i++) {
//         bool rowContains1 = false, rowContains0 = false;
//         bool colContains1 = false, colContains0 = false;
//         for (int j = 0; j < 4; j++) {
//             if (game.grid[i][j] == 1) rowContains1 = true;
//             if (game.grid[i][j] == 0) rowContains0 = true;
//             if (game.grid[j][i] == 1) colContains1 = true;
//             if (game.grid[j][i] == 0) colContains0 = true;
//         }
//         if ((rowContains1 && rowContains0) || (colContains1 && colContains0)) {
//             return true;
//         }
//     }

//     // Check diagonals
//     bool diag1Contains1 = false, diag1Contains0 = false;
//     bool diag2Contains1 = false, diag2Contains0 = false;
//     for (int i = 0; i < 4; i++) {
//         if (game.grid[i][i] == 1) diag1Contains1 = true;
//         if (game.grid[i][i] == 0) diag1Contains0 = true;
//         if (game.grid[i][3-i] == 1) diag2Contains1 = true;
//         if (game.grid[i][3-i] == 0) diag2Contains0 = true;
//     }
//     if ((diag1Contains1 && diag1Contains0) || (diag2Contains1 && diag2Contains0)) {
//         return true;
//     }

//     // If no condition is met, return false
//     return false;
// }
// // Function to get the weight of a cell



#endif