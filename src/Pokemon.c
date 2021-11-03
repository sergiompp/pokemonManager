#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"
#include <assert.h>
#include <pthread.h>
#include <unistd.h>


/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de constantes                                                 */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de tipos                                                      */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de estructuras                                                */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de variables                                                  */
/*---------------------------------------------------------------------------*/

pthread_mutex_t mutex;
/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de macros                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Prototipos de las funciones estÃ¡ticas                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* DefiniciÃ³n de las funciones                                               */
/*---------------------------------------------------------------------------*/


int int_data_read(){  
  int numeroIntroducido=0;
  size_t numero_bytes=0;
  char *linea=NULL;
    
  getline(&linea,&numero_bytes,stdin);

  numeroIntroducido=atoi(linea);

  free(linea);
  linea=NULL;
  return numeroIntroducido;
}
 
int int_data_read_control(int *ptr_data){ 
  int numeroIntroducido=0;
  size_t numero_bytes=0;
  char *linea=NULL;
  int control=0;
  control=getline(&linea,&numero_bytes,stdin);

  numeroIntroducido=atoi(linea);

  free(linea);
  linea=NULL;
  *ptr_data=control;
  return numeroIntroducido;
}

char *char_data_read(){
  
  int bytes_leidos;
  size_t numero_bytes=0;
  char *cadena=NULL;
  bytes_leidos=getline(&cadena,&numero_bytes,stdin);
   
  if(cadena[bytes_leidos-1]=='\n'){
    cadena[bytes_leidos-1]='\0';
  }
    
  return cadena;
}

char *char_read(){
  
  int bytes_leidos;
  size_t numero_bytes=1;
  char *cadena=(char*)malloc(sizeof(char));
  bytes_leidos=getline(&cadena,&numero_bytes,stdin);
   
  if(cadena[bytes_leidos-1]=='\n'){
    cadena[bytes_leidos-1]='\0';
  }
    
  return cadena;
}

int salir(){
  char *si = "s ";
  char *no = "N ";
  char *opcion;
  int opcion_si;
  int opcion_no;
  do{
    printf("¿Está seguro de que desea salir del programa?[s/N]: ");
    opcion =char_read();
    opcion_si = memcmp(si, opcion, 1);
    opcion_no = memcmp(no, opcion, 1);
    if(opcion_si !=0 && opcion_no!=0){
      free(opcion);
    }
  }

  while(opcion_si !=0 && opcion_no!=0 );
    free(opcion); 
    if(opcion_si == 0)
    {
      return opcion_si;
    }

    if(opcion_no == 0){
      opcion_no = -1;
      return opcion_no;
    }
  return 0;
}


int d_salir(){
  
  char *d = "d ";
  char *opcion;
  int d_salir;
 
  opcion = char_data_read();
  d_salir = memcmp(d, opcion, 1); 

  if(d_salir ==0  ){
    return 0;
  }
  return -1;
}

int borrar_lista(struct nodo** ptr_cabeza){
   
  if(ptr_cabeza == NULL){
    return -1;
  }
  
  struct nodo* cabeza = *ptr_cabeza;
  
  struct nodo* aux = NULL;
  
  for(; cabeza!=NULL; cabeza=aux){
    aux = cabeza->next;
    free(cabeza->pokemon.s_name);
    free(cabeza);
    
  }
  *ptr_cabeza = NULL;
  
  return 0;
}


