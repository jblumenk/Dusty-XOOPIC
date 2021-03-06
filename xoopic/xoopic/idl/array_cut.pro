; NAME:      array_cut
;
; PURPOSE:   Select elements out of an array
;
; CATEGORY:
;
; CALLING SEQUENCE:
;   Result = array_cut(x, y, z, x_cutoff, y_cutoff)
;
; INPUTS:
;   x:         array of x values
;   y:         array of y values
;   z:         two-d array of z values
;   x_cutoff:  floating point cutoff value for x (non-inclusive)
;   y_cutorr:  floating point cutoff value for y (non-inclusive)
;
; OPTIONAL INPUTS:    None.
;
; KEYWORD PARAMETERS: None.
;
; OUTPUTS:   A structure of arrays of doubles, which are called
;            "xnew", "ynew", and "znew"
;
; OPTIONAL OUTPUTS:  None.
;
; COMMON BLOCKS:     None.
;
; SIDE EFFECTS:      None.
;
; RESTRICTIONS:      None.
;
; PROCEDURE:
;
; EXAMPLE:
;   Cut off all values of x above 3 and y above 6, storing
;   the results in A, and print the new array and new x and new y
;
;   A = array_cut(x, y, z, 3, 6)
;   print, A.znew
;   print, A.xnew
;   print, A.ynew
;
; MODIFICATION HISTORY:
;   May  8, 2001:  original code (PHS)
;   May 10, 2001:  renamed, with cosmetic changes (DLB)
;
;   Version: $Id: array_cut.pro 1644 2001-06-06 22:16:09Z dad $
;
;   Copyright (c) 2000-2001 by Tech-X Corporation.  All rights reserved.


function array_cut, x, y, z, xc, yc

 xs = n_elements(x)
 ys = n_elements(y)

 whx = where(x gt xc)
 why = where(y gt yc)

 nx = n_elements(whx)
 ny = n_elements(why)

 znew=dindgen(nx,ny)

 for i=0, nx-1 do begin
   for j=0, ny-1 do begin
     znew(i,j) = z( whx(i), why(j) )
   endfor
 endfor

 mystruct = { znew:znew, xnew:x(whx), ynew:y(why) }

 return, mystruct
end
