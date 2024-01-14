#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RESET "\x1B[0m"

void rgb_to_hex(int r, int g, int b, char *hex);
void rgb_to_hsl(int r, int g, int b, double *h, double *s, double *l);
void rgb_to_cmyk(int r, int g, int b, double *c, double *m, double *y, double *k);
void hexToRgb(char *hex, int *r, int *g, int *b);
void hslToRgb(double h, double s, double l, int *r, int *g, int *b);
void cmykToRgb(double c, double m, double y, double k, int *r, int *g, int *b);

int main()

{
    int ct;
    int r, g, b;
    double h, s, l;
    double c, m, y, k;
    char hex[7];
    int i, len, isValid;
    printf(" \n +++++++++++++++++++++++++++ \n \x1B[1m\e[1;5;32mWelcome to Color Converter.%s \n +++++++++++++++++++++++++++ \n ", RESET);
    printf("What type of color you want to convert? \n ..... Type 1 for RGB ..... \n ..... Type 2 for HEX ..... \n ..... Type 3 for HSL ..... \n ..... Type 4 for CMYK .... \n");
    printf("---------------------------\n");
    do
    {
        scanf("%d", &ct);
        if (ct < 1 || ct > 4)
        {
            printf("\x1b[1;31mInvalid Input%s\n", RESET);
        }
    } while (ct < 1 || ct > 4);
    switch (ct)
    {
    case 1:
        printf("Write the values in the RGB format: ");
        do
        {
            scanf("%d%d%d", &r, &g, &b);
            if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
            {
                printf("\x1b[1;31mInvalid RGB values.%s RGB values must be in the range of 0-255.\n", RESET);
            }
        } while (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255);
        rgb_to_hex(r, g, b, hex);
        rgb_to_hsl(r, g, b, &h, &s, &l);
        rgb_to_cmyk(r, g, b, &c, &m, &y, &k);
        break;

    case 2:
        printf("Write the HEX code: ");
        do
        {
            isValid = 1;
            scanf("%s", hex);
            len = strlen(hex);
            if (len != 6)
            {
                isValid = 0;
            }
            for (i = 1; i < len; i++)
            {
                if (!((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'a' && hex[i] <= 'f') || (hex[i] >= 'A' && hex[i] <= 'F')))
                {
                    isValid = 0;
                    break;
                }
            }
            if (isValid == 0)
            {
                printf("\x1b[1;31mInvalid HEX code.%s HEX code must be of 6 characters and each character must be in the range 0-f.\n", RESET);
            }
        } while (isValid == 0);
        hexToRgb(hex, &r, &g, &b);
        rgb_to_hsl(r, g, b, &h, &s, &l);
        rgb_to_cmyk(r, g, b, &c, &m, &y, &k);
        break;

    case 3:
        printf("Write the values in the HSL format: ");
        do
        {
            scanf("%lf%lf%lf", &h, &s, &l);
            if (h < 0 || h > 360 || s < 0 || s > 100 || l < 0 || l > 100)
            {
                printf("\x1b[1;31mInvalid HSL values.%s In HSL values H must be in the range of 0-360 and S & L must be in the range of 0-100.\n", RESET);
            }
        } while (h < 0 || h > 360 || s < 0 || s > 100 || l < 0 || l > 100);
        hslToRgb(h, s, l, &r, &g, &b);
        rgb_to_hex(r, g, b, hex);
        rgb_to_cmyk(r, g, b, &c, &m, &y, &k);
        break;

    case 4:
        printf("Write the values in the CMYK format: ");
        do
        {
            scanf("%lf%lf%lf%lf", &c, &m, &y, &k);
            if (c < 0 || c > 100 || m < 0 || m > 100 || y < 0 || y > 100 || k < 0 || k > 100)
            {
                printf("\x1b[1;31mInvalid CMYK values.%s CMYK values must be in the range of 0-100.\n", RESET);
            }
        } while (c < 0 || c > 100 || m < 0 || m > 100 || y < 0 || y > 100 || k < 0 || k > 100);
        cmykToRgb(c, m, y, k, &r, &g, &b);
        rgb_to_hex(r, g, b, hex);
        rgb_to_hsl(r, g, b, &h, &s, &l);
        break;
    }
    printf("Converted values are: \n");
    printf("RGB: (%d, %d, %d)\n", r, g, b);
    printf("HEX: #%s\n", hex);
    printf("HSL: (%.2f, %.2f, %.2f)\n", h, s, l);
    printf("CMYK: (%.2f, %.2f, %.2f, %.2f)\n", c, m, y, k);
    printf("Color: \x1b[48;2;%d;%d;%dm            \x1b[0m\n", r, g, b);

    return 0;
}

