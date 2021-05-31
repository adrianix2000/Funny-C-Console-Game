//#define _WIN32_WINNT 0x0500
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>

#define strzalka_lewo 0x25
#define strzalka_prawo 0x27
#define strzalka_dol 0x28
#define strzalka_gora 0x26
#define enter 0x0D
#define spacja 32

int szerokosc = 20, wysokosc = 20;
int wspolzednaX, wspolzednaY;
char pole[20][20];
char kierunek, kierunekpocisku;
int pktX, pktY;
int punkty = 0;
int historiaWspolzednejXp[1000], historiaWspolzednejYp[1000];
char waz = 219;
char pd = 188, pg = 187, lg = 201, ld = 200, poz = 205, pio = 186;
int pociskX, pociskY;
bool pocisk=0;

clock_t start, stop;
double czas;

void idzdoxy(int x, int y){
    HANDLE hcon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hcon, dwPos);
}
void inicjalizacja_tablicy();
void rysowanie_aktualizacja_planszy();
void menu_glowne();

struct przeciwnik{
    int X;
    int Y;
};

int licznik = 0;
int ile = 0;
int co_ile = 0;
przeciwnik wrogowie[10000];
int czestotliwosc = 10;
bool gra = true;
bool czy1 = false;
bool number_of_game;



