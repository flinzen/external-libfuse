/*
 * VUI - Voice User Interface for TFP  
 * 
 * Author: Anton Prozorov <prozanton@gmail.com>
 * 
 * Copyright 2013-2014 KRUST, Ltd.
 */

#ifndef LKF_H
#define LKF_H

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

	#define LKF_BLOCK_SIZE 512

	void decode_lkf_block(uint32_t *v, int num_blocks);

	void btea(uint32_t *v, int16_t n);

#ifdef  __cplusplus
}
#endif

#endif //LKF_H
