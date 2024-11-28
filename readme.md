# Project

## Question 2



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

