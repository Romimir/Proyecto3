#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <locale>
using namespace std;

// Estructura para representar un punto en el laberinto, que puede contener tesoros o una corona
struct Point {
    int x, y;
    bool EsTesoro, Corona;  // Indicadores de tesoro y corona en el punto
    char c;                 // Representa el carácter del punto (espacio, muro, tesoro, corona)
    vector<Point*> Vecinos; // Lista de vecinos del punto para facilitar el movimiento
};

// Estructura para representar al jugador, con posición, tesoros recolectados y movimientos realizados
struct Jugador {
    int x, y;          // Posición del jugador
    int Tesoro;        // Contador de tesoros recolectados
    int Movimientos;   // Total de movimientos realizados
    bool Corona;       // Indicador de si el jugador ha obtenido la corona
};

#pragma region Laberintos

// Dimensiones del laberinto
const int Ancho = 20;
const int Alto = 20;

// Definición de laberintos
// ' ' representa caminos, 'X' representa muros, 'T' representa tesoros, 'C' representa la corona
// Matriz del laberinto 1
const char LABERINTO1[Alto][Ancho] =
{
    {' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
    {' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ','X','X',' ',' ',' ',' ',' ','X'},
    {'X',' ','T',' ','X','X','X','X','X','X','X',' ',' ','X',' ','X','X','X',' ','X'},
    {'X',' ',' ',' ','X',' ',' ',' ',' ',' ',' ','T',' ',' ',' ','X',' ',' ',' ','X'},
    {'X',' ','X','X','X',' ','X','X','X','X','X','X','X','X','X','X','X','X','T','X'},
    {'X',' ',' ',' ',' ',' ','T',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ','X'},
    {'X',' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X',' ','X',' ','X'},
    {'X',' ','T',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ','X',' ',' ',' ','X'},
    {'X',' ','X','X','X',' ','X',' ','X','X',' ','X',' ','X',' ',' ',' ','X','X','X'},
    {'X',' ',' ',' ',' ',' ','X',' ',' ',' ',' ','T',' ','X','X','X',' ','X',' ','X'},
    {'X',' ','X','X','X','X','X','X','X','X','X','X',' ',' ',' ','X',' ','X',' ','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X',' ','X',' ','X','X','X'},
    {'X','X','X',' ','X',' ','X',' ',' ','X',' ','T',' ','X',' ','X',' ',' ',' ','X'},
    {'X',' ','T',' ','X',' ','X','X','X','X',' ','X',' ','X',' ','X','X','X','X','X'},
    {'X',' ','X',' ','X','X','X',' ',' ',' ',' ','X',' ',' ',' ','X',' ',' ','C','X'},
    {'X',' ','X',' ','X',' ','X',' ','X','X','X','X','X','X','X','X',' ','X','X','X'},
    {'X',' ','X',' ','X',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ','X'},
    {'X',' ','X','T','X',' ','X',' ','X','X','X','X',' ','X','X','X','X','X',' ','X'},
    {'X',' ',' ',' ',' ',' ','X',' ',' ',' ',' ','T',' ',' ',' ',' ',' ',' ',' ','X'},
    {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'}
};

// Matriz del laberinto 2
const char LABERINTO2[Alto][Ancho] =
{
    {' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ','X'},
    {'X',' ','X','X','X','T','X','X',' ','X',' ',' ',' ',' ','X','X','X','X','T','X'},
    {'X',' ','T',' ',' ',' ',' ','X',' ','X',' ','X',' ','T','X','X',' ',' ',' ','X'},
    {'X',' ','X','X','X','X',' ','X',' ','X',' ','X',' ',' ',' ','X',' ','X',' ','X'},
    {'X',' ',' ',' ',' ',' ',' ','X',' ','X',' ','X','X','X',' ','X',' ','X',' ','X'},
    {'X',' ','X','X','X','X','X','X',' ','X',' ',' ',' ',' ',' ','X',' ','X','X','X'},
    {'X',' ','T',' ',' ',' ',' ',' ',' ','X',' ','X','X',' ','X','X',' ',' ',' ','X'},
    {'X',' ',' ',' ','X','X','X','X','X','X','X','C','X','X','X','X',' ','X','T','X'},
    {'X','X','X',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X','X',' ',' ',' ','X'},
    {'X',' ','X','X',' ','X','X','X','X','X','X',' ','X','X','X','X','X','X','X','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ',' ','X'},
    {'X',' ','X',' ','T',' ','X',' ','X',' ','X',' ','X',' ','X','X','X','X','X','X'},
    {'X','X','X',' ','X',' ','X','T','X','X','X',' ','T',' ',' ','X',' ',' ',' ','X'},
    {'X',' ',' ',' ','X',' ','X',' ','X',' ',' ',' ','X','X',' ','X',' ','X','X','X'},
    {'X',' ','X','X',' ',' ','X',' ','X',' ','X',' ','X',' ',' ','X',' ',' ',' ','X'},
    {'X','X',' ','X',' ',' ',' ',' ','X',' ','X',' ',' ',' ',' ','X','X','X',' ','X'},
    {'X',' ',' ','X',' ','X',' ','X','X',' ','X','T','X','X',' ',' ',' ','X',' ','X'},
    {'X',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X','X',' ',' ',' ',' ','X'},
    {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'}
};

// Matriz del laberinto 3
const char LABERINTO3[Alto][Ancho] =
{
    {' ',' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
    {'X',' ',' ',' ',' ','X','X',' ','X','X',' ','X','X','X','X','X',' ',' ','C','X'},
    {'X','X','X',' ','X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X'},
    {'X',' ',' ',' ','X',' ',' ',' ','X','X','T','X','X','X','X','X','X',' ',' ','X'},
    {'X',' ','X','X',' ',' ','X','X','X',' ',' ',' ','X',' ',' ',' ',' ',' ','T','X'},
    {'X',' ','X','T','X',' ',' ',' ',' ',' ','X','X',' ','X',' ','X','X','X','X','X'},
    {'X',' ',' ',' ',' ','X','X',' ','X','X','X','X',' ','X',' ','X',' ',' ',' ','X'},
    {'X','X','X','X',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ','X','X',' ','X','X'},
    {'X',' ',' ','X',' ','X',' ','X','X','X','X',' ','X','X',' ',' ',' ',' ','X','X'},
    {'X','X',' ','T',' ','X',' ','X',' ',' ',' ',' ','X','X',' ','X','X','X','X','X'},
    {'X',' ',' ',' ',' ',' ','X','X','X','T','X',' ','X','X',' ',' ',' ','X',' ','X'},
    {'X',' ','X','X','X',' ','X',' ',' ',' ','X',' ',' ',' ','T','X',' ','X','X','X'},
    {'X',' ',' ',' ','X',' ','X',' ','X','X','X',' ','X',' ','X',' ',' ',' ',' ','X'},
    {'X','X','T','X','X',' ','T',' ',' ',' ',' ',' ','X',' ','X','X','X',' ','X','X'},
    {'X',' ',' ',' ',' ',' ','X','X','X','X','X','X','X',' ',' ',' ','X',' ',' ','X'},
    {'X',' ','X',' ','X','X','X',' ',' ',' ',' ','X','X',' ','X',' ',' ','X','X','X'},
    {'X',' ','X','X','X',' ',' ',' ',' ','T',' ',' ',' ',' ','X','X',' ','X',' ','X'},
    {'X',' ',' ',' ','X','X','X',' ','X','X','X','X','X',' ','X','X','T','X','X','X'},
    {'X',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ','X'},
    {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'}
};

// Matriz del laberinto 4
const char LABERINTO4[Alto][Ancho] =
{
    {' ',' ','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ','X'},
    {'X','X','X','T','X','X','X',' ','X','X','T','X','X','X',' ','X','X','X','X','X'},
    {'X',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ','X'},
    {'X',' ','X','T','X','X','X',' ','X','X','X','T','X','X','X','X','X','X',' ','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
    {'X',' ','X',' ','X','X','X','X','X','X','X','X','X','X','X','X','X','T','X','X'},
    {'X',' ','X',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ','X',' ','X',' ','X','X'},
    {'X','X','X',' ','X','T','X','X','X',' ','X','X','X',' ','X',' ',' ',' ',' ','X'},
    {'X',' ','X',' ','X',' ',' ',' ','X',' ','X',' ',' ',' ','X','X','T','X','X','X'},
    {'X',' ',' ',' ','X',' ','X',' ',' ',' ','X',' ','X','X','X',' ',' ',' ','X','X'},
    {'X',' ','X','X','X',' ','X',' ','X',' ','X',' ','X',' ','X',' ','X',' ','X','X'},
    {'X',' ',' ',' ',' ',' ','X',' ','X',' ',' ',' ','X',' ',' ',' ','X',' ',' ','X'},
    {'X','X','X','X','X','X','X','X','X',' ','X','X','X','T','X','X','X','X','X','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','T',' ','X',' ',' ',' ',' ','X'},
    {'X',' ','X','X','X','T','X',' ','X','X','X','X','X',' ','X','X','X','X','X','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
    {'X','X','C','X','X',' ','X','X','X','X',' ','X','X','X','X','X','X','X','X','X'},
    {'X',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
    {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'}
};

// Matriz para representar el laberinto actual en juego
Point Laberinto[Alto][Ancho];

#pragma endregion

// Estructura para representar una pregunta de trivia
struct Pregunta
{
    string Texto;
    string Respuesta;
};

//Lista de preguntas con respectivas respuestas para la trivia
vector<Pregunta> Preguntas =
{
    {"¿Tabby es lindo?", "n"},
    {"¿Tabby odia el papel higiénico?", "n"},
    {"¿Tabby es naranja?", "n"},
    {"¿El collar de tabby es rojo?", "s"},
    {"¿El churu favorito de tabby es del sabor pollo con queso?", "s"},
    {"¿Tabby odia dormir?", "n"},
    {"¿Tabby es amoroso?", "s"},
    {"¿Tabby se porta mal?", "n"},
    {"¿Tabby es hembra?", "n"},
    {"¿Tabby tiene la cola chueca?", "n"}
};

vector<int> indicesPreguntas;   // Índices para las preguntas, se aleatorizan antes de comenzar
int contadorPreguntas = 0;      // Contador de preguntas realizadas

// Inicializa el laberinto configurando cada punto y marcando los tesoros y la corona
void InicializarLaberinto(const char LaberintoMatriz[Alto][Ancho], Point Laberinto[Alto][Ancho])
{
    for (int y = 0; y < Alto; ++y)
    {
        for (int x = 0; x < Ancho; ++x)
        {
            Laberinto[y][x] = { x, y, false, false, LaberintoMatriz[y][x], {} };
            if (LaberintoMatriz[y][x] == 'C') {
                Laberinto[y][x].Corona = true;
            }
            if (LaberintoMatriz[y][x] == 'T') {
                Laberinto[y][x].EsTesoro = true;
            }
        }
    }
}

// Conecta nodos vecinos del laberinto permitiendo movimientos a celdas adyacentes
void NodosConectados(Point Laberinto[Alto][Ancho])
{
    for (int y = 0; y < Alto; ++y)
    {
        for (int x = 0; x < Ancho; ++x)
        {
            if (Laberinto[y][x].c != 'X')
            {
                if (x > 0 && Laberinto[y][x - 1].c != 'X') Laberinto[y][x].Vecinos.push_back(&Laberinto[y][x - 1]);
                if (x < Ancho - 1 && Laberinto[y][x + 1].c != 'X') Laberinto[y][x].Vecinos.push_back(&Laberinto[y][x + 1]);
                if (y > 0 && Laberinto[y - 1][x].c != 'X') Laberinto[y][x].Vecinos.push_back(&Laberinto[y - 1][x]);
                if (y < Alto - 1 && Laberinto[y + 1][x].c != 'X') Laberinto[y][x].Vecinos.push_back(&Laberinto[y + 1][x]);
            }
        }
    }
}

// Cambia el color del texto en la consola
void ColorTexto(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Imprime el laberinto con el jugador en su posición actual
void ImprimirLaberinto(Point Laberinto[Alto][Ancho], Jugador jugador, int jugador_numero)
{
    int colorJugador = (jugador_numero == 1) ? 9 : 10;      // Color para cada jugador
    for (int y = 0; y < Alto; ++y)
    {
        for (int x = 0; x < Ancho; ++x)
        {
            if (Laberinto[y][x].c == 'P')       // Posición del jugador
            {
                ColorTexto(colorJugador);
            }
            else if (Laberinto[y][x].c == 'C')  //Corona
            {
                ColorTexto(14);
            }
            else if (Laberinto[y][x].c == 'T') //Tesoro
            {
                ColorTexto(12);
            }
            else {
                ColorTexto(7);      //Otros caracteres (X)
            }
            cout << Laberinto[y][x].c << ' ';
        }
        cout << endl;
    }
    ColorTexto(7);
}

// Mueve al jugador en el laberinto según la dirección indicada
void moverJugador(Jugador& jugador, Point Laberinto[Alto][Ancho], char move, int jugador_numero)
{
    move = tolower(move);
    int nuevoX = jugador.x, nuevoY = jugador.y;
    switch (move)
    {
    case 'w':
        nuevoY--;
        break;
    case 's':
        nuevoY++;
        break;
    case 'a':
        nuevoX--;
        break;
    case 'd':
        nuevoX++;
        break;
    default:
        cout << "Movimiento no válido." << endl;
        cout << "Use las teclas w, s, a o d para moverse." << endl;
        Sleep(500);
        return;
    }

    // Validación de límites y obstáculos
    if (nuevoX < 0 || nuevoX >= Ancho || nuevoY < 0 || nuevoY >= Alto)
    {
        cout << "Movimiento fuera de los límites del laberinto." << endl;
        return;
    }

    if (Laberinto[nuevoY][nuevoX].c == 'X')
    {
        cout << "¡Colisión con una pared!" << endl;
        Sleep(500);
        return;
    }

    if (Laberinto[nuevoY][nuevoX].c == 'T') // Recolectar tesoro
    {
        jugador.Tesoro++;
        cout << "¡Tesoro recolectado!" << endl;
        Sleep(500);
    }

    // Actualización de la posición del jugador en el laberinto
    if (Laberinto[jugador.y][jugador.x].EsTesoro)
    {
        Laberinto[jugador.y][jugador.x].c = 'X'; // El tesoro recolectado se convierte en muro
    }
    else
    {
        Laberinto[jugador.y][jugador.x].c = ' ';
    }

    if (move == 'w' || move == 's') {
        jugador.Movimientos += 10;  // Sumar 10 para movimiento vertical
    }
    else if (move == 'a' || move == 'd') {
        jugador.Movimientos += 5;   // Sumar 5 para movimiento horizontal
    }

    jugador.x = nuevoX;
    jugador.y = nuevoY;
    Laberinto[jugador.y][jugador.x].c = 'P';
    system("CLS");
    ImprimirLaberinto(Laberinto, jugador, jugador_numero);
}

bool responderPregunta()
{
    if (contadorPreguntas >= indicesPreguntas.size())
    {
        return false;
    }

    int index = indicesPreguntas[contadorPreguntas++];
    Pregunta p = Preguntas[index];

    string respuesta;
    while (true)
    {
        cout << p.Texto << " (s/n): ";
        respuesta = _getch();

        // Convertir respuesta a minúsculas
        transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

        if (respuesta == "s" || respuesta == "n")
        {
            break;
        }
        else
        {
            cout << "Respuesta no válida." << endl;
            cout << " Por favor, responde 's' para si o 'n' para no." << endl;
            Sleep(500);
        }
    }

    if (respuesta == p.Respuesta)
    {
        cout << "¡Respuesta correcta!" << endl;
        Sleep(500);
        return true;
    }
    else
    {
        cout << "¡Respuesta incorrecta." << endl;
        Sleep(500);
        return false;
    }
}

void jugarLaberinto(Jugador& jugador, Point Laberinto[Alto][Ancho], int jugador_numero)
{
    char Opcion;
    while (true)
    {
        system("CLS");
        ImprimirLaberinto(Laberinto, jugador, jugador_numero);
        Opcion = _getch();
        // Convertir opción a minúsculas
        Opcion = tolower(Opcion);

        if (Opcion == 'a' || Opcion == 's' || Opcion == 'd' || Opcion == 'w')
        {
            moverJugador(jugador, Laberinto, Opcion, jugador_numero);

            if (Laberinto[jugador.y][jugador.x].Corona)
            {
                if (responderPregunta()) {
                    jugador.Corona = true;
                }
                ColorTexto(jugador_numero == 1 ? 9 : 10);
                cout << "Movimientos realizados: " << jugador.Movimientos << endl;
                cout << "Tesoros recolectados: " << jugador.Tesoro << endl;
                cout << "Corona : " << (jugador.Corona ? "s" : "n") << endl;
                ColorTexto(7);
                break;
            }
        }
        else
        {
            ColorTexto(12);
            cout << "Use las teclas w, s, a o d para moverse." << endl;
            Sleep(1000);
        }
    }
    Sleep(5000);
}

void imprimirResultados(Jugador jugador1, Jugador jugador2)
{
    cout << "Jugador\tMovimientos\tTesoros\tCorona\n";
    ColorTexto(9);
    cout << "1\t" << jugador1.Movimientos << "\t\t" << jugador1.Tesoro << "\t" << (jugador1.Corona ? "Si" : "No") << "\n";
    ColorTexto(10);
    cout << "2\t" << jugador2.Movimientos << "\t\t" << jugador2.Tesoro << "\t" << (jugador2.Corona ? "Si" : "No") << "\n";

    if (jugador1.Movimientos < jugador2.Movimientos)
    {
        ColorTexto(9);
        cout << "\nGanador: Jugador 1\n";
    }
    else if (jugador2.Movimientos < jugador1.Movimientos)
    {
        ColorTexto(10);
        cout << "\nGanador: Jugador 2\n";
    }
    else
    {
        ColorTexto(11);
        cout << "\nEs un empate\n";
    }
    ColorTexto(7);
}

void seleccionarLaberinto(Point Laberinto[Alto][Ancho])
{
    srand(time(0));
    int Opcion = rand() % 4 + 1;
    switch (Opcion)
    {
    case 1:
        InicializarLaberinto(LABERINTO1, Laberinto);
        break;
    case 2:
        InicializarLaberinto(LABERINTO2, Laberinto);
        break;
    case 3:
        InicializarLaberinto(LABERINTO3, Laberinto);
        break;
    case 4:
        InicializarLaberinto(LABERINTO4, Laberinto);
        break;
    }
    NodosConectados(Laberinto);
}

int main()
{
    setlocale(LC_CTYPE, "es_ES.UTF-8");
    char Opcion;
    Point Laberinto1[Alto][Ancho];
    Jugador jugador1 = { 0, 0, 0, 0, false };
    Jugador jugador2 = { 0, 0, 0, 0, false };

    char Opcion_Menu = '0';

    srand(time(0));
    for (int i = 0; i < Preguntas.size(); ++i)
    {
        indicesPreguntas.push_back(i);
    }
    random_shuffle(indicesPreguntas.begin(), indicesPreguntas.end());


    do
    {
        cout << "~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~" << endl;
        cout << "|             Bienvenid@ al laberinto              |" << endl;
        cout << "|       Por favor, elija una de las opciones       |" << endl;
        cout << "|                     1. Jugar                     |" << endl;
        cout << "|                     2. Salir                     |" << endl;
        cout << " " << endl;
        Opcion_Menu = _getch();
        cout << " " << endl;
        cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -" << endl;
        cout << " " << endl;

        switch (Opcion_Menu)
        {
        case '1':
            do
            {

                int laberintoSeleccionado;

                do
                {
                    seleccionarLaberinto(Laberinto1);

                    system("CLS");
                    cout << "~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~" << endl;
                    cout << "|           A -> Izquierda    S -> Abajo           |" << endl;
                    cout << "|             D -> Derecha    W -> Arriba          |" << endl;
                    cout << "|   Debes llegar hasta la corona para finalizar    |" << endl;
                    cout << "|       ¡Cuidado! Cuando agarres un tesoro (T)     |" << endl;
                    cout << "|   el lugar en el que estaba será una pared       |" << endl;
                    cout << "|      Al llegar a la corona, debes responder      |" << endl;
                    cout << "|             una pregunta de sí o no              |" << endl;
                    cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -" << endl;
                    Sleep(5000);
                    system("CLS");
                    jugador1 = { 0, 0, 0, 0, false };
                    //jugador2 = { 0, 0, 0, 0, false};
                    contadorPreguntas = 0;  // Reiniciar el contador de preguntas

                    ColorTexto(9);
                    cout << "Jugador 1, es tu turno:\n";
                    Sleep(2000);
                    system("CLS");
                    ColorTexto(7);
                    Laberinto1[0][0].c = 'P';
                    jugarLaberinto(jugador1, Laberinto1, 1);

                    seleccionarLaberinto(Laberinto1);
                    jugador2 = { 0, 0, 0, 0, false };
                    Laberinto1[0][0].c = 'P';
                    system("CLS");
                    ColorTexto(10);
                    cout << "Jugador 2, es tu turno:\n";
                    Sleep(2000);
                    system("CLS");
                    ColorTexto(7);
                    jugarLaberinto(jugador2, Laberinto1, 2);

                    imprimirResultados(jugador1, jugador2);
                    cout << "¿Desea seguir jugando? (si|no): ";
                    string respuesta;
                    respuesta = _getch();

                    // Convertir respuesta a minúsculas
                    transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

                    if (respuesta == "s" || respuesta == "n")
                    {
                        break;
                    }
                    else
                    {
                        cout << "Respuesta no válida." << endl;
                        cout << " Por favor, responde 's' para si o 'n' para no." << endl;
                        Sleep(500);
                    }
                    Opcion = respuesta == "s" ? 's' : 'n';
                } while (Opcion == 's');
            } while (!Opcion);
            break;

        case '2':
            cout << "Saliendo del programa. . ." << endl;
            break;


        default:
            cout << " " << endl;
            cout << "|     Por favor, ingrese una opción válida...      |" << endl;
            cout << " " << endl;
            break;
        }
    } while (Opcion_Menu != '2');
    return 0;
}
