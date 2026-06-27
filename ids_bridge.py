import ctypes
import os
import sys

class PacketIdsBridge:
    def __init__(self):
        if not os.path.exists("./libids.so") and not os.path.exists("./libids.dll"):
            print("[*] Compiling backend native pattern matching engine pipelines...")
            if sys.platform.startswith("win"):
                os.system("gcc -shared -o libids.dll packet_pipeline.c ids_engine.c")
                lib_path = "./libids.dll"
            else:
                os.system("gcc -shared -fPIC -o libids.so packet_pipeline.c ids_engine.c")
                lib_path = "./libids.so"
        else:
            lib_path = "./libids.dll" if sys.platform.startswith("win") else "./libids.so"

        self.lib = ctypes.CDLL(lib_path)

        # Mapping bindings parameters configuration
        self.lib.init_ids_buffer.restype = ctypes.c_void_p
        self.lib.enqueue_packet.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.enqueue_packet.restype = ctypes.c_bool
        
        self.lib.inspect_next_packet.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.inspect_next_packet.restype = ctypes.c_bool
        
        self.lib.destroy_ids.argtypes = [ctypes.c_void_p]

        self.ids_ptr = self.lib.init_ids_buffer()

    def receive_packet(self, raw_payload: str) -> bool:
        return self.lib.enqueue_packet(self.ids_ptr, raw_payload.encode('utf-8'))

    def pop_and_analyze(self, threat_signature: str) -> bool:
        return self.lib.inspect_next_packet(self.ids_ptr, threat_signature.encode('utf-8'))

    def __del__(self):
        if hasattr(self, 'lib') and self.ids_ptr:
            self.lib.destroy_ids(self.ids_ptr)
            print("[+] Packet queue sequence streams torn down cleanly.")
