# PacketSift-IDS // Signature-Based Packet Inspector

A performance-focused network stream intrusion detection inspection utility utilizing low-latency circular memory buffers and linear string comparison algorithms to identify network attacks.

## Performance Mechanics
- **Circular Queue Ring Buffers ($O(1)$ Enqueue/Dequeue):** Manages inbound payload tracking strings within fixed spatial constraints in native C to prevent runtime overhead limits during data bursts.
- **Knuth-Morris-Pratt Search ($O(n + m)$):** Completely skips basic nested loop pattern parsing strategies by engineering custom tracking shift arrays (LPS) to process payloads in deterministic processing times.

## Directory Layout
- `packet_pipeline.c`: KMP matching components and LPS state preprocessors.
- `ids_engine.c`: Structural ring buffer data queue implementations.
- `packet_pipeline.h`: Parameter definitions and fixed framework layouts.
- `ids_bridge.py`: Dynamic variable array translation adapters.
- `live_sniffer.py`: Production integration execution runtime entry point.

## Running the Engine
Execute the live capture stream verification app via:
```bash
python live_sniffer.py
