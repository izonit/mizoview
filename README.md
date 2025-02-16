# [mizoview](https://github.com/izonit/mizoview)
### A tiny, fast application to view images.

## Instructions:
**For now, the application is officially __Linux-only__. You CAN NOT compile it on Windows by default. I am not planning to provide binaries, neither.**

### Prerequisites:
- X11-based DE/WM for any Linux distro
- OpenGL
- Make

### Building.
Run `git clone https://github.com/izonit/mizoview && cd mizoview && make -k` in your terminal in your preferred directory.

### Using mizoview.
Run `./build/mizoview` in your terminal - it will open up the application. You will be asked to drag and drop the desired image at the interface. You can also run `./build/mizoview [FILE_PATH]` (without the square brackets), where FILE_PATH is the path (preferrably, absolute) to the image you want to view. To make it usable globally, run `sudo cp build/mizoview /usr/bin/`, then try running the application wherever you prefer.

### TODO
- Add support of multiple images to be dragged & dropped into the UI (can be selected using a sidebar)
- Implement a fullscreen option (removing all the UI clutter, leaving just the image)
- Add Windows support (Unlikely)

  ### Screenshots
  ![No image](https://github.com/izonit/mizoview/blob/main/mizoview_screenshots/mizoview_noimage.png)
  ![Image selected](https://github.com/izonit/mizoview/blob/main/mizoview_screenshots/mizoview_image.png)
