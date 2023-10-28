	.file	"TIMER0_prog.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
.global	numOverflows
.global	numOverflows
	.section .bss
	.type	numOverflows, @object
	.size	numOverflows, 4
numOverflows:
	.skip 4,0
.global	remainingCounts
.global	remainingCounts
	.type	remainingCounts, @object
	.size	remainingCounts, 4
remainingCounts:
	.skip 4,0
.global	prescaler
.global	prescaler
	.type	prescaler, @object
	.size	prescaler, 2
prescaler:
	.skip 2,0
.global	fast_oc0_mode
.global	fast_oc0_mode
	.type	fast_oc0_mode, @object
	.size	fast_oc0_mode, 2
fast_oc0_mode:
	.skip 2,0
.global	Action_Timer
.global	Action_Timer
	.type	Action_Timer, @object
	.size	Action_Timer, 4
Action_Timer:
	.skip 4,0
	.text
.global	M_TIMER0_void_Init
	.type	M_TIMER0_void_Init, @function
M_TIMER0_void_Init:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r25
	std Y+1,r24
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+2
	ldd r25,Z+3
	sts (prescaler)+1,r25
	sts prescaler,r24
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	ldd r25,Z+1
	sbiw r24,0
	brne .L2
	ldi r30,lo8(83)
	ldi r31,hi8(83)
	ldi r24,lo8(-128)
	st Z,r24
	rjmp .L6
.L2:
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	ldd r25,Z+1
	cpi r24,2
	cpc r25,__zero_reg__
	brne .L4
	ldi r26,lo8(92)
	ldi r27,hi8(92)
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	st X,r24
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+4
	ldd r25,Z+5
	swap r24
	andi r24,lo8(-16)
	ori r24,lo8(-120)
	st X,r24
	rjmp .L6
.L4:
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	ldd r25,Z+1
	cpi r24,3
	cpc r25,__zero_reg__
	brne .L5
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+4
	ldd r25,Z+5
	sts (fast_oc0_mode)+1,r25
	sts fast_oc0_mode,r24
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+4
	ldd r25,Z+5
	swap r24
	andi r24,lo8(-16)
	ori r24,lo8(72)
	st X,r24
	rjmp .L6
.L5:
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	ldd r25,Z+1
	cpi r24,1
	cpc r25,__zero_reg__
	brne .L6
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+4
	ldd r25,Z+5
	swap r24
	andi r24,lo8(-16)
	ori r24,lo8(64)
	st X,r24
.L6:
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	M_TIMER0_void_Init, .-M_TIMER0_void_Init
.global	M_TIMER0_void_start
	.type	M_TIMER0_void_start, @function
M_TIMER0_void_start:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldi r30,lo8(83)
	ldi r31,hi8(83)
	ld r24,Z
	andi r24,lo8(-8)
	st X,r24
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldi r30,lo8(83)
	ldi r31,hi8(83)
	ld r18,Z
	lds r24,prescaler
	lds r25,(prescaler)+1
	or r24,r18
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	M_TIMER0_void_start, .-M_TIMER0_void_start
.global	M_TIMER0_void_stop
	.type	M_TIMER0_void_stop, @function
M_TIMER0_void_stop:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldi r30,lo8(83)
	ldi r31,hi8(83)
	ld r24,Z
	andi r24,lo8(-8)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	M_TIMER0_void_stop, .-M_TIMER0_void_stop
	.data
	.type	prescalerMap.1307, @object
	.size	prescalerMap.1307, 12
prescalerMap.1307:
	.word	0
	.word	1
	.word	8
	.word	64
	.word	256
	.word	1024
	.text
.global	M_TIMER0_void_setDelayTimeMilliSec
	.type	M_TIMER0_void_setDelayTimeMilliSec, @function
