/* ----------------------------------------------------------------------------

   Cosmography routines in C.

-------------------------------------------------------------------------------

   Use at your own risk.  Note that, where necessary, integration is
   done with stepsize roughly MINSTEP and that the integrator is not
   pretty.

   For more information, please see
      http://arxiv.org/abs/astro-ph/9905116

-------------------------------------------------------------------------------

   David W. Hogg
   hogg@physics.nyu.edu

---------------------------------------------------------------------------- */

#define PI       (3.141592653589793238462643)
#define TINY     (1.0e-16)
#define MINSTEP  (0.01)


/* ----------------------------------------------------------------------------
   angdidis
-------------------------------------------------------------------------------
   This function calculates the angular diameter distance d_A as a
   function of z, Omega_M and Omega_L in a matter-dominated universe,
   using the function propmotdis().  H0=c=1.
---------------------------------------------------------------------------- */
double angdidis(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  double propmotdis() ;
  return propmotdis(z,OmegaM,OmegaL)/(1.0+z) ;
}


/* ----------------------------------------------------------------------------
   angdidis2
-------------------------------------------------------------------------------
   This function calculates the angular diameter distance d_A from z1
   to z2 as a function of Omega_M and Omega_L in a matter-dominated
   universe, using the function propmotdis().  H0=c=1.
---------------------------------------------------------------------------- */
double angdidis2(z1,z2,OmegaM,OmegaL)
     double z1,z2,OmegaM,OmegaL ;
{
  double propmotdis(),sqrt(),y1,y2,y12,OmegaR ;

  OmegaR= 1.0-OmegaM-OmegaL ;
  if(OmegaR<-TINY) printf("WARNING: angdidis2() does not work at Omega_R<0!") ;
  y1= propmotdis(z1,OmegaM,OmegaL) ;
  y2= propmotdis(z2,OmegaM,OmegaL) ;
  y12= y2*sqrt(1.0+y1*y1*OmegaR)-y1*sqrt(1.0+y2*y2*OmegaR) ;

  return y12/(1.0+z2) ;
}


/* ----------------------------------------------------------------------------
   comdis
-------------------------------------------------------------------------------
   This function calculates the line-of-sight comoving distance d_C as
   a function of z, Omega_M and Omega_L in a matter-dominated
   universe, using dcomdisdz().  H0=c=1.
---------------------------------------------------------------------------- */
double comdis(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  int nsteps ;
  double dz,dC,zz,dcomdisdz() ;

  nsteps= ((int) (z/MINSTEP))+1 ;
  dz= z/((double) nsteps) ;
  dC= 0.0 ;
  for(zz=0.5*dz; zz<z; zz+=dz) dC += dz*dcomdisdz(zz,OmegaM,OmegaL) ;

  return dC ;
}


/* ----------------------------------------------------------------------------
   comvol
-------------------------------------------------------------------------------
   This function calculates the all-sky comoving volume V as a
   function of z, Omega_M and Omega_L in a matter-dominated universe.
   Formulae from Carrol, Press & Turner, 1992, and my own calculation.
---------------------------------------------------------------------------- */
double comvol(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  double V,dM,OmegaK,sqrtOmegaK,sqrt(),fabs(),asin(),asinh(),propmotdis() ;

  OmegaK= 1.0-OmegaM-OmegaL ;
  sqrtOmegaK= sqrt(fabs(OmegaK)) ;
  dM= propmotdis(z,OmegaM,OmegaL) ;

  if(OmegaK < -TINY)
    V= (dM*sqrt(1.0+OmegaK*dM*dM)-asin(dM*sqrtOmegaK)/sqrtOmegaK)
      /(2.0*OmegaK) ;
  else if(OmegaK > TINY)
    V= (dM*sqrt(1.0+OmegaK*dM*dM)-asinh(dM*sqrtOmegaK)/sqrtOmegaK)
      /(2.0*OmegaK) ;
  else
    V= dM*dM*dM/3.0 ;

  return 4.0*PI*V ;
}


