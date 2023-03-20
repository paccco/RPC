/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>

double
calculadora_1(char *host, double v1, double v2, int op)
{
		CLIENT *clnt;
		result  *result_1;
		double _val1=v1;
		double _val2=v2;

	#ifndef	DEBUG
		clnt = clnt_create (host, CALCULADORA, CALCULADORA_1, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

		result_1->code=0;

		switch(op){
			case 1:
				result_1 = suma_1(_val1, _val2, clnt);
				if (result_1 == (result *) NULL) {
					clnt_perror (clnt, "call failed");
				}
			break;
			case 2:
				result_1 = restar_1(_val1, _val2, clnt);
				if (result_1 == (result *) NULL) {
				clnt_perror (clnt, "call failed");
				}
			break;
			case 3:
				result_1 = multiplica_1(_val1, _val2, clnt);
				if (result_1 == (result *) NULL) {
				clnt_perror (clnt, "call failed");
				}
			break;
			case 4:
				result_1 = divide_1(_val1, _val2, clnt);
				if (result_1 == (result *) NULL) {
				clnt_perror (clnt, "call failed");
				}
			break;
			default: 
				clnt_perror (clnt, "call failed");
			break;
		}

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */

	int fallo=result_1->code;

	if(fallo > 0){
		printf("\n Algo fue mal, codigo de error: %d \n", fallo);

		if(fallo == -1){
			printf("Division por 0 o valor muy cercano a este");
			exit(1);
		}
	}

	return result_1->result_value;
}


MiVector
calculadora_2(char *host, MiVector v1, MiVector v2, int op)
{
	CLIENT *clnt;
	result  *result_1;
	MiVector val1=v1;
	MiVector val2=v2;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_2, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	switch (op)
	{
		case(1):
			result_1 = suma_2(val1, val2, clnt);
			if (result_1 == (result *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		break;

		case(2):
			result_1 = restar_2(val1, val2, clnt);
			if (result_1 == (result *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		break;
		case(3):
			result_1 = multiplica_2(val1, val2, clnt);
			if (result_1 == (result *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		break;
		default: 
			clnt_perror (clnt, "call failed");
		break;
	}
	
	
	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */

	return result_1->result_vect;
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc != 5 && argc != 3) {
		printf ("usage: %s server_host numero1 signo numero2\n Numero de argumentos pasados: %i \n", argv[0], argc);

		exit (1);
	}
	host = argv[1];

	if(argc==3){
		if(argv[2][0]!='V'){
			printf("\ningrese el caracter V como tercer argumento para que funcione la caluladora\n");

			exit(1);
		}
		else{
			printf("\nIngrese el vector 1 (el vector es de 3 componentes)\n");
			MiVector vect1;

			scanf("%lf",&vect1.a);
			scanf("%lf",&vect1.b);
			scanf("%lf",&vect1.c);

			printf("\nIngrese el vector 1 (el vector es de 3 componentes)\n");
			MiVector vect2;

			scanf("%lf",&vect2.a);
			scanf("%lf",&vect2.b);
			scanf("%lf",&vect2.c);

			printf("\nQue opeeracion quiere hacer?(+,-,x)\n");
			char aux;
			scanf("%c",&aux);
			scanf("%c",&aux);

			int op;
			switch (aux)
			{
				case('+'):
					op=1;
				break;
				case('-'):
					op=2;
				break;
				case('x'):
					op=3;
				break;
				default:
					printf("\nSimbolo %c incorrecto\n",aux);

					exit(1);
				break;
			}

			MiVector resultado;

			resultado=calculadora_2 (host,vect1,vect2,op);
			printf("\n( %f , %f , %f )\n",resultado.a,resultado.b,resultado.c);
		}
	}
	else{
		double val1=atof(argv[2]), val2=atof(argv[4]);
		char aux=argv[3][0];
		int op=-1;

		if(aux=='+')
			op=1;
		else if(aux=='-'){
			op=2;
		}else if(aux=='x'){
			op=3;
		}else if(aux=='/'){
			op=4;
		}

		double resultado;

		if(op!=-1){
			if(op==4){
				double epsilon=0.0000001f;

				if(val2<epsilon && val2>-epsilon){
					printf("\nDividiendo por cero\n");
					exit(1);
				}

			}
			
			resultado=calculadora_1 (host,val1,val2,op);
			printf("\n%f\n",resultado);
			
		}
		else{
			printf("\nFallo en el signo\n");
			exit(1);
		}
	}

	exit (0);
}