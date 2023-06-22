#include <string>
#include <vector>
using namespace std;
#include "dictionary.h"
#include "gamestate.h"
#include "server_utils/crow_all.h"

#ifndef TUFFLE_H
#define TUFFLE_H

class TuffleGame {
 public:
  TuffleGame(Dictionary dict)
      : dictionary_(dict), game_state_(dict.GetRandomTuffle()) {}
  // Called by the Tuffle frontend when the user clicks "Next Tuffle".


  void NewGame(){
    GameState new_game(dictionary_.GetRandomTuffle());
    game_state_ = new_game;
  }



void LetterKeyPressed(char key){
 
  game_state_.ClearErrorMessage();
  
    std::vector<std::string>& wordsGuessed = game_state_.GuessedWords();
  if(wordsGuessed.size() == 0){
    wordsGuessed.push_back("");
  }
     int current_guess_index = wordsGuessed.size()-1;
  std::string current_guess = wordsGuessed.at(current_guess_index);
     if(current_guess.length()!=5)
  wordsGuessed[current_guess_index] = current_guess+key;

  }



  
  void EnterKeyPressed(){
    std::vector<std::string>& wordsGuessed = game_state_.GuessedWords();
    
   // this is the extra 

     game_state_.Lose(); //checks and changes the game state. 
    
    
    

   
    int current_guess_index = wordsGuessed.size()-1;
    //std::string current_guess = guessedWords.at(current_guess_index);
    if(wordsGuessed.size()==0 || wordsGuessed.at(current_guess_index).length()!=5)
    {
      game_state_.SetErrorMessage("Not Enough Letters!");
      return;
    }
    else if(!dictionary_.IsValidGuess(wordsGuessed.at(current_guess_index)))
    {
      game_state_.SetErrorMessage("Not a Valid Guess!");
      return;
    }
    else
    {
      //this store the current word at which we have to check and the answer to the wordle
      string color = BoardColors(wordsGuessed.at(current_guess_index), game_state_.Answer());
      //this sets the color to the board 
      game_state_.SetBoardColors(color);
      string ank = game_state_.Answer();
      game_state_.SetLetterColors(KeyBoardColors(wordsGuessed, ank));
      //if the color of the board is all green we won if not check when we lose but not here 
      if(color=="GGGGG")
        game_state_.SetGameStatus("win");
      wordsGuessed.push_back("");
      //extra credit
 //  string KeyBoardColorsVar=  KeyBoardColors(wordsGuessed,game_state_.Answer();
    }
    }


//if this is not equal to 5



std::string BoardColors(string guess, string answer) {
   
  std::string result = "BBBBB";
  //cancelling out the letters from answer result and guess. Not passed by reference so no change made outside of the scope of the variable. 
   for(int i = 0 ; i < answer.length() ; i++)
    {
      if (answer.at(i) == guess.at(i))
      {
        result[i] = 'G'; 
        guess[i] = '_';
        answer[i] = '$';
      }
    }

//make a loop to look from answerkey. if the correct answer is present somewhere then the result should be yellow and the answer should be changed to dollar to cancel it out. 
    for(int i = 0; i< answer.size(); i++)
      {
        if(answer.find(guess.at(i)) != std::string::npos)
        {
          int correctIndex = answer.find(guess.at(i));
          answer[correctIndex] = '$';
          result[i] = 'Y';
          guess[i] = '_';
        }
      }
  
  return result; 
}

string KeyBoardColors(vector<string>& all_guesses, string& answer)
{
  std::map<char,char> letter_states;
  for(const std::string& guess : all_guesses){
      for(int p = 0; p < guess.size(); p++){
          char guesses_char = guess.at(p);
          if(letter_states[guesses_char] == 'G')
            continue;//break the loop iteration and continue
      if(answer.find(guesses_char) != std::string::npos){ 
        for(int i = 0 ; i < answer.length(); i++) {//break the loop iteration 
            if(i==p && answer.at(i) == guesses_char) {
              letter_states[guesses_char] = 'G';
              break;}
            letter_states[guesses_char] = 'Y';
          }   }
      else{letter_states[guesses_char] = 'D';}
    }
    }
  std::string letters = "abcdefghijklmnopqrstuvwxyz";
  std::string letter_states_string = "";
  for(char c: letters){
    if(letter_states.count(c))
      letter_states_string+=letter_states[c];
    else
      letter_states_string += 'B';
  }
  return letter_states_string;
}

















void DeleteKeyPressed(){
std::vector<std::string>& wordsGuessed = game_state_.GuessedWords();

if(wordsGuessed.size()==0 || game_state_.IsInactive())
    return;
  game_state_.ClearErrorMessage();

  
  int current_guess_index = wordsGuessed.size()-1;
  std::string current_guess = wordsGuessed.at(current_guess_index);

  if(current_guess.size() != 0)
  {
    wordsGuessed.at(current_guess_index) = current_guess.substr(0,current_guess.length()-1);
  }
    
  }













  crow::json::wvalue GameStateInJson();
 private:
  GameState game_state_;
  Dictionary dictionary_;
};

#endif  // TUFFLE_H