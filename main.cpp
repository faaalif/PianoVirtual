#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>

#pragma comment(lib, "winmm.lib")  // para poder vincular la libreria 

using namespace cv;
using namespace std;

#define AREA_THRESHOLD 5000
#define DURATION 200  

// funcion con ruta de sonido
void detectarYReproducir(Mat& mask, Rect zona, LPCWSTR sonido, Scalar colorActiva, Mat& frame) {
    if (zona.x >= 0 && zona.y >= 0 &&
        zona.x + zona.width <= mask.cols &&
        zona.y + zona.height <= mask.rows) {

        Mat roi = mask(zona);
        int area = countNonZero(roi);

        if (area > AREA_THRESHOLD) {
            PlaySound(sonido, NULL, SND_FILENAME | SND_ASYNC);
            rectangle(frame, zona, colorActiva, FILLED);
        }
        else {
            rectangle(frame, zona, Scalar(200, 200, 200), 2);
        }
    }
}

int main() {
    VideoCapture cam(0);
    if (!cam.isOpened()) {
        cout << "No se pudo acceder a la camara" << endl;
        return -1;
    }

    cam.set(CAP_PROP_FRAME_WIDTH, 640);
    cam.set(CAP_PROP_FRAME_HEIGHT, 480);

    vector<Rect> teclas = {
        Rect(20, 100, 80, 200),   // Rojo - DO
        Rect(110, 100, 80, 200),  // Azul - RE
        Rect(200, 100, 80, 200),  // Verde - MI
        Rect(290, 100, 80, 200),  // Amarillo - FA
        Rect(380, 100, 80, 200),  // Naranja - SOL
        Rect(470, 100, 80, 200),  // Rosa - LA
        Rect(560, 100, 80, 200)   // Morado - SI
    };

    while (true) {
        Mat frame, hsv;
        cam >> frame;
        if (frame.empty()) break;

        flip(frame, frame, 1);
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        Mat rojo1, rojo2, maskRojo, maskAzul, maskVerde, maskAmarillo, maskNaranja, maskRosa, maskMorado;

        inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), rojo1);
        inRange(hsv, Scalar(170, 120, 70), Scalar(180, 255, 255), rojo2);
        maskRojo = rojo1 | rojo2;

        inRange(hsv, Scalar(100, 150, 0), Scalar(140, 255, 255), maskAzul);
        inRange(hsv, Scalar(40, 70, 70), Scalar(80, 255, 255), maskVerde);
        inRange(hsv, Scalar(20, 100, 100), Scalar(30, 255, 255), maskAmarillo);
        inRange(hsv, Scalar(10, 100, 100), Scalar(20, 255, 255), maskNaranja);
        inRange(hsv, Scalar(140, 100, 100), Scalar(160, 255, 255), maskRosa);
        inRange(hsv, Scalar(125, 50, 50), Scalar(145, 255, 255), maskMorado);

        // rutas para el sonido
        detectarYReproducir(maskRojo, teclas[0], L"do.wav", Scalar(0, 0, 255), frame);
        detectarYReproducir(maskAzul, teclas[1], L"re.wav", Scalar(255, 0, 0), frame);
        detectarYReproducir(maskVerde, teclas[2], L"mi.wav", Scalar(0, 255, 0), frame);
        detectarYReproducir(maskAmarillo, teclas[3], L"fa.wav", Scalar(0, 255, 255), frame);
        detectarYReproducir(maskNaranja, teclas[4], L"sol.wav", Scalar(0, 128, 255), frame);
        detectarYReproducir(maskRosa, teclas[5], L"la.wav", Scalar(255, 0, 255), frame);
        detectarYReproducir(maskMorado, teclas[6], L"si.wav", Scalar(128, 0, 128), frame);

        vector<string> notas = { "Do", "Re", "Mi", "Fa", "Sol", "La", "Si" };
        for (int i = 0; i < teclas.size(); ++i) {
            putText(frame, notas[i], Point(teclas[i].x + 20, teclas[i].y - 10), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 2);
        }

        imshow("Piano Virtual", frame);
        if (waitKey(30) == 27) break;
    }

    cam.release();
    destroyAllWindows();
    return 0;
}
