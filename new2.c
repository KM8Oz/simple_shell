#include<stdio.h>// gerer l'entrer /sortie scanf /printf
#include<stdlib.h>
#include<math.h> //sqrt,pow,cos,sin,tan,fabs
int main(){ 
float xa,xb,ya,yb; // all floats
float d;
printf("saisir xa xb ya yb");
scanf("%f%f%f%f",&xa,&xb,&ya,&yb);
d=sqrt(pow(xa-xb,2)+pow(ya-yb,2));
printf("la distance est %f",d);
return 0;
}

