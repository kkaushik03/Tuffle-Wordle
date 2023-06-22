#pragma once
/*1. NewGame();   <---
2. LetterKeyPressed(char c); <---
3. EnterKeyPressed();
4. DeleteKeyPressed();
5. GameStateInJson();
*/
#include <string>
#include <vector>
using namespace std;
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "dictionary.h"
/*Things needed:
- Game move- current secret truffle. <--
- vector colors for row. - return the vector for letter.
- guessed words- return vector of moves. <--
- game status- retrun if the player is dead or alive. <--
- latest action performed is invalid. <--
  */
class GameState {
 public:
  //=================== YOUR CODE HERE ===================
  // TODO: Add the constructor(s), accessors, mutators,
  // and any other member function you may need here.
  //======================================================
//constructor is called and the secret code is store in the variable through the constructor
  GameState(const std::string& ans):secret_code_(ans), game_status_("active") //correct
  {}

std::string Answer(){return secret_code_;} //<--//correct


string GetLetterColors() {//correct
 return letter_color_;
  }


void SetLetterColors(string color) {//correct
  letter_color_= color;
  }

  vector<std::string> GetBoardColors() {return board_colors_;}//correct


void SetBoardColors(string color)
{
  board_colors_.push_back(color);
}
std::vector<std::string>& GuessedWords() {return present_moves_;} //<--//correct

void AddMove(std::string move) {present_moves_.push_back(move);}//correct


 /*
void RemoveMove(){
  if (present_moves_.size()>0)
  present_moves_.pop_back(); }


*/

void SetGuessWords(std::vector<std::string> present_moves){//correct
  present_moves_=present_moves;
}
void SetColor(string letter_color){
  letter_color_= letter_color;
}



// the last word in the vector is same as the secret code then the game is over and the player wins. 
void SetGameStatus(string game_status)
{
  game_status_=game_status;
}
string GameStatus()
{
  return game_status_;
}

void Lose()
{
  if(present_moves_.size()==6)
    game_status_="lose";
}

bool IsInactive()
{
  return !(game_status_== "active");
}
std::string GetErrorMessage()
{
  return error_message_;
}

void SetErrorMessage(string error_message)
{
  error_message_=error_message;
}

void ClearErrorMessage() {
  error_message_.clear();
}

 private:
  //=================== YOUR CODE HERE ===================
  // TODO: Add any member variables you need here to store
  // the state of the game. What information needs to be
  // stored to fully represent the game state at a single
  // point in time?
  //======================================================
std::string secret_code_; 
std::vector<std::string> present_moves_;
std::vector<std::string> first_moves_;
std::vector<std::string>  board_colors_;
string letter_color_;
string error_message_;
string game_status_;
string isInactive_;
};

#endif  // GAMESTATE_H