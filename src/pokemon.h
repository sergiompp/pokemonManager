/***CHeaderFile*****************************************************************

  Fichero     [pokemon.h]

  Resumen     [pokemon.h]

  Descripcion [Archivo .h] 

  Ver tambien [opcional]

  Autor       [Grupo ARS]

  Copyright   [Copyright (c) 2012 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningÃºn tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentaciÃ³n para cualquier propÃ³sito siempre y cuando esta advertencia
  y los siguientes dos pÃ¡rrafos aparezcan en las copias.

  EN NINGÃšN CASO SE RECONOCERÃ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÃ‘OS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÃ“N, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÃ‘OS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÃFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÃAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÃCITAS
  DE LA COMERCIALIZACIÃ“N Y ADECUACIÃ“N PARA CUALQUIER PROPÃ“SITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÃ“N ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de constantes                                                 */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de tipos                                                      */
/*---------------------------------------------------------------------------*/
enum {T_NORMAL,T_SPECIAL};

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de estructuras                                                */
/*---------------------------------------------------------------------------*/

struct points{
  
  int hp;
  int attack[2];
  int defense[2];
  int speed;
  
  
};
 
struct save{
  
  struct nodo ** cabeza;
  int * bandera;
  
};

struct pokemons{
  
  int id;
  char *s_name;
  int size_name;
  struct points characteristics;

};



struct nodo{
  
struct pokemons pokemon;
struct nodo* next;

};


/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de variables                                                  */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de macros                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Protitpos de las funciones                                                */
/*---------------------------------------------------------------------------*/
int int_data_read();
//int int_data_read_control(int *ptr_data);
char *char_data_read();
char *char_read();
int salir();
int d_salir();
int borrar_lista(struct nodo** ptr_cabeza);
int insertar_pokemon(struct nodo** ptr);
int mostrar_pokemons(struct nodo* cabeza);
int mostrar_pokemon_id(struct nodo* cabeza);
struct nodo * borrar_pokemon_id(struct nodo * ptr_cabeza);
int modificar_pokemon_id(struct nodo* cabeza);
int combate(struct nodo* cabeza);
void exportar(struct nodo* cabeza);
int contar_pokemons(struct nodo *cabeza);
void imprimir_menu(int contador);
struct nodo* importar(struct nodo *cabeza);
struct nodo *importar_nodo(FILE *f2);
char* importar_string(FILE *f2);