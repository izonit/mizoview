#include "raylib.h"
#include <stdio.h>

typedef struct {
    int width;
    int height;
    int TargetFPS;
    char title[256];
} Window;

int main(int argc, char *argv[])
{
    Texture2D texture = { 0 };
    char fileInfo[256] = "NO FILE";

    Window window = { 1152, 648, 60, "mizoview - image viewer" };
    InitWindow(window.width, window.height, window.title);
    SetTargetFPS(window.TargetFPS);

    while (!WindowShouldClose())
    {
      if (argc < 2)
      {
          if (IsFileDropped())
          {
                FilePathList droppedFiles = LoadDroppedFiles();
                if (droppedFiles.count > 0)
                {
                  Image image = LoadImage(droppedFiles.paths[0]);
                  int origImageWidth  = image.width;
                  int origImageHeight = image.height;
                  ImageResize(&image, window.width, window.height);
                  if (image.data != NULL)
                  {
                      if (texture.id != 0) UnloadTexture(texture);
                      texture = LoadTextureFromImage(image);
                      snprintf(fileInfo, sizeof(fileInfo), "File: %s (Original size: %dx%d)", droppedFiles.paths[0], origImageWidth, origImageHeight);
                      UnloadImage(image);
                  }
              }

              UnloadDroppedFiles(droppedFiles);
          }
      } else {
          Image image = LoadImage(argv[1]);
          int origImageWidth  = image.width;
          int origImageHeight = image.height;
          ImageResize(&image, window.width, window.height);
          if (image.data != NULL)
          {
              if (texture.id != 0) UnloadTexture(texture);
              texture = LoadTextureFromImage(image);
              snprintf(fileInfo, sizeof(fileInfo), "File: %s (Original size: %dx%d)", argv[0], origImageWidth, origImageHeight);
              UnloadImage(image);
          }
      }

				BeginDrawing();

						ClearBackground(BLACK);
						DrawText(fileInfo, 10, 1, 20, RAYWHITE);
						if (texture.id != 0)
            {
								DrawTexture(texture, (window.width - texture.width) / 2, (window.height - texture.height) / 2 + 21, WHITE);
						} else if (argc < 2)
            {
								DrawText("Drop an image here!\nAdditional -flags for command line (Linux only):\n  -h: Display help for this application", window.width - 648, window.height /2, 20, RAYWHITE);
            } else
            {
                DrawTexture(texture, (window.width - texture.width) / 2, (window.height - texture.height) / 2 + 21, WHITE);
            }
        EndDrawing();
    }

    if (texture.id != 0) UnloadTexture(texture);
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
