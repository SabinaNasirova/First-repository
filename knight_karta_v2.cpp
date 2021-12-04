#include "TXLib.h"
//#include "Knight_struct.cpp"

struct Map
{
    int a[10][10];
    int xmap;
    int ymap;
    HDC karta;

    void init();
    void draw();
    void delete_all();
    int get_cell(int x, int y);
    void set_cell(int x, int y, int type);
};

struct person
{
    int x; //где будет стоять
    int y; //где будет стоять
    int xpic;//координаты картинки
    int ypic;//координаты картинки
    HDC my_image;

    void draw();
    void move_up(Map m);
    void move_down(Map m);
    void move_right(Map m);
    void move_left(Map m);
    void update(Map m);
};

void Map::init()
{
    int b[10][10]={{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
                   { 0, 2, 0, 0, 1, 0, 0, 1, 1, 1},
                   { 0, 1, 0, 1, 1, 0, 0, 0, 0, 0},
                   { 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
                   { 0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
                   { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                   { 0, 0, 1, 1, 1, 0, 1, 1, 1, 0},
                   { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
                   { 0, 1, 1, 0, 1, 1, 1, 1, 2, 0},
                   { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}};
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            a[i][j]=b[i][j];
        }
    }
    karta = txLoadImage ("mape.bmp");
    if (!karta)
    {
        txMessageBox ("Не могу загрузить фон из mape.bmp");
    }
}

void Map::draw()
{
    int x=0, y=0;
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(a[i][j]==0)
            {
                xmap=37;
                ymap=34;
            }
            if(a[i][j]==1)
            {
                xmap=35;
                ymap=349;
            }
            if(a[i][j]==2)
            {
                xmap=148;
                ymap=350;
            }
            txTransparentBlt (txDC(), x, y, 90, 90, karta, xmap, ymap, RGB(0,32,64));
            x+=90;
        }
        y+=90;
        x=0;
    }
}

void Map::delete_all()
{
    txDeleteDC (karta);
}

int Map::get_cell(int x, int y)
{

    return  a[y/90][x/90];
}

void Map:: set_cell(int x, int y, int type)
{
    a[y/90][x/90]=type;
}

void person::draw()
{
    txTransparentBlt (txDC(), x, y, 48, 73, my_image, xpic, ypic, TX_WHITE);
}

void person::move_right(Map m)
{
    ypic=147;
    if(xpic == 96)
    {
        xpic=0;
    }
    else
    {
        xpic+=48;
    }

    if((m.get_cell(x+48, y+36) != 0) && (m.get_cell(x+48, y+60) != 0))
    {
        x+=10;
    }
}

void person::move_left(Map m)
{

    ypic=73;
    if(xpic == 96)
    {
        xpic=0;
    }
    else
    {
        xpic+=48;
    }
    if((m.get_cell(x, y+36) != 0) && (m.get_cell(x, y+10) != 0))
    {
        x-=10;
    }
}

void person::move_up(Map m)
{
    ypic=219;
    if(xpic == 96)
    {
        xpic=0;
    }
    else
    {
        xpic+=48;
    }
    if(m.get_cell(x+14, y) != 0)
    {
        y-=10;
    }
}

void person::move_down(Map m)
{
    ypic=0;
    if(xpic == 96)
    {
        xpic=0;
    }
    else
    {
        xpic+=48;
    }
    if(m.get_cell(x+24, y+72) != 0)
    {
        y+=10;
    }
}

void person::update(Map m)
{
    if (GetAsyncKeyState(VK_RIGHT))
    {
        move_right(m);
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        move_left(m);
    }
    if (GetAsyncKeyState(VK_UP))
    {
        move_up(m);
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        move_down(m);
    }
}
int main()
{
    txCreateWindow(900, 900);
    struct Map m;
    struct person p={250, 330, 0, 0, txLoadImage ("Knight.bmp")};

    m.init();
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        //m.set_cell(400, 400, 2);
        txClear();
        m.draw();
        p.draw();
        p.update(m);
        txSleep(50);
        //printf("%d", m.get_cell(298, 366));

    }
    txDeleteDC (p.my_image);
    m.delete_all();
}
