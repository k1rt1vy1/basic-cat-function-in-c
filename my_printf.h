#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

void my_printf(const char *format, ...)
{
    va_list args; // naming the list
    va_start(args, format);

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'd')
            {
                int num = va_arg(args, int);
                if (num < 0)
                {
                    write(1, "-", 1);
                    num = num * -1;
                }

                char buff[10]; // taking the max size of integer
                int i = 0;

                while (num != 0)
                {
                    buff[i++] = (num % 10) + '0'; // as the ASCII value of '0' is 48, and hence every number (0-9) has some ASCII value
                    num = num / 10;
                }
                while (i > 0)
                {
                    write(1, &buff[--i], 1);
                }
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);
                size_t size = strlen(str);

                write(1, str, size);
                format++;
            }
            else if (*format == 'c')
            {
                char c = va_arg(args, int);
                write(1, &c, 1);
                format++;
            }
            else if (*format == 'f')
            {
                double num = va_arg(args, double);
                if (num < 0)
                {
                    write(1, "0", 1);
                    num = num * -1;
                }

                int intPart = (int)num;
                int decPart = (int)((num - intPart) * 1000000); // taking max precision in mind
                int integer[15], decimal[15];
                int i = 0;
                while (intPart != 0)
                {
                    integer[i++] = (intPart % 10) + '0';
                    intPart = intPart / 10;
                }
                while (i > 0)
                {
                    write(1, &integer[--i], 1);
                }

                write(1, ".", 1);

                while (decPart != 0)
                {
                    decimal[i++] = (decPart % 10) + '0';
                    decPart = decPart / 10;
                }
                while (i > 0)
                {
                    write(1, &decimal[--i], 1);
                }
            }
            else if (*format == '.')
            {
                format++;                // here the pointer points at the precision number
                int prec = *format - 48; // as the ASCII value of '0' is 48;
                format++;                // now the pointer points at 'f'
                double num = va_arg(args, double);

                int intPart = (int)num;
                int decPart = (int)((num - intPart) * pow(10, prec));
                int integer[15];
                int decimal[15];
                int i = 0;
                while (intPart != 0)
                {
                    integer[i++] = (intPart % 10) + '0';
                    intPart = intPart / 10;
                }
                while (i > 0)
                {
                    write(1, &integer[--i], 1);
                }

                write(1, ".", 1);

                while (decPart != 0)
                {
                    decimal[i++] = (decPart % 10) + '0';
                    decPart = decPart / 10;
                }
                while (i > 0)
                {
                    write(1, &decimal[--i], 1);
                }
            }
            else if (*format == 'l')
            {
                format++;
                if (*format == 'd')
                {
                    long num = va_arg(args, long);
                    if (num < 0)
                    {
                        write(1, "-", 1);
                        num = num * - 1;
                    }

                    char buff[10]; // taking the max size of integer
                    int i = 0;

                    while (num != 0)
                    {
                        buff[i++] = (num % 10) + '0'; // as the ASCII value of '0' is 48, and hence every number (0-9) has some ASCII value
                        num = num / 10;
                    }
                    while (i > 0)
                    {
                        write(1, &buff[--i], 1);
                    }
                }
            }
            else if (*format == '%')
            {
                write(1, format, 1);
                format++;
            }
        }
        else
        {
            write(1, format, 1);
        }
        format++;
    }
    va_end(args);
}