int insertar_pokemon(struct nodo** ptr){
  
  if(ptr == NULL){
    return -1;
  }
  int vida;
  int ataque[2];
  int defensa[2];
  int velocidad;
  int identificador;
  char* nombre;
  int tamano_nombre;
  char *str1;
  str1 = "Pepe";
  int resultado;
  
  printf("\tInsertando Pokemon\n");
  printf("\t\tDame el ID del Pokemon: ");
  identificador=int_data_read();
  printf("\t\tDame el nombre del Pokemon: ");
  nombre=char_data_read();
  resultado = strncmp(str1, nombre, 4);
  if(resultado == 0) {
    printf("\t\tNombre de pokemon no valido");
    return 0;
  } 

  tamano_nombre=sizeof(&nombre)-1;
  printf("\t\tDame la vida: ");
  vida=int_data_read();
  printf("\t\tDame el ataque: ");
  ataque[T_NORMAL]=int_data_read();
  printf("\t\tDame la defensa: ");
  defensa[T_NORMAL]=int_data_read();
  printf("\t\tDame el ataque especial: ");
  ataque[1]=int_data_read();
  printf("\t\tDame la defensa especial: ");
  defensa[1]=int_data_read(); 
  printf("\t\tDame la velocidad: ");
  velocidad=int_data_read();
  
  
  
  struct nodo* aux = malloc(sizeof(struct nodo));
  aux->pokemon.characteristics.hp = vida;
  aux->pokemon.characteristics.attack[T_NORMAL]= ataque[T_NORMAL];
  aux->pokemon.characteristics.attack[T_SPECIAL]= ataque[T_SPECIAL];
  aux->pokemon.characteristics.defense[T_NORMAL]= defensa[T_NORMAL];
  aux->pokemon.characteristics.defense[T_SPECIAL]= defensa[T_SPECIAL];
  aux->pokemon.characteristics.speed = velocidad;
  aux->pokemon.id = identificador;
  aux->pokemon.s_name = nombre;
  aux->pokemon.size_name = tamano_nombre;
  aux->next = NULL;

  struct nodo* cabeza = *ptr;
  aux->next=NULL;
  
  
  if(cabeza == NULL){
    *ptr = aux;

  } else {
    aux->next = cabeza;
    *ptr = aux;
    
  }
  
  return 0;
}


int mostrar_pokemons(struct nodo* cabeza){
  if (cabeza == NULL){
    return -1;
  }

  printf("\t\t\t================================\n");
  printf("\t\t\t|  ID|    Nomb. |Vida|Ata.|Def.|\n");
  printf("\t\t\t================================\n");
  char nombre[10];
    
  while(cabeza!=NULL){
    strncpy( nombre,cabeza->pokemon.s_name,10);
    printf("\t\t\t|  %d|  %s |  %d |  %d |  %d |\n", cabeza->pokemon.id,nombre, cabeza->pokemon.characteristics.hp, 
    cabeza->pokemon.characteristics.attack[T_NORMAL], cabeza->pokemon.characteristics.defense[T_NORMAL]);
    printf("\t\t\t================================\n"); 
    cabeza = cabeza->next;
  }
  return 0; 
}


int mostrar_pokemon_id(struct nodo* cabeza){
  if(cabeza == NULL){
    return -1;
  } 
  printf("\t\tIntroduzca el ID del Pokemon que quiere mostrar: " );
  int id = int_data_read();

  struct nodo * aux = NULL;
  aux = cabeza;

  if (aux->pokemon.id == id){
    
    printf("\t\t\t= Información completa de Pokemon\n");
  
    printf("\t\t\t= id: %d\n",aux->pokemon.id);
    printf("\t\t\t= vida: %d\n", aux->pokemon.characteristics.hp);
    printf("\t\t\t= nombre: %s\n",aux->pokemon.s_name);
    printf("\t\t\t= ataque: %d\n",aux->pokemon.characteristics.attack[T_NORMAL]);
    printf("\t\t\t= defensa: %d\n",aux->pokemon.characteristics.defense[T_NORMAL]);
    printf("\t\t\t= s ataque: %d\n",aux->pokemon.characteristics.attack[T_SPECIAL]);
    printf("\t\t\t= s defensa: %d\n",aux->pokemon.characteristics.defense[T_SPECIAL]);
    printf("\t\t\t= velocidad: %d\n",aux->pokemon.characteristics.speed);
    
  } else {

    while(aux!=NULL && aux->pokemon.id != id){
      aux = aux->next;
    }

    if(aux==NULL){
      printf("Pokemon no encontrado");
      return -1;
    }

    printf("\t\t\t= Información completa de Pokemon\n");
    printf("\t\t\t= id: %d\n",aux->pokemon.id);
    printf("\t\t\t= vida: %d\n", aux->pokemon.characteristics.hp);
    printf("\t\t\t= nombre: %s\n",aux->pokemon.s_name);
    printf("\t\t\t= ataque: %d\n",aux->pokemon.characteristics.attack[T_NORMAL]);
    printf("\t\t\tdefensa: %d\n",aux->pokemon.characteristics.defense[T_NORMAL]);
    printf("\t\t\ts ataque: %d\n",aux->pokemon.characteristics.attack[T_SPECIAL]);
    printf("\t\t\ts defensa: %d\n",aux->pokemon.characteristics.defense[T_SPECIAL]);
    printf("\t\t\tvelocidad: %d\n",aux->pokemon.characteristics.speed);
    
  }
  return 0;
}

