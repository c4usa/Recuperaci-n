#include <stdio.h> 
#include <string.h>

int nombreExiste(char nombres[6][50], int cantidad, char nombre[])
{
    for (int i = 0; i < cantidad; i++)
    {
        if (strcmp(nombres[i], nombre) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int leerEntero(int minimo, int maximo)
{
    int valor;
    int resultado;
    do
    {
        resultado = scanf("%d", &valor);
        while (getchar() != '\n')
            ;
        if (resultado != 1 || valor < minimo || valor > maximo)
        {
            printf("Entrada inválida. Ingrese un número entre %d y %d: ", minimo, maximo);
        }
    } while (resultado != 1 || valor < minimo || valor > maximo);
    return valor;
}

void ingresarCompetidores(char nombres[6][50], int puntos[6], int total)
{
    char nombreTemporal[50];
    int i = 0;
    while (i < total)
    {
        printf("Ingrese el nombre del boxeador #%d: ", i);
        if (fgets(nombreTemporal, sizeof(nombreTemporal), stdin) == NULL)
        {
            continue;
        }
        nombreTemporal[strcspn(nombreTemporal, "\n")] = '\0';
        if (strlen(nombreTemporal) == 0)
        {
            printf("El nombre no puede estar vacío.\n");
        }
        else if (nombreExiste(nombres, i, nombreTemporal))
        {
            printf("Ese nombre ya fue ingresado. Intente con otro.\n");
        }
        else
        {
            strcpy(nombres[i], nombreTemporal);
            puntos[i] = 0;
            i++;
        }
    }
}
void combatesIniciales(char nombres[6][50], int puntos[6], int total)
{
    for (int i = 0; i < total; i += 2)
    {
        int ganador;
        int margen;
        int indiceGanador;
        printf("\nCombate entre %s y %s\n", nombres[i], nombres[i + 1]);
        printf("Ingrese 1 si gana %s o 2 si gana %s: ", nombres[i], nombres[i + 1]);
        ganador = leerEntero(1, 2);
        if (ganador == 1)
        {
            indiceGanador = i;
        }
        else
        {
            indiceGanador = i + 1;
        }
        printf("¿Por cuántos puntos ganó?: ");
        margen= leerEntero(1,100);
        puntos[indiceGanador] = puntos[indiceGanador] + margen;
    }
}

int desempate(int indices[], int count, char nombres[6][50])
{
    while (count > 2)
    {
        int a = indices[0];
        int b = indices[1];
        int ganador;
        printf("\nDesempate entre %s y %s\n", nombres[a], nombres[b]);
        printf("Ingrese 1 si gana %s o 2 si gana %s: ", nombres[a], nombres[b]);
        ganador = leerEntero(1, 2);
        if (ganador == 1)
        {
            indices[0] = a;
        }
        else
        {
            indices[0] = b;
        }
        {
            int j;
            for (j = 2; j < count; j++)
            {
                indices[j - 1] = indices[j];
            }
            count = count - 1;
        }
    }
    return count;
}

int main()
{
    const int total = 6;
    char nombres[6][50];
    int puntos[6];
    int i;
    ingresarCompetidores(nombres, puntos, total);
    combatesIniciales(nombres, puntos, total);
    int max1 = -1;
    for (int i = 0; i < total; i++)
    {
        if (puntos[i] > max1)
        {
            max1 = puntos[i];
        }
    }
    int emp1[6];
    int cnt1 = 0;
    for (i = 0; i < total; i++)
    {
        if (puntos[i] == max1)
        {
            emp1[cnt1] = i;
            cnt1 = cnt1 + 1;
        }
    }
    if (cnt1 > 2)
    {
        cnt1 = desempate(emp1, cnt1, nombres);
    }

    int finalistas[2];
    if (cnt1 == 2)
    {
        finalistas[0] = emp1[0];
        finalistas[1] = emp1[1];
    }
    else
    {
        finalistas[0] = emp1[0];
        int max2 = -1;
        for (i = 0; i < total; i++)
        {
            if (i != finalistas[0] && puntos[i] > max2)
            {
                max2 = puntos[i];
            }
        }
        int emp2[6];
        int cnt2 = 0;
        for (i = 0; i < total; i++)
        {
            if (i != finalistas[0] && puntos[i] == max2)
            {
                emp2[cnt2] = i;
                cnt2 = cnt2 + 1;
            }
        }
        if (cnt2 > 1)
        {
            cnt2 = desempate(emp2, cnt2, nombres);
        }
        finalistas[1] = emp2[0];
    }

    int resultado;
    printf("\nFINAL: %s vs %s\n", nombres[finalistas[0]], nombres[finalistas[1]]);
    printf("Ingrese 1 si gana %s o 2 si gana %s: ", nombres[finalistas[0]], nombres[finalistas[1]]);
    resultado = leerEntero(1, 2);
    if (resultado == 1)
    {
        printf("¡El ganador del torneo es: %s!\n", nombres[finalistas[0]]);
    }
    else
    {
        printf("¡El ganador del torneo es: %s!\n", nombres[finalistas[1]]);
    }
    return 0;
}
