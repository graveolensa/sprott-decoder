#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* GFDL, or whatever. use it. */
/* l is the variable used to index the string in the Sprott Code Legality Test */
int l;
int aur;
/* the coefficients array, thirty long */
/* temporarily out of the water for the memory allocation test */


/* Note: this is exactly the same as syllegy, except that it handles
   the differential equations case */

/* type definition of point */
typedef struct
{
  double x;
  double y;
  double z;
} point;

/* definition of transformation function */
/* this is necessary so that we can write shorthand like T(q), where the */
/* argument of the function q, and its return value are both points */

/* the current point and the next point */

point current, next;

/* iteration count variable */
int bboxitercount;

/* bounding box ranges */
double xmin,xmax;
double ymin,ymax;
double zmin,zmax;

/* bounding box spans */
double xspan, yspan, zspan;

/* bounding box centers */
double xcen, ycen, zcen;

/* bounding box radii */
double xrad, yrad, zrad;

/* maximum bounding box radius */
double maxrad;

/* 768 by 768 array for displaying the results of the computation */
int display[768][768];

/* m and n, integer variables for indexing display */
int m,n;

/* iterations count for the main plot */
int plotiter;

/* display x and display y coordinates for the projections */
int dispX, dispY;

/* file declaration for attractor filehandle */
FILE *file;


/* integer variable for order */
int order;

