const wasmModule = new WebAssembly.Module(wasmBytes);
const wasmInstance = new WebAssembly.Instance(wasmModule);
const addFunction = wasmInstance.exports.add;

const result = addFunction(2, 3);
console.log(result);