#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

// Defines for keys
#define TAB 9
#define ENT 13
#define BKSP 8
#define ESC 27

// Unit labels
const char* lbls[] = { "KM", "M", "CM", "MM" };

void draw(int u_sel, int mode, char* buf)
{
    double val;
    double b_m; // base meters

    system("cls");

    // Parse input to double, default to 0 if empty
    val = (strlen(buf) > 0) ? atof(buf) : 0.0;

    // Convert input to base meters first
    if (u_sel == 0) { b_m = val * 1000.0; }
    else if (u_sel == 1) { b_m = val; }
    else if (u_sel == 2) { b_m = val / 100.0; }
    else { b_m = val / 1000.0; }

    printf("Unit Converter\n\n");
    printf("Input: %s %s\n", buf, lbls[u_sel]);
    printf("----------------------\n");
    printf("%.4f KM\n", b_m / 1000.0);
    printf("%.4f M\n", b_m);
    printf("%.2f CM\n", b_m * 100.0);
    printf("%.2f MM\n", b_m * 1000.0);
    printf("\n\n");

    // ASCII Frame for Unit Selection
    printf("Select Unit (TAB to switch, ENTER to pick):\n");
    printf("Press ESC to exit program\n");

    // Draw top border
    for (int i = 0; i < 4; i++)
    {
        printf("+----+\t");
    }
    printf("\n");

    // Draw content with selection marker
    for (int i = 0; i < 4; i++)
    {
        // If in selection mode and this is the selected index
        if (mode == 1 && u_sel == i)
        {
            printf("|>%s<|\t", lbls[i]);
        }
        else
        {
            printf("| %s |\t", lbls[i]);
        }
    }
    printf("\n");

    // Draw bottom border
    for (int i = 0; i < 4; i++)
    {
        printf("+----+\t");
    }
    printf("\n");
}

int main()
{
    char buf[32] = ""; // Input buffer
    int u = 1; // Current unit (0=KM, 1=M, 2=CM, 3=MM). Default M
    int m = 0; // Mode: 0 = Typing, 1 = Selecting Unit
    int k; // Key input
    int len;

    while (1)
    {
        draw(u, m, buf);

        // Pause for input
        k = _getch();

        if (k == ESC)
        {
            break;
        }

        // Handle Special Keys
        if (k == 0 || k == 224)
        {
            k = _getch();

            if (m == 1)
            {
                if (k == 75 && u > 0) { u--; }
                if (k == 77 && u < 3) { u++; }
            }
        }
        else if (k == TAB)
        {
            m = !m;
        }
        else if (k == ENT)
        {
            if (m == 1) { m = 0; } // Confirm selection, go back to typing
        }
        else if (m == 0)
        {
            // Typing Mode Logic
            len = strlen(buf);

            if (k == BKSP)
            {
                if (len > 0)
                {
                    buf[len - 1] = '\0';
                }
            }
            // Allow digits and one decimal point
            else if ((k >= '0' && k <= '9') || k == '.')
            {
                if (len < 30)
                {
                    if (k == '.' && strchr(buf, '.')) // Prevent multiple dots
                    {
                        continue;
                    }
                    buf[len] = (char)k;
                    buf[len + 1] = '\0';
                }
            }
        }
    }

    return 0;
}