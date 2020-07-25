#include "common.h"

#include "hw_accelerator.h"
#include "mp_arith.h"
#include "montgomeryOpt.h"

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
				R2_1024[32];
				//One[32] ;

int main()
{
	xil_printf("Start");
    init_platform();
    xil_printf("P done");
    //init_performance_counters(1);
    init_HW_access();

	uint32_t c[32];
	uint32_t src[32];
	uint32_t srcW[32];
	uint32_t cq[16];
	uint32_t cp[16];
	uint8_t  i;
	START_TIMING
	exponentation(M, R_1024, R2_1024, e,e_len, N,N_prime,c, 32);
	STOP_TIMING
	START_TIMING
	for(i=0; i<16;i++)
	{
		src[i]    = q[i];
		src[i+16] = 0;
	}
	CMD_READ_MOD_HW_accelerator(src);
	for(i=0; i<16;i++)
	{
		src[i]    = R2q[i];
		src[16+i] = c[16+i];
	}
	CMD_READ_RSQ_HW_accelerator(src);
	CMD_COMPUTE_MONT_HW_accelerator();
	for(uint32_t i=0; i<32; i++){
		srcW[i] = 0;
	}
	CMD_WRITE_HW_accelerator(srcW);
	for(uint32_t i=0; i<32; i++){
			src[i] = 0;
	}
	mp_add(srcW, c, src, 16);
	for(uint32_t i=0; i<16; i++){
				src[16 + i] =  Rq[i];
	}
	//CMD_READ_MOD_HW_accelerator(src);
	CMD_READ_RSQ_HW_accelerator(src);
	CMD_COMPUTE_MONT_HW_accelerator();
	for(uint32_t i=0; i<32; i++){
				src[i] = 0;
	}
	CMD_WRITE_HW_accelerator(src);
	for(uint32_t i=0; i<16; i++)
	{
		cq[i]    = src[i];
	}


	//Reduction P



	for(i=0; i<16;i++)
	{
		src[i]    = p[i];
		src[i+16] = 0;
	}
	CMD_READ_MOD_HW_accelerator(src);
	for(i=0; i<16;i++)
	{
		src[i]    = R2p[i];
		src[16+i] = c[16+i];
	}
	CMD_READ_RSQ_HW_accelerator(src);

	CMD_COMPUTE_MONT_HW_accelerator();
	xil_printf("END");
	for(uint32_t i=0; i<32; i++){
		srcW[i] = 0;
	}
	CMD_WRITE_HW_accelerator(srcW);
	for(uint32_t i=0; i<32; i++){
			src[i] = 0;
	}
	mp_add(srcW, c, src, 16);
	for(uint32_t i=0; i<16; i++){
				src[16 + i] =  Rp[i];
	}
	CMD_READ_RSQ_HW_accelerator(src);
	CMD_COMPUTE_MONT_HW_accelerator();
	for(uint32_t i=0; i<32; i++){
				src[i] = 0;
	}
	CMD_WRITE_HW_accelerator(src);
	for(uint32_t i=0; i<16; i++)
	{
		cp[i]    = src[i];
	}

	// exponentation P

	for(i=0; i<16;i++)
	{
		src[i]    = p[i];
		src[i+16] = 0;
	}
	CMD_READ_MOD_HW_accelerator(src);
	for(i=0; i<16;i++)
	{
		src[i]    = R2p[i];
		src[i+16] = cp[i];
	}
	CMD_READ_RSQ_HW_accelerator(src);
	for(i=0; i<16;i++)
	{
		src[i]    = d_p[i];
		src[i+16] = Rp[i];
	}
	CMD_READ_EXP_HW_accelerator(src);
	CMD_COMPUTE_EXP_HW_accelerator();
	for(uint32_t i=0; i<32; i++){
		src[i] = 0;
	}
	CMD_WRITE_HW_accelerator(src);

	 // exponentation Q

	for(i=0; i<16;i++)
	{
		srcW[i]    = q[i];
		srcW[i+16] = 0;
	}
	CMD_READ_MOD_HW_accelerator(srcW);
	for(i=0; i<16;i++)
	{
		srcW[i]    = R2q[i];
		srcW[i+16] = cq[i];
	}
	CMD_READ_RSQ_HW_accelerator(srcW);
	for(i=0; i<16;i++)
	{
		srcW[i]    = d_q[i];
		srcW[i+16] = Rq[i];
	}
	CMD_READ_EXP_HW_accelerator(srcW);
	CMD_COMPUTE_EXP_HW_accelerator();
	for(uint32_t i=0; i<32; i++){
		srcW[i] = 0;
	}
	CMD_WRITE_HW_accelerator(srcW);
	uint32_t T_p[32];
	uint32_t T_q[32];
	uint32_t Ttemp[32];
	uint32_t T[32];
	uint32_t plaintext[32];

	uint32_t src2[32] = {0x7f28d041, 0xef1a5c9b, 0x960f593b, 0x0704632e, 0xae04966d, 0xbc7b0191, 0x1845ce62, 0x4bc94140, 0x59296477, 0xd74d151d, 0xb5f3e40f, 0xde22f56d, 0xd7147dc8, 0xe254ca4d, 0x1fa73428, 0x3d55fd1f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
	montMulOpt(src2,x_p,N,N_prime,T_p,32);
	montMulOpt(srcW,x_q,N,N_prime,T_q,32);


	mp_add(T_p, T_q, Ttemp, 32);
	condSubtractOpt(N, T, Ttemp, 32);

	montMulOpt(T,R2_1024,N,N_prime,plaintext,32);
	STOP_TIMING

	customprint3(plaintext, "h",32);
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