/* ----------------------------------------------------------------------------
   dcomdisdz
-------------------------------------------------------------------------------
   This function calculates the differential line-of-sight comoving
   distance dD_c/dz as a function of z, Omega_M and Omega_L in a
   matter-dominated universe.  H0=c=1.
---------------------------------------------------------------------------- */
double dcomdisdz(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  double sqrt() ;
  return (1.0/sqrt((1.0+z)*(1.0+z)*(1.0+OmegaM*z)-z*(2.0+z)*OmegaL)) ;
}


/* ----------------------------------------------------------------------------
   dcomvoldz
-------------------------------------------------------------------------------
   This function calculates the one-steradian differential comoving
   volume dV/dz as a function of z, Omega_M and Omega_L in a
   matter-dominated universe.  Formulae from Carrol, Press & Turner,
   1992, Kolb & Turner, 1990, and my own calculation.  H0=c=1.
---------------------------------------------------------------------------- */
double dcomvoldz(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  double dM,OmegaK,ddMdz,sqrt(),propmotdis(),dpropmotdisdz() ;

  OmegaK= 1.0-OmegaM-OmegaL ;
  dM= propmotdis(z,OmegaM,OmegaL) ;
  ddMdz= dpropmotdisdz(z,OmegaM,OmegaL) ;

  return dM*dM*ddMdz/sqrt(1.0+OmegaK*dM*dM) ;
}


/* ----------------------------------------------------------------------------
   dlookbackdz
-------------------------------------------------------------------------------
   This function calculates the change in lookback time dt/dz with
   redshift z as a function of z, Omega_M and Omega_L in a
   matter-dominated universe.  Formula from Carrol, Press & Turner,
   1992.  H0=c=1.
---------------------------------------------------------------------------- */
double dlookbackdz(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  double sqrt() ;
  return 1.0/((1.0+z)*sqrt((1.0+z)*(1.0+z)*(1.0+OmegaM*z)-z*(2.0+z)*OmegaL)) ;
}


/* ----------------------------------------------------------------------------
   doptdepthdz
-------------------------------------------------------------------------------
   This function calculates the change in optical depth dtau/dz with
   redshift z as a function of z, Omega_M and Omega_L in a
   matter-dominated universe.  Formula from Peebles, 1993.
   H0=c=sigma=n=1.
---------------------------------------------------------------------------- */
double doptdepthdz(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  double sqrt() ;
  return (1.0+z)*(1.0+z)/
    sqrt((1.0+z)*(1.0+z)*(1.0+OmegaM*z)-z*(2.0+z)*OmegaL) ;
}


/* ----------------------------------------------------------------------------
   dpropmotdisdz
-------------------------------------------------------------------------------
   This function calculates the derivative of the proper motion
   distance d_M with respect to redshift z as a function of z, Omega_M
   and Omega_L in a matter-dominated universe.  Formula from Carrol,
   Press & Turner, 1992.  This function also requires the function
   propmotdis(). H0=c=1.
---------------------------------------------------------------------------- */
double dpropmotdisdz(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  double ddMdz,OmegaK,dM,sqrt(),propmotdis() ;

  ddMdz = 1.0/sqrt((1.0+z)*(1.0+z)*(1.0+OmegaM*z)-z*(2.0+z)*OmegaL) ;

  OmegaK= 1.0-OmegaM-OmegaL ;
  if(OmegaK < -TINY){
    dM= propmotdis(z,OmegaM,OmegaL) ;
    ddMdz= sqrt(1.0-OmegaK*dM*dM)*ddMdz ;
  }else if(OmegaK > TINY){
    dM= propmotdis(z,OmegaM,OmegaL) ;
    ddMdz= sqrt(1.0+OmegaK*dM*dM)*ddMdz ;
  }

  return ddMdz ;
}


