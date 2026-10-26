# Assignment 2: Manual AES and Key Distribution

This individual coursework project implements the approved C++17 command-line design: a KDC, Alice, and Bob at three distinct IP addresses. Alice obtains a session key through the five-step scenario supplied with the assignment. Alice and Bob then communicate directly in both directions.

## Approved design

- One executable provides `kdc`, `alice`, and `bob` roles.
- AES-128 encryption, decryption, key expansion, CBC, padding, and the KDC protocol are implemented manually.
- Long-term keys are entered locally, never hardcoded or sent over the network. Key changes require a fresh session.
- Keys and user messages use ASCII. Ciphertext uses hexadecimal in terminal output and network payloads.
- The intended demonstration uses two physical devices and a bridged VM, each with its own LAN IP.
- Documentation, design decisions, verification results, and demonstration instructions belong only in this README. Other files are implementation, build support, and tests.

Implementation and verification are in progress.
