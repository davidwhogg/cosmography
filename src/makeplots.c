/* ----------------------------------------------------------------------------
   makeplots.c
-------------------------------------------------------------------------------

   This program makes output for plots of cosmological quantities as a
   function of z.

-------------------------------------------------------------------------------
   David W. Hogg / hogg@tapir.caltech.edu / May 1996
---------------------------------------------------------------------------- */
#include <stdio.h>
#define SLOPE(x)  (0.2*((log10(comvol((x)+dz,OmegaM[i],OmegaL[i]))-log10(comvol((x)-dz,OmegaM[i],OmegaL[i])))/(log10(lumdis((x)+dz,OmegaM[i],OmegaL[i]))-log10(lumdis((x)-dz,OmegaM[i],OmegaL[i])))))
#define NMODELS 3
#define LN10 (2.303)
#define PI (3.14159265)
#define PHISTAR (1.0e8)    /* in HV, from Lilly ?? */
#define MSTAR (-23.0)      /* for h=1, I band, from Lilly ?? */
#define DH (3.0e8)         /* for h=1, in units of 10 pc */

main()
{
/* initialize functions and variables */
  int i,j ;
  double pow(),log10(),dlookbackdz(),lookback(),dpropmotdisdz(),propmotdis(),
  angdidis(),lumdis(),dcomvoldz(),comvol(),intcomvol(),fabs(),schechter(),
  doptdepthdz(),
  z,zmin,zmax,dz,tmax[NMODELS],dH,z1,z2,s,s1,s2,m,M,dm,mmin,mmax,
  DM[NMODELS],N[NMODELS],x,alpha ;
  static double OmegaM[]= {1.0, 0.05, 0.2} ;
  static double OmegaL[]= {0.0, 0.00, 0.8} ;
  FILE *fp,*fopen() ;

/* make integrated volume plot */

  zmin= 0.0 ; zmax= 10.0 ; dz= 0.01 ;
  fp= fopen("comvol.out","w") ;
  for(z=zmin+0.5*dz;z<=zmax;z+=dz){
    fprintf(fp,"%8.4f",z) ;
    for(i=0;i<NMODELS;i++) fprintf(fp,"%11.6f",
				   comvol(z,OmegaM[i],OmegaL[i])) ;
    fprintf(fp,"\n") ;
  }
  fclose(fp) ;

/* make luminosity distance plot */

  zmin= 0.0 ; zmax= 10.0 ; dz= 0.01 ;
  fp= fopen("lumdis.out","w") ;
  for(z=zmin+0.5*dz;z<=zmax;z+=dz){
    fprintf(fp,"%8.4f",z) ;
    for(i=0;i<NMODELS;i++) fprintf(fp,"%11.6f",
				   lumdis(z,OmegaM[i],OmegaL[i])) ;
    fprintf(fp,"\n") ;
  }
  fclose(fp) ;

/* make proper motion distance plot */

  zmin= 0.0 ; zmax= 10.0 ; dz= 0.01 ;
  fp= fopen("propmotdis.out","w") ;
  for(z=zmin+0.5*dz;z<=zmax;z+=dz){
    fprintf(fp,"%8.4f",z) ;
    for(i=0;i<NMODELS;i++) fprintf(fp,"%11.6f",
				   propmotdis(z,OmegaM[i],OmegaL[i])) ;
    fprintf(fp,"\n") ;
  }
  fclose(fp) ;

/* make angular diameter distance plot */

  zmin= 0.0 ; zmax= 10.0 ; dz= 0.01 ;
  fp= fopen("angdidis.out","w") ;
  for(z=zmin+0.5*dz;z<=zmax;z+=dz){
    fprintf(fp,"%8.4f",z) ;
    for(i=0;i<NMODELS;i++) fprintf(fp,"%11.6f",
				   angdidis(z,OmegaM[i],OmegaL[i])) ;
    fprintf(fp,"\n") ;
  }
  fclose(fp) ;

/* make lookback time plot */

  zmin= 0.0 ; zmax= 10.0 ; dz= 0.01 ;
  fp= fopen("lookback.out","w") ;
  for(z=zmin+0.5*dz;z<=zmax;z+=dz){
    fprintf(fp,"%8.4f",z) ;
    for(i=0;i<NMODELS;i++) fprintf(fp,"%11.6f",
				   lookback(z,OmegaM[i],OmegaL[i])) ;
    fprintf(fp,"\n") ;
  }
  fclose(fp) ;

/* make age plot */

  zmin= 0.0 ; zmax= 10.0 ; dz= 0.01 ;
  fp= fopen("age.out","w") ;
  for(i=0;i<NMODELS;i++) tmax[i]= lookback(1.0e3,OmegaM[i],OmegaL[i]) ;
  for(z=zmin+0.5*dz;z<=zmax;z+=dz){
    fprintf(fp,"%8.4f",z) ;
    for(i=0;i<NMODELS;i++) fprintf(fp,"%11.6f",
				   tmax[i]-lookback(z,OmegaM[i],OmegaL[i])) ;
    fprintf(fp,"\n") ;
  }
  fclose(fp) ;

/* make comoving volume element plot */

  zmin= 0.0 ; zmax= 10.0 ; dz= 0.01 ;
  fp= fopen("dcomvoldz.out","w") ;
  for(z=zmin+0.5*dz;z<=zmax;z+=dz){
    fprintf(fp,"%8.4f",z) ;
    for(i=0;i<NMODELS;i++) fprintf(fp,"%11.6f",
				   dcomvoldz(z,OmegaM[i],OmegaL[i])) ;
    fprintf(fp,"\n") ;
  }
  fclose(fp) ;

/* make optical depth element plot */

  zmin= 0.0 ; zmax= 10.0 ; dz= 0.01 ;
  fp= fopen("doptdepthdz.out","w") ;
  for(z=zmin+0.5*dz;z<=zmax;z+=dz){
    fprintf(fp,"%8.4f",z) ;
    for(i=0;i<NMODELS;i++) fprintf(fp,"%11.6f",
				   doptdepthdz(z,OmegaM[i],OmegaL[i])) ;
    fprintf(fp,"\n") ;
  }
  fclose(fp) ;

/* find redshift at which dlogV/dDM=0.3 */
/*
  for(i=0;i<NMODELS;i++){
    z1= 1.0 ; z2= 2.0 ;
    s1= SLOPE(z1) ; s2= SLOPE(z2) ;
    while(fabs(z1-z2)>0.00001){
      z= 0.5*(z1+z2) ;
      s= SLOPE(z) ;
      if(s>0.3){
	z1= z ;
	s1= s ;
      } else{
	z2= z ;
	s2= s ;
      }
    }
    fprintf(stderr,"(OmegaM,OmegaL)=(%.2f,%.2f) z_0=%.4f V=%.4f D_L=%.4f\n",
	    OmegaM[i],OmegaL[i],z,comvol(z,OmegaM[i],OmegaL[i]),
	    lumdis(z,OmegaM[i],OmegaL[i])) ;
  }

/* predict counts from flat and steep Schechter functions */
/*
  for(j=0;j<2;j++){
    if(j==0) alpha= -1.0 ;
    else alpha= -1.75 ;
    mmin= 9.0 ; mmax= 35.0 ; dm= 0.1 ;
    zmin= 0.0 ; zmax= 8.0 ; dz= 0.1 ;
    if(j==0) fp= fopen("neflat.out","w") ;
    else fp= fopen("nesteep.out","w") ;
    for(m=mmin+0.5*dm;m<mmax;m+=dm){
      fprintf(fp,"%8.4f",m) ;
      for(i=0;i<NMODELS;i++){
	N[i]= 0.0 ;
	for(z=zmin+0.5*dz;z<zmax;z+=dz){
	  DM[i]= 5.0*log10(DH*lumdis(z,OmegaM[i],OmegaL[i])) ;
	  x= pow(10.0,(-0.4)*(m-DM[i]-MSTAR)) ;
	  N[i]+= dz*4.0*PI*dcomvoldz(z,OmegaM[i],OmegaL[i])*
	    (LN10/2.5)*PHISTAR*schechter(x,alpha+1) ;
	}
	fprintf(fp,"%11.4e",N[i]) ;
      }
      fprintf(fp,"\n") ;
    }
    fclose(fp) ;
  }

/* predict redshift distribution at faint magnitudes with steep LF */
/* output is number per mag per steradian per redshift */
/*
  for(j=0;j<2;j++){
    alpha= -1.75 ;
    if(j==0){
      m= MSTAR+45.0 ;
      fp= fopen("nesteepzdist.45.out","w") ;
    } else{
      m= MSTAR+50.0 ;
      fp= fopen("nesteepzdist.50.out","w") ;
    }
    zmin= 0.0 ; zmax= 10.0 ; dz= 0.01 ;
    for(z=zmin+0.5*dz;z<zmax;z+=dz){
      fprintf(fp,"%8.4f",z) ;
      for(i=0;i<NMODELS;i++){
	DM[i]= 5.0*log10(DH*lumdis(z,OmegaM[i],OmegaL[i])) ;
	x= pow(10.0,(-0.4)*(m-DM[i]-MSTAR)) ;
	N[i]= dcomvoldz(z,OmegaM[i],OmegaL[i])*
	  (LN10/2.5)*PHISTAR*schechter(x,alpha+1) ;
	fprintf(fp,"%11.4e",N[i]) ;
      }
      fprintf(fp,"\n") ;
    }
    fclose(fp) ;
  }

/* done */
}
