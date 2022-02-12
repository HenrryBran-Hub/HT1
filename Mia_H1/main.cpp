#include <QCoreApplication>
#include <iostream>
#include "iostream"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

//ESTRUCTURA DE EL ALUMNO TAMANIO
struct Alumno{
    int Id_Alumno;
    char CUI[13];
    char Nombre[25];
    char Carnet[10];
};

//ESTRUCTURA DE EL PROFESOR TAMANIO
struct Profesor{
    int Id_Profesor;
    char CUI[13];
    char Nombre[25];
    char Curso[25];
};

//VERIFICA SI ES NUMERO
int isNumber2(char caracter) {
    if (caracter >= '0' && caracter <= '9') {
        return 1;
    } else {
        return 0;
    }
}

//VERIFICA SI ES UNA CADENA DE NUMEROS
int isNumber(char cadena[]) {
    int resultado = 0;
    int contador = 0;
    while (cadena[contador] != '\0') {
        if (isNumber2(cadena[contador]) == 0) {
            resultado++;
        }
        contador++;
    }
    return resultado;
}

//METODO PARA LIMPIAR LA CADENA
void clear(char cadena[], int tamanio) {
    for (int i = 0; i < tamanio; i++) {
        cadena[i] = '\0';
    }
}

//METODO PARA VALIDAR QUE EXISTA EL ARCHIVO
int existsFile(char path[]) {
    FILE* f = NULL;
    f = fopen(path, "r");
    if (f == NULL)
        return 0;
    else {
        fclose(f);
        return 1;
    }
}

//METODO PARA VERIFICAR SI YA EXISTE EL ARCHIVO BINARIO
int creararchivo(){
    int a = existsFile("//home//ht1_201314439.dk");
    if (a == 1) {
        printf("\nCrearArchivo(): ERROR: Ya existe ruta/nombre del disco %s \n", "//home//ht1_201314439.dk");
        return 0;
    }else{
        return 1;
    }
}

