;+
; NAME:
;   comdis
; PURPOSE:
;   Compute comoving line-of-sight distances (for c/H_0=1).
; CALLING SEQUENCE:
;   D= comdis(z,OmegaM,OmegaL)
; INPUTS:
;   z       - redshift or vector of redshifts
;   OmegaM  - Omega-matter at z=0
;   OmegaL  - Omega-Lambda at z=0
; OPTIONAL INPUTS:
;   w       - if set, treat OmegaL as a dark energy with this EOS
; KEYWORDS
; OUTPUTS:
;   comoving line-of-sight distance in units of the Hubble length c/H_0
; COMMENTS:
; BUGS:
;   The integrator is crude, slow and repetetive.
;   May not work for pathological parts of the OmegaM-OmegaL plane.
; EXAMPLES:
; PROCEDURES CALLED:
;   dcomdisdz()
; REVISION HISTORY:
;   2000-Jun-25  Written by Hogg (IAS)
;-
;------------------------------------------------------------------------------
function comdis, z,OmegaM,OmegaL,w=w
  TINY= double(1.0e-16)
  stepsize= 0.01D              ; minimum stepsize of 0.01
  nsteps= long(z/stepsize)+10  ; minimum of 10 steps
  dz= z/double(nsteps)
  dC= double(0.0*z)
  nz= n_elements(z)
  if nz EQ 1 then begin
    if abs(z) LT TINY then dC= z else begin
      for zz=0.5*dz,z,dz do dC= dC+dz*dcomdisdz(zz,OmegaM,OmegaL,w=w)
    endelse
  endif else begin
    for i=0L,nz-1L do dC[i]= comdis(z[i],OmegaM,OmegaL)
  endelse
  return, dC
end