struct nodo * borrar_pokemon_id(struct nodo *ptr_cabeza){
  
  if(ptr_cabeza == NULL){
    printf("\t\tLa lista está vacía.\n");
    return NULL;
  }
  
  printf("\t\tTeclee el ID del Pokemon que quieres borrar: ");
  int id = int_data_read();
  struct nodo * aux = NULL;
  struct nodo * aux2 =NULL;

  aux = ptr_cabeza; 
  aux2 = aux->next;
  
  if(aux->pokemon.id == id){
    aux2  = aux->next;
    free(aux->pokemon.s_name);
    free(aux);
    aux=NULL;
    return aux2;    
  }
        
  while(aux2!=NULL && aux2->pokemon.id != id){  
    aux = aux->next;
    aux2= aux2->next;
  }

  if(aux2==NULL){
    printf("Pokemon no encontrado");
    return ptr_cabeza;
  }
 
  aux->next = aux2->next;
  free(aux2->pokemon.s_name);
  free(aux2);
      
  return ptr_cabeza;
}   

int modificar_pokemon_id(struct nodo* cabeza){
  
  int vida;
  int ataque[2];
  int defensa[2];
  int velocidad;
  char* nombre;
  int tamano_nombre;
  int identificador;

  if(cabeza == NULL){
    return -1;
  } 
  printf("\t\tIntroduzca el ID del Pokemon que quiere modificar: " );
  int id = int_data_read();

  struct nodo * aux = NULL;
  aux = cabeza;
  
  if (aux->pokemon.id == id){
    free(aux->pokemon.s_name);
    printf("\t\tDame el ID del Pokemon: ");
    identificador=int_data_read();
    printf("\t\tDame el nombre del Pokemon: ");
    nombre=char_data_read();
    tamano_nombre=sizeof(&nombre)-1;
    printf("\t\tDame la vida: ");
    vida=int_data_read();
    printf("\t\tDame el ataque: ");
    ataque[T_NORMAL]=int_data_read();
    printf("\t\tDame la defensa: ");
    defensa[T_NORMAL]=int_data_read();
    printf("\t\tDame el ataque especial: ");
    ataque[1]=int_data_read();
    printf("\t\tDame la defensa especial: ");
    defensa[1]=int_data_read(); 
    printf("\t\tDame la velocidad: ");
    velocidad=int_data_read();
  
    aux->pokemon.characteristics.hp = vida;
    aux->pokemon.characteristics.attack[T_NORMAL]= ataque[T_NORMAL];
    aux->pokemon.characteristics.attack[T_SPECIAL]= ataque[T_SPECIAL];
    aux->pokemon.characteristics.defense[T_NORMAL]= defensa[T_NORMAL];
    aux->pokemon.characteristics.defense[T_SPECIAL]= defensa[T_SPECIAL];
    aux->pokemon.characteristics.speed = velocidad;
    aux->pokemon.id = identificador;
    aux->pokemon.s_name = nombre;
    aux->pokemon.size_name = tamano_nombre; 
  
  } else {
    
    while(aux!=NULL && aux->pokemon.id != id){
      aux = aux->next;
    }

    if(aux==NULL){
      printf("\t\t\tPokemon no encontrado\n");
      return 0;
    }
    
    free(aux->pokemon.s_name);
    printf("\t\tDame el ID del Pokemon: ");
    identificador=int_data_read();
    printf("\t\tDame el nombre del Pokemon: ");
    nombre=char_data_read();
    tamano_nombre=sizeof(&nombre)-1;
    printf("\t\tDame la vida: ");
    vida=int_data_read();
    printf("\t\tDame el ataque: ");
    ataque[T_NORMAL]=int_data_read();
    printf("\t\tDame la defensa: ");
    defensa[T_NORMAL]=int_data_read();
    printf("\t\tDame el ataque especial: ");
    ataque[1]=int_data_read();
    printf("\t\tDame la defensa especial: ");
    defensa[1]=int_data_read(); 
    printf("\t\tDame la velocidad: ");
    velocidad=int_data_read();
    
    aux->pokemon.characteristics.hp = vida;
    aux->pokemon.characteristics.attack[T_NORMAL]= ataque[T_NORMAL];
    aux->pokemon.characteristics.attack[T_SPECIAL]= ataque[T_SPECIAL];
    aux->pokemon.characteristics.defense[T_NORMAL]= defensa[T_NORMAL];
    aux->pokemon.characteristics.defense[T_SPECIAL]= defensa[T_SPECIAL];
    aux->pokemon.characteristics.speed = velocidad;
    aux->pokemon.id = identificador;
    aux->pokemon.s_name = nombre;
    aux->pokemon.size_name = tamano_nombre;
  }
  return 0;
}

