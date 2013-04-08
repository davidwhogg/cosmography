;+
; NAME:
;   dcomdisdz
; PURPOSE:
;   Compute differential comoving line-of-sight distances (for c/H_0=1).
; CALLING SEQUENCE:
;   dDdz= dcomdisdz(z,OmegaM,OmegaL)
; INPUTS:
;   z       - redshift or vector of redshifts
;   OmegaM  - Omega-matter at z=0
;   OmegaL  - Omega-Lambda at z=0
; OPTIONAL INPUTS:
;   w       - if set, treat OmegaL as a dark energy with this EOS
; KEYWORDS
; OUTPUTS:
;   differential comoving distance DD/dz in units of the Hubble length c/H_0
; COMMENTS:
; BUGS:
;   May not work for pathological parts of the OmegaM-OmegaL plane.
; EXAMPLES:
; PROCEDURES CALLED:
; REVISION HISTORY:
;   2000-06-25  Written by Hogg (IAS)
;   2006-08-02  added w - Hogg (NYU)
;-
function dcomdisdz, z,OmegaM,OmegaL,w=w
  if (NOT keyword_set(w)) then w= -1D0
  OmegaK= 1D0-OmegaM-OmegaL
  return, ((1D0)/sqrt(OmegaM*(1D0+z)^3 $
                      +OmegaK*(1D0+z)^2 $
                      +OmegaL*(1D0+z)^(-3D0*(1D0+w))))
end
