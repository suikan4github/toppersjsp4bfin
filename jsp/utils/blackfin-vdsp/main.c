#include <stdio.h>
#include <jsp_kernel.h>
#include <task.h>
struct task_control_block tcb;
int offset;
int main(void)
{
    FILE * f;
    unsigned int * a;
    f = fopen ( "..\\offset.h", "w");
    
    fprintf( f, "// Generated by makeoffset.dxe\n" );
    
    offset = (unsigned int)&tcb.tskctxb.sp - (unsigned int)&tcb;
    fprintf( f, "#define TCB_sp %d\n", offset );

    offset = (unsigned int)&tcb.tskctxb.pc - (unsigned int)&tcb;
    fprintf( f, "#define TCB_pc %d\n", offset );

    offset = (unsigned int)&tcb.texptn - (unsigned int)&tcb;
    fprintf( f, "#define TCB_texptn %d\n", offset );
    
    offset = (unsigned int)&tcb.tinib - (unsigned int)&tcb + sizeof( tcb.tinib );
    a = (void *) &tcb.tinib + sizeof( tcb.tinib );
        
    *a = 0;
    tcb.enatex = 1;

    while ( *a > 0xFF ){
        *a >>= 8;
        offset ++;
    }

    fprintf( f, "#define TCB_enatex %d\n", offset );
    fprintf ( f, "#define TCB_enatex_mask 0x%x\n", *a );
    
    fclose( f );
}