int contar_pokemons(struct nodo *cabeza){
  struct nodo *aux=NULL;
  int contador=0;
  for(aux=cabeza;aux!=NULL;aux=aux->next){
    
  }
  return contador;
}

void exportar(struct nodo* cabeza) {

  printf("Elige el nombre del fichero:");
  char *nombre_fichero = char_data_read();
  FILE *ptr_pokemon = fopen(nombre_fichero, "wb");
  if (ptr_pokemon == NULL) {
    perror("fopen writing");
  } else {
    int numero_pokemons=0;
    numero_pokemons=contar_pokemons(cabeza);
    assert(fwrite(&numero_pokemons, sizeof(int), 1, ptr_pokemon) == 1) ;
    struct nodo* aux=NULL;
    
    for(aux=cabeza;aux!=NULL; aux=aux->next){
      assert(fwrite(&aux->pokemon.characteristics.hp, sizeof(int), 1, ptr_pokemon) == 1);
      assert(fwrite(&aux->pokemon.characteristics.attack[T_NORMAL], sizeof(int), 1, ptr_pokemon) == 1);
      assert(fwrite(&aux->pokemon.characteristics.attack[T_SPECIAL], sizeof(int), 1, ptr_pokemon) == 1);
      assert(fwrite(&aux->pokemon.characteristics.defense[T_NORMAL], sizeof(int), 1, ptr_pokemon) == 1);
      assert(fwrite(&aux->pokemon.characteristics.defense[T_SPECIAL], sizeof(int), 1, ptr_pokemon) == 1);
      assert(fwrite(&aux->pokemon.characteristics.speed , sizeof(int), 1, ptr_pokemon) == 1);
      assert(fwrite(&aux->pokemon.id, sizeof(int), 1, ptr_pokemon) == 1);
      int name=strlen(aux->pokemon.s_name);
      assert(fwrite(&name, sizeof(int), 1, ptr_pokemon) == 1);
      assert(fwrite(aux->pokemon.s_name, sizeof(char), name, ptr_pokemon) == name);
    }
    fclose(ptr_pokemon);

    printf("archivo exportado con éxito");
    free(nombre_fichero);
  }
}

