#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#include "sea_battle.h"

using namespace std;

sea_battle::sea_battle() {

    create_ships(4, 1, ships);
    create_ships(3, 2, ships);
    create_ships(2, 3, ships);
    create_ships(1, 4, ships);
    create_ships(4, 1, enemy_ships);
    create_ships(3, 2, enemy_ships);
    create_ships(2, 3, enemy_ships);
    create_ships(1, 4, enemy_ships);
}

void sea_battle::start() {

    splash_screen();
    Field.draw();
    Field.label("Левое поле - ваше. Расставьте корабли при помощи клавиш стрелок или букв WASD.\n"
        "\t\t\t     Чтобы выстрелить или поставить корабль нажмите: ENTER.\n"
        "\t\t\t\tДля того, чтобы развернуть корабль нажмите: 'R'. ", 18, 23, 45);

    Field.label("Примечание: поворот невозможен, если корабль "
        "после него будет перекрывать другие корабли.", 12, 28, 20);

    insert_ships();
    insert_enemy_ships();
    player_turn();
}

void sea_battle::label_animation(int time) {

    gotoxy(24, 11);
    cout << "================================================================";
    gotoxy(27, 10);
    int y = 9;
    for (int i = 0; i < label.length(); i++)
    {
        if (label[i] == '\n') { gotoxy(27, y); y--; }

        else { cout << label[i]; Sleep(time); }
    }
    Sleep(300);
}

void sea_battle::splash_screen() {

    hidecursor();
    label_animation(1);
    for (int i = 0; i < 3; i++)
    {
        clrscr();
        Sleep(200);
        label_animation();
    }
    Sleep(300);
    clrscr();
}

void sea_battle::create_ships(int n, int deck, vector<ship>& ships) {

    for (int i = 0; i < n; i++) { ship new_ship(deck); ships.push_back(new_ship); }
}

void sea_battle::set_point(int cnt) { 

    int p;
    COORD dxy;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 99);
    bool remake = false;
    
    while (true)
    {
        p = dis(gen);
        gotoxy(Field.cells[p].X, Field.cells[p].Y);
        dxy = wherexy();

        for (int i = 0; i < cnt; i++)
        {
            for (int j = 0; j < ships[cnt].tails.size(); j++)
            {
                if (((dxy.X + ships[cnt].tails[j].X) == ships[i].coord.X &&
                     (dxy.Y + ships[cnt].tails[j].Y) == ships[i].coord.Y) ||
                     (dxy.X + ships[cnt].tails[j].X) > 40) { remake = true; break; }
            }
            if (dxy.X == ships[i].coord.X &&
                dxy.Y == ships[i].coord.Y) { remake = true; break; }

            for (int j = 0; j < ships[i].tails.size(); j++)
            {
                for (int g = 0; g < ships[cnt].tails.size(); g++)
                {
                    if (((dxy.X + ships[cnt].tails[g].X) == ships[i].tails[j].X &&
                         (dxy.Y + ships[cnt].tails[g].Y) == ships[i].tails[j].Y) ||
                         (dxy.X == ships[i].tails[j].X && dxy.Y == ships[i].tails[j].Y)) { remake = true; break; }
                }
            }
        }

        if (!remake) { break; }
        else { remake = false; }
    }
}

