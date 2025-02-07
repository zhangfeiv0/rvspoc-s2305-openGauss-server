/*
 * Copyright (c) 2020 Huawei Technologies Co.,Ltd.
 *
 * openGauss is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 * -------------------------------------------------------------------------
 *
 * security_gs_ktool.h
 *      gs_ktool is an independent key management tool provided by GaussDB Kernel, can generate and store symmetric
 *      key with [16, 112] bytes.
 *      when CREATE CMKO, if KEY_STROE = gs_ktool, then:
 *          1. KEY_PATH: gs_ktool use $key_id to identify keys, KEY_PATH = "gs_ktool/$key_id"
 *          2. ALGORITHM: gs_ktool cannot generate asymmetric key pairs, so keys generated by gs_ktool are only
 *          available for AES_256 algorithm
 *      if you register gs_ktool, you should be sure your system has installed gs_ktool, and the environment variables
 *      and the configuration files are available.
 *
 * IDENTIFICATION
 *	  src/gausskernel/security/keymgr/include/ktool/security_gs_ktool.h
 *
 * -------------------------------------------------------------------------
 */


#ifndef __KM_GS_KTOOL_H_
#define __KM_GS_KTOOL_H_

#include "keymgr/security_key_mgr.h"

const int MAX_CMK_CACHE_NODE_CNT = 100;
const int DEFAULT_CMK_CACHE_LEN = 32;

typedef struct CmkCacheNode {
    unsigned int cmk_id;
    unsigned char cmk_plain[DEFAULT_CMK_CACHE_LEN];
    struct CmkCacheNode *next;
} CmkCacheNode;

typedef struct CmkCacheList {
    unsigned int cmk_node_cnt;
    CmkCacheNode *first_cmk_node;
} CmkCacheList;

typedef struct {
    KeyMgr kmgr;

    CmkCacheList *cache;
} GsKtoolMgr;

extern KeyMethod gs_ktool;

#endif
