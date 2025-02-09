#include "raylib.h"
#include <stdio.h>  // snprintf(), printf()
#include <string.h> // strcmp()

#define KEY_FULLSCREEN KEY_F

typedef struct {
    int width;
    int height;
    int TargetFPS;
    bool fullscreen;
    char title[256];
} Window;

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp("-h", argv[1]) == 0)
    {
      printf(
        "mizoview - Simple Image Viewer\n"
        "\n"
        "Usage: mizoview [image_path]\n"
        "\n"
        "Options:\n"
        "  -h  Display this help message\n"
        "\n"
        "Controls:\n"
        "  Drag and drop an image file into the window to view it.\n"
      );
      return 0;
    }

    Texture2D texture = { 0 };
    char fileInfo[256] = "NO FILE";

    Window window = { GetMonitorWidth(-1), GetMonitorHeight(-1), 60, false, "mizoview - image viewer" };
    InitWindow(window.width, window.height, window.title);
    SetTargetFPS(window.TargetFPS);

    // TODO: Add support for multiple files
    // *including a sidebar!

    Rectangle fullscreen_button = { 50, 50, 50, 50 };
    Rectangle fullscreen_button_bounds = { window.width / 2 - fullscreen_button.width / 2, window.height / 2 - fullscreen_button.height / 2, fullscreen_button.width, fullscreen_button.height };
    Vector2 mouse_point = { 0, 0 };

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
                  if (image.data != NULL)
                  {
                      ImageResize(&image, GetScreenWidth(), GetScreenHeight());
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
          if (image.data != NULL)
          {
              ImageResize(&image, GetScreenWidth(), GetScreenHeight());
              if (texture.id != 0) UnloadTexture(texture);
              texture = LoadTextureFromImage(image);
              snprintf(fileInfo, sizeof(fileInfo), "File: %s (Original size: %dx%d)", argv[1], origImageWidth, origImageHeight);
              UnloadImage(image);
          }
      }

      BeginDrawing();
      ClearBackground(BLACK);

      mouse_point = GetMousePosition();

      if (CheckCollisionPointRec(mouse_point, fullscreen_button_bounds))
      {
          if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) window.fullscreen = !window.fullscreen;
          else window.fullscreen = false;
      }

      if (IsKeyPressed(KEY_FULLSCREEN))
      {
          window.fullscreen = !window.fullscreen;
      }

      if (!window.fullscreen)
      {
          DrawText(fileInfo, 10, 0, 20, RAYWHITE);
          if (texture.id != 0)
          {
              DrawTexture(texture, 0, 20, WHITE);
          } else if (argc <= 1)
          {
              DrawText("Drop an image here!\nControls:\n  Press F to enter fullscreen mode.\nAdditional -flags for command line:\n  -h: Display help for this application", 50, 50, 20, RAYWHITE);
          }
      } else
      {
          if (texture.id != 0)
          {
              DrawTexture(texture, 0, 0, WHITE);
          } else if (argc <= 1)
          {
              DrawText("Drop an image here!\nControls:\n  Press F to exit fullscreen.\nAdditional -flags for command line:\n  -h: Display help for this application", 50, 50, 20, RAYWHITE);
          }
      }
      EndDrawing();
    }

    if (texture.id != 0) UnloadTexture(texture);
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