char* importar_string(FILE *f2){

  int tamano = 0;
  char *prueba=NULL;
  int leidos = fread(&tamano, sizeof(int), 1, f2);
  if (leidos != 1 || tamano < 0) {
    fprintf(stderr, "Error de lectura\n");
  } else {
    prueba= (char *) calloc(tamano+1, sizeof(char)); 
    leidos=fread(prueba, sizeof(char), tamano, f2);
    if (leidos != tamano) {
      fprintf(stderr, "Error de lectura\n");
    } else {
    }
  }
  return prueba;
}

struct nodo *importar_nodo(FILE *f2){
  
  struct nodo *aux = (struct nodo *) calloc (1,sizeof(struct nodo));
  
  fread(&aux->pokemon.characteristics.hp, sizeof(int), 1, f2);
  fread(&aux->pokemon.characteristics.attack[T_NORMAL], sizeof(int), 1, f2);
  fread(&aux->pokemon.characteristics.attack[T_SPECIAL], sizeof(int), 1, f2);
  fread(&aux->pokemon.characteristics.defense[T_NORMAL],sizeof(int), 1, f2);
  fread(&aux->pokemon.characteristics.defense[T_SPECIAL],sizeof(int), 1, f2);
  fread(&aux->pokemon.characteristics.speed ,sizeof(int), 1, f2);
  fread(&aux->pokemon.id,sizeof(int), 1, f2);

  aux->pokemon.s_name=importar_string(f2);
  return aux;
}

struct nodo* importar(struct nodo *cabeza){
  int i=0;
  printf("Elije el nombre del fichero a importar: ");
  char *nombre_fichero = char_data_read();
  FILE *f2 = fopen(nombre_fichero, "rb");
  if (f2 == NULL) {
    printf("archivo no encontrado");
    return cabeza;
  } else {
    int n_nodos_leer=0;
    fread(&n_nodos_leer, sizeof(int),1,f2);
    for(i=0; i<n_nodos_leer; i++){ 
      if(cabeza==NULL){
        cabeza=importar_nodo(f2);
      } else {
        struct nodo *aux;
        aux=importar_nodo(f2);
        aux->next=cabeza;
        cabeza=aux;
      }
    }

    fclose(f2);
  }

  printf("archivo exportado con éxito");
  free(nombre_fichero);
  return cabeza;
}

