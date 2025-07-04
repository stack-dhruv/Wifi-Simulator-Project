# Project
Your provided Makefile is well-structured and adheres to the goal of generating two versions of the binary: one for debugging and another for optimized execution. Here's how it works step by step:

---

### **Steps to Use the Makefile**

1. **Run the Setup Script**
   - The `setup` rule ensures that the `setup.sh` script is executed before building the binaries. The script is made executable and then executed.

2. **Build Debug and Optimized Binaries**
   - **Debug Version (`wifi_simulator_debug`)**: Compiles the sources with debugging flags (`-g`, `-DDEBUG`) to facilitate debugging.
   - **Optimized Version (`wifi_simulator_opt`)**: Compiles the sources with optimization flags (`-O3`) for performance.
   - Both binaries are placed in the `bin/` directory.

3. **Generate a Shared Library**
   - Creates a shared library `libwifi_simulator.so` in the `lib/` directory, using the compiled object files.

4. **Clean Build Files**
   - Removes all compiled object files, binaries, and libraries to ensure a clean rebuild.

5. **Dynamic Targets**
   - The `print-%` rule allows for debugging Makefile variables by printing their values.

6. **Directories**
   - Ensures that the `build/`, `bin/`, and `lib/` directories exist before the build starts.

---

### **Running Commands**

#### 1. **Build All (Default Target)**

```bash
make
```

This builds both the debug and optimized binaries, as well as the shared library.

---

#### 2. **Build Only Debug Version**

```bash
make $(BINDIR)/wifi_simulator_debug
```

This command builds only the debug binary and the shared library.

---

#### 3. **Build Only Optimized Version**

```bash
make $(BINDIR)/wifi_simulator_opt
```

This command builds only the optimized binary and the shared library.

---

#### 4. **Clean Build Files**

```bash
make clean
```

This removes all object files, binaries, and the shared library.

---

#### 5. **Print Variable Values**

For debugging Makefile variables, use:

```bash
make print-VARIABLE_NAME
```

For example, to print the `SOURCES` variable:

```bash
make print-SOURCES
```

---

### **Key Highlights**

- **Portability**: Using `@mkdir -p` ensures that directory creation works across environments without error if the directories already exist.

- **Shared Library**: Generates a `.so` file, making the project reusable as a dynamic library.

- **Dynamic Dependency Resolution**: The object files are created dynamically for every source file in the `src/` directory.

## Question 3

WiFi 6 Communication WiFi 6 allowed a yet new type of communication, using OFDMA. In this case, a second type of parallel transmission was allowed, where the 20 MHz channel could be further subdivided into units of 2 MHz, 4 MHz or 10 MHz, and each of these sub-channels could be utilized in parallel for a total of 5ms. After 5ms, the channel allocation is done once again. Again, find out the throughput, average and maximum latency in each of the above cases, using a process of round-robin scheduling of the users.

## Question 2

WiFi 5 Communication WiFi 5 allowed a new type of communication, using multi-user MIMO. In this case, parallel transmission was allowed. However, parallel communication could be done only after (i) a single broadcast packet was sent by the access point, and (ii) each user would sequentially send their channel state information, which would be a single packet of 200 bytes. Once this was done, each user could communicate in parallel for a total of 15 ms. After 15 ms, the above process is repeated. Find out the throughput, average and maximum latency in each of the above cases once again, assuming round-robin scheduling of the users.

## Question 1

**(Q)** WiFi 4 Communication WiFi communication happens via a single access point and a set of users. A single transmission consists of sniffing of the channel, and transmission of the data packet if the channel is free. If the channel is not free, the transmission is deferred by a random unit of time (subject to a maximum limit of backoff time), followed by repetition of the above process. Simulate this above process of transmission to find out the throughput, average and maximum latency if a total of (i) 1 user and 1 AP is communicating, (ii) 10 users and 1 AP is communicating, and (iii) 100 users and 1 AP are communicating. You may assume that a total of 20 MHz being used as bandwidth, modulation of 256-QAM and coding rate of 5/6 is used for transmission and that each packet has size of 1 KB. You may ignore the other periods of time wastage such as DIFS, CIFS and guard intervals.

Let's start fresh, start coding the structure for the below things. Design of class structure, modeling of access point, user, packet, frequency channel is a must.

1. Data Rate (R):
    - The data rate in WiFi is determined using the formula: $R=Bandwidth×log_2(M)×Coding Rate$
    - $R = (20 * 10^6) * 8 * (5/6) = 133.33 \text{Mbps}$

