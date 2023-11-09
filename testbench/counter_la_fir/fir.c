#include "fir.h"

void __attribute__ ( ( section ( ".mprjram" ) ) ) initfir() {
	//initial your fir
	tap0 = 0;
	tap1 = -10;
	tap2 = -9;
	tap3 = 23;
	tap4 = 56;
	tap5 = 63;
	tap6 = 56;
	tap7 = 23;
	tap8 = -9;
	tap9 = -10;
	tap10 = 0;

	datalength = 64;

	reg_mprj_datal = 0x00A50000;
	ap_config = 0x00000001;
}

int* __attribute__ ( ( section ( ".mprjram" ) ) ) fir(int method){
	initfir();
	//write down your fir
	reg_mprj_datal = (0xA5 << 16);
	
	int ap;
	
	ap = ap_config;
	for (int i=0; i<64; i++) {
		while ((ap >> 4) & 1 != 1) {} // 0x00-[4] Xn is ready to accept input
		ap = ap_config;
		Xn = i;
		while ((ap >> 5) & 1 != 1) {} // 0x00-[5] Yn is ready to read
		ap = ap_config;
		outputsignal[i] = Yn;
	}
        
	ap = ap_config;
	reg_mprj_datal = ((outputsignal[63] & 0xFF) << 24) | (0x5A << 16);

	return outputsignal;
}
		
