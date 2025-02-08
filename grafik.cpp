#include <GLUT/glut.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int mode = 0;   // 0: Pilihan menu, 1: y = x^2, 2: y = ax + 4
double a = 1.0; // Gradien untuk fungsi linier

// Fungsi untuk menggambar teks
void DrawText(float x, float y, const string& text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }
}

// Fungsi untuk menggambar grid
void DrawGrid() {
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_LINES);
    for (float x = -1.0; x <= 1.0; x += 0.2) {
        glVertex2f(x, -1.0);
        glVertex2f(x, 1.0);
    }
    for (float y = -1.0; y <= 1.0; y += 0.2) {
        glVertex2f(-1.0, y);
        glVertex2f(1.0, y);
    }
    glEnd();
}

// Fungsi untuk menggambar sumbu
void DrawAxes() {
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0); glVertex2f(1.0, 0.0);
    glVertex2f(0.0, -1.0); glVertex2f(0.0, 1.0);
    glEnd();
    glLineWidth(1.0);
}

// Fungsi menggambar y = x^2
void DrawFunction1() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (float x = -1.0; x <= 1.0; x += 0.01) {
        glVertex2f(x, x * x);
    }
    glEnd();
}

// Fungsi menggambar y = ax + 4
void DrawFunction2() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (float x = -1.0; x <= 1.0; x += 0.01) {
        glVertex2f(x, a * x + 0.4);
    }
    glEnd();
}

// Fungsi utama untuk menggambar
void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    if (mode == 0) {
        DrawText(-0.3, 0.2, "Pilih fungsi:");
        DrawText(-0.3, 0.1, "1: y = x^2");
        DrawText(-0.3, 0.0, "2: y = ax + 4");
        DrawText(-0.3, -0.1, "Tekan 1 atau 2");
    } else {
        DrawGrid();
        DrawAxes();
        
        if (mode == 1) {
            DrawFunction1();
            DrawText(-0.9, 0.9, "y = x^2");
        } else if (mode == 2) {
            DrawFunction2();
            stringstream ss;
            ss << "y = " << a << "x + 4";
            DrawText(-0.9, 0.9, ss.str());
        }
    }
    
    glFlush();
}

// Fungsi untuk menangani input keyboard
void Keyboard(unsigned char key, int x, int y) {
    if (key == '1') {
        mode = 1;
        glutPostRedisplay();
    } else if (key == '2') {
        cout << "Masukkan nilai a untuk y = ax + 4: ";
        cin >> a;
        mode = 2;
        glutPostRedisplay();
    }
}

// Inisialisasi OpenGL
void InitOpenGL() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Grafik Fungsi");

    InitOpenGL();
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
    return 0;
}