int combate (struct nodo* cabeza){
 
  if (cabeza == NULL){
    return -1;
  }
    
  struct nodo* aux = NULL;
  aux = cabeza;
    
  int id1;
    
  printf("\t\tElige el id del primer pokemon: ");
  id1 = int_data_read(); 
  
  if (aux->pokemon.id == id1 && aux->pokemon.characteristics.hp > 0) {
    printf("\t\tPokemon valido\n");
  } else {
    while(aux->pokemon.id != id1){
      if(aux->next == NULL) {
        return 0;
      } else {
        aux=aux->next;
      }
    }
      
    if (aux->pokemon.id == id1 && aux->pokemon.characteristics.hp > 0) {
      printf("\t\tPokemon valido\n");
    }
      
    if (aux->pokemon.id == id1 && aux->pokemon.characteristics.hp < 0) {
      printf("\t\tPokemon no valido\n");
      return 0;
    }
  }
    
  struct nodo* pokemon = NULL;
  pokemon = cabeza;
    
  int id2;
  printf("\t\tElige el id del segundo pokemon: ");
  id2 = int_data_read(); 
    
  if (pokemon->pokemon.id == id2 && pokemon->pokemon.characteristics.hp > 0) {
    printf("\t\tPokemon valido\n");
  } else {
    while(pokemon->pokemon.id != id2){
      if(pokemon->next == NULL) {
        return 0;
      } else {
        pokemon=pokemon->next;
      }       
    }
      
    if (pokemon->pokemon.id == id2 && pokemon->pokemon.characteristics.hp > 0) {
      printf("\t\tPokemon valido\n");
    }
      
    if (pokemon->pokemon.id == id2 && pokemon->pokemon.characteristics.hp < 0) {
      printf("\t\tPokemon no valido\n");
      return 0;
    }
  }
     
  printf("\n");

  int power1; 
  power1 = (((86+rand()%15)*aux->pokemon.characteristics.attack[T_NORMAL])/pokemon->pokemon.characteristics.defense[T_NORMAL])/10;
  printf("\t\tEl pokemon 1 ataca con un daño de: %d\n", power1);
    
  printf("\n");
     
  int power2;
  power2 = (((86+rand()%15)*pokemon->pokemon.characteristics.attack[T_NORMAL])/aux->pokemon.characteristics.defense[T_NORMAL])/10;
  printf("\t\tEl pokemon 2 ataca con un daño de: %d\n", power2);
    
  printf("\n");
    
  aux->pokemon.characteristics.hp = (aux->pokemon.characteristics.hp)-power2;
  pokemon->pokemon.characteristics.hp = (pokemon->pokemon.characteristics.hp)-power1;
    
  printf("\n");
    
  printf("\t\tLa vida del pokemon 1 es: %d\n", aux->pokemon.characteristics.hp);
  printf("\t\tLa vida del pokemon 2 es: %d\n", pokemon->pokemon.characteristics.hp);
    
  printf("\n");


  if(aux->pokemon.characteristics.hp < 0){
    printf("\t\tEl pokemon 1 no podra combatir mas\n");
  }
    
  if(pokemon->pokemon.characteristics.hp < 0){
    printf("\t\tEl pokemon 2 no podra combatir mas\n");
    }

  return 0;
}

int imprimir_pokemon_introducido(struct nodo* cabeza){
  printf("\t\t\t= id: %d\n",cabeza->pokemon.id);
  printf("\t\t\t= vida: %d !!Es >0!!\n", cabeza->pokemon.characteristics.hp);
  printf("\t\t\t= nombre: %s\n",cabeza->pokemon.s_name);
  printf("\t\t\t= ataque: %d\n",cabeza->pokemon.characteristics.attack[T_NORMAL]);
  printf("\t\t\t= defensa: %d\n",cabeza->pokemon.characteristics.defense[T_NORMAL]);
  printf("\t\t\t= s ataque: %d\n",cabeza->pokemon.characteristics.attack[T_SPECIAL]);
  printf("\t\t\t= s defensa: %d\n",cabeza->pokemon.characteristics.defense[T_SPECIAL]);
  printf("\t\t\t= velocidad: %d\n",cabeza->pokemon.characteristics.speed);
  
  return 0;
}

int pokemon_corrupto(struct nodo* cabeza){
  
  if (cabeza==NULL){
    printf("\t\tLa lista esta vacía");
  return -1;
  }
  
  if(cabeza->next==NULL){
    if(cabeza->pokemon.characteristics.hp < 0){
      printf("Hay un pokemon corrupto\n");
      imprimir_pokemon_introducido(cabeza);
      return 0;
    } else {
    printf("\t\t No hay pokemons corruptos");
    return 0;
  }
}

struct nodo *aux=cabeza;
struct nodo *aux2=cabeza->next;
struct nodo *ceros=cabeza;

  for(; ceros!=NULL; ceros=ceros->next){
  if(ceros->pokemon.characteristics.hp < 0){
    printf("Pokemons con vida menor que cero\n\n");
    imprimir_pokemon_introducido(ceros);
  }
  }

while (aux!=NULL){
  if(aux->pokemon.id==aux2->pokemon.id){
    printf("Pokemons con el mismo id:\n\n");
    
    printf("pokemon\n");
    imprimir_pokemon_introducido(aux);
 
        printf("copia\n");
    imprimir_pokemon_introducido(aux2);
    
  }
  
  aux2=aux2->next;
  
  if (aux2==NULL){
    if(aux->next==NULL){
     return 0; 
    }
    aux=aux->next;
    aux2=aux->next;
        if(aux2==NULL){
     return 0; 
    }
 
    
  }
}
return 0;
}

