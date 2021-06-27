#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct CardData {
  int Vitality;
  int Strength;
  int Manning;
  int Competence;
  char* Name;
  char* Equipment;
  char* Special;
  char* Bio;
};


struct CardData* processCardData(char* textfile){
  
  struct CardData* card = (struct CardData*)malloc(sizeof(struct CardData));
  FILE* textptr = fopen(textfile, "r");
  if (textptr == NULL)
    exit(EXIT_FAILURE);

  ssize_t read;
  char *line = NULL;
  size_t len = 0;
  read = getline(&line, &len, textptr);
  card->Vitality = atoi(line);
  
  read = getline(&line, &len, textptr);
  card->Strength = atoi(line);
  
  read = getline(&line, &len, textptr);
  card->Manning = atoi(line);

  read = getline(&line, &len, textptr);
  card->Competence = atoi(line);
  
  read = getline(&line, &len, textptr);
  char* cp = (char*) malloc(read);
  strcpy(cp, line);
  card->Name = cp;

  read = getline(&line, &len, textptr);
  cp  = (char*) malloc(read);
  strcpy(cp, line);
  card->Equipment = cp;

  read = getline(&line, &len, textptr);
  cp  = (char*) malloc(read);
  strcpy(cp, line);
  card->Special = cp;

  read = getline(&line, &len, textptr);
  cp  = (char*) malloc(read);
  strcpy(cp, line);
  card->Bio = cp;
  
  return card;
}

void DrawCard(struct CardData* card){
  DrawText(TextFormat("%d", card->Vitality), 220, 62, 22.0, RED);
  DrawText(TextFormat("%d", card->Strength), 220, 132, 22.0, RED);
  DrawText(TextFormat("%d", card->Manning), 340, 62, 22.0, RED);
  DrawText(TextFormat("%d", card->Competence), 340, 132, 22.0, RED);

  DrawTextRec(GetFontDefault(), card->Name, (Rectangle){30, 425, 400, 60}, 22.0, 1.8, 1, WHITE);
  DrawTextRec(GetFontDefault(), TextFormat("Equipment - %s", card->Equipment), (Rectangle){30, 200, 400, 60}, 18.0, 1.8, 1, WHITE);
  DrawTextRec(GetFontDefault(), TextFormat("Specials - %s", card->Special), (Rectangle){30, 260, 400, 60}, 18.0, 1.8, 1, WHITE);
  DrawTextRec(GetFontDefault(), TextFormat("Bio - %s", card->Bio), (Rectangle){30, 320, 400, 60}, 18.0, 1.8, 1, WHITE);
  return;
}
int main(int argc, char* argv[]){

 
  const int screenWidth = 450;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "epic piratecard generator V0x01");

  struct CardData* card = processCardData(argv[2]);
  
  Image cardimg = LoadImage(argv[1]);
  ImageResize(&cardimg, 150, 150);
  Texture2D texture = LoadTextureFromImage(cardimg);     
  UnloadImage(cardimg);
    
  SetTargetFPS(60);
   
  while (!WindowShouldClose()){

    BeginDrawing();

    ClearBackground(DARKBLUE);
    DrawTextureEx(texture, (Vector2){20,20}, 0, 1,  WHITE);
    DrawCircle(200, 70, 12.0, BLACK);
    DrawCircle(320, 70, 12.0, BLACK);
    DrawCircle(200, 140, 12.0, BLACK);
    DrawCircle(320, 140, 12.0, BLACK);
    DrawText("Crew Card", 240, 20, 20, RED);
    DrawText("V", 195, 65, 14, RED);
    DrawText("S", 195, 135, 14, RED);
    DrawText("M", 315, 65, 14, RED);
    DrawText("C", 315, 135, 14, RED);
    DrawRectangle(0, 180, 450, 10, RED);
    DrawRectangle(0, 420, 450, 30, RED);
    DrawCard(card);
    EndDrawing();

  }
  TakeScreenshot(TextFormat("Card-%s", argv[1]));
  UnloadTexture(texture);      

  CloseWindow();               

  return 0;
}
