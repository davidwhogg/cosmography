;+
; NAME:
;   propmotdis
; PURPOSE:
;   Compute proper motion distances (for c/H_0=1).
; CALLING SEQUENCE:
;   D= propmotdis(z,OmegaM,OmegaL)
; INPUTS:
;   z       - redshift or vector of redshifts
;   OmegaM  - Omega-matter at z=0
;   OmegaL  - Omega-Lambda at z=0
; OPTIONAL INPUTS:
;   w       - if set, treat OmegaL as a dark energy with this EOS
; KEYWORDS
; OUTPUTS:
;   proper motion distance in units of the Hubble length c/H_0
; COMMENTS:
; BUGS:
;   May not work for pathological parts of the OmegaM-OmegaL plane.
; EXAMPLES:
; PROCEDURES CALLED:
;   comdis()
; REVISION HISTORY:
;   2000-06-25  Written by Hogg (IAS)
;   2006-08-02  added w - Hogg (NYU)
;-
function propmotdis, z,OmegaM,OmegaL,w=w
  if (NOT keyword_set(w)) then w= -1D0
  TINY= double(1.0e-16)
  if (abs(OmegaM) LT TINY) AND (abs(OmegaL) LT TINY) then begin
    dM= (z+0.5*z*z)/(1.0+z)
  endif else begin
    if abs(OmegaL) LT TINY then begin
      q0= 0.5*OmegaM-OmegaL
      dM= (z*q0+(q0-1.0)*(sqrt(2.0*q0*z+1.0)-1.0))/(q0*q0*(1.0+z))
    endif else begin
      dM= comdis(z,OmegaM,OmegaL,w=w)
      OmegaK= 1.0-OmegaM-OmegaL
      sqrtOmegaK= sqrt(abs(OmegaK))
      if OmegaK LT (-1.0*TINY) then dM= sin(sqrtOmegaK*dM)/sqrtOmegaK $
      else if OmegaK GT TINY then dM= sinh(sqrtOmegaK*dM)/sqrtOmegaK
    endelse
  endelse
  return, dM
end