void * exportar_autosalvado(void* data) {
  FILE *ptr_pokemon = fopen("all_info.back", "w+b");
	struct save *save =(struct save *) data;
  int *boole = save->bandera;
  if (ptr_pokemon == NULL) {
    perror("fopen writing");
  } else {
    while(1){
      sleep(10);
	    printf("\nguardando...\n");
      rewind(ptr_pokemon);
      pthread_mutex_lock(&mutex);
      
      struct nodo* export = *(save->cabeza);
      if (*boole == 0){
        int numero_pokemons=0;
        numero_pokemons=contar_pokemons(export);
        assert(fwrite(&numero_pokemons,sizeof(int), 1, ptr_pokemon) == 1);

        for(;export!=NULL; export=export->next){
          assert(fwrite(&export->pokemon.characteristics.hp, sizeof(int), 1, ptr_pokemon) == 1);
          assert(fwrite(&export->pokemon.characteristics.attack[T_NORMAL], sizeof(int), 1, ptr_pokemon) == 1);
          assert(fwrite(&export->pokemon.characteristics.attack[T_SPECIAL], sizeof(int), 1, ptr_pokemon) == 1);
          assert(fwrite(&export->pokemon.characteristics.defense[T_NORMAL], sizeof(int), 1, ptr_pokemon) == 1);
          assert(fwrite(&export->pokemon.characteristics.defense[T_SPECIAL], sizeof(int), 1, ptr_pokemon) == 1);         
          assert(fwrite(&export->pokemon.characteristics.speed , sizeof(int), 1, ptr_pokemon) == 1);
          assert(fwrite(&export->pokemon.id, sizeof(int), 1, ptr_pokemon) == 1);

          int name=strlen(export->pokemon.s_name);
          assert(fwrite(&name, sizeof(int), 1, ptr_pokemon) == 1);
          assert(fwrite(export->pokemon.s_name, sizeof(char), name, ptr_pokemon) == name);
        }

        pthread_mutex_unlock(&mutex);
      } else {
        pthread_mutex_unlock(&mutex);
        break;
      }
    }
	}
  fclose(ptr_pokemon);
  pthread_exit(NULL);
}
  
void imprimir_menu(int contador){

  
  printf("\n\t\t=========================================\n");
  printf("\t\t[*][2016][SAUCEM APPS][PokeManager]======\n");
  printf("\t\t=========================================\n");
  printf("\t\t[1] Salir\n");
  printf("\t\t[2] Insertar Pokemon\n");
  printf("\t\t[3] Mostrar Pokemons\n");
  printf("\t\t[4] Mostrar Pokemon por ID\n");
  printf("\t\t[5] Modificar un Pokemon por ID\n");
  printf("\t\t[6] Borrar Pokemon por ID\n");
  printf("\t\t[7] Exportar catálogo Pokemon\n");
  printf("\t\t[8] Importar catálogo Pokemon\n");
  printf("\t\t[9] Combate Pokemon\n");
  printf("\t\t[10] Mostrar Pokemons corruptos\n");
  printf("\t\t[11] Autosalvado Pokemon (10 segundos)\n");
  printf("\t\t\t\t#INFO:   %d veces mostrado el menú principal\n\n",contador);
  printf("\t\tDame una opción: ");
  
}

