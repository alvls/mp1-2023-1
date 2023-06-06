#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include "Game.h"
HWND player_field[10][10], computer_field[10][10];
HWND auto_placement;
Game g;
int count_now = 0;
int last_k = -1;

//void convert(LPCSTR &ss, char c)
//{
//	string s = "";
//	s += c + '\0';
//	ss = s.c_str();
//}

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{

		PAINTSTRUCT ps;
		HDC hdc;

		switch (uMsg)
		{
		case WM_CREATE:
		{
			MessageBox(hWnd, "Здравствуйте!\nВас приветствует игра 'Морской бой'\n\nОбозначения:\nо - корабль\n. - промах\nx - попадание",
				"Win", MB_ICONINFORMATION);
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
				{
					player_field[i][j] = CreateWindowA("BUTTON", "", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50 + 30 * j, 30 + 30 * i, 30, 30, hWnd, 
						reinterpret_cast<HMENU>(i * 100 + j * 10 + 1), nullptr, nullptr);
					computer_field[i][j] = CreateWindowA("BUTTON", "", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 450 + 30 * j, 30 + 30 * i, 30, 30, hWnd, 
						reinterpret_cast<HMENU>(i * 100 + j * 10 + 2), nullptr, nullptr);
				}
			auto_placement = CreateWindowA("BUTTON", "Авторасстановка", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50 , 30 * 11, 120, 30, hWnd, 
				reinterpret_cast<HMENU>(0), nullptr, nullptr);
		}
		return 0;

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			/*LPCSTR number, letter;
			for (int i = 0; i < 10; i++)
			{
				convert(number, i);
				convert(letter, (char)(i + 160));
				TextOut(hdc, 40, 35 + 30 * i, number, 2);
				TextOut(hdc, 60 + 30 * i, 15, letter, 2);
				TextOut(hdc, 440, 35 + 30 * i, number, 2);
			}*/
			TextOut(hdc, 40, 35, "1", 1); TextOutA(hdc, 40, 65, "2", 1); TextOut(hdc, 40, 95, "3", 1);
			TextOut(hdc, 40, 125, "4", 1); TextOut(hdc, 40, 155, "5", 1); TextOut(hdc, 40, 185, "6", 1);
			TextOut(hdc, 40, 215, "7", 1); TextOut(hdc, 40, 245, "8", 1); TextOut(hdc, 40, 275, "9", 1);
			TextOut(hdc, 30, 305, "10", 2); TextOut(hdc, 440, 35, "1", 1); TextOut(hdc, 440, 65, "2", 1);
			TextOut(hdc, 440, 95, "3", 1); TextOut(hdc, 440, 125, "4", 1); TextOut(hdc, 440, 155, "5", 1); 
			TextOut(hdc, 440, 185, "6", 1); TextOut(hdc, 440, 215, "7", 1); TextOut(hdc, 440, 245, "8", 1); 
			TextOut(hdc, 440, 275, "9", 1); TextOut(hdc, 430, 305, "10", 2); TextOut(hdc, 60, 15, "а", 1);
			TextOut(hdc, 90, 15, "б", 1); TextOut(hdc, 120, 15, "в", 1); TextOut(hdc, 150, 15, "г", 1); 
			TextOut(hdc, 180, 15, "д", 1); TextOut(hdc, 210, 15, "е", 1); TextOut(hdc, 240, 15, "ж", 1); 
			TextOut(hdc, 270, 15, "з", 1); TextOut(hdc, 300, 15, "и", 1); TextOut(hdc, 330, 15, "к", 1);
			TextOut(hdc, 460, 15, "а", 1); TextOut(hdc, 490, 15, "б", 1); TextOut(hdc, 520, 15, "в", 1); 
			TextOut(hdc, 550, 15, "г", 1); TextOut(hdc, 580, 15, "д", 1); TextOut(hdc, 610, 15, "е", 1); 
			TextOut(hdc, 640, 15, "ж", 1); TextOut(hdc, 670, 15, "з", 1); TextOut(hdc, 700, 15, "и", 1); 
			TextOut(hdc, 730, 15, "к", 1);
			EndPaint(hWnd, &ps);
		}
		return 0;

		case WM_COMMAND:
		{
			int num;
			int i1, i2, j1, j2;
			switch (LOWORD(wParam))
			{
			case 0:
			{
				if (count_now > 0)
				{
					for (int i = 0; i < 10; i++)
						for (int j = 0; j < 10; j++)
						{
							SetWindowText(player_field[i][j], "");
						}
					num = 2;
				}
				else
					num = 0;
				vector <tuple<int, int, int, int>> ships = g.auto_placement(num);
				for (int k = 0; k < ships.size(); k++)
				{
					tie(i1, j1, i2, j2) = ships[k];
					for (int i = i1; i <= i2; i++)
						for (int j = j1; j <= j2; j++)
							SetWindowText(player_field[i][j], "o");
				}
				count_now = 10;
				DestroyWindow(auto_placement);
			}
			break;

			default:
			{

				int k = LOWORD(wParam);
				if ((count_now < 10) && (k % 10 == 1))
				{
					if (last_k == -1)
						last_k = k / 10;
					else
					{
						if (g.initialize_of_ship(k / 100, k % 100 / 10, last_k / 10, last_k % 10, 0))
						{
							if((k/100< last_k / 10)||(k % 100 / 10< last_k % 10))
								for(int i=k/100; i<=last_k/10; i++)
									for (int j = k % 100 / 10; j <= last_k % 10; j++)
									{
										SetWindowText(player_field[i][j], "o");
									}
							else
								for (int i = k / 100; i >= last_k / 10; i--)
									for (int j = k % 100 / 10; j >= last_k % 10; j--)
									{
										SetWindowText(player_field[i][j], "o");
									}
							count_now++;
							last_k = -1;
						}
						else
							last_k = k / 10;
					}
					if (count_now==10)
						DestroyWindow(auto_placement);
				}
				else if ((count_now == 10) && (k % 10 == 2))
				{
					vector <vector<tuple<int, int, int, int>>> ships = g.new_move(k / 100, k % 100 / 10);
					for (int j = 0; j < ships.size(); j++)
					{
						for (int i = 0; i < ships[j].size(); i++)
						{
							tie(i2, i1, j1, j2) = ships[j][i];
							if (i2 == 1)
							{
								if (j2 == -1)
									SetWindowText(player_field[i1][j1], ".");
								else
									SetWindowText(player_field[i1][j1], "x");
							}
							else
							{
								if (j2 == -1)
									SetWindowText(computer_field[i1][j1], ".");
								else
									SetWindowText(computer_field[i1][j1], "x");
							}
						}
						Sleep(300);
					}
				}
				if ((count_now == 10) && (g.ending()))
				{
					if (g.winner() == 1)
						MessageBox(hWnd, "Победа! Вы выиграли", "Win", MB_ICONINFORMATION);
					else
						MessageBox(hWnd, "Поражение! Вы проиграли", "Lose", MB_ICONINFORMATION);
					PostQuitMessage(EXIT_SUCCESS);
				}
			}
			break;
			}
		}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = "MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	hwnd = CreateWindow(wc.lpszClassName, "Game", WS_OVERLAPPEDWINDOW, 380, 200, 800, 400, nullptr, nullptr, wc.hInstance, nullptr);
	if (hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
};