;+
; NAME:
;   age
; PURPOSE:
;   Compute cosmic age (for c/H_0=1).
; CALLING SEQUENCE:
;   t= age(z,OmegaM,OmegaL)
; INPUTS:
;   z       - redshift or vector of redshifts
;   OmegaM  - Omega-matter at z=0
;   OmegaL  - Omega-Lambda at z=0
; OPTIONAL INPUTS:
; KEYWORDS
; OUTPUTS:
;   age since z=1000 in units of the Hubble time 1/H_0
; COMMENTS:
; BUGS:
;   The integrator is crude, slow and repetetive.
;   May not work for pathological parts of the OmegaM-OmegaL plane.
; EXAMPLES:
; PROCEDURES CALLED:
;   lookback()
; REVISION HISTORY:
;   2001-May-12  Written by Hogg (NYU)
;-
;------------------------------------------------------------------------------
function age, z,OmegaM,OmegaL
  return, lookback(double(1000.0),OmegaM,OmegaL)-lookback(z,OmegaM,OmegaL)
end