int main(){

    while(true){
        licznik = 0;
start1:
        if(czy1){
            for(int i=0; i<ile; i++){
                pole[wrogowie[i].X][wrogowie[i].Y] = 'p';
                wrogowie[i].X = 0;
            }
            ile = 0;
            czestotliwosc = 10;
            punkty = 0;
        }
        // HWND hwnd = GetConsoleWindow();
        RECT r;
        // GetWindowRect(hwnd, &r);
        // MoveWindow(hwnd, r.left, r.top, 600, 600, TRUE);
        srand(time(NULL));
        SetConsoleTitle("funny C++ game ");

        std::cout << "[G]raj" << std::endl;
        std::cout << std::endl;

        char wybor;

        std::string komunikat = "wybierz numer operacji (press g) : ";
        std::cout << komunikat;
        wybor = getch();

        if(wybor == 'G' || wybor == 'g'){
            system("cls");
            wspolzednaX = 5;
            wspolzednaY = 5;
            inicjalizacja_tablicy();

            pole[wspolzednaX][wspolzednaY] = 'o';

            do
            {
                pktX=rand()%szerokosc;
                pktY=rand()%wysokosc;
            }
            while(pole[pktX][pktY]!='p' || pktX<3 || pktX > 17 && pktY<3 || pktY>17);

            pole[pktX][pktY]='j';
            start = clock();
            for(;;)
            {
                // MoveWindow(hwnd, r.left, r.top, 700, 650, TRUE);
                idzdoxy(0,0);
                //rysowanie areny
                rysowanie_aktualizacja_planszy();
                Sleep(30);
                pole[wspolzednaX][wspolzednaY] = 'p';
                if ((GetKeyState(strzalka_prawo) & 0x8000)){
                    wspolzednaX++;
                    kierunek = 'p';
                }
                else if ((GetKeyState(strzalka_lewo) & 0x8000)){
                    wspolzednaX--;
                    kierunek = 'l';
                }
                else if ((GetKeyState(strzalka_dol) & 0x8000)){
                    wspolzednaY++;
                    kierunek = 'd';
                }
                else if ((GetKeyState(strzalka_gora) & 0x8000)){
                    wspolzednaY--;
                    kierunek = 'g';
                }
                else if ((GetKeyState(spacja) & 0x8000) && co_ile > 90)
                    if(!pocisk){
                        pocisk = 1;
                        pociskX = wspolzednaX;
                        pociskY = wspolzednaY;
                        kierunekpocisku = kierunek;
                        pole[pociskX][pociskY] = '-';
                    }

                if(wspolzednaX==szerokosc)
                    wspolzednaX=szerokosc-1;
                if(wspolzednaX==-1)
                    wspolzednaX=0;
                if(wspolzednaY==-1)
                    wspolzednaY=0;
                if(wspolzednaY==wysokosc)
                    wspolzednaY=wysokosc-1;

                if(co_ile%100 == 0 && czestotliwosc > 2 && co_ile > 100)
                    czestotliwosc--;

                if(co_ile%czestotliwosc == 0 && co_ile > 100){
                    wrogowie[ile].X = 19;
                    wrogowie[ile].Y = rand()%18+2;
                    pole[wrogowie[ile].X][wrogowie[ile].Y] = '*';
                    ile++;
                }

                if(co_ile%2 == 0){
                    for(int i=0; i<ile; i++){
                        pole[wrogowie[i].X][wrogowie[i].Y] = 'p';
                        wrogowie[i].X--;
                        pole[wrogowie[i].X][wrogowie[i].Y] = '*';
                        if(wrogowie[i].X == -1)
                            wrogowie[i].X = 0;

                        if(abs(wrogowie[i].X-pociskX)<2 && wrogowie[i].Y==pociskY || abs(wrogowie[i].Y-pociskY)<2 && wrogowie[i].X==pociskX){
                            pocisk = 0;
                            pole[pociskX][pociskY] = 'p';
                            pole[wrogowie[i].X][wrogowie[i].Y] = 'p';
                            pole[wrogowie[i].X][wrogowie[i].Y] = 'p';
                            //wrogowie[i].X = 0;
                            pociskX=0;
                            pociskY=0;

                            wrogowie[i].X = 0;
                            wrogowie[i].Y = 0;

                        }

                        if(pole[wrogowie[i].X][wrogowie[i].Y] == pole[pktX][pktY]){
                            do{
                                pktX=rand()%15+3;
                                pktY=rand()%15+3;
                            }
                            while(pole[pktX][pktY]!='p' || pktX<3 || pktX > 17 && pktY<3 || pktY>17);
                            pole[pktX][pktY]='j';
                        }
                        if(pole[wrogowie[i].X-1][wrogowie[i].Y] == 'j'){
                            pole[pktX][pktY] = 'p';
                            if(pktY < 10)
                                pktY++;
                            else
                                pktY--;
                            pole[pktX][pktY] = 'j';
                        }
                    }
                }

                if(gra == false){
                    std::cout << "error1" << std::endl;
                    system("pause");
                    break;
                }
                //zdobycie punktu
                if(pole[wspolzednaX][wspolzednaY]=='j'){
                    do{
                        pktX=rand()%15+3;
                        pktY=rand()%15+3;
                    }
                    while(pole[pktX][pktY]!='p' || pktX<3 || pktX > 17 && pktY<3 || pktY>17);

                    pole[pktX][pktY]='j';
                    punkty++;
                }

                //ruch pocisku
                if(pocisk){
                    pole[pociskX][pociskY] = 'p';
                    switch(kierunekpocisku)
                    {
                    case 'p':
                        pociskX++;
                        break;
                    case 'l':
                        pociskX--;
                        break;
                    case 'g':
                        pociskY--;
                        break;
                    case 'd':
                        pociskY++;
                        break;
                    default:
                        break;
                    }
                    if(pociskX>=szerokosc || pociskX<0 || pociskY<0 || pociskY>=wysokosc){
                        pocisk=0;
                        pociskX = 0;
                        pole[pociskX][pociskY] = 'p';
                    }
                    else
                        pole[pociskX][pociskY] = '-';

                }

                if(pole[wspolzednaX][wspolzednaY]=='*'){
                    break;
                    system("cls");
                    std::cout << "                     PRZEGRANA!!!\n";
                    system("pause");
                }

                pole[wspolzednaX][wspolzednaY] = 'o';

                co_ile++;

            }
            stop = clock();
            czas = (double)(stop-start)/CLOCKS_PER_SEC;

            system("cls");

            std::cout<<"Koniec gry !!"<<std::endl<<std::endl;
            std::cout<<"czas rozgrywki:        "<<czas<<std::endl;
            std::cout<<"zdobyte punkty:        "<<punkty<<std::endl<<std::endl;

            Sleep(2000);
            czy1 = true;


            std::cout << std::endl;

            system("pause");

            system("cls");
        }
        else
        {
            std::cout << "wybierz poprawna opcje!!!";
            Sleep(1000);
            system("cls");
            goto start1;
        }

    }

    return 0;

}
void inicjalizacja_tablicy(){
    for(int i=0; i<wysokosc; i++){
        for(int j=0; j<szerokosc; j++){
            pole[j][i]='p';
        }
    }
    pole[wspolzednaX][wspolzednaY] = 'o';
}
void rysowanie_aktualizacja_planszy(){
    std::cout << lg;
    for(int i=0; i<szerokosc; i++){
        std::cout<<poz << poz;
    }
    std::cout << pg;
    for(int i=0; i<wysokosc; i++){
        std::cout<<std::endl<<pio;

        for(int j=0; j<szerokosc; j++){
            if(pole[j][i]=='p')
                std::cout<<"  ";
            else if(pole[j][i]=='o')
                std::cout<<waz<<waz;
            else if(pole[j][i]=='j')
                std::cout<<"{}";
            else if(pole[j][i]=='*')
                std::cout<<" #";
            else if(pole[j][i]=='-')
                //cout<<" *";
                if(kierunekpocisku=='p' || kierunekpocisku=='l')
                    std::cout<<"--";
                else
                    std::cout<<" |";
        }

        std::cout<<pio;
    }
    std::cout<<std::endl;
    std::cout << ld;
    for(int i=0; i<szerokosc; i++){
        std::cout<<poz << poz;
    }
    std::cout << pd;
    std::cout << std::endl;
    std::string napis1 = "Poruszamy sie strzalkami";
    std::string napis2 = "Mozna zdobywac punkty               ZDOBYTE PUNKTY: ";
    std::string napis3 = "strzelamy spacja";
    if(co_ile > 5)
        std::cout << napis1 << std::endl;

    if(co_ile == 15)
        punkty = 0;

    if(co_ile > 15){
        std::cout << napis2 << punkty << std::endl;
    }

    if(co_ile > 80)
        std::cout << napis3 << std::endl;

    if(co_ile > 90)
        std::cout << "GOOD LUCK HAVE FUN" << std::endl;

}
