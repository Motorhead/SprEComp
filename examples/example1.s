			; SprEComp Example
		
			; Declare image variable
			img light, "red-light.png"
			
			; Declare frame variables
			frm lighton, light, 0, 0, 100, 100, 1000	; Duration is 1s
			frm lightoff, light, 100, 0, 100, 100, 500	; Duration is 0.5s
			
			; Begin with our code
begin:		ren lightoff		; Render lightoff, default duration
			ren lighton, 1000	; Render lighton, 1 s
			ren lightoff, 100
			jmp begin			; just to exemplify.
		
		