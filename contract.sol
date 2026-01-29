// 2022-2024 (c) Copyright Contributors to the GOSH DAO. All rights reserved.
//
pragma gosh-solidity >=0.76.1;
pragma AbiHeader expire;
pragma AbiHeader pubkey;

contract Tester {
    uint public counter = 0;

    bool public res = false;

    bytes public tt;
  
    constructor() {
        gosh.cnvrtshellq(1000000 vmshell);
        tvm.accept();
    }

    function test_halo2(bytes pub_inputs, bytes proof) public {
        tvm.accept();
        res = gosh.zkhalo2verify(pub_inputs, proof);
        tt = pub_inputs;
    }
}