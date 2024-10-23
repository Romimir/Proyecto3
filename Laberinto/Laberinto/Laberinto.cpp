#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <conio.h>

using namespace std;

struct Point
{
    int x, y;
    bool EsTesoro, Corona;
    char c;
    vector<Point*> Vecinos;
};

struct Jugador 
{
    int x, y;
    int Tesoro;
    int Movimientos;
    bool Corona;
};

const int Ancho = 20;
const int Alto = 20;

const char LABERINTO1[Alto][Ancho] = 
{
    {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
    {'X',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ','X','X',' ',' ',' ',' ',' ','X'},
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

const char LABERINTO2[Alto][Ancho] =
{
    {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ','X'},
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

const char LABERINTO3[Alto][Ancho] = 
{
    {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
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

const char LABERINTO4[Alto][Ancho] =
{
    {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
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

Point Laberinto[Alto][Ancho];

struct Pregunta 
{
    string texto;
    string respuesta;
};

vector<Pregunta> preguntas =
{
    {"¿Tabby es lindo?", "si"},
    {"¿Tabby odia el papel higienico?", "no"},
    {"¿Tabby es naranjo?", "no"},
    {"¿El collar de tabby es rojo?", "si"},
    {"¿El churu favorito de tabby es pollo-queso?", "si"},
    {"¿Tabby odia dormir?", "no"},
    {"¿Tabby es amoroso?", "si"},
    {"¿Tabby se porta mal?", "no"},
    {"¿Tabby es hembra?", "no"},
    {"¿Tabby tiene la cola chueca?", "si"}
};

vector<int> indicesPreguntas;
int contadorPreguntas = 0;

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

void textcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ImprimirLaberinto(Point Laberinto[Alto][Ancho], Jugador jugador, int jugador_numero) 
{
    int colorJugador = (jugador_numero == 1) ? 9 : 10;
    for (int y = 0; y < Alto; ++y) 
    {
        for (int x = 0; x < Ancho; ++x) 
        {
            if (Laberinto[y][x].c == 'P') 
            {
                textcolor(colorJugador);
            }
            else if (Laberinto[y][x].c == 'C') {
                textcolor(14);
            }
            else if (Laberinto[y][x].c == 'T') {
                textcolor(12);
            }
            else {
                textcolor(7);
            }
            cout << Laberinto[y][x].c << ' ';
        }
        cout << endl;
    }
    textcolor(7);
}

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
        cout << "Movimiento no válido. Use w, a, s, d para moverse." << endl;
        return;
    }

    if (nuevoX < 0 || nuevoX >= Ancho || nuevoY < 0 || nuevoY >= Alto) 
    {
        cout << "Movimiento fuera de los límites del laberinto." << endl;
        return;
    }

    if (Laberinto[nuevoY][nuevoX].c == 'X') 
    {
        cout << "¡Colisión con una pared!" << endl;
        return;
    }

    if (Laberinto[nuevoY][nuevoX].c == 'T') 
    {
        jugador.Tesoro++;
        cout << "¡Tesoro recolectado!" << endl;
    }

    if (Laberinto[jugador.y][jugador.x].EsTesoro)
    {
        Laberinto[jugador.y][jugador.x].c = 'X';
    }
    else
    {
        Laberinto[jugador.y][jugador.x].c = ' ';
    }

    jugador.x = nuevoX;
    jugador.y = nuevoY;
    Laberinto[jugador.y][jugador.x].c = 'P';
    jugador.Movimientos++;
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
    Pregunta p = preguntas[index];

    string respuesta;
    while (true) 
    {
        cout << p.texto << " (si/no): ";
        cin >> respuesta;

        // Convertir respuesta a minúsculas
        transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

        if (respuesta == "si" || respuesta == "no") 
        {
            break;
        }
        else 
        {
            cout << "Respuesta no válida. Por favor, responde 'si' o 'no'." << endl;
        }
    }

    if (respuesta == p.respuesta)
    {
        cout << "Respuesta correcta!" << endl;
        return true;
    }
    else 
    {
        cout << "Respuesta incorrecta." << endl;
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
        Opcion = getch();
        // Convertir opción a minúsculas
        Opcion = tolower(Opcion);

        if (Opcion == 'a' || Opcion == 's' || Opcion  == 'd' || Opcion == 'w')
        {
            moverJugador(jugador, Laberinto, Opcion, jugador_numero);

            if (Laberinto[jugador.y][jugador.x].Corona)
            {
                if (responderPregunta()) {
                    jugador.Corona = true;
                }
                textcolor(jugador_numero == 1 ? 9 : 10);
                cout << "Movimientos realizados: " << jugador.Movimientos << endl;
                cout << "Tesoros recolectados: " << jugador.Tesoro << endl;
                cout << "Corona : " << (jugador.Corona ? "Si" : "No") << endl;
                textcolor(7);
                break;
            }
        }
        else
        {
            textcolor(12);
            cout << "Recuerda que para moverte debes usar 'A', 'S', 'D', 'W'." << endl;
        }
    }
    Sleep(5000);
}

void imprimirResultados(Jugador jugador1, Jugador jugador2)
{
    cout << "Jugador\tMovimientos\tTesoros\tCorona\n";
    textcolor(9);
    cout << "1\t" << jugador1.Movimientos << "\t\t" << jugador1.Tesoro << "\t" << (jugador1.Corona ? "Si" : "No") << "\n";
    textcolor(10);
    cout << "2\t" << jugador2.Movimientos << "\t\t" << jugador2.Tesoro << "\t" << (jugador2.Corona ? "Si" : "No") << "\n";

    if (jugador1.Movimientos < jugador2.Movimientos) 
    {
        textcolor(9);
        cout << "\nGanador: Jugador 1\n";
    }
    else if (jugador2.Movimientos < jugador1.Movimientos) 
    {
        textcolor(10);
        cout << "\nGanador: Jugador 2\n";
    }
    else 
    {
        textcolor(11);
        cout << "\nEs un empate\n";
    }
    textcolor(7);
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
    default:
        cout << "Opción no válida. Seleccionando el Laberinto 1 por defecto." << endl;
        InicializarLaberinto(LABERINTO1, Laberinto);
        break;
    }
    NodosConectados(Laberinto);
}

int main() 
{
    srand(time(0));
    for (int i = 0; i < preguntas.size(); ++i)
    {
        indicesPreguntas.push_back(i);
    }
    random_shuffle(indicesPreguntas.begin(), indicesPreguntas.end());

    char Opcion;
    Point Laberinto1[Alto][Ancho];
    Jugador jugador1 = { 1, 1, 0, 0, false };
    Jugador jugador2 = { 1, 1, 0, 0, false };

    char Opcion_Menu = '0';

    do 
    {
        cout << "~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~" << endl;
        cout << "|             Bienvenid@ al laberinto              |" << endl;
        cout << "|        Por favor elija una de las opciones       |" << endl;
        cout << "|                    1-. Jugar                     |" << endl;
        cout << "|                    2-. Salir                     |" << endl;
        cout << " " << endl;
        cin >> Opcion_Menu;
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
                        cout << "|             D-> Derecha   W-> Arriba             |" << endl;
                        cout << "|   Debes llegar hasta la corona para finalizar    |" << endl;
                        cout << "|       Cuidado! cuando agarres un tesoro (T)      |" << endl;
                        cout << "|   el lugar en el que estaban sera una pareded    |" << endl;
                        cout << "|      al llegar a la corona tienes responder      |" << endl;
                        cout << "|             una pregunta de si o no              |" << endl;
                        cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -" << endl;
                        Sleep(5000);
                        system("CLS");
                        jugador1 = { 1, 1, 0, 0, false };
                        jugador2 = { 1, 1, 0, 0, false };
                        contadorPreguntas = 0;  // Reiniciar el contador de preguntas

                        textcolor(9);
                        cout << "Jugador 1 tu turno:\n";
                        Sleep(2000);
                        system("CLS");
                        textcolor(7);
                        Laberinto1[jugador1.y][jugador1.x].c = 'P';
                        jugarLaberinto(jugador1, Laberinto1, 1);

                        seleccionarLaberinto(Laberinto1);
                        jugador2 = { 1, 1, 0, 0, false };
                        Laberinto1[jugador2.y][jugador2.x].c = 'P';
                        system("CLS");
                        textcolor(10);
                        cout << "Jugador 2 tu turno:\n";
                        Sleep(2000);
                        system("CLS");
                        textcolor(7);
                        jugarLaberinto(jugador2, Laberinto1, 2);

                        imprimirResultados(jugador1, jugador2);
                        cout << "¿Desea seguir jugando? (si|no): ";
                        string respuesta;
                        cin >> respuesta;
                        // Convertir la respuesta a minúsculas
                        transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);
                        // Validar respuesta
                        while (respuesta != "si" && respuesta != "no")
                        {
                            cout << "Por favor, ingrese 'si' o 'no': ";
                            cin >> respuesta;
                            transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);
                        }
                        Opcion = respuesta == "si" ? 's' : 'n';
                    } while (Opcion == 's');
                } while (!Opcion);
                break;
            
            default:
                cout << " " << endl;
                cout << "|     Por favor ingrese una opcion valida. . .     |" << endl;
                cout << " " << endl;
                break;
        }
    } while (Opcion_Menu != '2');
    return 0;
}
