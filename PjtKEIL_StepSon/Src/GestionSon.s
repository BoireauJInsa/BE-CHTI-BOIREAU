	PRESERVE8
	THUMB
		
	import Son
	import LongueurSon
	

;/*
;static int position;

;void CallbackSon(void){
;	if (position < LongeurSon){
;		SortieSon = son[position] * (360 / 32767) + 360
;		position = position +1
;	}
;}
;*/


; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite

SortieSon dcw 0
Position dcd 0
	
	export SortieSon
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		
	
timer_callback FUNCTION
	export timer_callback
	push {lr}
	
	ldr r1,=LongueurSon ;adresse de LongeurSon dans R1
	ldr r2,=Position ;adresse de Position dans R2
	ldr r3,[r1] ;valeur de LongeurSon dans R3
	ldr r1,[r2] ;valeur de Position dans R1
	cmp r1,r3
	bge exit
	
		
	
	
	ldr r0,=Son
	
	ldrsh r3, [r0,r1,lsl #1] ; r3 = r0(Adresse son)[r1(valeur position)]
	
	add r1, r1, #1 ; increment position
	str r1, [r2] ; maj position
	; 2**15 = 32768
	
	mov r2, #360
	mov r0,r3 ; valeur de son[position] dans r0 (deviendra SortieSon)
	mul r0, r0, r2 ;SortieSon = SortieSon * 360
	asr r0, #15 ;r3 = r3 / 32768, SortieSon = SortieSon / 32768
	add r0, r0, #360 ; SortieSon = SortieSon + 360

	ldr r1,=SortieSon
	str r0, [r1]
	
	pop {lr}
	bx lr
	
	
	
exit
	pop {lr}
	bx lr
	
	
	endp
		
	END	