2. Packet Transmission Time (T):
    - $T = Data Rate (R) / Packet Size (in bits)$
    - $T = (8192)/(133.33 * 10^6) \approx 61.44 \text{ }\mu s$

3. Throughput (S):
    - Throughput is defined as the total data successfully transmitted divided by the total simulation time: $S = \text{Total data transmitted (in bits)}/\text{Simulation Time}$
    - For 𝑛 users, collisions and backoff delays affect throughput. The more users, the higher the likelihood of collisions, which reduces throughput.

4. Average Latency:
    - Average latency is the mean time a packet takes from its first transmission attempt to its successful transmission. It includes:
        - Backoff delays due to collisions.
        - Actual transmission time.

5. Maximum Latency:
    - Maximum latency is the longest delay experienced by any packet, which depends on:
        - Maximum backoff time.
        - Number of retries before successful transmission.

## References

- `.gitignore` file gist taken from: <https://gist.github.com/Yousha/3830712334ac30a90eb6041b932b68d7>
- <https://www.perplexity.ai/>: LLM used for research about the terms and wireless networks
- Bandwidth vs Throughput vs Latency, What is the Difference in Computer Networking?-QSFPTEK. (n.d.). <https://www.qsfptek.com/qt-news/bandwidth-vs-throughput-vs-latency-what-is-the-difference-in-computer-networking.html>
- Latency vs Throughput vs Bandwidth: Unraveling the Complexities of Network Speed. (2024, October 31). Kentik. <https://www.kentik.com/kentipedia/latency-vs-throughput-vs-bandwidth/>
- Darah, D. (2022, August 25). Network bandwidth vs. throughput: What’s the difference? Search Networking. <https://www.techtarget.com/searchnetworking/feature/Network-bandwidth-vs-throughput-Whats-the-difference>
- GeeksforGeeks. (2023, June 2). Performance of a network. GeeksforGeeks. <https://www.geeksforgeeks.org/performance-of-a-network/>
- Magnat. (2024, July 11). Bandwidth, speed, latency and throughput. V500 Systems. <https://www.v500.com/bandwidth/>
- Contributor, S. (2022, February 17). Network Latency vs. Throughput vs. Bandwidth Guide - DNSstuff. Software Reviews, Opinions, and Tips - DNSstuff. <https://www.dnsstuff.com/latency-throughput-bandwidth>
- Writer, T. P. S. C. (2020, March 19). What are bandwidth, latency and throughput, and what is right for your business? Ecessa, a Product of OneNet Global. <https://www.ecessa.com/blog/what-are-bandwidth-latency-and-throughput-and-what-is-right-for-your-business/>

## ASCII Art

Ignore this, I did this for fun...

```sh
############################################################################
# $$\      $$\ $$$$$$$$\  $$$$$$\  $$\   $$\  $$$$$$\   $$$$$$\   $$$$$$\  #
# $$$\    $$$ |\__$$  __|$$  __$$\ $$ |  $$ |$$$ __$$\ $$ ___$$\ $$  __$$\ #
# $$$$\  $$$$ |   $$ |   \__/  $$ |$$ |  $$ |$$$$\ $$ |\_/   $$ |\__/  $$ |#
# $$\$$\$$ $$ |   $$ |    $$$$$$  |$$$$$$$$ |$$\$$\$$ |  $$$$$ /  $$$$$$  |#
# $$ \$$$  $$ |   $$ |   $$  ____/ \_____$$ |$$ \$$$$ |  \___$$\ $$  ____/ #
# $$ |\$  /$$ |   $$ |   $$ |            $$ |$$ |\$$$ |$$\   $$ |$$ |      #
# $$ | \_/ $$ |   $$ |   $$$$$$$$\       $$ |\$$$$$$  /\$$$$$$  |$$$$$$$$\ #
# \__|     \__|   \__|   \________|      \__| \______/  \______/ \________|#
############################################################################
```

## Grading criteria

Grading criteria:

- Design of class structure, modeling of access point, user, packet, frequency channel is a must.
- Proper functioning of each class
- Use of appropriate data structure
- Modeling of CSMA/CA
- Computation of throughput, average and maximum latency in each case
- Additional cases of code cleanliness, such as use of Makefile (both for building library and test program), git commits and proper function/variable names.
- Extra functionality based on the student’s understanding.
- The C++ program sources. Templates and exception handling must be utilized.
- Makefile to compile the sources and generate the running binary for the shell. The Makefile should generate two versions of the binary – one for debugging and another for optimized execution.