void sea_battle::occupied_point(int x, int y, int cnt) {

    dxy = wherexy();
    color = GREEN;
    perm = true;
    offset = 1;

    for (int i = 0; i < busy_poits.size(); i++)
    {
        if (((dxy.X + x) == busy_poits[i].X) &&
            ((dxy.Y + y) == busy_poits[i].Y)) {
            color = RED; break;
        }

        if (ships[cnt].tails.size() != 0)
        {
            if ((dxy.X + x + ships[cnt].tails.back().X) == busy_poits[i].X &&
                (dxy.Y + y + ships[cnt].tails.back().Y) == busy_poits[i].Y)
            {
                color = RED;
                break;
            }
        }
    }

    for (int i = 0; i < ships.size(); i++)
    {
        if (((dxy.X + x) == ships[i].coord.X) &&
            ((dxy.Y + y) == ships[i].coord.Y)) {
            perm = false; break;
        }

        if (ships[cnt].tails.size() != 0)
        {
            for (int j = 0; j < ships[cnt].tails.size(); j++)
            {
                if ((dxy.X + x + ships[cnt].tails[j].X) == ships[i].coord.X &&
                    (dxy.Y + y + ships[cnt].tails[j].Y) == ships[i].coord.Y) {
                    perm = false; break;
                }
            }
        }

        if (ships[i].tails.size() != 0)
        {
            for (int j = 0; j < ships[cnt].tails.size(); j++)
            {
                for (int g = 0; g < ships[i].tails.size(); g++)
                {
                    if (((dxy.X + x + ships[cnt].tails[j].X) == ships[i].tails[g].X &&
                        (dxy.Y + y + ships[cnt].tails[j].Y) == ships[i].tails[g].Y) ||
                        ((dxy.X + x) == ships[i].tails[g].X &&
                            (dxy.Y + y) == ships[i].tails[g].Y)) {
                        perm = false; break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < ships[cnt].tails.size(); i++)
    {
        for (int j = 0; j < ships[cnt - offset].tails.size(); j++)
        {
            if (((dxy.X + x) == ships[cnt - offset].tails[j].X) &&
                ((dxy.Y + y) == ships[cnt - offset].tails[j].Y)) {
                perm = false; break;
            }

            if (((dxy.X + x + ships[cnt].tails[i].X) == ships[cnt - offset].tails[j].X) &&
                ((dxy.Y + y + ships[cnt].tails[i].Y) == ships[cnt - offset].tails[j].Y))
            {
                perm = false;
                break;
            }
        }
        offset++;
    }

    if (perm)
    {
        ships[cnt].draw(' ', color, false);
        gotoxy(dxy.X + x, dxy.Y + y);
        ships[cnt].draw('X', color, false);
    }
}

bool sea_battle::sides(bool x, int bord_1, int bord_2, int cnt, int dxy) {

    if ((dxy + offset) < bord_1 || (dxy + offset) > bord_2) { return cont = true; }

    for (int i = 0; i < ships[cnt].tails.size(); i++)
    {
        if (x)
        {
            if ((dxy + offset + ships[cnt].tails[i].X) < bord_1 ||
                (dxy + offset + ships[cnt].tails[i].X) > bord_2) {
                cont = true; return cont;
            }
        }
        else
        {
            if ((dxy + offset + ships[cnt].tails[i].Y) < bord_1 ||
                (dxy + offset + ships[cnt].tails[i].Y) > bord_2) {
                cont = true; return cont;
            }
        }
    }
    return cont;
}

void sea_battle::not_special_key(bool option, bool x, int bord_1, int bord_2, int bord_3,
    int bord_4, int cnt, int dx, int dy) {

    for (int i = 0; i < keys.size(); i++)
    {
        if (c == keys[i])
        {
            spot = (i < keys.size() / 2) ? true : (false);
            offset = i;

            if (spot)
            {
                offset = (offset >= keys.size() / 4) ? 4 : (-4);

                if (sides(x, bord_1, bord_2, cnt, dx)) continue;

                if (option) { occupied_point(offset, 0, cnt); }

                else { gotoxy(dx + offset, dy); }

            }
            else
            {
                offset = (offset >= keys.size() * 0.75) ? 2 : (-2);

                if (sides(!x, bord_3, bord_4, cnt, dy)) continue;

                if (option) { occupied_point(0, offset, cnt); }

                else { gotoxy(dx, dy + offset); }
            }
            break;
        }
    }
}

void sea_battle::add_main_points(vector<COORD>& points, bool enemy, int i) {

    for (int g = 0; g < 9; g++)
    {
        if ((i + num[g]) < 100 && (i + num[g]) >= 0 &&
            ((i + num[g]) % 10 == (i % 10) ||
                (i + num[g]) % 10 == ((i % 10) + 1) ||
                (i + num[g]) % 10 == ((i % 10) - 1)))
        {
            if (enemy) { points.push_back(Field.enemy_cells[i + num[g]]); }
            else { points.push_back(Field.cells[i + num[g]]); }
        }
    }
}

void sea_battle::add_tail_points(vector<COORD>& points, vector<ship>& ships,
    bool enemy, int i, int ship_iter) {

    COORD cell_xy;
    int size;
    size = ships[ship_iter].tails.size();

    if (enemy) { cell_xy = Field.enemy_cells[i]; }
    else { cell_xy = Field.cells[i]; }

    for (int j = 0; j < size; j++)
    {
        if (ships[ship_iter].tails[j].X == cell_xy.X &&
            (ships[ship_iter].tails[j].Y) == cell_xy.Y) {
            add_main_points(points, enemy, i);
        }
    }
}

void sea_battle::print_points(COORD point, bool enemy, int i) {

    for (int g = 0; g < 9; g++)
    {
        if ((i + num[g]) < 100 && (i + num[g]) >= 0 &&
            ((i + num[g]) % 10 == (i % 10) ||
                (i + num[g]) % 10 == ((i % 10) + 1) ||
                (i + num[g]) % 10 == ((i % 10) - 1)))
        {
            if (enemy)
            {
                gotoxy(Field.enemy_cells[i + num[g]].X, Field.enemy_cells[i + num[g]].Y);
                point = wherexy();
                player_turns.push_back(point);
                cout << 'O';
            }
            else
            {
                turns.push_back(Field.cells[i + num[g]]);
                gotoxy(Field.cells[i + num[g]].X, Field.cells[i + num[g]].Y);
                textcolor(WHITE);
                cout << 'O';
                gotoxy(point.X, point.Y);
            }
        }
    }
}

void sea_battle::dead_ship(COORD point, int i) {

    if (enemy_ships[i].dead)
    {
        ship::kills++;
        COORD dxy = wherexy();
        textcolor(WHITE);

        for (int i1 = 0; i1 < Field.enemy_cells.size(); i1++)
        {
            if (enemy_ships[i].coord.X == Field.enemy_cells[i1].X &&
                enemy_ships[i].coord.Y == Field.enemy_cells[i1].Y)
            {
                print_points(point, true, i1);
            }
            for (int j = 0; j < enemy_ships[i].tails.size(); j++)
            {
                if (enemy_ships[i].tails[j].X == Field.enemy_cells[i1].X &&
                    (enemy_ships[i].tails[j].Y) == Field.enemy_cells[i1].Y)
                {
                    print_points(point, true, i1);
                }
            }
        }
        enemy_ships[i].draw('X', MAGENTA);
        gotoxy(dxy.X, dxy.Y);
    }
}

void sea_battle::insert_ships() {

    cnt = 0;
    offset = 0;
    bool is_in = false;
    int clone = - 1;
    showcursor();

    while (cnt < ships.size())
    {
        if (cnt != clone) { clone = cnt; set_point(cnt); }
        
        ships[cnt].draw(' ', color, false);
        ships[cnt].draw('X', color, false);
        c = _getch();

        dxy = wherexy();
        cont = false;

        if (c == Keycodes::Special) { special_key = true; continue; }

        if (c == Keycodes::Enter)
        {
            for (int i = 0; i < busy_poits.size(); i++)
            {
                if ((dxy.X == busy_poits[i].X) &&
                    (dxy.Y == busy_poits[i].Y)) { is_in = true; break; }

                if (ships[cnt].tails.size() != 0)
                {
                    if (dxy.X + ships[cnt].tails.back().X == busy_poits[i].X &&
                        dxy.Y + ships[cnt].tails.back().Y == busy_poits[i].Y) { is_in = true; break; }
                }
            }

            if (is_in)
            {
                is_in = false;
                ships[cnt].draw(' ', color, false);

                Field.label("Недопустимая Позиция!", 46, 10, 30);
                gotoxy(dxy.X, dxy.Y);
                color = GREEN;
                continue;
            }

            ships[cnt].set_coords();

            for (int i = 0; i < Field.cells.size(); i++)
            {
                if ((ships[cnt].coord.X == Field.cells[i].X) &&
                    (ships[cnt].coord.Y == Field.cells[i].Y)) {
                    add_main_points(busy_poits, false, i);
                }

                add_tail_points(busy_poits, ships, false, i, cnt);
            }

            Field.label("                     ", 46, 10);
            rotate = false;
            cnt++;
            continue;
        }

        if (c == Keycodes::R || c == Keycodes::R_l)
        {
            int bit = 0;
            bool permit = true;

            if (ships[cnt].deck == 3) bit = 4;

            else if (ships[cnt].deck == 4) bit = 8;

            for (int i = 0; i < cnt; i++)
            {
                if ((dxy.X + bit == ships[i].coord.X) &&
                    (dxy.Y == ships[i].coord.Y)) { permit = false; break; }

                for (int j = 0; j < ships[cnt].tails.size(); j++)
                {
                    if (((dxy.X + ships[cnt].tails[j].Y) == ships[i].coord.X &&
                         (dxy.Y + ships[cnt].tails[j].X / 2) == ships[i].coord.Y) || 
                        ((dxy.X + ships[cnt].tails[j].Y * 2) == ships[i].coord.X &&
                         (dxy.Y + ships[cnt].tails[j].X) == ships[i].coord.Y))
                    {
                        permit = false;
                        break;
                    }
                }

                for (int j = 0; j < ships[i].tails.size(); j++)
                {
                    for (int g = 0; g < ships[cnt].tails.size(); g++)
                    {
                        if (((dxy.X + ships[cnt].tails[g].Y) == ships[i].tails[j].X &&
                             (dxy.Y + ships[cnt].tails[g].X / 2) == ships[i].tails[j].Y) ||
                             (dxy.X + bit == ships[i].tails[j].X &&
                              dxy.Y == ships[i].tails[j].Y)) { permit = false; break; }
                    }
                }
            }

            if (dxy.X + 4 + bit > 40 || dxy.Y + 2 + bit / 2 > 19 || !permit) { continue; }

            ships[cnt].draw(' ', color, false);

            for (int i = 0; i < ships[cnt].tails.size(); i++)
            {
                int tmp = ships[cnt].tails[i].X;
                ships[cnt].tails[i].X = ships[cnt].tails[i].Y;
                ships[cnt].tails[i].Y = tmp;

                if (rotate) ships[cnt].tails[i].X *= 2;
                else ships[cnt].tails[i].Y /= 2;
            }
            rotate = !rotate;
            occupied_point(0, 0, cnt);
        }

        if (special_key)
        {
            if (c == Keycodes::Right || c == Keycodes::Left)
            {
                offset = (c == Keycodes::Right) ? 4 : (-4);

                if (sides(true, 3, 40, cnt, dxy.X)) continue;

                occupied_point(offset, 0, cnt);
            }

            else if (c == Keycodes::Up || c == Keycodes::Down)
            {
                offset = (c == Keycodes::Down) ? 2 : (-2);

                if (sides(false, 1, 19, cnt, dxy.Y)) continue;

                occupied_point(0, offset, cnt);
            }

            special_key = false;
            continue;
        }

        else { not_special_key(true, true, 3, 40, 1, 19, cnt, dxy.X, dxy.Y); }
    }
    Field.label("Поехали!", 52, 2, 30);
    Sleep(1000);
    Field.label("        ", 52, 2, 30);
}

void sea_battle::insert_enemy_ships() {

    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 99);
    uniform_int_distribution<> rad(0, 1);
    bool total_remake = true;
    bool total_stop;
    bool remake;
    bool stop;
    int randm;
    int lost;
    int p;
    textcolor(WHITE);

    while (total_remake)
    {
        stop = true;
        total_stop = true;
        enemy_ships.clear();
        enemy_busy_poits.clear();
        create_ships(4, 1, enemy_ships);
        create_ships(3, 2, enemy_ships);
        create_ships(2, 3, enemy_ships);
        create_ships(1, 4, enemy_ships);

        for (int k = 0; k < enemy_ships.size(); k++)
        {
            randm = rad(gen);
            if (randm == 0)
            {
                for (int i = 0; i < enemy_ships[k].tails.size(); i++)
                {
                    int tmp = enemy_ships[k].tails[i].X;
                    enemy_ships[k].tails[i].X = enemy_ships[k].tails[i].Y;
                    enemy_ships[k].tails[i].Y = tmp;

                    enemy_ships[k].tails[i].Y /= 2;
                }
            }

            remake = true;
            COORD tail;
            lost = 0;

            while (remake)
            {
                stop = true;
                if (lost == 50) { total_stop = false; break; }

                lost++;
                p = dis(gen);

                if (enemy_ships[k].tails.size() == 0) { tail.X = 0; tail.Y = 0; }

                else
                {
                    tail.X = enemy_ships[k].tails.back().X;
                    tail.Y = enemy_ships[k].tails.back().Y;
                }

                if ((Field.enemy_cells[p].X + tail.X) >= 110 ||
                    (Field.enemy_cells[p].Y + tail.Y) > 19) continue;

                for (int j = 0; j < enemy_busy_poits.size(); j++)
                {
                    if ((Field.enemy_cells[p].X + tail.X == enemy_busy_poits[j].X &&
                        Field.enemy_cells[p].Y + tail.Y == enemy_busy_poits[j].Y) ||
                        (Field.enemy_cells[p].X == enemy_busy_poits[j].X &&
                            Field.enemy_cells[p].Y == enemy_busy_poits[j].Y)) {
                        stop = false; break;
                    }
                }

                if (stop) { remake = false; }
            }

            if (!total_stop) { total_stop = true; break; }

            gotoxy(Field.enemy_cells[p].X, Field.enemy_cells[p].Y);
            enemy_ships[k].set_coords();

            add_main_points(enemy_busy_poits, true, p);

            for (int i = 0; i < Field.enemy_cells.size(); i++)
            {
                add_tail_points(enemy_busy_poits, enemy_ships, true, i, k);
            }

            if (k == enemy_ships.size() - 1) { total_remake = false; }
        }
    }
}

void sea_battle::enemy_turn() {

    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 99);
    COORD dxy = wherexy();
    COORD back;

    int p;
    int index = 0;
    bool del = true;
    bool remake = true;
    bool allright = true;
    p = dis(gen);

    if (fight)
    {
        was = true;
        if (first_turn) { first_turn = false; main_dp = dp; }

        for (int i = 0; i < num2.size(); i++)
        {
            del = true;
            if (dp + num2[i] < 100 && dp + num2[i] >= 0 &&
                !(num2[i] == 1 && Field.cells[dp].Y == 19))
            {
                for (int j = 0; j < turns.size(); j++)
                {
                    if (Field.cells[dp + num2[i]].X == turns[j].X &&
                        Field.cells[dp + num2[i]].Y == turns[j].Y)
                    {
                        dp = main_dp;
                        num2.erase(num2.begin() + i);
                        i--;
                        del = false;
                        break;
                    }
                }
                if (del)
                {
                    index = i;
                    p = dp + num2[i];
                    remake = false;
                    break;
                }
            }
            else { dp = main_dp; num2.erase(num2.begin() + i); i--; }
        }
    }

    while (remake)
    {
        allright = true;
        p = dis(gen);

        for (int i = 0; i < turns.size(); i++)
        {
            if (Field.cells[p].X == turns[i].X &&
                Field.cells[p].Y == turns[i].Y) {
                allright = false; break;
            }
        }
        if (allright) { remake = false; }
    }

    bool no_hit = true;
    bool end = false;
    COORD point;

    for (int i = 0; i < ships.size(); i++)
    {
        if (Field.cells[p].X == ships[i].coord.X &&
            Field.cells[p].Y == ships[i].coord.Y)
        {
            no_hit = false;
            ships[i].take_damage();
            gotoxy(Field.cells[p].X, Field.cells[p].Y);
            point = wherexy();
            turns.push_back(point);
            textcolor(RED);
            cout << 'X';
        }

        for (int j = 0; j < ships[i].tails.size(); j++)
        {
            if (Field.cells[p].X == ships[i].tails[j].X &&
                Field.cells[p].Y == ships[i].tails[j].Y)
            {
                no_hit = false;
                ships[i].take_damage();
                gotoxy(Field.cells[p].X, Field.cells[p].Y);
                point = wherexy();
                turns.push_back(point);
                textcolor(RED);
                cout << 'X';
                break;
            }
        }

        if (!no_hit)
        {
            fight = true;
            end = true;
            dp = p;

            if (ships[i].dead)
            {
                ship::enemy_kills++;
                first_turn = true;
                fight = false;
                was = false;
                num2 = { 10, -10, 1, -1 };
                back = wherexy();

                for (int i1 = 0; i1 < Field.cells.size(); i1++)
                {
                    if ((ships[i].coord.X == Field.cells[i1].X) &&
                        (ships[i].coord.Y == Field.cells[i1].Y))
                    {
                        print_points(back, false, i1);
                    }

                    for (int j = 0; j < ships[i].tails.size(); j++)
                    {
                        if (ships[i].tails[j].X == Field.cells[i1].X &&
                            (ships[i].tails[j].Y) == Field.cells[i1].Y)
                        {
                            print_points(back, false, i1);
                        }
                    }
                }
                ships[i].draw('X', RED);
            }
            break;
        }
    }

    if (ship::enemy_kills == 10)
    {
        ship::kills = 10;
        textcolor(RED);
        Field.label("Поражение!\n", 52, 10, 30);
        textcolor(WHITE);
        win = false;
        return;
    }
    if (end) { Sleep(1000); enemy_turn(); }

    if (no_hit)
    {
        if (was) { num2.erase(num2.begin() + index); fight = true; dp = main_dp; }

        gotoxy(Field.cells[p].X, Field.cells[p].Y);
        point = wherexy();
        turns.push_back(point);
        textcolor(WHITE);
        cout << 'O';
    }

    Sleep(1000);
    gotoxy(dxy.X, dxy.Y);
    textcolor(WHITE);
}

void sea_battle::player_turn() {

    showcursor();
    bool is_in = false;
    gotoxy(72, 1);

    while (ship::kills != 10)
    {
        c = _getch();
        dxy = wherexy();
        cont = false;

        if (c == Keycodes::Special) { special_key = true; continue; }

        if (c == Keycodes::Enter)
        {
            for (int i = 0; i < player_turns.size(); i++)
            {
                if (dxy.X == player_turns[i].X &&
                    dxy.Y == player_turns[i].Y) {
                    is_in = true; break;
                }
            }

            if (is_in)
            {
                is_in = false;
                Field.label("Вы уже стреляли сюда!", 46, 10, 30);
                Field.label("                     ", 46, 10, 30);
                gotoxy(dxy.X, dxy.Y);
                continue;
            }

            COORD point;
            bool no_hit = true;

            for (int i = 0; i < enemy_ships.size(); i++)
            {
                if (dxy.X == enemy_ships[i].coord.X &&
                    dxy.Y == enemy_ships[i].coord.Y)
                {
                    point = wherexy();
                    player_turns.push_back(point);
                    enemy_ships[i].take_damage();
                    textcolor(MAGENTA);
                    cout << 'X';
                    gotoxy(point.X, point.Y);

                    dead_ship(point, i);
                    no_hit = false;
                    break;
                }

                for (int j = 0; j < enemy_ships[i].tails.size(); j++)
                {
                    if (dxy.X == enemy_ships[i].tails[j].X &&
                        dxy.Y == enemy_ships[i].tails[j].Y)
                    {
                        point = wherexy();
                        player_turns.push_back(point);
                        enemy_ships[i].take_damage();
                        textcolor(MAGENTA);
                        cout << 'X';
                        gotoxy(point.X, point.Y);

                        no_hit = false;
                        break;
                    }
                }

                if (!no_hit) { dead_ship(point, i); break; }
            }
            if (no_hit)
            {
                point = wherexy();
                player_turns.push_back(point);
                textcolor(WHITE);
                cout << 'O';
                gotoxy(point.X, point.Y);
                enemy_turn();
            }
            continue;
        }

        if (special_key)
        {
            if (c == Keycodes::Right || c == Keycodes::Left)
            {
                offset = (c == Keycodes::Right) ? 4 : (-4);

                if ((dxy.X + offset) < 70 || (dxy.X + offset) > 110) continue;

                gotoxy(dxy.X + offset, dxy.Y);
            }

            else if (c == Keycodes::Up || c == Keycodes::Down)
            {
                offset = (c == Keycodes::Down) ? 2 : (-2);

                if ((dxy.Y + offset) < 1 || (dxy.Y + offset) > 19) continue;

                gotoxy(dxy.X, dxy.Y + offset);
            }

            special_key = false;
            continue;
        }

        else { not_special_key(false, true, 70, 110, 1, 19, 0, dxy.X, dxy.Y); }
    }
    if (win) { textcolor(GREEN); Field.label("Победа!\n", 53, 10, 30); textcolor(WHITE); }
}