M_TIMER0_void_setDelayTimeMilliSec:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,12
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 12 */
	std Y+9,r22
	std Y+10,r23
	std Y+11,r24
	std Y+12,r25
	lds r24,prescaler
	lds r25,(prescaler)+1
	lsl r24
	rol r25
	mov r30,r24
	mov r31,r25
	subi r30,lo8(-(prescalerMap.1307))
	sbci r31,hi8(-(prescalerMap.1307))
	ld r24,Z
	ldd r25,Z+1
	swap r25
	swap r24
	andi r24,0x0f
	eor r24,r25
	andi r25,0x0f
	eor r24,r25
	mov r24,r24
	mov r25,r25
	ldi r26,lo8(0)
	ldi r27,hi8(0)
	std Y+5,r24
	std Y+6,r25
	std Y+7,r26
	std Y+8,r27
	ldd r22,Y+9
	ldd r23,Y+10
	ldd r24,Y+11
	ldd r25,Y+12
	ldi r18,lo8(1000)
	ldi r19,hi8(1000)
	ldi r20,hlo8(1000)
	ldi r21,hhi8(1000)
	rcall __mulsi3
	mov r27,r25
	mov r26,r24
	mov r25,r23
	mov r24,r22
	ldd r18,Y+5
	ldd r19,Y+6
	ldd r20,Y+7
	ldd r21,Y+8
	mov r22,r24
	mov r23,r25
	mov r24,r26
	mov r25,r27
	rcall __udivmodsi4
	mov r27,r21
	mov r26,r20
	mov r25,r19
	mov r24,r18
	std Y+1,r24
	std Y+2,r25
	std Y+3,r26
	std Y+4,r27
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r26,Y+3
	ldd r27,Y+4
	mov r24,r25
	mov r25,r26
	mov r26,r27
	clr r27
	sts numOverflows,r24
	sts (numOverflows)+1,r25
	sts (numOverflows)+2,r26
	sts (numOverflows)+3,r27
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r26,Y+3
	ldd r27,Y+4
	andi r25,hi8(255)
	andi r26,hlo8(255)
	andi r27,hhi8(255)
	sts remainingCounts,r24
	sts (remainingCounts)+1,r25
	sts (remainingCounts)+2,r26
	sts (remainingCounts)+3,r27
/* epilogue start */
	adiw r28,12
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	M_TIMER0_void_setDelayTimeMilliSec, .-M_TIMER0_void_setDelayTimeMilliSec
.global	M_TIMER0_void_IntEnable
	.type	M_TIMER0_void_IntEnable, @function
M_TIMER0_void_IntEnable:
	push r29
	push r28
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
	std Y+1,r24
	ldd r24,Y+1
	tst r24
	brne .L14
	ldi r26,lo8(89)
	ldi r27,hi8(89)
	ldi r30,lo8(89)
	ldi r31,hi8(89)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	rjmp .L16
.L14:
	ldd r24,Y+1
	cpi r24,lo8(1)
	brne .L16
	ldi r26,lo8(89)
	ldi r27,hi8(89)
	ldi r30,lo8(89)
	ldi r31,hi8(89)
	ld r24,Z
	ori r24,lo8(2)
	st X,r24
.L16:
/* epilogue start */
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	M_TIMER0_void_IntEnable, .-M_TIMER0_void_IntEnable
.global	M_TIMER0_void_IntDisable
	.type	M_TIMER0_void_IntDisable, @function
M_TIMER0_void_IntDisable:
	push r29
	push r28
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
	std Y+1,r24
	ldd r24,Y+1
	tst r24
	brne .L18
	ldi r26,lo8(89)
	ldi r27,hi8(89)
	ldi r30,lo8(89)
	ldi r31,hi8(89)
	ld r24,Z
	andi r24,lo8(-2)
	st X,r24
	rjmp .L20
.L18:
	ldd r24,Y+1
	cpi r24,lo8(1)
	brne .L20
	ldi r26,lo8(89)
	ldi r27,hi8(89)
	ldi r30,lo8(89)
	ldi r31,hi8(89)
	ld r24,Z
	andi r24,lo8(-3)
	st X,r24
.L20:
/* epilogue start */
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	M_TIMER0_void_IntDisable, .-M_TIMER0_void_IntDisable
.global	M_TIMER0_void_setFastPWM
	.type	M_TIMER0_void_setFastPWM, @function
M_TIMER0_void_setFastPWM:
	push r29
	push r28
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+2,r24
	std Y+3,r22
	ldd r24,Y+3
	mov r18,r24
	ldi r19,lo8(0)
	mov r24,r18
	mov r25,r19
	swap r24
	swap r25
	andi r25,0xf0
	eor r25,r24
	andi r24,0xf0
	eor r25,r24
	sub r24,r18
	sbc r25,r19
	mov r18,r24
	mov r19,r25
	swap r18
	swap r19
	andi r19,0xf0
	eor r19,r18
	andi r18,0xf0
	eor r19,r18
	add r24,r18
	adc r25,r19
	ldi r18,lo8(100)
	ldi r19,hi8(100)
	mov r22,r18
	mov r23,r19
	rcall __divmodhi4
	mov r24,r22
	mov r25,r23
	std Y+1,r24
	ldi r30,lo8(92)
	ldi r31,hi8(92)
	ldd r24,Y+1
	st Z,r24
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldi r30,lo8(83)
	ldi r31,hi8(83)
	ld r24,Z
	andi r24,lo8(-8)
	st X,r24
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldi r30,lo8(83)
	ldi r31,hi8(83)
	ld r18,Z
	lds r24,prescaler
	lds r25,(prescaler)+1
	or r24,r18
	st X,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	M_TIMER0_void_setFastPWM, .-M_TIMER0_void_setFastPWM
