/*
  Brainfuck interactive shell interpreter
*/

// Includes
#include <windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

// Defines
#define TAPE_SIZE 32
#define DEBUG

// Debug stuff definition
#ifdef DEBUG
  #define DISP_COL 8
  bool dbg = false;
  #define DBG_SYM '#'
#endif

// Functions
#ifdef DEBUG
void Mem_Dump(int ptr, int* Memory) {
  printf("Memory:\n");
  for(int i = 0; i < 32; i++) {
    if(i%DISP_COL==0 && i) printf("|\n");
    if(i%DISP_COL==0 && ptr/DISP_COL==i/DISP_COL) printf("> ");
    else if( i%DISP_COL==0 ) printf("  ");

    printf("| %03d ", Memory[i]);
  }
  printf("|\n  ");
  for(int i=0; i < DISP_COL; i++)
    if(i==ptr%DISP_COL) printf("   ^  "); else printf("      ");
}
#endif
void ExecuteString(int &ptr, int *&Location, std::string input) {
  for (unsigned int i = 0; i < input.length(); i++) {
    switch (input[i]) {
    case '<': // move ptr left
      if (ptr == 0)
        ptr = TAPE_SIZE;
      ptr--;
      break;
    case '>': // move ptr right
      if (ptr == 31)
        ptr = 0;
      else
        ptr++;
      break;
    case '+': // increse value
      if (Location[ptr] >= 255)
        Location[ptr] = 0;
      else
        Location[ptr]++;
      break;
    case '-': // decrese value
      if (Location[ptr] <= 0)
        Location[ptr] = 255;
      else
        Location[ptr]--;
      break;
    case '.': // print value
      putchar(Location[ptr]);
      break;
    case ',':
      getchar();
      Location[ptr] = getchar();
      break;
    case '[':
      if (Location[ptr] != 0)
        break;
      else {
        int j = i;
        while (input[j] != ']')
          j++;
        i = j;
      }
      break;
    case ']': {

      int j = i;
      while (input[j] != '[')
        j--;
      i = j - 1;
    } break;
#ifdef DEBUG
    case DBG_SYM:
      dbg = true;
      break;
#endif
    }
  }
}

// Main loop
int main(int ac, char const *av[]) {

  // Initialize Tape and pointer
  int ptr = 0;
  int* Location = new int[TAPE_SIZE];
  for(int i=0; i < TAPE_SIZE; i++)
    Location[i] = 0;

  // Check for paramaters if they exist run it as file with bf code
  if(ac>1)
    try {
      std::ifstream file(av[1]);
      if( !file ) throw(1);
      std::string line;
      while(std::getline(file, line)) {
        std::cout << line << "\n";
        ExecuteString(ptr, Location, line);
      } std::cout << "\n\n";

    } catch(int error) {
      switch(error) {
        case 1: // Not existing file with that name
          std::cout << "File named " << av[1] << " doesnt exist!";
          break;
        default:
          std::cout << "Unknown error!";
      }
      return 1;
    }

  // Intro message
  std::cout << "BrainFuck Interactive Shell\n";
  std::cout << "Known commands: \"< > [ ] + - , .";
  #ifdef DEBUG
  std::cout << " " << DBG_SYM;
  #endif
  std::cout << "\"\n\n";


  std::string input;
  while(true) { // Main shell loop

    #ifdef DEBUG // Information
    if(dbg) {
      printf("\n");
      Mem_Dump(ptr, Location);
      printf("\n\n");
      dbg=false;
    }
    #endif

    // Get input
    printf("\n");
    printf("%d. %03d >>> ", ptr, Location[ptr]);
    std::cin >> input;

    // Parse input
    if(std::count(input.begin(), input.end(), '[')!=
       std::count(input.begin(), input.end(), ']')) {
         std::cout << "Unbalanced brackets!";
    } else ExecuteString(ptr, Location, input);
  }
  return 0;
}
