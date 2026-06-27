from ids_bridge import PacketIdsBridge

def main():
    print("=== PACKETSIFT-IDS: STREAMING INTELLIGENT MATCH PIPELINE ===")
    ids = PacketIdsBridge()

    # Define threat database signatures to intercept
    # Exploits matching malicious script injection strings
    signature_db = "<script>alert(1)</script>"

    # Mock ingest payload telemetry stream packets
    network_stream = [
        "GET /index.html HTTP/1.1\r\nHost: local\r\n\r\n",
        "POST /submit HTTP/1.1\r\nContent-Length: 32\r\n\r\n<script>alert(1)</script>",
        "GET /assets/style.css HTTP/1.1\r\n\r\n"
    ]

    print("\n[*] Pushing live network packet payloads into the circular C ring-buffer queue...")
    for idx, packet in enumerate(network_stream):
        success = ids.receive_packet(packet)
        if success:
            print(f" -> Enqueued Packet [{idx}] Frame Stream Successfully.")
        else:
            print(f" [!] Alert: Packet Frame [{idx}] dropped. Queue saturation overflow reached.")

    print("\n[*] Processing inspection loops via Knuth-Morris-Pratt algorithmic lookups...")
    for idx in range(len(network_stream)):
        # Inspect packets sequentially out of the queue array spaces
        is_threat = ids.pop_and_analyze(signature_db)
        if is_threat:
            print(f"\n[!!!] ALERT SECURITY THREAT MATCH DETECTED IN FRAME [{idx}]")
            print(f" -> Exploitation Payload Signature Identified: '{signature_db}'")
            print(" -> Triggering active state mitigation drop-rules rules configuration.")
        else:
            print(f"[+] Frame [{idx}] analyzed. Payload is verified secure.")

if __name__ == "__main__":
    main()
