#pragma once
#include <windows.h>
#include <stdio.h>
#include <memory.h>

enum TColor {
  BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
  DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
  LIGHTMAGENTA, YELLOW, WHITE
};

enum Keys {
  UP = 72, DOWN = 80, RIGHT = 77, ARROW = -32, SPACE = 32, ENTER = 13, ESCAPE = 27,
};

COORD wherexy(void)
{
  HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos = { -1, -1 };
  if (!Console)
    return pos;

  CONSOLE_SCREEN_BUFFER_INFO buf;

  GetConsoleScreenBufferInfo(Console, &buf);
  return buf.dwCursorPosition;
}

void gotoxy(int x, int y)
{
  HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
  if (!Console)
    return;

  CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
  GetConsoleScreenBufferInfo(Console, &bufferInfo);
  SHORT width = bufferInfo.dwSize.X;
  SHORT height = bufferInfo.dwSize.Y;

  // ��������, ��� ���������� ��������� � �������� �������� ����
  if (x < 0 || x >= width || y < 0 || y >= height)
  {
    // ��������� �������� ����������� ����, ���� ���������� ������� �� ��� �������
    width = max(x + 1, width);
    height = max(y + 1, height);
    COORD size = { width, height };
    SetConsoleScreenBufferSize(Console, size);
  }

  COORD pos = { 0, 0 };
  pos.X = x;
  pos.Y = y;

  SetConsoleCursorPosition(Console, pos);
}

void hidecursor()
{
  CONSOLE_CURSOR_INFO cursor_info = { 1, false };
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void textcolor(int color)
{
  // �������� ���������� �������
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  if (console == INVALID_HANDLE_VALUE) {
    // � ������ ������ ������� ��������� � ��������� �������
    perror("Cannot retrieve console handle");
    return;
  }

  // �������� ���������� � ������ ������
  CONSOLE_SCREEN_BUFFER_INFO buffer_info;
  if (!GetConsoleScreenBufferInfo(console, &buffer_info)) {
    // � ������ ������ ������� ��������� � ��������� �������
    perror("Cannot retrieve console buffer info");
    return;
  }

  // �������� ������� ���� ������ � ����
  WORD current_attributes = buffer_info.wAttributes;

  // �������� ��� ����� ������, ������� ����� ����������
  int new_text_color = color % 16;
  if (new_text_color < 0) {
    new_text_color += 16;
  }

  // �������� ��� ����� ����
  int background_color = current_attributes / 16;

  // ��������� ���� ������ � ����
  WORD new_attributes = (background_color << 4) | new_text_color;
  if (!SetConsoleTextAttribute(console, new_attributes)) {
    // � ������ ������ ������� ��������� � ��������� �������
    perror("Cannot set console text attribute");
    return;
  }

  // ��������� ������� �������
  COORD cursor_pos = buffer_info.dwCursorPosition;

  // ��������������� ���� ������ �� ������ � ������� �������
  DWORD chars_written;
  if (!WriteConsoleOutputAttribute(console, &new_attributes, 1, cursor_pos, &chars_written)) {
    // � ������ ������ ������� ��������� � ��������� �������
    perror("Cannot write console output attribute");
    return;
  }
}
