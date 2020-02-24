#include "common.h"

#include "hw_accelerator.h"
#include "mp_arith.h"

// These variables are defined in the testvector.c
// that is created by the testvector generator python script
extern uint32_t M[32],
				p[16],
				q[16],
				N[32],
				N_prime[32],
				e[32],
				e_len,
				d_p[16],
				d_q[16],
				d_p_len,
				d_q_len,
				x_p[32],
				x_q[32],
				Rp[16],
				Rq[16],
				R2p[16],
				R2q[16],
				R_1024[32],
				R2_1024[32],
                p_src[32],
				q_src[32],
				p_exp_scr[32],
				q_exp_scr[32];
				//One[32] ;

void customprint(uint32_t *in, char *str, uint32_t size);

int main()
{
    init_platform();
    init_performance_counters(1);
    init_HW_access();


//    example_HW_accelerator();
//
    uint32_t src[32];
    uint32_t modulus[32] = {0x22657e83, 0xf1e3a8f4, 0xad407fdc, 0xa89fb32d, 0x0424a00c, 0xc238f070, 0x4e49a42a, 0xfd7babf7, 0xae77882a, 0x4d869657, 0xedf1795c, 0x982df051, 0x379c9f93, 0x014faf07, 0xfd6eb140, 0x8dc4379c,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
    uint32_t a[32] =  {0xc33a1372, 0x9704268d, 0xa209116b, 0x1b2479d5, 0x933a4d1e, 0x1e4a56c1, 0x012ac09f, 0x98d8b668, 0x6055d814, 0xa6a7e1fe, 0x28b8d34b, 0x7c330d8c, 0x08ebc866, 0xc65743ee, 0x7d37bf2a, 0xda8f5c92,0xedbbe33c, 0xb78a1752, 0xacbb31d3, 0x3106f880, 0x4eba864e, 0x3f771c3f, 0x05e43d3b, 0xb871a75f, 0x6396f35d, 0x7eb9a0ca, 0x2405c20c, 0x345d17b6, 0xdaf47fed, 0x2208ae0e, 0xc2d12d12, 0xdebcfd28};
	CMD_READ_MOD_HW_accelerator(modulus);
	CMD_READ_RSQ_HW_accelerator(a);
	CMD_COMPUTE_MONT_HW_accelerator();
	for(uint32_t i=0; i<32; i++){
			src[i] = 0;
	}
	CMD_WRITE_HW_accelerator(src);
	customprint3(src,"a",32);
	cleanup_platform();

    return 0;
}







void customprint3(uint32_t *in, char *str, uint32_t size)        {
    int32_t i;

    xil_printf("0x");
    for (i = size-1; i >= 0 ; i--) {
        xil_printf("%9x", in[i]);
    }
    xil_printf("\n\r");
}