/* ----------------------------------------------------------------------------
   intcomvol
-------------------------------------------------------------------------------
   This function calculates the all-sky comoving volume V as a
   function of z, Omega_M and Omega_L in a matter-dominated universe
   by integrating dcomvoldz().  It was written to test comvol().
---------------------------------------------------------------------------- */
double intcomvol(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  int nsteps ;
  double dz,zz,V,dcomvoldz() ;

  nsteps= ((int) (z/MINSTEP))+1 ;
  dz= z/((double) nsteps) ;
  V= 0.0 ;
  for(zz=0.5*dz;zz<z;zz+=dz) V+= dz*dcomvoldz(zz,OmegaM,OmegaL) ;

  return 4.0*PI*V ;
}


/* ----------------------------------------------------------------------------
   lookback
-------------------------------------------------------------------------------
   This function calculates the lookback time t(0)-t(z) as a function
   of z, OmegaM and OmegaL by integrating the output of dlookbackdz.
---------------------------------------------------------------------------- */
double lookback(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  int nsteps ;
  double t,zz,dz,dlookbackdz() ;
  
  nsteps= ((int) (z/MINSTEP))+1 ;
  dz= z/((double) nsteps) ;
  t= 0.0 ;
  for(zz=0.5*dz; zz<z; zz+=dz) t+= dlookbackdz(zz,OmegaM,OmegaL)*dz ;

  return t ;
}


/* ----------------------------------------------------------------------------
   lumdis
-------------------------------------------------------------------------------
   This function calculates the luminosity distance d_L as a function
   of z, Omega_M and Omega_L in a matter-dominated universe, using the
   function propmotdis().  H0=c=1.
---------------------------------------------------------------------------- */
double lumdis(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  double propmotdis() ;
  return propmotdis(z,OmegaM,OmegaL)*(1.0+z) ;
}


/* ----------------------------------------------------------------------------
   optdepth
-------------------------------------------------------------------------------
   This function calculates the optical depth tau as a function
   of z, OmegaM and OmegaL by integrating the output of doptdepthdz.
   Again, H0=c=sigma=n=1.
---------------------------------------------------------------------------- */
double optdepth(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  int nsteps ;
  double tau,zz,dz,doptdepthdz() ;
  
  nsteps= ((int) (z/MINSTEP))+1 ;
  dz= z/((double) nsteps) ;
  tau= 0.0 ;
  for(zz=0.5*dz; zz<z; zz+=dz) tau+= doptdepthdz(zz,OmegaM,OmegaL)*dz ;

  return tau ;
}


/* ----------------------------------------------------------------------------
   propmotdis
-------------------------------------------------------------------------------
   This function calculates the proper motion distance d_M as a
   function of z, Omega_M and Omega_L in a matter-dominated universe.
   Formulae from Carrol, Press & Turner, 1992, Kolb \& Turner, 1990,
   and my own derivation.  Makes use of comdis().  H0=c=1.
---------------------------------------------------------------------------- */
double propmotdis(z,OmegaM,OmegaL)
     double z,OmegaM,OmegaL ;
{
  double dM,q0,OmegaK,sqrtOmegaK,sqrt(),fabs(),sin(),sinh() ;

  if(fabs(OmegaM)<TINY && fabs(OmegaL)<TINY){
    dM= (z+0.5*z*z)/(1.0+z) ;

  }else if(fabs(OmegaL)<TINY){
    q0= 0.5*OmegaM ;
    dM= (z*q0+(q0-1.0)*(sqrt(2.0*q0*z+1.0)-1.0))/(q0*q0*(1.0+z)) ;

  }else{
    dM= comdis(z,OmegaM,OmegaL) ;
    OmegaK= 1.0-OmegaM-OmegaL ;
    sqrtOmegaK= sqrt(fabs(OmegaK)) ;
    if(OmegaK < -TINY) dM= sin(sqrtOmegaK*dM)/sqrtOmegaK ;
    else if(OmegaK > TINY) dM= sinh(sqrtOmegaK*dM)/sqrtOmegaK ;
  }

  return dM ;
}
