// 2022-2024 (c) Copyright Contributors to the GOSH DAO. All rights reserved.
//
pragma gosh-solidity >=0.76.1;
pragma AbiHeader expire;
pragma AbiHeader pubkey;

contract Tester {
    uint public counter = 0;

    bool public res = false;
  
    constructor(uint arg1, uint arg2, uint arg3, bytes arg4) {
        gosh.cnvrtshellq(1000000 vmshell);
        tvm.accept();
        res = gosh.zkhalo2verify(arg1, arg2, arg3, arg4);
    }
}