int main(int argc, char *argv[])
{
  /* ##### block 1: Sprott Code Legality Testing ##### */

  /* step one: check the number of arguments */
  if(argc!=2)
    {
      printf("This program takes one argument:\n");
      printf("the attractor codes from chapter four\n");
      printf("of Julien Sprott's book\n");
      return 0;
    }
  else
    {
      /* the second argument should be a thirty long */
      /* string of all capital letters. This should be */
      /* sanity tested now */
      if((strlen(argv[1])!=30)&&(strlen(argv[1])!=60)&&(strlen(argv[1])!=105)&&(strlen(argv[1])!=168))
  {
	  printf("Sprott code is not 30, 60, 105, or 168 characters long\n");
	  printf("entered Sprott code is of length %d\n", strlen(argv[1]));
	  return 0;
	}
      else
	{
	  if((strlen(argv[1])==30)||(strlen(argv[1])==60)||(strlen(argv[1])==105)||(strlen(argv[1])==168))
	    {
	      for(l=0;l<strlen(argv[1]);l++)
		{
		  if(argv[1][l]<65 || argv[1][l]>97)
		    {
		    
		      printf("Character in Sprott code out of range\n");
		      printf("please check your Sprott code\n");
		      return 0;
		    }
		  else
		    {
		      printf("character %d of Sprott Code is legal\n", l+1);
		    }
		}
	      printf("The entire Sprott Code is legal\n");
	    }
	  else
	    {
	      printf("an impossible condition has occurred");
	    }
	}
    }
  /* block 1a: generate the order parameter from the length of the entered Sprott code */
  /* dynamically generate the coeffs array here */
  if(strlen(argv[1])==30)
    {
      order=2;
    }
  if(strlen(argv[1])==60)
    {
      order=3;
    }
  if(strlen(argv[1])==105)
    {
      order=4;
    }
  if(strlen(argv[1])==168)
    {
      order=5;
    }
  double * coeff = calloc(strlen(argv[1])+1,sizeof(double));
  /* ##### block 2: Sprott Code Parsing: turn the Sprott Code into numbers ##### */

  /* we can reuse l from the first section because we're also doing a thirty long */
  /* index. This time we know the index's length, since execution would have stopped */
  /* if the Sprott code string weren't legal */
  for(l=0;l<strlen(argv[1]);l++)
    {
      coeff[l]= -1.2 + 0.1 * (argv[1][l] - 65);
      /* since the purpose of encode.c is just to test that we can make */
      /* the encoding, we'll print out the coefficients here */
      printf("the %d th coefficient is %f\n", l+1, coeff[l]);
    }

  /* ##### block 3: Generate the Transformation from the coefficients array */
  /* since we don't want to spend a lot of time mucking about with the transformation, we'll */
  /* define a function here (I can do that, can't I? But first we're going to need to make */
  /* a data type called a point. */
  point transformation(point start)
    {
      point out;
      /* let's simplify the process of writing these */
      double sx,sy,sz;
      sx = start.x;
      sy = start.y;
      sz = start.z;
      out.x=0;
      out.y=0;
      out.z=0;
      double x1,x2,x3,x4,x5;
      double y1,y2,y3,y4,y5;
      double z1,z2,z3,z4,z5;

      double sx2,sx3,sx4,sx5;
      double sy2,sy3,sy4,sy5;
      double sz2,sz3,sz4,sz5;
      sx2 = sx*sx; sx3 = sx * sx * sx; sx4 = sx* sx* sx* sx; sx5 = sx*sx*sx*sx*sx;
      sy2 = sy*sy; sy3 = sy * sy * sy; sy4 = sy* sy* sy* sy; sy5 = sy*sy*sy*sy*sy;
      sz2 = sz*sz; sz3 = sz * sz * sz; sz4 = sz* sz* sz* sz; sz5 = sz*sz*sz*sz*sz;


if(order==2)
	{
	  out.x = coeff[0]+coeff[1]*(start.x)+coeff[2]*((start.x)*(start.x))+coeff[3]*((start.x)*(start.y))+coeff[4]*((start.x)*(start.z))+coeff[5]*(start.y)+coeff[6]*((start.y)*(start.y))+coeff[7]*((start.y)*(start.z))+coeff[8]*(start.z)+coeff[9]*((start.z)*(start.z));
 out.y = coeff[10]+coeff[11]*(start.x)+coeff[12]*((start.x)*(start.x))+coeff[13]*((start.x)*(start.y))+coeff[14]*((start.x)*(start.z))+coeff[15]*(start.y)+coeff[16]*((start.y)*(start.y))+coeff[17]*((start.y)*(start.z))+coeff[18]*(start.z)+coeff[19]*((start.z)*(start.z));
      out.z = coeff[20]+coeff[21]*(start.x)+coeff[22]*((start.x)*(start.x))+coeff[23]*((start.x)*(start.y))+coeff[24]*((start.x)*(start.z))+coeff[25]*(start.y)+coeff[26]*((start.y)*(start.y))+coeff[27]*((start.y)*(start.z))+coeff[28]*(start.z)+coeff[29]*((start.z)*(start.z));
    	}      
      if(order==3)
	{
	  out.x = out.x + coeff[0];
	  out.x = out.x + coeff[1]*(start.x);
	  out.x = out.x + coeff[2]*((start.x)*(start.x));
	  out.x = out.x + coeff[3]*((start.x)*(start.x)*(start.x));
	  out.x = out.x + coeff[4]*((start.x)*(start.x)*(start.y));
	  out.x = out.x + coeff[5]*((start.x)*(start.x)*(start.z));
	  out.x = out.x + coeff[6]*((start.x)*(start.y));
	  out.x = out.x + coeff[7]*((start.x)*(start.y)*(start.y));
         out.x = out.x + coeff[8]*((start.x)*(start.y)*(start.z));
         out.x = out.x + coeff[9]*((start.x)*(start.z));
         out.x = out.x + coeff[10]*((start.x)*(start.z)*(start.z));
         out.x = out.x + coeff[11]*(start.y);
         out.x = out.x + coeff[12]*((start.y)*(start.y));
         out.x = out.x + coeff[13]*((start.y)*(start.y)*(start.y));
         out.x = out.x + coeff[14]*((start.y)*(start.y)*(start.z));
         out.x = out.x + coeff[15]*((start.y)*(start.z));
         out.x = out.x + coeff[16]*((start.y)*(start.z)*(start.z));
         out.x = out.x + coeff[17]*(start.z);
         out.x = out.x + coeff[18]*((start.z)*(start.z));
         out.x = out.x + coeff[19]*((start.z)*(start.z)*(start.z));
         
         
         out.y = out.y + coeff[20];
         out.y = out.y + coeff[21]*(start.x);
         out.y = out.y + coeff[22]*((start.x)*(start.x));
         out.y = out.y + coeff[23]*((start.x)*(start.x)*(start.x));
         out.y = out.y + coeff[24]*((start.x)*(start.x)*(start.y));
         out.y = out.y + coeff[25]*((start.x)*(start.x)*(start.z));
         out.y = out.y + coeff[26]*((start.x)*(start.y));
         out.y = out.y + coeff[27]*((start.x)*(start.y)*(start.y));
         out.y = out.y + coeff[28]*((start.x)*(start.y)*(start.z));
         out.y = out.y + coeff[29]*((start.x)*(start.z));
         out.y = out.y + coeff[30]*((start.x)*(start.z)*(start.z));
         out.y = out.y + coeff[31]*(start.y);
         out.y = out.y + coeff[32]*((start.y)*(start.y));
         out.y = out.y + coeff[33]*((start.y)*(start.y)*(start.y));
         out.y = out.y + coeff[34]*((start.y)*(start.y)*(start.z));
         out.y = out.y + coeff[35]*((start.y)*(start.z));
         out.y = out.y + coeff[36]*((start.y)*(start.z)*(start.z));
         out.y = out.y + coeff[37]*(start.z);
         out.y = out.y + coeff[38]*((start.z)*(start.z));
         out.y = out.y + coeff[39]*((start.z)*(start.z)*(start.z));
         
         out.z = out.z + coeff[40];
         out.z = out.z + coeff[41]*(start.x);
         out.z = out.z + coeff[42]*((start.x)*(start.x));
         out.z = out.z + coeff[43]*((start.x)*(start.x)*(start.x));
         out.z = out.z + coeff[44]*((start.x)*(start.x)*(start.y));
         out.z = out.z + coeff[45]*((start.x)*(start.x)*(start.z));
         out.z = out.z + coeff[46]*((start.x)*(start.y));
         out.z = out.z + coeff[47]*((start.x)*(start.y)*(start.y));
         out.z = out.z + coeff[48]*((start.x)*(start.y)*(start.z));
         out.z = out.z + coeff[49]*((start.x)*(start.z));
         out.z = out.z + coeff[50]*((start.x)*(start.z)*(start.z));
    
         out.z = out.z + coeff[51]*(start.y);
         out.z = out.z + coeff[52]*((start.y)*(start.y));
         out.z = out.z + coeff[53]*((start.y)*(start.y)*(start.y));
         out.z = out.z + coeff[54]*((start.y)*(start.y)*(start.z));
         out.z = out.z + coeff[55]*((start.y)*(start.z));
         out.z = out.z + coeff[56]*((start.y)*(start.z)*(start.z));
         out.z = out.z + coeff[57]*(start.z);
         out.z = out.z + coeff[58]*((start.z)*(start.z));
         out.z = out.z + coeff[59]*((start.z)*(start.z)*(start.z));
	}
      if(order==4)
	{

	  /* good, works, tested */
	  out.x = out.x + coeff[0];
	  out.x = out.x + coeff[1]*sx;
	  out.x = out.x + coeff[2]*sx*sx;
	  out.x = out.x + coeff[3]*sx*sx*sx;
	  out.x = out.x + coeff[4]*sx*sx*sx*sx;
	  out.x = out.x + coeff[5]*sx*sx*sx*sy;
	  out.x = out.x + coeff[6]*sx*sx*sx*sz;
	  out.x = out.x + coeff[7]*sx*sx*sy;
	  out.x = out.x + coeff[8]*sx*sx*sy*sy;
	  out.x = out.x + coeff[9]*sx*sx*sy*sz;
	  out.x = out.x + coeff[10]*sx*sx*sz;
	  out.x = out.x + coeff[11]*sx*sx*sz*sz;
	  out.x = out.x + coeff[12]*sx*sy;
	  out.x = out.x + coeff[13]*sx*sy*sy;
	  out.x = out.x + coeff[14]*sx*sy*sy*sy;
	  out.x = out.x + coeff[15]*sx*sy*sy*sz;
	  out.x = out.x + coeff[16]*sx*sy*sz;
	  out.x = out.x + coeff[17]*sx*sy*sz*sz;
	  out.x = out.x + coeff[18]*sx*sz;
	  out.x = out.x + coeff[19]*sx*sz*sz;
	  out.x = out.x + coeff[20]*sx*sz*sz*sz;
	  out.x = out.x + coeff[21]*sy;
	  out.x = out.x + coeff[22]*sy*sy;
	  out.x = out.x + coeff[23]*sy*sy*sy;
	  out.x = out.x + coeff[24]*sy*sy*sy*sy;
	  out.x = out.x + coeff[25]*sy*sy*sy*sz;
	  out.x = out.x + coeff[26]*sy*sy*sz;
	  out.x = out.x + coeff[27]*sy*sy*sz*sz;
	  out.x = out.x + coeff[28]*sy*sz;
	  out.x = out.x + coeff[29]*sy*sz*sz;
	  out.x = out.x + coeff[30]*sy*sz*sz*sz;
	  out.x = out.x + coeff[31]*sz;
	  out.x = out.x + coeff[32]*sz*sz;
	  out.x = out.x + coeff[33]*sz*sz*sz;
	  out.x = out.x + coeff[34]*sz*sz*sz*sz;

	  out.y = out.y + coeff[35];
	  out.y = out.y + coeff[36]*sx;
	  out.y = out.y + coeff[37]*sx*sx;
	  out.y = out.y + coeff[38]*sx*sx*sx;
	  out.y = out.y + coeff[39]*sx*sx*sx*sx;
	  out.y = out.y + coeff[40]*sx*sx*sx*sy;
	  out.y = out.y + coeff[41]*sx*sx*sx*sz;
	  out.y = out.y + coeff[42]*sx*sx*sy;
	  out.y = out.y + coeff[43]*sx*sx*sy*sy;
	  out.y = out.y + coeff[44]*sx*sx*sy*sz;
	  out.y = out.y + coeff[45]*sx*sx*sz;
	  out.y = out.y + coeff[46]*sx*sx*sz*sz;
	  out.y = out.y + coeff[47]*sx*sy;
	  out.y = out.y + coeff[48]*sx*sy*sy;
	  out.y = out.y + coeff[49]*sx*sy*sy*sy;
	  out.y = out.y + coeff[50]*sx*sy*sy*sz;
	  out.y = out.y + coeff[51]*sx*sy*sz;
	  out.y = out.y + coeff[52]*sx*sy*sz*sz;
	  out.y = out.y + coeff[53]*sx*sz;
	  out.y = out.y + coeff[54]*sx*sz*sz;
	  out.y = out.y + coeff[55]*sx*sz*sz*sz;
	  out.y = out.y + coeff[56]*sy;
	  out.y = out.y + coeff[57]*sy*sy;
	  out.y = out.y + coeff[58]*sy*sy*sy;
	  out.y = out.y + coeff[59]*sy*sy*sy*sy;
	  out.y = out.y + coeff[60]*sy*sy*sy*sz;
	  out.y = out.y + coeff[61]*sy*sy*sz;
	  out.y = out.y + coeff[62]*sy*sy*sz*sz;
	  out.y = out.y + coeff[63]*sy*sz;
	  out.y = out.y + coeff[64]*sy*sz*sz;
	  out.y = out.y + coeff[65]*sy*sz*sz*sz;
	  out.y = out.y + coeff[66]*sz;
	  out.y = out.y + coeff[67]*sz*sz;
	  out.y = out.y + coeff[68]*sz*sz*sz;
	  out.y = out.y + coeff[69]*sz*sz*sz*sz;

	  out.z = out.z + coeff[70];
	  out.z = out.z + coeff[71]*sx;
	  out.z = out.z + coeff[72]*sx*sx;
	  out.z = out.z + coeff[73]*sx*sx*sx;
	  out.z = out.z + coeff[74]*sx*sx*sx*sx;
	  out.z = out.z + coeff[75]*sx*sx*sx*sy;
	  out.z = out.z + coeff[76]*sx*sx*sx*sz;
	  out.z = out.z + coeff[77]*sx*sx*sy;
	  out.z = out.z + coeff[78]*sx*sx*sy*sy;
	  out.z = out.z + coeff[79]*sx*sx*sy*sz;
	  out.z = out.z + coeff[80]*sx*sx*sz;
	  out.z = out.z + coeff[81]*sx*sx*sz*sz;
	  out.z = out.z + coeff[82]*sx*sy;
	  out.z = out.z + coeff[83]*sx*sy*sy;
	  out.z = out.z + coeff[84]*sx*sy*sy*sy;
	  out.z = out.z + coeff[85]*sx*sy*sy*sz;
	  out.z = out.z + coeff[86]*sx*sy*sz;
	  out.z = out.z + coeff[87]*sx*sy*sz*sz;
	  out.z = out.z + coeff[88]*sx*sz;
	  out.z = out.z + coeff[89]*sx*sz*sz;
	  out.z = out.z + coeff[90]*sx*sz*sz*sz;
	  out.z = out.z + coeff[91]*sy;
	  out.z = out.z + coeff[92]*sy*sy;
	  out.z = out.z + coeff[93]*sy*sy*sy;
	  out.z = out.z + coeff[94]*sy*sy*sy*sy;
	  out.z = out.z + coeff[95]*sy*sy*sy*sz;
	  out.z = out.z + coeff[96]*sy*sy*sz;
	  out.z = out.z + coeff[97]*sy*sy*sz*sz;
	  out.z = out.z + coeff[98]*sy*sz;
	  out.z = out.z + coeff[99]*sy*sz*sz;
	  out.z = out.z + coeff[100]*sy*sz*sz*sz;
	  out.z = out.z + coeff[101]*sz;
	  out.z = out.z + coeff[102]*sz*sz;
	  out.z = out.z + coeff[103]*sz*sz*sz;
	  out.z = out.z + coeff[104]*sz*sz*sz*sz;
	}
      if(order == 5)
	{
	  /* there is a problem here and I do not know what is
	     yet. */

	  /* X = a1  */
	  out.x = out.x + coeff[0];
	  /* + a2X +  */
	  out.x = out.x + coeff[1]*sx;
	  /* a3X2 +  */
	  out.x = out.x + coeff[2]*sx2;
	  /* a4X3 +  */
	  out.x = out.x + coeff[3]*sx3;
	  /* a5X4 +  */
	  out.x = out.x + coeff[4]*sx4;
	  /* a6X5 +  */
	  out.x = out.x + coeff[5]*sx5;
	  /* a7X4Y +  */
	  out.x = out.x + coeff[6]*sx4*sy;
	  /* a8X4Z +  */
	  out.x = out.x + coeff[7]*sx4*sz;
	  /* a9X3Y +  */
	  out.x = out.x + coeff[8]*sx3*sy;
	  /* a10X3Y2 +  */
	  out.x = out.x + coeff[9]*sx3*sy2;
	  /* a11X3YZ + */
	  out.x = out.x + coeff[10]*sx3*sy*sz;
	  /* a12X3Z +  */
	  out.x = out.x + coeff[11]*sx3*sz;
	  /* a13X3Z2 +  */
	  out.x = out.x + coeff[12]*sx3*sz2;
	  /* a14X2Y +  */
	  out.x = out.x + coeff[13]*sx2*sy;
	  /* a15X2Y2 +  */
	  out.x = out.x + coeff[14]*sx2*sy2;
	  /* a16X2Y3 +  */
	  out.x = out.x + coeff[15]*sx2*sy3;
	  /* a17X2Y2Z +  */
	  out.x = out.x + coeff[16]*sx2*sy2*sz;
	  /* a18X2YZ +  */
	  out.x = out.x + coeff[17]*sx2*sy*sz;
	  /* a19X2YZ2 +  */
	  out.x = out.x + coeff[18]*sx2*sy*sz2;
	  /* a20X2Z + */
	  out.x = out.x + coeff[19]*sx2*sz;
	  /* a21X2Z2 +  */
	  out.x = out.x + coeff[20]*sx2*sz2;
	  /* a22X2Z3 +  */
	  out.x = out.x + coeff[21]*sx2*sz3;
	  /* a23XY +  */
	  out.x = out.x + coeff[22]*sx*sy;
	  /* a24XY2 +  */
	  out.x = out.x + coeff[23]*sx*sy2;
	  /* a25XY3 +  */
	  out.x = out.x + coeff[24]*sx*sy3;
	  /* a26XY4 +  */
	  out.x = out.x + coeff[25]*sx*sy4;
	  /* a27XY3Z +  */
	  out.x = out.x + coeff[26]*sx*sy3*sz;
	  /* a28XY2Z +  */
	  out.x = out.x + coeff[27]*sx*sy2*sz;
	  /* a29XY2Z2 +  */
	  out.x = out.x + coeff[28]*sx*sy2*sz2;
	  /* a30XYZ +  */
	  out.x = out.x + coeff[29]*sx*sy*sz;
	  /* a31XYZ2 +  */
	  out.x = out.x + coeff[30]*sx*sy*sz2;
	  /* a32XYZ3 +  */
	  out.x = out.x + coeff[31]*sx*sy*sz3;
	  /* a33XZ +  */
	  out.x = out.x + coeff[32]*sx*sz;
	  /* a34XZ2 +  */
	  out.x = out.x + coeff[33]*sx*sz2;
	  /* a35XZ3 +  */
	  out.x = out.x + coeff[34]*sx*sz3;
	  /* a36XZ4 +  */
	  out.x = out.x + coeff[35]*sx*sz4;
	  /* a37Y +  */
	  out.x = out.x + coeff[36]*sy;
	  /* a38Y2 +  */
	  out.x = out.x + coeff[37]*sy2;
	  /* a39Y3 +  */
	  out.x = out.x + coeff[38]*sy3;
	  /* a40Y4 + */
	  out.x = out.x + coeff[39]*sy4;
	  /* a41Y5 +  */
	  out.x = out.x + coeff[40]*sy5;
	  /* a42Y4Z +  */
	  out.x = out.x + coeff[41]*sy4*sz;
	  /* a43Y3Z +  */
	  out.x = out.x + coeff[42]*sy3*sz;
	  /* a44Y3Z2 +  */
	  out.x = out.x + coeff[43]*sy3*sz2;
	  /* a45Y2Z +  */
	  out.x = out.x + coeff[44]*sy2*sz;
	  /* a46Y2Z2 +  */
	  out.x = out.x + coeff[45]*sy2*sz2;
	  /* a47Y2Z3 +  */
	  out.x = out.x + coeff[46]*sy2*sz3;
	  /* a48YZ +  */
	  out.x = out.x + coeff[47]*sy*sz;
	  /* a49YZ2 +  */
	  out.x = out.x + coeff[48]*sy*sz2;
	  /* a50YZ3+  */
	  out.x = out.x + coeff[49]*sy*sz3;
	  /* a51YZ4 +  */
	  out.x = out.x + coeff[50]*sy*sz4;
	  /* a52Z +  */
	  out.x = out.x + coeff[51]*sz;
	  /* a53Z2 +  */
	  out.x = out.x + coeff[52]*sz2;
	  /* a54Z3 +  */
	  out.x = out.x + coeff[53]*sz3;
	  /* a55Z4 +  */
	  out.x = out.x + coeff[54]*sz4;
	  /* a56Z5 */
	  out.x = out.x + coeff[55]*sz5;

	  /* X = a1  */
	  out.y = out.y + coeff[56];
	  /* + a2X +  */
	  out.y = out.y + coeff[57]*sx;
	  /* a3X2 +  */
	  out.y = out.y + coeff[58]*sx2;
	  /* a4X3 +  */
	  out.y = out.y + coeff[59]*sx3;
	  /* a5X4 +  */
	  out.y = out.y + coeff[60]*sx4;
	  /* a6X5 +  */
	  out.y = out.y + coeff[61]*sx5;
	  /* a7X4Y +  */
	  out.y = out.y + coeff[62]*sx4*sy;
	  /* a8X4Z +  */
	  out.y = out.y + coeff[63]*sx4*sz;
	  /* a9X3Y +  */
	  out.y = out.y + coeff[64]*sx3*sy;
	  /* a10X3Y2 +  */
	  out.y = out.y + coeff[65]*sx3*sy2;
	  /* a11X3YZ + */
	  out.y = out.y + coeff[66]*sx3*sy*sz;
	  /* a12X3Z +  */
	  out.y = out.y + coeff[67]*sx3*sz;
	  /* a13X3Z2 +  */
	  out.y = out.y + coeff[68]*sx3*sz2;
	  /* a14X2Y +  */
	  out.y = out.y + coeff[69]*sx2*sy;
	  /* a15X2Y2 +  */
	  out.y = out.y + coeff[70]*sx2*sy2;
	  /* a16X2Y3 +  */
	  out.y = out.y + coeff[71]*sx2*sy3;
	  /* a17X2Y2Z +  */
	  out.y = out.y + coeff[72]*sx2*sy2*sz;
	  /* a18X2YZ +  */
	  out.y = out.y + coeff[73]*sx2*sy*sz;
	  /* a19X2YZ2 +  */
	  out.y = out.y + coeff[74]*sx2*sy*sz2;
	  /* a20X2Z + */
	  out.y = out.y + coeff[75]*sx2*sz;
	  /* a21X2Z2 +  */
	  out.y = out.y + coeff[76]*sx2*sz2;
	  /* a22X2Z3 +  */
	  out.y = out.y + coeff[77]*sx2*sz3;
	  /* a23XY +  */
	  out.y = out.y + coeff[78]*sx*sy;
	  /* a24XY2 +  */
	  out.y = out.y + coeff[79]*sx*sy2;
	  /* a25XY3 +  */
	  out.y = out.y + coeff[80]*sx*sy3;
	  /* a26XY4 +  */
	  out.y = out.y + coeff[81]*sx*sy4;
	  /* a27XY3Z +  */
	  out.y = out.y + coeff[82]*sx*sy3*sz;
	  /* a28XY2Z +  */
	  out.y = out.y + coeff[83]*sx*sy2*sz;
	  /* a29XY2Z2 +  */
	  out.y = out.y + coeff[84]*sx*sy2*sz2;
	  /* a30XYZ +  */
	  out.y = out.y + coeff[85]*sx*sy*sz;
	  /* a31XYZ2 +  */
	  out.y = out.y + coeff[86]*sx*sy*sz2;
	  /* a32XYZ3 +  */
	  out.y = out.y + coeff[87]*sx*sy*sz3;
	  /* a33XZ +  */
	  out.y = out.y + coeff[88]*sx*sz;
	  /* a34XZ2 +  */
	  out.y = out.y + coeff[89]*sx*sz2;
	  /* a35XZ3 +  */
	  out.y = out.y + coeff[90]*sx*sz3;
	  /* a36XZ4 +  */
	  out.y = out.y + coeff[91]*sx*sz4;
	  /* a37Y +  */
	  out.y = out.y + coeff[92]*sy;
	  /* a38Y2 +  */
	  out.y = out.y + coeff[93]*sy2;
	  /* a39Y3 +  */
	  out.y = out.y + coeff[94]*sy3;
	  /* a40Y4 + */
	  out.y = out.y + coeff[95]*sy4;
	  /* a41Y5 +  */
	  out.y = out.y + coeff[96]*sy5;
	  /* a42Y4Z +  */
	  out.y = out.y + coeff[97]*sy4*sz;
	  /* a43Y3Z +  */
	  out.y = out.y + coeff[98]*sy3*sz;
	  /* a44Y3Z2 +  */
	  out.y = out.y + coeff[99]*sy3*sz2;
	  /* a45Y2Z +  */
	  out.y = out.y + coeff[100]*sy2*sz;
	  /* a46Y2Z2 +  */
	  out.y = out.y + coeff[101]*sy2*sz2;
	  /* a47Y2Z3 +  */
	  out.y = out.y + coeff[102]*sy2*sz3;
	  /* a48YZ +  */
	  out.y = out.y + coeff[103]*sy*sz;
	  /* a49YZ2 +  */
	  out.y = out.y + coeff[104]*sy*sz2;
	  /* a50YZ3+  */
	  out.y = out.y + coeff[105]*sy*sz3;
	  /* a51YZ4 +  */
	  out.y = out.y + coeff[106]*sy*sz4;
	  /* a52Z +  */
	  out.y = out.y + coeff[107]*sz;
	  /* a53Z2 +  */
	  out.y = out.y + coeff[108]*sz2;
	  /* a54Z3 +  */
	  out.y = out.y + coeff[109]*sz3;
	  /* a55Z4 +  */
	  out.y = out.y + coeff[110]*sz4;
	  /* a56Z5 */
	  out.y = out.y + coeff[111]*sz5;

	  /* X = a1  */
	  out.z = out.z + coeff[112];
	  /* + a2X +  */
	  out.z = out.z + coeff[113]*sx;
	  /* a3X2 +  */
	  out.z = out.z + coeff[114]*sx2;
	  /* a4X3 +  */
	  out.z = out.z + coeff[115]*sx3;
	  /* a5X4 +  */
	  out.z = out.z + coeff[116]*sx4;
	  /* a6X5 +  */
	  out.z = out.z + coeff[117]*sx5;
	  /* a7X4Y +  */
	  out.z = out.z + coeff[118]*sx4*sy;
	  /* a8X4Z +  */
	  out.z = out.z + coeff[119]*sx4*sz;
	  /* a9X3Y +  */
	  out.z = out.z + coeff[120]*sx3*sy;
	  /* a10X3Y2 +  */
	  out.z = out.z + coeff[121]*sx3*sy2;
	  /* a11X3YZ + */
	  out.z = out.z + coeff[122]*sx3*sy*sz;
	  /* a12X3Z +  */
	  out.z = out.z + coeff[123]*sx3*sz;
	  /* a13X3Z2 +  */
	  out.z = out.z + coeff[124]*sx3*sz2;
	  /* a14X2Y +  */
	  out.z = out.z + coeff[125]*sx2*sy;
	  /* a15X2Y2 +  */
	  out.z = out.z + coeff[126]*sx2*sy2;
	  /* a16X2Y3 +  */
	  out.z = out.z + coeff[127]*sx2*sy3;
	  /* a17X2Y2Z +  */
	  out.z = out.z + coeff[128]*sx2*sy2*sz;
	  /* a18X2YZ +  */
	  out.z = out.z + coeff[129]*sx2*sy*sz;
	  /* a19X2YZ2 +  */
	  out.z = out.z + coeff[130]*sx2*sy*sz2;
	  /* a20X2Z + */
	  out.z = out.z + coeff[131]*sx2*sz;
	  /* a21X2Z2 +  */
	  out.z = out.z + coeff[132]*sx2*sz2;
	  /* a22X2Z3 +  */
	  out.z = out.z + coeff[133]*sx2*sz3;
	  /* a23XY +  */
	  out.z = out.z + coeff[134]*sx*sy;
	  /* a24XY2 +  */
	  out.z = out.z + coeff[135]*sx*sy2;
	  /* a25XY3 +  */
	  out.z = out.z + coeff[136]*sx*sy3;
	  /* a26XY4 +  */
	  out.z = out.z + coeff[137]*sx*sy4;
	  /* a27XY3Z +  */
	  out.z = out.z + coeff[138]*sx*sy3*sz;
	  /* a28XY2Z +  */
	  out.z = out.z + coeff[139]*sx*sy2*sz;
	  /* a29XY2Z2 +  */
	  out.z = out.z + coeff[140]*sx*sy2*sz2;
	  /* a30XYZ +  */
	  out.z = out.z + coeff[141]*sx*sy*sz;
	  /* a31XYZ2 +  */
	  out.z = out.z + coeff[142]*sx*sy*sz2;
	  /* a32XYZ3 +  */
	  out.z = out.z + coeff[143]*sx*sy*sz3;
	  /* a33XZ +  */
	  out.z = out.z + coeff[144]*sx*sz;
	  /* a34XZ2 +  */
	  out.z = out.z + coeff[145]*sx*sz2;
	  /* a35XZ3 +  */
	  out.z = out.z + coeff[146]*sx*sz3;
	  /* a36XZ4 +  */
	  out.z = out.z + coeff[147]*sx*sz4;
	  /* a37Y +  */
	  out.z = out.z + coeff[148]*sy;
	  /* a38Y2 +  */
	  out.z = out.z + coeff[149]*sy2;
	  /* a39Y3 +  */
	  out.z = out.z + coeff[150]*sy3;
	  /* a40Y4 + */
	  out.z = out.z + coeff[151]*sy4;
	  /* a41Y5 +  */
	  out.z = out.z + coeff[152]*sy5;
	  /* a42Y4Z +  */
	  out.z = out.z + coeff[153]*sy4*sz;
	  /* a43Y3Z +  */
	  out.z = out.z + coeff[154]*sy3*sz;
	  /* a44Y3Z2 +  */
	  out.z = out.z + coeff[155]*sy3*sz2;
	  /* a45Y2Z +  */
	  out.z = out.z + coeff[156]*sy2*sz;
	  /* a46Y2Z2 +  */
	  out.z = out.z + coeff[157]*sy2*sz2;
	  /* a47Y2Z3 +  */
	  out.z = out.z + coeff[158]*sy2*sz3;
	  /* a48YZ +  */
	  out.z = out.z + coeff[159]*sy*sz;
	  /* a49YZ2 +  */
	  out.z = out.z + coeff[160]*sy*sz2;
	  /* a50YZ3+  */
	  out.z = out.z + coeff[161]*sy*sz3;
	  /* a51YZ4 +  */
	  out.z = out.z + coeff[162]*sy*sz4;
	  /* a52Z +  */
	  out.z = out.z + coeff[163]*sz;
	  /* a53Z2 +  */
	  out.z = out.z + coeff[164]*sz2;
	  /* a54Z3 +  */
	  out.z = out.z + coeff[165]*sz3;
	  /* a55Z4 +  */
	  out.z = out.z + coeff[166]*sz4;
	  /* a56Z5 */
	  out.z = out.z + coeff[167]*sz5;



	 
	}
      /* here is the modification that gets us the differential equation mode */
      point or;
      or.x = sx + 0.1*out.x;
      or.y = sy + 0.1*out.y;
      or.z = sz + 0.1*out.z;


      return or;
    }
  /* since the purpose of this program is to test the transformation, we're going to just run the argument transformation of the point 1.1, -1.1, 0.2 */
  current.x=1.1;
  current.y=-1.1;
  current.z=0.2;
  next=transformation(current);
  printf("The transformation of point (%f,%f,%f) is point (%f,%f,%f)\n",current.x,current.y,current.z,next.x,next.y,next.z);

  /* ##### block 4: calculate the bounding box of a given transformation ##### */
  /* This step is necessary because we don't know what the extent of an attractor is, and */
  /* at this stage, we're not actively searching for Sprott type attractors, we're just */
  /* assuming that we're not dealing with a fixed point, but we've got to check against that anyway */
  /* since fixed points aren't readily plottable. This would be the ideal place to insert Lyapunov */
  /* searching code later */

  /* initialize the first point to (0,0,0) */
  current.x=-drand48(); current.y=-drand48(); current.z=-drand48();
  /* hey, we need an itercount; declared above */
  /* make an initial bounding box of the unit cube */
  xmin=0.0; xmax=0.0;
  ymin=0.0; ymax=0.0;
  zmin=0.0; zmax=0.0;
  /* hey, I can define functions as I'm programming! I don't need to keep all the function */
  /* definitions at the beginning of the program */

  /* the below function calculates the volume of the bounding box */

  /* preseed step, get rid of any initial transients */

  for(aur=0;aur<1000;aur++)
    {
      next=transformation(current);
      current=next;
    }

  double bboxvol(double xsmall, double xlarge, double ysmall, double ylarge, double zsmall, double zlarge)
    {
      double outtmp;
      outtmp = (xlarge-xsmall)*(ylarge-ysmall)*(zlarge-zsmall);
      return outtmp;
    }
  
  for(bboxitercount=0;bboxitercount<15000000;bboxitercount++)
    {
      next=transformation(current);
      if(next.x>xmax)
	{
	  printf("iteration %d: xmax increased! bounding box has changed from:\n",bboxitercount);
	  printf("iteration %d: [%f,%f]x[%f,%f]x[%f,%f] to [%f,%f]x[%f,%f]x[%f,%f]\n",bboxitercount,xmin,xmax,ymin,ymax,zmin,zmax,xmin,next.x,ymin,ymax,zmin,zmax);
	  printf("iteration %d: bounding box volume changed from %f to %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,ymax,zmin,zmax), bboxvol(xmin,next.x,ymin,ymax,zmin,zmax));

	  printf("dboxvol: %d %f\n", bboxitercount, bboxvol(xmin,next.x,ymin,ymax,zmin,zmax)-bboxvol(xmin,xmax,ymin,ymax,zmin,zmax));
	  xmax=next.x;
	}
      if(next.y>ymax)
	{
	  printf("iteration %d: ymax increased! bounding box has changed from:\n",bboxitercount);
	  printf("iteration %d: [%f,%f]x[%f,%f]x[%f,%f] to [%f,%f]x[%f,%f]x[%f,%f]\n",bboxitercount,xmin,xmax,ymin,ymax,zmin,zmax,xmin,xmax,ymin,next.y,zmin,zmax);
	  printf("iteration %d: bounding box volume changed from %f to %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,ymax,zmin,zmax), bboxvol(xmin,xmax,ymin,next.y,zmin,zmax));
	  printf("dboxvol: %d %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,next.y,zmin,zmax)-bboxvol(xmin,xmax,ymin,ymax,zmin,zmax));
	  ymax=next.y;
	}
      if(next.z>zmax)
	{
	  printf("iteration %d: zmax increased! bounding box has changed from:\n",bboxitercount);
	  printf("iteration %d: [%f,%f]x[%f,%f]x[%f,%f] to [%f,%f]x[%f,%f]x[%f,%f]\n",bboxitercount,xmin,xmax,ymin,ymax,zmin,zmax,xmin,xmax,ymin,ymax,zmin,next.z);
	  printf("iteration %d: bounding box volume changed from %f to %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,ymax,zmin,zmax), bboxvol(xmin,xmax,ymin,ymax,zmin,next.z));
	  printf("dboxvol: %d %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,ymax,zmin,next.z)-bboxvol(xmin,xmax,ymin,ymax,zmin,zmax));
	  zmax=next.z;
	}
      if(next.x<xmin)
	{
	  
	  printf("iteration %d: xmin decreased! bounding box has changed from:\n",bboxitercount);
	  printf("iteration %d: [%f,%f]x[%f,%f]x[%f,%f] to [%f,%f]x[%f,%f]x[%f,%f]\n",bboxitercount,xmin,xmax,ymin,ymax,zmin,zmax,next.x,xmax,ymin,ymax,zmin,zmax);
	  printf("iteration %d: bounding box volume changed from %f to %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,ymax,zmin,zmax), bboxvol(next.x,xmax,ymin,ymax,zmin,zmax));
	  
	  printf("dboxvol: %d %f\n", bboxitercount,bboxvol(next.x,xmax,ymin,ymax,zmin,zmax)-bboxvol(xmin,xmax,ymin,ymax,zmin,zmax));
	  xmin=next.x;
	}
      if(next.y<ymin)
	{
	  printf("iteration %d: ymin decreased! bounding box has changed from:\n",bboxitercount);
	  printf("iteration %d: [%f,%f]x[%f,%f]x[%f,%f] to [%f,%f]x[%f,%f]x[%f,%f]\n",bboxitercount,xmin,xmax,ymin,ymax,zmin,zmax,xmin,xmax,next.y,ymax,zmin,zmax);
	  printf("iteration %d: bounding box volume changed from %f to %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,ymax,zmin,zmax), bboxvol(xmin,xmax,next.y,ymax,zmin,zmax));
	  
	  printf("dboxvol: %d %f\n", bboxitercount, bboxvol(xmin,xmax,next.y,ymax,zmin,zmax)-bboxvol(xmin,xmax,ymin,ymax,zmin,zmax));
	  ymin=next.y;
	}
      if(next.z<zmin)
	{
	  printf("iteration %d: zmin decreased! bounding box has changed from:\n",bboxitercount);
	  printf("iteration %d: [%f,%f]x[%f,%f]x[%f,%f] to [%f,%f]x[%f,%f]x[%f,%f]\n",bboxitercount,xmin,xmax,ymin,ymax,zmin,zmax,xmin,xmax,ymin,ymax,next.z,zmax);
	  printf("iteration %d: bounding box volume changed from %f to %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,ymax,zmin,zmax), bboxvol(xmin,xmax,ymin,ymax,next.z,zmax));
	  
	  printf("dboxvol: %d %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,ymax,next.z,zmax)-bboxvol(xmin,xmax,ymin,ymax,zmin,zmax));
	  zmin=next.z;
	}
      if(fabs(bboxvol(xmin,xmax,ymin,ymax,zmin,zmax))>100.0)
	{
	  printf("iteration %d: Bounding box volume is greater than one hundred.\n",bboxitercount);
	  printf("iteration %d: ABORTING EXECUTION\n", bboxitercount);
	  printf("iteration %d: bounding box volume is %f\n", bboxitercount, bboxvol(xmin,xmax,ymin,ymax,zmin,zmax));
	  return 0;
	}
      current=next;
    }
  printf("################################################\n");

  printf("10 MILLION ITERATIONS COMPLETE:\n");
  printf("After 10 million iterations, the bounding box is [%f,%f]x[%f,%f]x[%f,%f]\n",xmin,xmax,ymin,ymax,zmin,zmax);
  printf("The volume of the bounding box is %f\n", bboxvol(xmin,xmax,ymin,ymax,zmin,zmax));

  /* calculate the spans from the bounding box data */
  xspan=xmax-xmin; 
  yspan=ymax-ymin;
  zspan=zmax-zmin;
 
  /* calculate the radii from the spans */
  xrad=xspan/2.0;
  yrad=yspan/2.0;
  zrad=zspan/2.0;
  
  /* calculate the center from the radii and the bounding box data */
  xcen=xmin+xrad;
  ycen=ymin+yrad;
  zcen=zmin+zrad;

  printf("x span: %f, x center: %f, x radius: %f\n", xspan, xcen, xrad);
  printf("y span: %f, y center: %f, y radius: %f\n", yspan, ycen, yrad);
  printf("z span: %f, z center: %f, z radius: %f\n", zspan, zcen, zrad);

  /* Now we have collected the data, we are ready to make a cubical bounding box which */
  /* contains the bounding box we're interested in looking at as a subset. */

  double max(double a, double b, double c)
    {
      if((a>b) && (a>c))
	{
	  return a;
	}
      if((b>a) && (b>c))
	{
	  return b;
	}
      if((c>a) && (c>b))
	{
	  return c;
	}
    }
  maxrad =max(xrad,yrad,zrad);
  printf("maximum radius is %f\n", maxrad);
  maxrad = maxrad + 0.001;
  printf("increased maxrad by 0.001 to %f\n", maxrad);
  
  /* Since I'm a signatory to the Variable Nonproliferation Treaty */
  /* I'm going to reuse xmin,xmax,ymin,ymax,zmin, and zmax now */

  xmin=xcen-maxrad;
  xmax=xcen+maxrad;
  
  ymin=ycen-maxrad;
  ymax=ycen+maxrad;

  zmin=zcen-maxrad;
  zmax=zcen+maxrad;

  /* announce the news */

  printf("Bounding cube parameters for ");
  printf(argv[1]);
  printf(" calculated:\n");
  printf("[%f,%f]x[%f,%f]x[%f,%f]\n",xmin,xmax,ymin,ymax,zmin,zmax);
  printf("with center at (%f,%f,%f)\n", xcen,ycen,zcen);

  /* ##### block 5 plot the attractor in the given bounding box ##### */

  /* note: current and next are wonderfully pre-seeded, and we'll just do ten million iterations below */

  /* first, seed the array to be eight bit white */
  for(m=0;m<768;m++)
    {
      for(n=0;n<768;n++)
	{
	  display[m][n]=255;
	}
    }
  /* using plotiter to count the plot iterations */
  for(plotiter=0;plotiter<15000000;plotiter++)
    {
      next=transformation(current);

      dispX= (int) (768.0*(next.x-xmin)/(xmax-xmin));
      dispY= (int) (768.0*(next.y-ymin)/(ymax-ymin));
      
      /*THIS IS THE DISPLAY ROUTINE! */
      if(display[768-dispY][dispX]>0)
	{
	  display[768-dispY][dispX]=display[768-dispY][dispX]-1;
	}
      else
	{
	  display[768-dispY][dispX]=0;
	}
      current=next;
    }
  /* finally, save the plotted array to a file */

  file=fopen(argv[1], "a");
  
  fprintf(file, "P2\n768 768\n255\n");
  for(m=0;m<768;m++)
    {
      for(n=0;n<768;n++)
	{
	  fprintf(file,"%d\n", display[m][n]);
	}
    }

  return 0;
}