.global	M_TIMER0_void_setPhaseCorrectPWM
	.type	M_TIMER0_void_setPhaseCorrectPWM, @function
M_TIMER0_void_setPhaseCorrectPWM:
	push r29
	push r28
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+2,r24
	std Y+3,r22
	ldd r24,Y+3
	mov r18,r24
	ldi r19,lo8(0)
	mov r24,r18
	mov r25,r19
	swap r24
	swap r25
	andi r25,0xf0
	eor r25,r24
	andi r24,0xf0
	eor r25,r24
	sub r24,r18
	sbc r25,r19
	mov r18,r24
	mov r19,r25
	swap r18
	swap r19
	andi r19,0xf0
	eor r19,r18
	andi r18,0xf0
	eor r19,r18
	add r24,r18
	adc r25,r19
	ldi r18,lo8(100)
	ldi r19,hi8(100)
	mov r22,r18
	mov r23,r19
	rcall __divmodhi4
	mov r24,r22
	mov r25,r23
	std Y+1,r24
	ldi r30,lo8(92)
	ldi r31,hi8(92)
	ldd r24,Y+1
	com r24
	st Z,r24
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldi r30,lo8(83)
	ldi r31,hi8(83)
	ld r24,Z
	andi r24,lo8(-8)
	st X,r24
	ldi r26,lo8(83)
	ldi r27,hi8(83)
	ldi r30,lo8(83)
	ldi r31,hi8(83)
	ld r18,Z
	lds r24,prescaler
	lds r25,(prescaler)+1
	or r24,r18
	st X,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	M_TIMER0_void_setPhaseCorrectPWM, .-M_TIMER0_void_setPhaseCorrectPWM
.global	M_TIMER0_void_setCallBack
	.type	M_TIMER0_void_setCallBack, @function
M_TIMER0_void_setCallBack:
	push r29
	push r28
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+2,r25
	std Y+1,r24
	std Y+3,r22
	ldd r24,Y+3
	tst r24
	brne .L26
	ldd r24,Y+1
	ldd r25,Y+2
	sts (Action_Timer)+1,r25
	sts Action_Timer,r24
	rjmp .L28
.L26:
	ldd r24,Y+3
	cpi r24,lo8(1)
	brne .L28
	ldd r24,Y+1
	ldd r25,Y+2
	sts (Action_Timer+2)+1,r25
	sts Action_Timer+2,r24
.L28:
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	M_TIMER0_void_setCallBack, .-M_TIMER0_void_setCallBack
	.lcomm counter.1405,4
.global	__vector_11
	.type	__vector_11, @function
__vector_11:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
	push r19
	push r20
	push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	push r30
	push r31
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
	lds r24,Action_Timer
	lds r25,(Action_Timer)+1
	sbiw r24,0
	brne .+2
	rjmp .L31
	lds r24,counter.1405
	lds r25,(counter.1405)+1
	lds r26,(counter.1405)+2
	lds r27,(counter.1405)+3
	adiw r24,1
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	sts counter.1405,r24
	sts (counter.1405)+1,r25
	sts (counter.1405)+2,r26
	sts (counter.1405)+3,r27
	lds r18,counter.1405
	lds r19,(counter.1405)+1
	lds r20,(counter.1405)+2
	lds r21,(counter.1405)+3
	lds r24,numOverflows
	lds r25,(numOverflows)+1
	lds r26,(numOverflows)+2
	lds r27,(numOverflows)+3
	cp r18,r24
	cpc r19,r25
	cpc r20,r26
	cpc r21,r27
	brne .L31
	ldi r30,lo8(82)
	ldi r31,hi8(82)
	lds r24,remainingCounts
	lds r25,(remainingCounts)+1
	lds r26,(remainingCounts)+2
	lds r27,(remainingCounts)+3
	neg r24
	st Z,r24
	sts counter.1405,__zero_reg__
	sts (counter.1405)+1,__zero_reg__
	sts (counter.1405)+2,__zero_reg__
	sts (counter.1405)+3,__zero_reg__
	lds r30,Action_Timer
	lds r31,(Action_Timer)+1
	icall
.L31:
/* epilogue start */
	pop r28
	pop r29
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti
	.size	__vector_11, .-__vector_11
.global	__vector_10
	.type	__vector_10, @function
__vector_10:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
	push r19
	push r20
	push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	push r30
	push r31
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
	lds r24,Action_Timer+2
	lds r25,(Action_Timer+2)+1
	sbiw r24,0
	breq .L34
	lds r30,Action_Timer+2
	lds r31,(Action_Timer+2)+1
	icall
.L34:
/* epilogue start */
	pop r28
	pop r29
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti
	.size	__vector_10, .-__vector_10
.global __do_copy_data
.global __do_clear_bss
