/* ----------------------------------------------------------------------------

   schechter.c

-------------------------------------------------------------------------------

   This function calculates the dimensionless value of the Schechter
   luminosity function y=phi/phistar as a function of x=L/Lstar, given
   an exponent alpha.

-------------------------------------------------------------------------------

   David W. Hogg / hogg@tapir.caltech.edu / 5 July 1994

---------------------------------------------------------------------------- */
double schechter(x,alpha)
     double x,alpha ;
{
  double pow(),exp() ;
  return (pow(x,alpha)*exp(-x)) ;
}
