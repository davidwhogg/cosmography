;+
; NAME:
;   angdidis
; PURPOSE:
;   Compute angular diameter distance (for c/H_0=1).
; CALLING SEQUENCE:
;   D= angdidis(z,OmegaM,OmegaL)
; INPUTS:
;   z       - redshift or vector of redshifts
;   OmegaM  - Omega-matter at z=0
;   OmegaL  - Omega-Lambda at z=0
; OPTIONAL INPUTS:
;   w       - if set, treat OmegaL as a dark energy with this EOS
; KEYWORDS
; OUTPUTS:
;   angular diameter distance in units of the Hubble length c/H_0
; COMMENTS:
; BUGS:
;   May not work for pathological parts of the OmegaM-OmegaL plane.
; EXAMPLES:
; PROCEDURES CALLED:
;   propmotdis()
; REVISION HISTORY:
;   2000-06-25  Written by Hogg (IAS)
;-
function angdidis, z,OmegaM,OmegaL,w=w
  return, propmotdis(z,OmegaM,OmegaL,w=w)/(1.0+z)
end
