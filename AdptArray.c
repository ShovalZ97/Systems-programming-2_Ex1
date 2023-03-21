#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    int ArrSize;
    PElement *pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray;
/*
 * CreateAdptArray
 * This function Initializes an empty array and all the variables we have in struct.
 * This function creates a new AdptArray.
 * The function that we have in our AdptArray:
 * CopyFunc:copy the elements in the array.
 * Delfunc:delete the elements in the array.
 * Printfunc:print the elements in the array.
*/
PAdptArray CreateAdptArray(COPY_FUNC copyFunc1, DEL_FUNC delFunc1, PRINT_FUNC printFunc1)
{
    PAdptArray pArr_New = (PAdptArray)malloc(sizeof(AdptArray));
    if (pArr_New == NULL)
        return NULL;
    pArr_New->ArrSize = 0;
    pArr_New->pElemArr = NULL;
    pArr_New->delFunc = delFunc1;
    pArr_New->copyFunc = copyFunc1;
    pArr_New->printFunc = printFunc1;
    return pArr_New;
}
/*
 * SetAdptArray
 * This function receives an index and element and saves a copy of the element in the requested location.
 * This function release the old element if exist.
*/
Result SetAdptArrayAt(PAdptArray pArr, int ind, PElement pNewElem)
{
    PElement *pElemArr_New;
    if (pArr == NULL)
        return FAIL;
    //Extends the array pointed to by pArr to accommodate the given index ind if it is out of bounds.
    if (ind >= pArr->ArrSize)
    {
        pElemArr_New = (PElement *)calloc((ind + 1), sizeof(PElement));
        if ((pElemArr_New) == NULL)
            return FAIL;

        if (pArr->pElemArr != NULL)
            //Copies a block of memory from one location to another
            memcpy(pElemArr_New, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));

        free(pArr->pElemArr);
        pArr->pElemArr = pElemArr_New;
    }
    //Delete Previous Element
    if ((pArr->pElemArr)[ind] != NULL)
        pArr->delFunc((pArr->pElemArr)[ind]);

    (pArr->pElemArr)[ind] = pArr->copyFunc(pNewElem);
    //Update Array Size
    pArr->ArrSize = (ind >= pArr->ArrSize) ? (ind + 1) : pArr->ArrSize;
    return SUCCESS;
}
/*
 * DeleteAdptArray
 * This function frees the memory of the object.
*/
void DeleteAdptArray(PAdptArray pArr)
{
    if (pArr == NULL)
        return;
    if (pArr->pElemArr == NULL)
        return;
    for (int i = 0; i < pArr->ArrSize;i++)
    {
        if ((pArr->pElemArr)[i] != NULL)
            pArr->delFunc((pArr->pElemArr)[i]);
    }

    free(pArr->pElemArr);
    free(pArr);
}
/*
 * GetAdptArrayAt
 * This function gets an index and returns a copy of the element at this location.
*/
PElement GetAdptArrayAt(PAdptArray pArr, int ind)
{
    if (pArr == NULL||ind < 0||ind >= pArr->ArrSize||pArr->pElemArr[ind] == NULL)
        return NULL;

    return pArr->copyFunc(pArr->pElemArr[ind]);
}
/*
 * GetAdptArraySize
 * This function returns the size of the array
 * Return -1 when the array was not initialized successfully.
*/
int GetAdptArraySize(PAdptArray pArr)
{
    if (pArr == NULL)
        return -1;

    return pArr->ArrSize;
}
/*
 * PrintDB
 * This function prints the elements in the array.
*/
void PrintDB(PAdptArray pArr)
{
    if (pArr == NULL)
    {
        printf("Array is not initialized!\n");
        return;
    }
    for (int i = 0; i < pArr->ArrSize; i++)
    {
        if ((pArr->pElemArr)[i] != NULL)
        {
            pArr->printFunc((pArr->pElemArr)[i]);
        }
    }
}