int main(int arg_count, char *arg_strings[]) {
  
    pthread_t thread;
    pthread_mutex_init(&mutex,NULL); 
    int salir88 = 0;  
    int contador=1;
    struct nodo* cabeza=NULL;
    struct save *guardar = (struct save *) calloc (1, sizeof(struct save));
    guardar->cabeza = &cabeza;
    guardar->bandera = &salir88;

    int NumeroTecleado=0;
    int si_no=1;
    int *controlador;
    int CTRL_pulsado=0;
    int d_pulsada=1;
    controlador=&CTRL_pulsado;



   controlador=&CTRL_pulsado;

    int bol_save = 0;

    do{
   
       imprimir_menu(contador);
       contador++;
       NumeroTecleado=int_data_read_control(controlador);
       
      pthread_mutex_lock(&mutex);
  switch (NumeroTecleado){
    if(CTRL_pulsado==-1){
      d_pulsada=d_salir();
    }
  case 1: do{
        si_no=salir();
  
  }
  while(si_no!=-1 && si_no!=0);
    if(si_no==0){
       salir88=1; 
       
       pthread_mutex_unlock(&mutex);
       free(guardar);
	pthread_mutex_destroy(&mutex);    
       
	borrar_lista(&cabeza);
      
      return 0;
    }; break;
  
  case 2: insertar_pokemon(&cabeza);break; 
  case 3: mostrar_pokemons(cabeza); break;
  case 4: mostrar_pokemon_id(cabeza);break;


  case 5:modificar_pokemon_id(cabeza);break;
  case 6:cabeza = borrar_pokemon_id(cabeza);break;
  case 7: exportar(cabeza); break;
  case 8: cabeza=importar(cabeza);break;
  case 9:combate(cabeza);break;
  case 10: pokemon_corrupto(cabeza);break;
  case 11: if(bol_save == 1){
        printf("\t\t\tAutosalvado activado\n" );
      }else{
        bol_save = 1;
        guardar->cabeza = &cabeza;
        guardar->bandera = &salir88;
        pthread_create(&thread, NULL, exportar_autosalvado, (void *) guardar);
      }
          break;
      }
      pthread_mutex_unlock(&mutex);
      
      
} while(CTRL_pulsado!=-1 && d_pulsada!=0 );


       pthread_mutex_lock(&mutex);
       
       if (bol_save == 1){
    pthread_mutex_lock(&mutex);
    salir88 = 1;
    pthread_join(thread,NULL);
    pthread_mutex_unlock(&mutex);
   
  }

       borrar_lista(&cabeza);
       pthread_mutex_destroy(&mutex);


  

printf("\n\n");
printf("________´$$$$`_____________________________,,,_ \n");
printf("_______´$$$$$$$`___________________________´$$$`\n");
printf("________`$$$$$$$`______,,________,,_______´$$$$´\n");
printf("_________`$$$$$$$`____´$$`_____´$$`____´$$$$$´ \n");
printf("__________`$$$$$$$`_´$$$$$`_´$$$$$`__´$$$$$$$´ \n");
printf("___________`$$$$$$$_$$$$$$$_$$$$$$$_´$$$$$´_ \n");
printf("____________`$$$$$$_$$$$$$$_$$$$$$$`´$$$$$´_ \n");
printf("___,,,,,,______`$$$$$$_$$$$$$$_$$$$$$$_$$$$$´_ \n");
printf("_´$$$$$`____`$$$$$$_$$$$$$$_$$$$$$$_$$$$$$´_ \n");
printf("´$$$$$$$$$`´$$$$$$$_$$$$$$$_$$$$$$$_$$$$$$´_ \n");
printf("´$$$$$$$$$$$$$$$$$$_$$$$$$$_$$$$$$$_$$$$$´_ \n");
printf("___`$$$$$$$$$$$$$$$_$$$$$$$_$$$$$$_$$$$$$´_ \n");
printf("______`$$$$$$$$$$$$$_$$$$$__$$_$$$$$$_$$´_ \n");
printf("_______`$$$$$$$$$$$$,___,$$$$,_____,$$$$$´_ \n");
printf("_________`$$$$$$$$$$$$$$$$$$$$$$$$$$$$$´_ \n");
printf("__________`$$$$$$$$$$$$$$$$$$$$$$$$$$$´_ \n");
printf("____________`$$$$$$$$$$$$$$$$$$$$$$$$´_ \n");
printf("_______________`$$$$$$$$$$$$$$$$$$$$´_\n");
    
  return 0;
}