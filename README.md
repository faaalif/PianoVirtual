Virtual Piano with Color Detection

This project is a virtual piano built using **OpenCV** and **C++**. It detects colored objects via webcam and plays corresponding musical notes using `.wav` audio files. It’s designed to be a fun, interactive way to combine computer vision and sound.

How It Works

- The program uses your webcam to track specific colors (Red, Blue, Green, Yellow, Orange, Pink, and Purple).
- When a colored object enters a defined area (key zone), it plays a note (DO, RE, MI, FA, SOL, LA, SI).
- Each key is represented as a colored rectangle on the screen.
- The audio is played asynchronously using the Windows API.

Notes and Colors

| Color   | Note | Audio File |
|---------|------|------------|
| Red     | Do   | `do.wav`   |
| Blue    | Re   | `re.wav`   |
| Green   | Mi   | `mi.wav`   |
| Yellow  | Fa   | `fa.wav`   |
| Light blue  | Sol  | `sol.wav`  |
| Pink    | La   | `la.wav`   |
| Purple  | Si   | `si.wav`   |

Technologies Used

- **C++**
- **OpenCV**
- **Windows Multimedia API** (`PlaySound` from `winmm.lib`)

  How to Run

1. Clone the repository:

   git clone https://github.com/faaalif/PianoVirtual
   cd PianoVirtual


2. Make sure the following files are in the same folder:

main.cpp
do.wav
re.wav
mi.wav
fa.wav
sol.wav
la.wav
si.wav


3. Compile the program (example with g++ and OpenCV installed):

g++ main.cpp -o piano -lopencv_core -lopencv_highgui -lopencv_imgproc -lwinmm


4. Run the program:
./piano


Demo

When the program runs, it shows a virtual piano. Move a colored object into the keys to play notes!


Requirements

-Windows OS

-OpenCV installed

-Webcam

-C++ compiler (MSVC or MinGW)


License

This project is for educational purposes.