void rgb_to_hex(int r, int g, int b, char *hex)
{
    sprintf(hex, "%02X%02X%02X\0", r, g, b);
}

void rgb_to_hsl(int r, int g, int b, double *h, double *s, double *l)
{
    double red = (double)r / 255.0;
    double green = (double)g / 255.0;
    double blue = (double)b / 255.0;

    double max = fmax(fmax(red, green), blue);
    double min = fmin(fmin(red, green), blue);
    double delta = max - min;

    if (delta == 0)
    {
        *h = 0;
    }
    else if (max == red)
    {
        *h = 60 * fmod(((green - blue) / delta), 6);
        if (green < blue) 
        {
            *h += 360;
        }
    }
    else if (max == green)
    {
        *h = 60 * (((blue - red) / delta) + 2);
    }
    else 
    {
        *h = 60 * (((red - green) / delta) + 4);
    }

    *l = (max + min) / 2.0;

    if (delta == 0)
    {
        *s = 0;
    }
    else
    {
        *s = delta / (1.0 - fabs(2.0 * *l - 1.0));
    }

    *s *= 100;
    *l *= 100;
}

void rgb_to_cmyk(int r, int g, int b, double *c, double *m, double *y, double *k)
{
    double red = (double)r / 255.0;
    double green = (double)g / 255.0;
    double blue = (double)b / 255.0;

    *k = 1.0 - fmax(fmax(red, green), blue);

    if (*k == 1.0)
    {
        *c = 0;
        *m = 0;
        *y = 0;
    }
    else
    {
        *c = ((1.0 - red - *k) / (1.0 - *k))*100;
        *m = ((1.0 - green - *k) / (1.0 - *k))*100;
        *y = ((1.0 - blue - *k) / (1.0 - *k))*100;
    }
}

void hexToRgb(char *hex, int *r, int *g, int *b)
{
    int hexValue = strtol(hex, NULL, 16);
    *r = (hexValue >> 16) & 0xFF;
    *g = (hexValue >> 8) & 0xFF;
    *b = hexValue & 0xFF;
}

void hslToRgb(double h, double s, double l, int *r, int *g, int *b)
{
    if (h < 0)
    {
        h += 360;
    }
    if (h > 360)
    {
        h -= 360;
    }

    s /= 100;
    l /= 100;

    double c = (1 - fabs(2 * l - 1)) * s;

    double x = c * (1 - fabs(fmod(h / 60, 2) - 1));
    double m = l - c / 2;

    double tmpR, tmpG, tmpB;
    if (h < 60)
    {
        tmpR = c;
        tmpG = x;
        tmpB = 0;
    }
    else if (h < 120)
    {
        tmpR = x;
        tmpG = c;
        tmpB = 0;
    }
    else if (h < 180)
    {
        tmpR = 0;
        tmpG = c;
        tmpB = x;
    }
    else if (h < 240)
    {
        tmpR = 0;
        tmpG = x;
        tmpB = c;
    }
    else if (h < 300)
    {
        tmpR = x;
        tmpG = 0;
        tmpB = c;
    }
    else
    {
        tmpR = c;
        tmpG = 0;
        tmpB = x;
    }

    *r = round((tmpR + m) * 255);
    *g = round((tmpG + m) * 255);
    *b = round((tmpB + m) * 255);
}

void cmykToRgb(double c, double m, double y, double k, int *r, int *g, int *b)
{
    c /= 100;
    m /= 100;
    y /= 100;
    k /= 100;

    double tmpC = c * (1 - k) + k;
    double tmpM = m * (1 - k) + k;
    double tmpY = y * (1 - k) + k;

    *r = (1 - tmpC) * 255;
    *g = (1 - tmpM) * 255;
    *b = (1 - tmpY) * 255;
}