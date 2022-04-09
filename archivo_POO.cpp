#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
const char *nombre_archivo= "archivo.dat";

class Estudiante{
	private: int codigo,telefono;
			 char nombre[50];
			 char apellido [50];
			 char direccion [50];
	public:
		Estudiante();
		void inscripcion();
		void abrir();
		void buscar();
		void modificar();
		void eliminar();
		void Setestudiante(int,int,char,char,char);
		int Getcodigo();
		int Gettelefono();
		void Getnombre();
		void Getapellido();
		void Getdireccion();
		
		
};

Estudiante::Estudiante(){
	codigo=0;
	telefono=0;
	nombre[50]=nombre[50];
	apellido[50]=apellido[50];
	direccion[50]=direccion[50];
}

void Estudiante::inscripcion(){
	char continuar;
	FILE* archivo = fopen("archivo.data","ab");
	
	Estudiante estudiante;
	string nombre, apellido, direccion;
	do{
		fflush(stdin);
		cout<<"Ingrese el codigo: ";
		cin>>estudiante.codigo;
		cin.ignore();
		cout<<"Ingrese el nombre: ";
		getline(cin,nombre);
		strcpy(estudiante.nombre,nombre.c_str());
		cout<<"Ingrese el apellido: ";
		getline(cin,apellido);
		strcpy(estudiante.apellido,apellido.c_str());
		cout<<"Ingrese la direccion: ";
		getline(cin,direccion);
		strcpy(estudiante.direccion,direccion.c_str());
		cout<<"Ingrese el telefono: ";
		cin>>estudiante.telefono;
		cin.ignore();
		fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		cout<<"Quieres ingresar otro esstudiante (s/n):";
		cin>>continuar;
	}while((continuar=='s')||(continuar=='S'));
	
	fclose(archivo);
}

void Estudiante::abrir(){
	system("Cls");
	FILE* archivo= fopen("archivo.data","rb");
	Estudiante estudiante;
	if(!archivo){
		archivo=fopen("archivo.data","w+b");
	}
	else{
		
		int registro=0;
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		cout<<"____________________________________________________________"<<endl;
		cout<<"id"<<"|"<<"Codigo"<<"|"<<"Nombre"<<"|"<<"Apellido"<<"|"<<"Direccion"<<"|"<<"Telefono"<<""<<endl;
		do{
			cout<<"__________________________________________________________________"<<endl;
			cout<<registro<<"|"<<estudiante.codigo<<"|"<<estudiante.nombre<<"|"<<estudiante.apellido<<"|"<<estudiante.direccion<<"|"<<estudiante.telefono<<endl;
			fread(&estudiante,sizeof(Estudiante),1,archivo);
			registro +=1;
			
		}while(feof(archivo)==0);
		cout<<endl;
	}
	fclose(archivo);
	
}

void Estudiante::buscar(){
	FILE* archivo=fopen("archivo.data","rb");
	
	int pos=0;
	cout<<"Que registro quieres ver:";
	cin>>pos;
	cout<<"---------------"<<pos<<"----------------"<<endl;
	fseek(archivo,pos* sizeof(Estudiante),SEEK_SET);
	Estudiante estudiante;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	cout<<"Codigo: "<<estudiante.codigo<<endl;
	cout<<"Nombre: "<<estudiante.nombre<<endl;
	cout<<"Apellido: "<<estudiante.apellido<<endl;
	cout<<"Direccion: "<<estudiante.direccion<<endl;
	cout<<"Telefono: "<<estudiante.telefono<<endl;
	cout<<endl;
	fclose(archivo);
}

void Estudiante::modificar(){
	FILE* archivo=fopen("archivo.data","r+b");
	int id;
	string nombre, apellido, direccion;
	Estudiante estudiante;
	cout<<"Ingrese el ID que quieres modificar: ";
	cin>>id;
	fseek(archivo,id* sizeof(Estudiante),SEEK_SET);
	cout<<"Ingrese el codigo: ";
	cin>>estudiante.codigo;
	cin.ignore();
	cout<<"Ingrese el nombre: ";
	getline(cin,nombre);
	strcpy(estudiante.nombre,nombre.c_str());
	cout<<"Ingrese el apellido: ";
	getline(cin,apellido);
	strcpy(estudiante.apellido,apellido.c_str());
	cout<<"Ingrese la direccion: ";
	getline(cin,direccion);
	strcpy(estudiante.direccion,direccion.c_str());
	cout<<"Ingrese el telefono: ";
	cin>>estudiante.telefono;
	fwrite(&estudiante,sizeof(Estudiante),1,archivo);
	fclose(archivo);
}

void Estudiante::eliminar(){
		FILE *archivo;
	archivo=fopen("archivo.data","rb");
	if(archivo==NULL)
		exit(1);
	cout<<"Ingresa el codigo a eliminar:";
	int cod;
	cin>>cod;
	Estudiante estudiante;
	FILE* nuevo;
	nuevo=fopen("archivo.tmp","ab");
	if(archivo==NULL)
		exit(1);
	int existe=0;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	while(!feof(archivo)){
		if(cod==estudiante.codigo){
			cout<<"Eliminando a:"<<"|"<<estudiante.codigo<<"|"<<estudiante.nombre<<"|"<<estudiante.apellido<<"|"<<estudiante.direccion<<"|"<<estudiante.telefono<<endl;
			existe=1;
		}
		else{
			fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		}
		fread(&estudiante,sizeof(Estudiante),1,archivo);
	}
	if(existe==0)
		cout<<"No existe alumno"<<endl;
	fclose(archivo);
	fclose(nuevo);
	
	remove("archivo.data");
	rename("archivo.tmp","archivo.data");
	
}

int main(){
	char eleccion;
	do{
		system("cls");
		fflush(stdin);
		Estudiante estudiante;
		int op=0;
		cout<<"Base de datos Estudiante:"<<endl;
		cout<<endl;
		cout<<"1.Ingresar estudiante"<<endl;
		cout<<"2.Mostrar estudiante"<<endl;
		cout<<"3.Buscar por registro"<<endl;
		cout<<"4.Modificar estudiante"<<endl;
		cout<<"5.Eliminar estudiante"<<endl;
		cout<<"6.Salir del programa"<<endl;
		cout<<"opcion: ";
		cin>>op;
		if((op>6) || (op<=0)){
			cout<<"Respuesta invalida intenta de nuevo";
		}
		switch(op){
			case 1:
				estudiante.inscripcion();
				break;
			case 2:
				estudiante.abrir();
				break;
			case 3:
				estudiante.buscar();
				break;
			case 4:
				estudiante.modificar();
				break;
			case 5:
				estudiante.eliminar();
				break;
			case 6:
				break;
			
		}
		
		cout<<"Deseas regresar al menu (s/n):";
		cin>>eleccion;		
	}while((eleccion=='s')||(eleccion=='S'));
	return 0;
}