//METODO PARA CREAR EL ARCHIVO
int creararchivoii(){
    if (creararchivo() != 0){
        int tamanio = 2 * (1024 * 1024);
        FILE* archivo = fopen("//home//ht1_201314439.dk", "ab");
        if (archivo != NULL) {
            int fin = tamanio / 1024;
            char buffer[1024];
            clear(buffer, 1024);
            int i = 0;
            while (i != fin) {
                fwrite(&buffer, 1024, 1, archivo);
                i++;
            }
            fclose(archivo);
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

//METODO PARA INGRESAR DATOS DE ALUMNO
int registroalumno(){
    Alumno alum;
    char comando[200];

    //OBTENEMOS LA INFORMACION
    clear(comando, 200);
    printf("\n\n");
    printf("%s\n", "Bienvenido REGISTRO ESTUDIANTE");
    printf("%s\n", "Ingrese Id_Estudiante (solo digitos)");
    printf(">>>>:~$ ");
    //LECTURA COMANDO
    scanf(" %[^\n]", comando);
    if (isNumber(comando) != 0){
        printf("\nregistroalumno(): ERROR: solo puede ingresar digitos en este campo");
        return 0;
    }

    alum.Id_Alumno = atoi(comando);
    clear(comando,200);
    printf("%s\n", "Ingrese CUI ");
    printf(">>>>:~$ ");
    //LECTURA COMANDO
    scanf(" %[^\n]", comando);
    strcpy(alum.CUI,comando);

    clear(comando,200);
    printf("%s\n", "Ingrese Nombre ");
    printf(">>>>:~$ ");
    //LECTURA COMANDO
    scanf(" %[^\n]", comando);
    strcpy(alum.Nombre,comando);

    clear(comando,200);
    printf("%s\n", "Ingrese Carnet ");
    printf(">>>>:~$ ");
    //LECTURA COMANDO
    scanf(" %[^\n]", comando);
    strcpy(alum.Carnet,comando);

    printf("\n\n DATOS RECOPILADOS\n\n");
    printf("Id_Alumno : %i\n", alum.Id_Alumno);
    printf("CUI : %s\n", alum.CUI);
    printf("Nombre : %s\n", alum.Nombre);
    printf("Carnet : %s\n", alum.Carnet);

    //LEEMOS EL ARCHIVO PARA SABER SI ESTA VACIO O TIENE INFORMACION EN EL
    FILE* archivo = fopen("//home//ht1_201314439.dk", "rb+");
    if (archivo != NULL) {
        bool aux = false;
        Alumno alumread;
        int posicion = 1048576;
        do{
            fseek(archivo, posicion, SEEK_SET);
            fread(&alumread, sizeof (Alumno), 1, archivo);
            if(alumread.Id_Alumno >= 0 && (strcmp(alumread.CUI,"\0") == 0) && (strcmp(alumread.Nombre,"\0") == 0) && (strcmp(alumread.Carnet,"\0") == 0)){
                fseek(archivo, posicion, SEEK_SET);
                fwrite(&alum, sizeof (Alumno), 1, archivo);
                printf("\nregistroalumno(): EXITO: informacion almacenada");
                fclose(archivo);
                return 1;
            }else{
                if (posicion >= 1048576 && posicion < 2097084){
                    posicion += sizeof (Alumno) +1;
                }else{
                    aux = true;
                }
            }
        }while(aux != true);
        fclose(archivo);
        printf("\nregistroalumno(): ERROR: NO se guardo la informacion ya no hay espacio disponible");
        return 0;
    }else{
        printf("\nregistroalumno(): ERROR: NO se guardo la informacion posible daño de archivo");
        return 0;
    }
}

//METODO PARA INGRESAR DATOS DE PROFESOR
int registroprofesor(){
    Profesor prof;
    char comando[200];

    //OBTENEMOS LA INFORMACION
    clear(comando, 200);
    printf("\n\n");
    printf("%s\n", "Bienvenido REGISTRO PROFESRO");
    printf("%s\n", "Ingrese Id_profesor (solo digitos)");
    printf(">>>>:~$ ");
    //LECTURA COMANDO
    scanf(" %[^\n]", comando);
    if (isNumber(comando) != 0){
        printf("\nregistroprofesor(): ERROR: solo puede ingresar digitos en este campo");
        return 0;
    }

    prof.Id_Profesor = atoi(comando);
    clear(comando,200);
    printf("%s\n", "Ingrese CUI ");
    printf(">>>>:~$ ");
    //LECTURA COMANDO
    scanf(" %[^\n]", comando);
    strcpy(prof.CUI,comando);

    clear(comando,200);
    printf("%s\n", "Ingrese Nombre ");
    printf(">>>>:~$ ");
    //LECTURA COMANDO
    scanf(" %[^\n]", comando);
    strcpy(prof.Nombre,comando);

    clear(comando,200);
    printf("%s\n", "Ingrese Curso ");
    printf(">>>>:~$ ");
    //LECTURA COMANDO
    scanf(" %[^\n]", comando);
    strcpy(prof.Curso,comando);

    printf("\n\n DATOS RECOPILADOS\n\n");
    printf("Id_Profesor : %i\n", prof.Id_Profesor);
    printf("CUI : %s\n", prof.CUI);
    printf("Nombre : %s\n", prof.Nombre);
    printf("Curso : %s\n", prof.Curso);

    //LEEMOS EL ARCHIVO PARA SABER SI ESTA VACIO O TIENE INFORMACION EN EL
    FILE* archivo = fopen("//home//ht1_201314439.dk", "rb+");
    if (archivo != NULL) {
        bool aux = false;
        Profesor profread;
        int posicion = 0;
        do{
            fseek(archivo, posicion, SEEK_SET);
            fread(&profread, sizeof (Profesor), 1, archivo);
            if(profread.Id_Profesor >= 0 && (strcmp(profread.CUI,"\0") == 0) && (strcmp(profread.Nombre,"\0") == 0) && (strcmp(profread.Curso,"\0") == 0)){
                fseek(archivo, posicion, SEEK_SET);
                fwrite(&prof, sizeof (Profesor), 1, archivo);
                printf("\nregistroprofesor(): EXITO: informacion almacenada");
                fclose(archivo);
                return 1;
            }else{
                if (posicion < 1048508){
                    posicion += sizeof (Profesor) -1;
                }else{
                    aux = true;
                }
            }
        }while(aux != true);
        fclose(archivo);
        printf("\nregistroprofesor(): ERROR: NO se guardo la informacion ya no hay espacio disponible");
        return 0;
    }else{
        printf("\nregistroprofesor(): ERROR: NO se guardo la informacion posible daño de archivo");
        return 0;
    }
}

//IMPRIMIR REGISTROS
int imprimir(){
    //IMPRIMIMOS DATOS PROFESORES
    FILE* archivo = fopen("//home//ht1_201314439.dk", "rb+");
    if (archivo != NULL) {
        bool aux = false;
        Profesor profread;
        int posicion = 0;
        int contador = 0;
        printf("\n\n DATOS RECOPILADOS DE PROFESOR \n\n");
        do{
            fseek(archivo, posicion, SEEK_SET);
            fread(&profread, sizeof (Profesor), 1, archivo);
            if(profread.Id_Profesor >= 0 && (strcmp(profread.CUI,"\0") != 0) && (strcmp(profread.Nombre,"\0") != 0) && (strcmp(profread.Curso,"\0") != 0)){
                printf("\n-------------------------------------------\n");
                printf("No. Registro:  %i\n",contador);
                printf("Id_Profesor : %i\n", profread.Id_Profesor);
                printf("CUI : %.13s\n", profread.CUI);
                printf("Nombre : %.25s\n", profread.Nombre);
                printf("Curso : %.25s\n", profread.Curso);
                printf("\n-------------------------------------------\n");
                posicion += sizeof (Profesor) -1;
                contador++;
            }else{
                aux = true;
            }
        }while(aux != true);
        //IMPRIMIMOS DATOS DE LOS ALUMNOS
        Alumno alumread;
        aux = false;
        posicion = 1048576;
        contador = 0;
        printf("\n\n /////////////////////////////////// \n\n");
        printf("\n\n DATOS RECOPILADOS DE ALUMNOS \n\n");
        do{
            fseek(archivo, posicion, SEEK_SET);
            fread(&alumread, sizeof (Alumno), 1, archivo);
            if(alumread.Id_Alumno >= 0 && (strcmp(alumread.CUI,"\0") != 0) && (strcmp(alumread.Nombre,"\0") != 0) && (strcmp(alumread.Carnet,"\0") != 0)){
                printf("\n-------------------------------------------\n");
                printf("No. Registro:  %i\n",contador);
                printf("Id_Alumno : %i\n", alumread.Id_Alumno);
                printf("CUI : %.13s\n", alumread.CUI);
                printf("Nombre : %.25s\n", alumread.Nombre);
                printf("Carnet : %.10s\n", alumread.Carnet);
                printf("\n-------------------------------------------\n");
                posicion += sizeof (Alumno) +1;
                contador++;
            }else{
                aux = true;
            }
        }while(aux != true);
        fclose(archivo);
        return 1;
    }else{
        printf("\nimprimir(): ERROR: no se puedo abrir el archivo");
        return 0;
    }
}

//MENU DE SELECCION DE OPCIONES
void menu(){
    int opcion;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do{
        try{
        printf("\n\n");
        printf("%s\n", "Bienvenido");
        printf("%s\n", "Ingresar opcion:");
        printf("%s\n", "1. Registro De Alumno");
        printf("%s\n", "2. Registro De Profesor");
        printf("%s\n", "3. Imprimir Registros");
        printf("%s\n", "4. Salir");
        printf(">>>>:~$ ");
        //LECTURA COMANDO DIGITO
        cin >> opcion;
        aux = true;
         //SELECCION DE OPCION
        int salida;
        switch(opcion){
            case 1 :
                printf("%s\n\n", "1. Registro De Alumno\n");                
                salida = registroalumno();
                if (salida == 1){
                    printf("\nmenu(): %s\n", "Datos almacenados con exito\n");
                }else{
                    printf("\nmenu(): %s\n", "Error no se puedo almacenar la informacion\n");
                }
                aux = false;
                break;
            case 2:
                printf("%s\n\n", "2. Registro De Profesor\n");
                salida = registroprofesor();
                if (salida == 1){
                    printf("\nmenu(): %s\n", "Datos almacenados con exito\n");
                }else{
                    printf("\nmenu(): %s\n", "Error no se puedo almacenar la informacion\n");
                }
                aux = false;
                break;
            case 3 :
                printf("%s\n\n", "3. Imprimir Registros\n");
                salida = imprimir();
                if (salida == 1){
                    printf("\nmenu(): %s\n", "Datos impresos con exito\n");
                }else{
                    printf("\nmenu(): %s\n", "Error no se puedo imprimir los datos\n");
                }
                aux = false;
                break;
            case 4:
                printf("%s\n\n", "4. Salir\n");
                aux = true;
                break;
            default:
                //TOMA DE ERRORES DE OPCIONES DE 1 A 4
                aux = false;
                printf("%s\n\n", "opciones validas de 1-4!!!!\n");
                break;

       }
       //TOMA DE ERRORES DE DIGITOS
       }catch(std::ios_base::failure &fail) {
            aux = false;
            printf("%s\n\n", "Inserte solo digitos!!!!");
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    }while(aux == false);
}

int main()
{
    int i = creararchivoii();
    if( i == 1){
        printf("\nCrearArchivoii(): Se ha creado el archivo %s por primera vez en el sistema \n", "//home//ht1_201314439.dk");
    }else{
        printf("\nCrearArchivoii(): Se sobreescribira el archivo %s \n", "//home//ht1_201314439.dk");
    }
    menu();
    return 0;
}
