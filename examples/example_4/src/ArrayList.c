#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ArrayList.h"

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElements;
    this = (ArrayList *)malloc(sizeof(ArrayList));

    if(this != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            this->size=0;
            this->pElements=pElements;
            this->reservedSize=AL_INITIAL_VALUE;
            this->add=al_add;
            this->len=al_len;
            this->set=al_set;
            this->remove=al_remove;
            this->clear=al_clear;
            this->clone=al_clone;
            this->get=al_get;
            this->contains=al_contains;
            this->push=al_push;
            this->indexOf=al_indexOf;
            this->isEmpty=al_isEmpty;
            this->pop=al_pop;
            this->subList=al_subList;
            this->containsAll=al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            returnAux = this;
        }
        else
        {
            free(this);
        }
    }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int res;
    int flag=1;

    if(this!=NULL && pElement!=NULL){ //Valida Que sea Distinto a NULL lo Que Se Ingrese.

        if(this->size==this->reservedSize){ // Compruebo Que reservedSize no este llena.

           res=resizeUp(this); // Si esta llena llamo a la funcion resizeUp, que contiene un Realloc para agrandar el array pElements

           if(res==-1){

            flag=0; // me aseguro que no se cargue el elemento si la funcion ResizeUp devuelve NULL.
            }
        }
        if(flag==1){
            *(this->pElements+this->size)=pElement; // pElement(elemento a ingresar) es igual a el valor.
            this->size++;                          // De la direccion de memoria del array pElements + la cantidad actual/espacio libre.
            returnAux=0;                          //Una vez agregado lo sumo a la cantidad.
        }
    }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this)
{
    int returnAux = -1;

    if(this!=NULL){ //Valido el NULL
        free(this); //Libero la Memoria Del arrayList.
        returnAux=0;
    }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL){           //Valida el NUll
        returnAux=this->size; //el valor Del size es la cantidad De elementos Que contiene el array.
    }

    return returnAux;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)
{
    void* returnAux = NULL;
    int tam;

    if(this!=NULL){                         //validA el NULL.

        tam=al_len(this);                   //Busco el tamanio del array.
        if( index>=0 && index<tam)
        {
            returnAux=*(this->pElements+index); // retorna el elemento del array pElements en la pocision Index.
        }
    }


    return returnAux;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int tam;

    if(this!=NULL && pElement!=NULL){          //Valida el NULL.

        tam=al_len(this);                      //Busco el tamanio Del array.

        for(int i=0;i<tam;i++){

            returnAux=0;

            if(*(this->pElements+i)==pElement){   //Si el elemento ingresado es igual a alguno en el array pElements.
                returnAux=1;                    //Encontro el elemento.
                break;
            }
        }
    }

    return returnAux;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement)
{
    int returnAux=-1;
    int aux;
    int tam;

    if(this!=NULL&&pElement!=NULL){             //Valida el NULL.

        tam=al_len(this);                       //Busco el tamanio.

        if(index>=0 && index<=tam){

            if(index==tam){                     //Si el indice es igual a lo que devolvio al_len lo puedo agragar en esa
                aux = al_add(this, pElement);   //posicion, devuele la cant. y el lugar libre.
            if(aux == 0){
                returnAux = 0;
            }
        }else
        {
           *(this->pElements+index) = pElement; //Inerto el elemento en el indice indicado Del pElements.
            returnAux = 0;

            }
        }
    }
    return returnAux;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index)
{
   int returnAux = -1;
   int res;
   if(this!=NULL){
        res=contract(this,index);
        if(res==0){
            returnAux=0;
        }
   }

    return returnAux;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)
{
    int returnAux = -1;
    int tam;

    if(this!=NULL){
        tam=this->len(this);
        for(int i=0;i<tam;i++){
            free(this->pElements+i);
            this->size--;
            returnAux=0;
        }
    }

    return returnAux;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this)
{
    ArrayList* returnAux = NULL;

    if(this!=NULL){

        returnAux=this;
    }

    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)
{
    int returnAux = -1;
    int tam;
    int ind;
    int res;

    if(this!=NULL && pElement!=NULL){

            tam=this->len(this);

        if(index>=0 && index<tam){

            ind=this->set(this,index,pElement);
            if(ind=0){

                for(int i=index;i<tam-1;i++){

                }
            }
        }



    }
         }
    }
    return returnAux;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int tam;

    if(this!=NULL && pElement!=NULL){

            tam=this->len(this);

            for(int i=0;i<tam;i++){

                if(*(this->pElements+i)==pElement){

                returnAux=i;
                break;


            }
        }
    }

    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)
{
    int returnAux = -1;
    int tam;

    if(this!=NULL){
         tam=this->len(this);
        if(tam==0){
            returnAux=1;
        }else if(tam>0){
            returnAux=0;
        }

    }

    return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */

void* al_pop(ArrayList* this,int index)
{
    void* returnAux = NULL;
    int tam;


    if(this!=NULL){

            tam=this->len(this);
        if(index>=0 && index<tam){

            returnAux=*(this->pElements+index);
            //contract(this,index);
        }
    }

    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to)
{
    void* returnAux = NULL;

    return returnAux ;
}





/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2)
{
    int returnAux = -1;

    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux = -1;

    return returnAux;
}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)
{
    int returnAux = -1;
    void** pAux;

    if(this!=NULL){ // Valido el NULL

        pAux = (void**) realloc(this->pElements,(AL_INCREMENT+this->reservedSize)*  sizeof(void*));
        //Hago el realloc para agrandar el array pElements, sumando AL_INCREMENT mas la reserva.

        if(pAux !=NULL)
            {

            this->pElements=pAux;
            this->reservedSize+=AL_INCREMENT;
            returnAux=0;
        }// le cargo el nuevo espacio al array pElements
    }

    return returnAux;

}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index)
{
    int returnAux = -1;

    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)
{
    int returnAux = -1;
    int tam;

    if(this!=NULL){
        tam=al_len(this);
        if(index>=0 && index<tam){

            for(int i=index;i<tam-1;i++){ // desde el indice hasta el tam -1 porque es tambien el lugar libre.
                *(this->pElements+i)=*(this->pElements+(i+1)); // el indice acutal(a borrar) es igual a el siguiente indice(lo va pisando).
            }
            this->size--;
            returnAux=0;

        }
    }

    return returnAux;
}
