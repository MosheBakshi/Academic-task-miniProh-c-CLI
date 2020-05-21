#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


#define RA 3 // defining for question 2!
#define CA 2
#define RB 2
#define CB 2

/*Structs declerations & defenitions*/
typedef struct xNODEx
{
	int Data;
	struct xNODEx *next;
}xNODEx;


typedef struct Element
{
	int Data;
	int Raws;
	int Collons;

}Element;


/* Function declarations & defenitions Ex1 & Ex2 */

int MatPrint(int **Mat, int Raws, int Collons) //printing the matrix
{
	int i, j; //indexers for the loop
	for (i = 0; i < Raws; i++)
	{
		for (j = 0; j < Collons; j++)
		{
			printf(" %d ", Mat[i][j]);
		}
		printf("\n");
	}
}

int multiplicationMatrx(int MatA[RA][CA], int MatB[RB][CB])//, int RaA, int CoA, int RaB, int CoB)
														   //recieving both adress of the matirxes and their size of raws and collons that defined on top
{
	int i, j, k;// indexers for for the loops
	int **C;//pointer for the new matrix
	C = (int**)calloc(RA, sizeof(void*));   // defining the RAW size in the new matrix
	for (i = 0; i < RA; i++) // loop for defining the collons for each raw
	{
		C[i] = (int*)calloc(CB, sizeof(int));
	}

	printf("Matrix A :\n");
	for (i = 0; i < RA; i++) // print MatA
	{
		for (k = 0; k < CA; k++)
		{
			printf(" %d ", MatA[i][k]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Matrix B :\n");
	for (i = 0; i < RB; i++) //print MatB
	{
		for (k = 0; k < CB; k++)
		{
			printf(" %d ", MatB[i][k]);
		}
		printf("\n");
	}
	printf("\n");

	for (i = 0; i < RA; i++) // tripple loop for multiplication
	{
		for (k = 0; k < CB; k++)
		{
			for (j = 0; j < CA; j++)
			{
				C[i][k] += (MatA[i][j] * MatB[j][k]);
				/* in case you want to see the actual action in live */

				//printf("C: %d       i: %d k: %d j: %d", C[i][k], i, k, j);
				//	printf("\n");
			}
		}
	}
	printf("\n");
	return C;
}

unsigned int powerArrey(int n) // function for Ex1
{
	int i;  //indexer for the loop
	unsigned int *a;   //for dynamic arrey as requested
	a = (unsigned int*)calloc(n, sizeof(unsigned int));
	if (!a)   //in case of no free memory space
	{
		free(a);    //insurence incase it using little bit space
		printf("Not enough memory\n");
	}
	else
	{

		for (i = 0; i<n; (i += 1) % 32)  //always adding 1 to 'i' yet moduling in 32
		{
			{
				if (i < 1)//the first element is 2^0=1
					a[i] = 1;
				else if (i > 0)//all the rest elemnts
					a[i] = ((a[i - 1]) * 2);// powing with 2
			}
		}
	}
	return a;//returning the first adress to the pointer.
}

void FreeMat(int **Arr, int n)
{
	int i;
	for (i = 0; i<n; i++)
		free(Arr[i]);
	free(Arr);
}

/*function declerationns & defenitions for : Ex3,Ex4 and Ex5*/

void free_xNODEx(xNODEx **head) //releasing list
{
	xNODEx *tmp = NULL;
	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void PrintTheArrEx3(Element * arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		if (arr[i].Data != NULL)
			printf("(( No#|%d| in Raw[%d] Collon[%d] ))    ", arr[i].Data, arr[i].Raws, arr[i].Collons);
	printf("\n");
}

int check_the_sum(int **matrix, int Raws, int Collons, Element **arr, xNODEx **Listed)
{
	int i, j, count = 0, lC = 1;
	xNODEx *Point = NULL;

	*arr = (Element*)calloc((Raws*Collons), sizeof(Element));
	for (i = 0; i < Raws; i++)
	{
		for (j = 0; j < Collons; j++)
		{
			if ((i + j) == matrix[i][j])
			{
				(*arr)[count].Data = matrix[i][j];
				(*arr)[count].Raws = i;
				(*arr)[count].Collons = j;

				Point = (xNODEx*)malloc(sizeof(xNODEx));
				Point->Data = matrix[i][j];

				Point->next = *Listed;
				*Listed = Point;
				count++;
			}

		}
	}
	(*arr) = (Element*)realloc((*arr), count * sizeof(Element));
	return count;
}

int **Zeroing_Mat(int Raws, int Collons)
{
	int **c, i;
	c = (int **)calloc(Raws, sizeof(int *));
	if (!c)
		return NULL;
	for (i = 0; i< Raws; i++)
	{
		c[i] = (int *)calloc(Collons, sizeof(int));
		if (!c[i])
		{
			FreeMat(c, i);
			return NULL;
		}

	}
	return c;

}

xNODEx* insert() //inserting to the list
{
	xNODEx *TempUse = NULL, *head = NULL;
	int num;
	printf("Enter a Value: ");
	scanf_s("%d", &num);
	while (num >= 0)
	{
		if (head == NULL)
		{
			head = (xNODEx *)malloc(sizeof(xNODEx));
			head->next = NULL;
			head->Data = num;
			TempUse = head;
		}
		else
		{
			TempUse->next = (xNODEx *)malloc(sizeof(xNODEx));
			TempUse = TempUse->next;
			TempUse->Data = num;
			TempUse->next = NULL;

		}
		printf("Enter a Value: ");
		scanf_s("%d", &num);
	}
	printf("\n");
	return head;
}

void PrintLST(xNODEx *head)// printing the list
{
	while (head != NULL)
	{
		printf("(%d)---> ", head->Data);
		head = head->next;
	}
	printf("NULL\n\n");
}

xNODEx * COLEx4(xNODEx **l) //creating list for the odd numbers in Ex4
{
	xNODEx *Point, *pre_Point = NULL, *oddPoint = NULL; // structs type pointers
	xNODEx *RecODD = NULL;
	Point = (*l);

	while (Point != NULL)
	{
		if (Point->Data % 2 != 0) // checking if the number is not even
		{
			if (Point == *l) //first element is odd
			{
				if (RecODD == NULL)
				{
					RecODD = (xNODEx*)malloc(sizeof(xNODEx));
					RecODD->Data = Point->Data;
					RecODD->next = NULL;
					oddPoint = RecODD;
					(*l) = (*l)->next;
					free(Point);
					Point = (*l);
				}
				else
				{
					oddPoint->next = (xNODEx*)malloc(sizeof(xNODEx));
					oddPoint = oddPoint->next;
					oddPoint->Data = Point->Data;
					oddPoint->next = NULL;
					(*l) = (*l)->next;
					free(Point);
					Point = (*l);

				}
			}
			else
			{
				if (RecODD == NULL)
				{
					RecODD = (xNODEx*)malloc(sizeof(xNODEx));
					RecODD->Data = Point->Data;
					RecODD->next = NULL;
					oddPoint = RecODD;
					pre_Point->next = Point->next;
					free(Point);
					Point = pre_Point->next;
				}
				else
				{
					oddPoint->next = (xNODEx*)malloc(sizeof(xNODEx));
					oddPoint = oddPoint->next;
					oddPoint->Data = Point->Data;
					oddPoint->next = NULL;
					pre_Point->next = Point->next;
					free(Point);
					Point = pre_Point->next;
				}

			}

		}
		else
		{
			pre_Point = Point;
			Point = Point->next;
		}
	}
	return RecODD;
}

xNODEx * COLEx5(xNODEx **l) // creating list for the odd numbers in Ex5
{
	xNODEx *Point, *pre_Point = NULL, *oddPoint = NULL; //structs type pointers
	xNODEx *RecODD = NULL;
	Point = (*l);

	while (Point != NULL)
	{
		if (Point->Data % 2 != 0) // checking if the number is not even
		{
			if (Point == *l) //first element is odd
			{
				if (RecODD == NULL)
				{
					RecODD = (*l);
					(*l) = (*l)->next;
					Point = (*l);
					oddPoint = RecODD;
					oddPoint->next = NULL;
				}
				else
				{
					oddPoint->next = (*l);
					(*l) = (*l)->next;
					Point = (*l);
					oddPoint = oddPoint->next;
					oddPoint->next = NULL;
				}
			}
			else
			{
				if (RecODD == NULL)
				{
					pre_Point->next = Point->next;
					oddPoint = Point;
					RecODD = oddPoint;
					oddPoint->next = NULL;
					Point = pre_Point->next;
				}
				else
				{
					pre_Point->next = Point->next;
					oddPoint->next = Point;
					oddPoint = oddPoint->next;
					oddPoint->next = NULL;
					Point = pre_Point->next;
				}

			}

		}
		else
		{
			pre_Point = Point;
			Point = Point->next;
		}
	}
	return RecODD;
}

// * Cases by questions * //

void Ex1()//main block of question 1
{
	int n, i;//'n' size of the arrey and 'i' is index
	unsigned int *p; // pointer for the arrey we'll get from the function
	printf("Please enter the size of the arrey: ");
	scanf_s("%d", &n);
	p = powerArrey(n);
	for (i = 0; i < n; i++)
		printf("%d \n", p[i]);
	free(p);//
}

void Ex2()//main block of question 2
{
	int i, k;//indexers for printing and releasing the matrix
	int A[RA][CA] = { 1,2,3,4,5,6 }; // raws and collons defined in the beginning of the script (scroll up)
	int B[RB][CB] = { 1,0,0,1 };
	int **NewMat;// pointer for the new recieved matrix
	NewMat = multiplicationMatrx(A, B);// calling for the function
	printf("The new Matrix is :\n");
	for (i = 0; i < RA; i++)//printing the new matrix
	{
		for (k = 0; k < CB; k++)
		{
			printf(" %d ", NewMat[i][k]);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < RA; i++)//releasing the memory of the internal arreys
		free(NewMat[i]);
	free(NewMat);//releasing the skelton of the pointers to the internal arreys
}

void Ex3() // main block of question 3
{
	Element *arr; //pointers of struct type
	xNODEx *Listed = NULL;
	int **mat;
	int Raws, Collons, size, i, j; //diferent kind of indexers and sizes
	printf("Enter the size of Raws in the matrix\n");
	scanf("%d", &Raws);
	printf("Enter the size of Collons in the matrix\n");
	scanf("%d", &Collons);
	printf("\n");
	mat = Zeroing_Mat(Raws, Collons);
	printf("Enter elements to the matrix\n");
	for (i = 0; i < Raws; i++)
		for (j = 0; j < Collons; j++)
			scanf("%d", &mat[i][j]);
	size = check_the_sum(mat, Raws, Collons, &arr, &Listed);
	PrintTheArrEx3(arr, size);
	printf("\n");
	if (size != 0)
	{
		printf("The Size is %d\n", size);
		PrintLST(Listed);
	}
	else if (size == 0)
	{
		printf("No element fit as requested to the arrey\nThe size is : %d and there is no list\n", size);
	}
	printf("\n");

	FreeMat(mat, Raws);
	free(arr);
	free_xNODEx(&Listed);

}

void Ex4() // main block question 4
{
	xNODEx* xNODEx, *xNODEx_odd;

	printf("Please enter values to the list (when you wish to stop press -1):\n");
	xNODEx = insert();
	printf("the original list is:\n");
	PrintLST(xNODEx);
	printf("\n");
	printf("\n");
	xNODEx_odd = COLEx4(&xNODEx);
	printf("The even list is :\n");
	PrintLST(xNODEx);
	printf("\n");
	printf("\n");
	printf("The odd list is :\n");
	printf("\n");
	PrintLST(xNODEx_odd);
	printf("\n");
}

void Ex5() // main block question 5
{
	int x;
	xNODEx* xNODEx, *xNODEx_odd;

	printf("please enter values to the list(when you wish to stop press -1):\n");
	xNODEx = insert();
	printf("The Original list is:\n");
	PrintLST(xNODEx);
	xNODEx_odd = COLEx5(&xNODEx);
	printf("The even list is :\n");
	PrintLST(xNODEx);
	printf("\n"); printf("\n");
	printf("\n");
	printf("The odd list is :\n");
	printf("\n");
	PrintLST(xNODEx_odd);
	printf("\n");
}

// main block //

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= 5; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do
			{
				select = 0;
				printf("please select 0-5 : ");
				scanf("%d", &select);
			} while ((select<0) || (select>5));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			case 4: Ex4(); break;
			case 5: Ex5(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}