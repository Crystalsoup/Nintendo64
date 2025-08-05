#constants
CONT_A = 0x8000
CONT_B = 0x4000
CONT_Z = 0x2000
CONT_START = 0x1000
CONT_UP = 0x0800
CONT_DOWN = 0x0400
CONT_LEFT = 0x0200
CONT_RIGHT = 0x0100

#initiation
input_handler;
    lui t0 0x8000
    addiu t0, t0, 0x5000 
    lh t1, 0x0000(t0) 
    
    #check a 
    li      t2, CONT_A
    and     t3, t1, t2
    bnez    t3, a_pressed
    nop

    #check b
    li      t2, CONT_B
    and     t3, t1, t2
    bnez    t3, b_pressed
    nop

    #check z
    li      t2, CONT_Z
    and     t3, t1, t2
    bnez    t3, z_pressed
    nop

    #check start
    li      t2, CONT_START
    and     t3, t1, t2
    bnez    t3, start_pressed
    nop

    #check up
    li      t2, CONT_UP
    and     t3, t1, t2
    bnez    t3, up_pressed
    nop

jr  ra

nop

#handlers
    a_pressed:
    #a input
    j       input_handler_end
    nop

    b_pressed:
    #b input
    j       input_handler_end
    nop

    z_pressed:
    #z trigger
    j       input_handler_end
    nop

    start_pressed:
    #pause
    j       input_handler_end
    nop

    up_pressed:
    #analog up input
    j       input_handler_end
    nop

#end
input_handler_end:
    jr      ra
    nop
