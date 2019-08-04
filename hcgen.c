static char help[]=
"Generator of Petri net model of hypercube grid\n"
"Product of Tatiana R. Shmeleva tishtri@rambler.ru\n\n" 
"USAGE: htgen e d k p b > pn_model.net \n"
"  e - edge: \'o\' - open, \'t\' - torus, \'r\' - truncated, \'g\' - plug,\n"
"  d - number of dimensions, k - size of hypercube,\n"
"  p - number of packets in each buffer section, b - available buffer size\n"
"  output format - .net file of Tina www.laas.fr/tina\n\n";

#include <stdio.h>
#include <stdlib.h>

/* print the current cell index */
#define PUTINDX { for( u=1; u<=d; u++) printf( ".%d", i[u] ); }

/* print the next cell index */
#define PUTINDXNEXT( r, e ) { for( u=1; u<=d; u++) if(e=='t') printf( ".%d", (u!=(r))? i[u] : (i[u]<k)? i[u]+1 : 1 ); else printf( ".%d", (u!=(r))? i[u] : i[u]+1 ); }

/* check edge */
#define CHECKEDGE( j, n ) {if( n==1&&i[j]==1 || n==2&&i[j]==k) che=1; else che=0;}

/* the port buffer size */
#define IOBL 1

int main( int argc, char * argv[] )
{
 int d, k, *i, j, u, v, dir, p, b;
 int loop, go;
 char e;
 int che;

 if( argc < 6 )
 {
   fprintf( stderr, "%s", help );
   exit(2);
 }
 else { e = argv[1][0]; d = atoi( argv[2] ); k = atoi( argv[3] ); p = atoi( argv[4] ); b = atoi( argv[5] );}
 if( e != 'o' && e != 't' && e != 'r' && e != 'g' )
 {
   fprintf( stderr, "%s", help );
   exit(2);
 }
 
 /* allocate the grid cell index i */
 i = (int *) malloc( (d+1)* sizeof( int ) );
 if( i == NULL )
 {
   printf( "*** not enough memory for i[]\n" );
   exit(2);
 }
 
 /* initialize index of the first grid node */
 for( j=1; j<=d; j++ ) i[j] = 1;

 loop=1;

 while( loop )
 {
   /* generate subnet for the current grid node */
   /* for on dimensions */
   for( j=1; j<=d; j++ )
   {
     /* direction 1 */
     /* output port */
     CHECKEDGE( j, 1 );
     if(!(e=='r'&&che))
     {
       printf( "tr {to.d%d.n1", j );
       PUTINDX;
       printf( "} {pol.d%d.n1", j );
       PUTINDX;
       printf( "} {pb.d%d.n1", j );
       PUTINDX;
       printf( "} -> {po.d%d.n1", j );
       PUTINDX;
       printf( "} {pbl" );
       PUTINDX;
       printf( "}\n" );
     
       /* packets in the buffer section */
       printf("pl {pb.d%d.n1", j);
       PUTINDX;
       printf("} (%d)\n", p);
     
       /* port buffer size */
       printf("pl {pol.d%d.n1", j);
       PUTINDX;
       printf("} (%d)\n", IOBL);
     
       /* input port */
       for( v=1; v<=d; v++ )
         for( dir=1; dir<=2; dir++ )
	     if( (v!=j) || (dir!=1) )
	     {
                CHECKEDGE( v, dir );
                if(!(e=='r'&&che))
                {
	          printf( "tr {ti.d%d.n1.d%d.n%d", j, v, dir );
	          PUTINDX;
	          printf( "} {pi.d%d.n1", j );
	          PUTINDX;
	          printf( "} {pbl" );
	          PUTINDX;
	          printf( "} -> {pil.d%d.n1", j );
	          PUTINDX;
	          printf( "} {pb.d%d.n%d", v, dir );
	          PUTINDX;
	          printf( "}\n" );
                }
	      } /* for v */
	 
       /* port buffer size */
       printf("pl {pil.d%d.n1", j);
       PUTINDX;
       printf("} (%d)\n", IOBL);
     } /* if(!(e=='r'&&che)) */

     /* edge: plug device */
     CHECKEDGE( j, 1 );
     if(e=='g'&&che)
     {
       printf( "tr {tg.d%d.n1", j );
       PUTINDX;
       printf( "} {po.d%d.n1", j );
       PUTINDX;
       printf( "} {pil.d%d.n1", j );
       PUTINDX;
       printf( "} -> {pi.d%d.n1", j );
       PUTINDX;
       printf( "} {pol.d%d.n1", j );
       PUTINDX;
       printf( "}\n" );
     }

     /* direction 2 */
     /* output port */
     CHECKEDGE( j, 2 );
     if(!(e=='r'&&che))
     {
       printf( "tr {to.d%d.n2", j );
       PUTINDX;
       printf( "} {pil.d%d.n1", j );
       PUTINDXNEXT( j, e );
       printf( "} {pb.d%d.n2", j );
       PUTINDX;
       printf( "} -> {pi.d%d.n1", j );
       PUTINDXNEXT( j, e );
       printf( "} {pbl" );
       PUTINDX;
       printf( "}\n" );
       
       /* packets in the buffer section */
       printf("pl {pb.d%d.n2", j);
       PUTINDX;
       printf("} (%d)\n", p);

       /* input port */
       for( v=1; v<=d; v++ )
	   for( dir=1; dir<=2; dir++ )
	     if( (v!=j) || (dir!=2) )
	     {
               CHECKEDGE( v, dir );
               if(!(e=='r'&&che))
               {
	         printf( "tr {ti.d%d.n2.d%d.n%d", j, v, dir );
	         PUTINDX;
	         printf( "} {po.d%d.n1", j );
	         PUTINDXNEXT( j, e );
	         printf( "} {pbl" );
	         PUTINDX;
	         printf( "} -> {pol.d%d.n1", j );
	         PUTINDXNEXT( j, e );
	         printf( "} {pb.d%d.n%d", v, dir );
	         PUTINDX;
	         printf( "}\n" );
               }
         } /* for v */
     } /* if(!(e=='r'&&che)) */

     /* edge: plug device */
     CHECKEDGE( j, 2 );
     if(e=='g'&&che)
     {
       printf( "tr {tg.d%d.n2", j );
       PUTINDXNEXT( j, e );
       printf( "} {po.d%d.n1", j );
       PUTINDXNEXT( j, e );
       printf( "} {pil.d%d.n1", j );
       PUTINDXNEXT( j, e );
       printf( "} -> {pi.d%d.n1", j );
       PUTINDXNEXT( j, e );
       printf( "} {pol.d%d.n1", j );
       PUTINDXNEXT( j, e );
       printf( "}\n" );
     } 
     	         
   } /* for j (on dimensions) */

   /* available size of the internal buffer */
   printf("pl {pbl" );
   PUTINDX;
   printf("} (%d)\n", b);

   /* calculate indices of the next grid cell */
   go = 1;
   j=d;
   while( go )
   {
     (i[j])++;
     if( i[j] > k )
     {
       if( j == 1 ) { loop=0; go=0; }
       else
       {
	     i[j]=1;
	     j--;
       }
     }
     else go=0;
   } /* while go */
 } /* while loop */

 printf("net ht%dd%dk%dp%db\n", d, k, p, b);
 free( i );
} /* main */

/*
The MIT License (MIT)

Copyright (c) 2019 Tatiana R. Shmeleva

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
